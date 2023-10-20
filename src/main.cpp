#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <rerun.hpp>

// Adapters so we can log eigen vectors as rerun positions:
template <>
struct rerun::ComponentBatchAdapter<rerun::components::Position3D, std::vector<Eigen::Vector3f>> {
    // Sanity check that this is binary compatible.
    static_assert(sizeof(components::Position3D) == sizeof(Eigen::Vector3f));
    static_assert(alignof(components::Position3D) <= alignof(Eigen::Vector3f));

    ComponentBatch<components::Position3D> operator()(const std::vector<Eigen::Vector3f>& container
    ) {
        return ComponentBatch<components::Position3D>::borrow(
            reinterpret_cast<const components::Position3D*>(container.data()),
            container.size()
        );
    }

    ComponentBatch<components::Position3D> operator()(std::vector<Eigen::Vector3f>&& container) {
        throw std::runtime_error("Not implemented for temporaries");
    }
};

// Adapters so we can log an eigen matrix as rerun positions:
template <>
struct rerun::ComponentBatchAdapter<rerun::components::Position3D, Eigen::MatrixX3f> {
    // Sanity check that this is binary compatible.
    static_assert(
        sizeof(components::Position3D) ==
        sizeof(Eigen::MatrixX3f::Scalar) * Eigen::MatrixX3f::ColsAtCompileTime
    );
    static_assert(alignof(components::Position3D) <= alignof(Eigen::MatrixX3f));

    ComponentBatch<components::Position3D> operator()(const Eigen::MatrixX3f& matrix) {
        return ComponentBatch<components::Position3D>::borrow(
            reinterpret_cast<const components::Position3D*>(matrix.data()),
            matrix.rows()
        );
    }

    ComponentBatch<components::Position3D> operator()(std::vector<Eigen::MatrixX3f>&& container) {
        throw std::runtime_error("Not implemented for temporaries");
    }
};

std::vector<Eigen::Vector3f> generate_random_points_vector(int num_points) {
    std::vector<Eigen::Vector3f> points(num_points);
    for (auto& point : points) {
        point.setRandom();
    }
    return points;
}

int main() {
    auto rec = rerun::RecordingStream("rerun_example_cpp");
    rec.connect().throw_on_failure();

    const int num_points = 1000;

    // Points represented by std::vector<Eigen::Vector3f>
    const auto points3d_vector = generate_random_points_vector(1000);
    rec.log("world/points_from_vector", rerun::Points3D(points3d_vector));

    // Points represented by Eigen::MatX3f (Nx3 matrix)
    const Eigen::MatrixX3f points3d_matrix = Eigen::MatrixX3f::Random(num_points, 3);
    rec.log("world/points_from_matrix", rerun::Points3D(points3d_matrix));

    // Posed pinhole camera
    float width = 640.0f;
    float height = 480.0f;
    Eigen::Matrix3f projection_matrix = Eigen::Matrix3f::Identity();
    projection_matrix(0, 0) = 500.0f;
    projection_matrix(1, 1) = 500.0f;
    projection_matrix(0, 2) = (width - 1) / 2.0;
    projection_matrix(1, 2) = (height - 1) / 2.0;
    rec.log(
        "world/camera",
        rerun::Pinhole(rerun::components::PinholeProjection(
                           *reinterpret_cast<float(*)[9]>(projection_matrix.data())
                       ))
            .with_resolution(rerun::components::Resolution({width, height}))
    );
    const Eigen::Vector3f camera_position{0.0, -1.0, 0.0};
    Eigen::Matrix3f camera_orientation;
    // clang-format off
    camera_orientation <<
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 0.0, 0.0;
    // clang-format on
    rec.log(
        "world/camera",
        rerun::Transform3D(
            rerun::datatypes::Vec3D(*reinterpret_cast<const float(*)[3]>(camera_position.data())),
            rerun::datatypes::Mat3x3(*reinterpret_cast<const float(*)[9]>(camera_orientation.data())
            )
        )
    );

    // Read image
    std::string image_path = "rerun-logo.png";
    cv::Mat img = imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    // Log image to Rerun
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB); // Rerun expects RGB format
    // NOTE currently we need to construct a vector to log an image, this will change in the future
    //  see https://github.com/rerun-io/rerun/issues/3794
    std::vector<uint8_t> img_vec(img.total() * img.channels());
    img_vec.assign(img.data, img.data + img.total() * img.channels());
    rec.log(
        "image",
        rerun::Image(
            {static_cast<size_t>(img.rows),
             static_cast<size_t>(img.cols),
             static_cast<size_t>(img.channels())},
            std::move(img_vec)
        )
    );

    return 0;
}

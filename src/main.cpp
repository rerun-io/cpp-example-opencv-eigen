#include <iostream>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <rerun.hpp>

#include "collection_adapters.hpp"

std::vector<Eigen::Vector3f> generate_random_points_vector(int num_points) {
    std::vector<Eigen::Vector3f> points(num_points);
    for (auto& point : points) {
        point.setRandom();
    }
    return points;
}

int main() {
    std::cout << "Rerun SDK Version: " << rerun::version_string() << std::endl;

    const auto rec = rerun::RecordingStream("rerun_example_cpp");
    rec.spawn().exit_on_failure();

    rec.log_static("world", rerun::ViewCoordinates::RIGHT_HAND_Z_UP); // Set an up-axis

    const int num_points = 1000;

    // Points represented by std::vector<Eigen::Vector3f>
    const auto points3d_vector = generate_random_points_vector(1000);
    rec.log("world/points_from_vector", rerun::Points3D(points3d_vector));

    // Points represented by Eigen::Mat3Xf (3xN matrix)
    const Eigen::Matrix3Xf points3d_matrix = Eigen::Matrix3Xf::Random(3, num_points);
    rec.log("world/points_from_matrix", rerun::Points3D(points3d_matrix));

    // Posed pinhole camera:
    rec.log(
        "world/camera",
        rerun::Pinhole::from_focal_length_and_resolution({500.0, 500.0}, {640.0, 480.0})
    );

    const Eigen::Vector3f camera_position{0.0, -1.0, 0.0};
    Eigen::Matrix3f camera_orientation;
    // clang-format off
    camera_orientation <<
        +1.0, +0.0, +0.0,
        +0.0, +0.0, +1.0,
        +0.0, -1.0, +0.0;
    // clang-format on
    rec.log(
        "world/camera",
        rerun::Transform3D(
            rerun::Vec3D(camera_position.data()),
            rerun::Mat3x3(camera_orientation.data())
        )
    );

    // Read image
    const auto image_path = "rerun-logo.png";
    cv::Mat img = imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    uint32_t width = img.cols;
    uint32_t height = img.rows;

    // Rerun expects RGB format
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    // Log image to rerun using the tensor buffer adapter defined in `collection_adapters.hpp`.
    rec.log("image0", rerun::Image::from_rgb24(img, {width, height}));

    // Or by passing a pointer to the image data.
    // The pointer cast here is redundant since `data` is already uint8_t in this case, but if you have e.g. a float image it may be necessary to cast to float*.
    rec.log(
        "image1",
        rerun::Image::from_rgb24(
            rerun::borrow(img.data, img.total() * img.elemSize()),
            {width, height}
        )
    );

    return 0;
}

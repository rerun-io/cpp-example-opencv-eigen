#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <rerun.hpp>

template <>
struct rerun::ComponentBatchAdapter<rerun::components::Position3D, std::vector<Eigen::Vector3f>> {
    // Sanity check that this is binary compatible.
    static_assert(sizeof(components::Position3D) == sizeof(Eigen::Vector3f));
    static_assert(alignof(components::Position3D) <= alignof(Eigen::Vector3f));

    ComponentBatch<components::Position3D> operator()(const std::vector<Eigen::Vector3f> &container
    ) {
        return ComponentBatch<components::Position3D>::borrow(
            reinterpret_cast<const components::Position3D *>(container.data()),
            container.size()
        );
    }

    ComponentBatch<components::Position3D> operator()(std::vector<Eigen::Vector3f> &&container) {
        throw std::runtime_error("Not implemented for temporaries");
    }
};

int main() {
    auto rec = rerun::RecordingStream("rerun_external_cpp_app");
    rec.connect("127.0.0.1:9876").throw_on_failure();

    // Points represented by std::vector<Eigen::Vector3f>
    std::vector<Eigen::Vector3f> points3d_eigen{{0.1f, 0.1f, 0.1f}};
    rec.log("random", rerun::Points3D(points3d_eigen));

    // Points represented by Nx3 Eigen::Mat...

    // Image
    std::string image_path = "rerun-logo.png";
    cv::Mat img = imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    cv::waitKey(0);

    return 0;
}

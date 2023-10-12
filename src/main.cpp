#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <rerun.hpp>

template <>
struct rerun::ComponentBatchAdapter<rerun::components::Position3D,
                                    std::vector<Eigen::Vector3f>> {
  // Sanity check that this is binary compatible.
  static_assert(sizeof(components::Position3D) == sizeof(Eigen::Vector3f));
  static_assert(alignof(components::Position3D) <= alignof(Eigen::Vector3f));

  ComponentBatch<components::Position3D>
  operator()(const std::vector<Eigen::Vector3f> &container) {
    return ComponentBatch<components::Position3D>::borrow(
        reinterpret_cast<const components::Position3D *>(container.data()),
        container.size());
  }

  ComponentBatch<components::Position3D>
  operator()(std::vector<Eigen::Vector3f> &&container) {
    throw std::runtime_error("Not implemented for temporaries");
  }
};

template <>
struct rerun::ComponentBatchAdapter<rerun::components::Position3D,
                                    Eigen::MatrixX3f> {
  // Sanity check that this is binary compatible.
  static_assert(sizeof(components::Position3D) ==
                sizeof(Eigen::MatrixX3f::Scalar) *
                    Eigen::MatrixX3f::ColsAtCompileTime);
  static_assert(alignof(components::Position3D) <= alignof(Eigen::MatrixX3f));

  ComponentBatch<components::Position3D>
  operator()(const Eigen::MatrixX3f &matrix) {
    return ComponentBatch<components::Position3D>::borrow(
        reinterpret_cast<const components::Position3D *>(matrix.data()),
        matrix.rows());
  }

  ComponentBatch<components::Position3D>
  operator()(std::vector<Eigen::MatrixX3f> &&container) {
    throw std::runtime_error("Not implemented for temporaries");
  }
};

std::vector<Eigen::Vector3f> generate_random_points_vector(int num_points) {
  std::vector<Eigen::Vector3f> points(num_points);
  for (auto &point : points) {
    point.setRandom();
  }
  return points;
}

int main() {
  auto rec = rerun::RecordingStream("rerun_cpp_example_opencv_eigen");
  rec.connect("127.0.0.1:9876").throw_on_failure();

  const int num_points = 1000;

  // Points represented by std::vector<Eigen::Vector3f>
  auto points3d_vector = generate_random_points_vector(1000);
  rec.log("points_from_vector", rerun::Points3D(points3d_vector));

  // Points represented by Eigen::MatX3f (Nx3 matrix)
  Eigen::MatrixX3f points3d_matrix = Eigen::MatrixX3f::Random(num_points, 3);
  rec.log("points_from_matrix", rerun::Points3D(points3d_matrix));

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

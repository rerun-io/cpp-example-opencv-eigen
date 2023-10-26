# C++ Example with OpenCV and Eigen

This is a minimal CMake project that shows how to use [Rerun](https://github.com/rerun-io/rerun) in your code in conjunction with [Eigen](https://eigen.tuxfamily.org/) and [OpenCV](https://opencv.org/).

<center>
  <picture>
    <img src="https://static.rerun.io/cpp-example-opencv-eigen/80ec7c698224eccb5ba1928136ba0a522d79b60a/full.png" alt="">
    <source media="(max-width: 480px)" srcset="https://static.rerun.io/cpp-example-opencv-eigen/80ec7c698224eccb5ba1928136ba0a522d79b60a/480w.png">
    <source media="(max-width: 768px)" srcset="https://static.rerun.io/cpp-example-opencv-eigen/80ec7c698224eccb5ba1928136ba0a522d79b60a/768w.png">
    <source media="(max-width: 1024px)" srcset="https://static.rerun.io/cpp-example-opencv-eigen/80ec7c698224eccb5ba1928136ba0a522d79b60a/1024w.png">
    <source media="(max-width: 1200px)" srcset="https://static.rerun.io/cpp-example-opencv-eigen/80ec7c698224eccb5ba1928136ba0a522d79b60a/1200w.png">
  </picture>
</center>

## Installing the Rerun viewer
The Rerun C++ SDK works by connecting to an awaiting Rerun Viewer over TCP.

#### Building from source
* [Install `cargo`](https://rustup.rs/)
* `cargo install rerun-cli`

#### Using `pip`
* `pip install rerun-sdk`

### Running the Rerun viewer
Just type `rerun` and the rerun viewer should show up. Then it is time to run this example!


## Run this example

### Using `pixi`
The easiest way to get started is to install [pixi](https://prefix.dev/docs/pixi/overview).

* Start the rerun viewer with `rerun` (see above)
* Run the example with `pixi run run`


### Manually
First install the required dependencies:
* `arrow-cpp` (required by Rerun)
* `eigen` and `opencv` (required by this example)
* `cmake` and `ninja` (build tools)

Build using:

```bash
mkdir build
cd build
cmake ..
cmake --build . -- -j8
```

Then run the binary with:

`build/rerun_ext_example`

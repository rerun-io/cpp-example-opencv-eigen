# C++ Example with OpenCV and Eigen

This is a minimal CMake project that shows how to use [Rerun](https://github.com/rerun-io/rerun) in your code in conjunction with [Eigen](https://eigen.tuxfamily.org/) and [OpenCV](https://opencv.org/).

## How to build and run

### Using `pixi`
The easiest way to get started is to install [pixi](https://prefix.dev/docs/pixi/overview) and then run: `pixi run run`.

### Manually

First install the required dependencies:
* `arrow-cpp`` (required by Rerun)
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

# C++ Example with OpenCV and Eigen

This is a minimal CMake project that shows how to use [Rerun](https://github.com/rerun-io/rerun) in your code in conjunction with [Eigen](https://eigen.tuxfamily.org/) and [OpenCV](https://opencv.org/).

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
* Run the example with `rerun run run`


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

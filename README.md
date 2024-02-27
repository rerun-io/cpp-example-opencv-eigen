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

## Using `pixi`
The easiest way to get started is to install [pixi](https://prefix.dev/docs/pixi/overview).

The pixi environment described in `pixi.toml` contains all of the dependencies, including the rerun viewer,
allowing you to run the example with a single command:
* `pixi run example`

## Without `pixi`
If you choose not to use pixi, you will need to install a few things yourself before you get started.

### Installing the Rerun Viewer
The Rerun C++ SDK works by connecting to an awaiting Rerun Viewer over TCP.

If you need to install the viewer, follow the [installation guide](https://www.rerun.io/docs/getting-started/installing-viewer). Two of the more common ways to install the Rerun are:
* Via cargo: `cargo install rerun-cli@0.14.0`
* Via pip: `pip install rerun-sdk==0.14.0`

After you have installed it, you should be able to type `rerun` in your terminal to start the viewer.

### Installing dependencies:
This project depends on a few libraries and toolchains. Installing these is outside the scope of this README,
but your OS should have these available though a common package manager:
* `eigen` and `opencv` (required by this example)
* `cmake` (for building)

### Build and run on Linux & Mac

Build:
```bash
cmake -B build
cmake --build build -j
```

Then run the binary with:
`build/rerun_ext_example`


### Build and run on Windows using Visual Studio 2022

Build
```cmd
cmake -B build  -G 'Visual Studio 17 2022'
cmake --build build
```
Instead of building via CMake you can also open `build/rerun_external_cpp_proj.sln` in Visual Studio and build & run from there.

Then run the binary with
```cmd
build\RelWithDebInfo\rerun_ext_example.exe
```
Make sure that all dependent dlls (OpenCV & Eigen) are in PATH or next to the executable.



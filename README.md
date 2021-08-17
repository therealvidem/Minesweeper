# Minesweeper

## Overview

A simple Minesweeper game coded in C using [RayLib](https://www.raylib.com/).

## TODO

- [x] Implement the backend of basic game functionality.
- [x] Implement the frontend (UI) of basic game functionality.
- [ ] Add some basic testing.
- [x] Implement the flood fill algorithm for opening empty cells.
- [x] Implement chording.
- [ ] Add info texts, such as number of mines and a timer.
- [ ] Add end screen.
- [ ] Implement menu functionality.
- [ ] Add multiple difficulties/sizes.
- [ ] Add custom sizes.
- [ ] Add (optional) animations.

## Project Structure

The `minesweeper/` folder contains the standalone library for the underlying Minesweeper game. This means any other project could utilize this library to make another interface. Using CMake, this is integrated into this game as a static library.

The `src/` folder contains the code for the actual game itself, utilizing the `minesweeper/` library. It uses RayLib to draw the game as well as handle user input. The `src/` folder is split into two other components: `src/graphics/` and `src/input/`, each handling their respective domain every frame in the game.

The `assets/` folder contains all assets for the game, including textures and sounds.

## Developing

This project uses [CMake](https://cmake.org/) to organize the building process (and, hopefully soon, testing process).

Fortunately, you do not have to have RayLib installed prior to using this project's CMake, as the CMakeLists.txt provided automatically installs RayLib if it is not found on your system.

Do note, however, that there are prerequisites for Linux, as outlined in [Linux Prerequisites](#linux-prerequisites).

Regardless, I personally develop on Windows and use [vcpkg](https://github.com/Microsoft/vcpkg) to install RayLib outside the project.

### Manually Installing RayLib on Windows

I personally use [vcpkg](https://github.com/Microsoft/vcpkg) to install the RayLib package. Note that when building your CMake build folder, you must set the `CMAKE_TOOLCHAIN_FILE` flag to `[your vcpkg location]/scripts/buildsystems/vcpkg.cmake`. This can be done by running the following command inside the build folder (`build/`):

```bash
cmake -DCMAKE_TOOLCHAIN_FILE="[your vcpkg location]/scripts/buildsystems/vcpkg.cmake" ..
```

If using VSCode, you can in use the following setting to make the CMake extension automatically use the flag:

```json
"cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE": "[your vcpkg location]/scripts/buildsystems/vcpkg.cmake"
}
```

### Manually Installing RayLib on Linux

Follow this guide on the [RayLib wiki](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).

### Linux Prerequisites

In order for RayLib to be installed, the libraries outlined [here](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#install-required-libraries) are necessary.

Note that OpenGL 3.3 is required for RayLib 3.5, which is the currently required version of this game. The game may not run properly otherwise, if at all.

### Building

Setup CMake first by making the build folder `build/` and running CMake inside of it:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

Note for Windows users using vcpkg: Add the flag `-DCMAKE_TOOLCHAIN_FILE="[your vcpkg location]/scripts/buildsystems/vcpkg.cmake"`.

Note that to build for release, use `-DCMAKE_BUILD_TYPE=Release` instead of `-DCMAKE_BUILD_TYPE=Debug`.

Finally, to build, run the following command:

```bash
cmake --build build/
```

The resulting binary or executable should be inside `build/`.

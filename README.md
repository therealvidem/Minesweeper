# Minesweeper

## Overview

A simple Minesweeper game coded in C using [RayLib](https://www.raylib.com/).

## Developing

First, install [RayLib](https://github.com/raysan5/raylib/wiki). You will need the `libraylib.a` static library and `raylib.h` header file. Detailed instructions for Windows can be found [here](https://github.com/raysan5/raylib/wiki/Working-on-Windows). If you are compiling RayLib from source, these are found in `raylib/src` after executing make.

Then, for this project, clone the repository:

```
git clone https://github.com/therealvidem/Minesweeper.git
cd Minesweeper/
```

Make two folders called `lib/` and `include/` inside the project root. Put `libraylib.a` inside `lib/` and `raylib.h` inside `include/`.

After that, you can compile using:

```
make
```

To debug, you can compile using:

```
make debug
```

The source code is in `src/` and the assets are in `assets/`.

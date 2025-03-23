# Text Editor

A simple text editor built using C++ and SDL2, with support for text rendering, cursor movement, and basic text editing features.

## Features

- Text rendering with line wrapping
- Cursor movement and rendering
- Basic text editing (insertion, deletion, and navigation)
- Adjustable text size using `Ctrl + Plus` and `Ctrl + Minus`
- Cross-platform support (Windows, Linux, macOS)

## Requirements

- C++20 compiler
- [SDL2](https://github.com/libsdl-org/SDL) and [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [CMake](https://cmake.org/) (minimum version 3.22)
- [vcpkg](https://github.com/microsoft/vcpkg) for dependency management

## Building the Project

Make sure to set the `VCPKG_ROOT` environment variable to the path of your vcpkg installation before building.

### Windows

This project uses Visual Studio 2022 as the generator on Windows.

1. Configure the project using CMake:

   ```sh
   cmake --preset windows-release
   ```

2. Build the project:
   ```sh
   cmake --build build --preset windows-release
   ```

### Linux

This project uses Ninja as the generator on Linux. Also note that using vcpkg to build SDL2 on Unix systems may take a significant amount of time.

1. Configure and build using CMake:
   ```sh
   cmake --preset linux-release
   cmake --build build --preset linux-release
   ```

### macOS

This project uses Ninja as the generator on macOS. Similar to Linux, building SDL2 dependencies with vcpkg on macOS may take longer than on Windows.

1. Configure and build using CMake:
   ```sh
   cmake --preset macos-release
   cmake --build build --preset macos-release
   ```

## Development Build

For development purposes, you can use the development presets:

- Windows: `windows-development`
- Linux: `linux-development`
- macOS: `macos-development`

Example:

```sh
cmake --preset linux-development
cmake --build build --preset linux-development
```

## CMake Presets

This project uses CMake presets for easy configuration and building. Windows presets use Visual Studio 2022 as the generator, while Linux and macOS presets use Ninja. The available presets are:

- `linux-release`: Linux release build
- `windows-release`: Windows release build
- `macos-release`: macOS release build
- `linux-development`: Linux debug build
- `windows-development`: Windows debug build
- `macos-development`: macOS debug build

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

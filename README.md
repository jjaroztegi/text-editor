# Text Editor

A simple text editor built using C++ and SDL3, featuring a clean interface and essential text editing capabilities.

## Features

### Implemented Features

-   Text rendering with automatic line wrapping
-   Cursor movement and rendering
-   Basic text editing operations:
    -   Insert and delete text
    -   Word-by-word navigation
    -   Line-by-line navigation
-   Adjustable text size (Ctrl + Plus/Minus)
-   Resizable window with automatic text wrapping

### Planned Features

-   File operations (save/load)
-   Search functionality (Ctrl + F)
-   Undo/Redo support (Ctrl + Z/Y)
-   Copy/Paste operations (Ctrl + C/V)
-   Text selection with Shift + Arrow keys
-   Line numbers display
-   Status bar with cursor position and file info
-   Settings menu for customization
-   Syntax highlighting
-   Search and replace functionality
-   Word wrap toggle
-   Drag and drop support
-   Dark/light mode toggle

## Keyboard Shortcuts

| Shortcut           | Action                |
| ------------------ | --------------------- |
| Ctrl + Q           | Quit editor           |
| Ctrl + S           | Save file             |
| Ctrl + O           | Open file             |
| Ctrl + F           | Start search          |
| Ctrl + Z           | Undo                  |
| Ctrl + Y           | Redo                  |
| Ctrl + C           | Copy selection        |
| Ctrl + V           | Paste                 |
| Ctrl + Plus        | Increase text size    |
| Ctrl + Minus       | Decrease text size    |
| Ctrl + Left/Right  | Move by word          |
| Shift + Arrow keys | Select text           |
| Escape             | Stop search/selection |

## Requirements

-   C++20 compiler
-   [SDL3](https://github.com/libsdl-org/SDL) and [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf)
-   [CMake](https://cmake.org/) (minimum version 3.22)
-   [vcpkg](https://github.com/microsoft/vcpkg) for dependency management

## Building the Project

Make sure to set the `VCPKG_ROOT` environment variable to the path of your vcpkg installation before building.

### Build Configuration

This project uses CMake presets for easy configuration and building:

-   Windows: Visual Studio 2022 generator
-   Linux/macOS: Ninja generator

Available presets:

-   `windows-release`, `windows-development`
-   `linux-release`, `linux-development`
-   `macos-release`, `macos-development`

### Building

1. Configure the project:

    ```sh
    cmake --preset <platform>-<build-type>
    ```

2. Build the project:
    ```sh
    cmake --build build --preset <platform>-<build-type>
    ```

Example for Windows release build:

```sh
cmake --preset windows-release
cmake --build build --preset windows-release
```

Note: Building SDL3 dependencies with vcpkg on Unix systems (Linux/macOS) may take longer than on Windows.

## Known Issues

-   Cursor misalignment with multi-byte UTF-8 characters
-   Cursor position issues when word wrapping is active
-   Some planned features are not yet implemented (see TODO.md for details)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

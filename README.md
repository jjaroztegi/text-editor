# Text Editor

A simple text editor built using C++ and SDL3, featuring a clean interface and essential text editing capabilities.

## Requirements

-   C++20 compiler
-   [SDL3](https://github.com/libsdl-org/SDL) and [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf)
-   [CMake](https://cmake.org/) (minimum version 3.16)

## Building the Project

### Cloning the Repository

```sh
git clone --depth=1 --recurse-submodules https://github.com/jjaroztegi/text-editor.git
cd text-editor
```

### Generic Build Instructions

1. Configure the project:

    ```sh
    cmake -S . -B build
    ```

2. Build the project:
    ```sh
    cmake --build build --target text_editor --config Release
    ```

### Using CMake Presets

This project supports CMake presets for easier configuration:

-   Windows: Visual Studio 2022 generator
-   Linux: Ninja generator
-   macOS: Xcode generator

Available presets:

-   `windows-release`, `windows-development`
-   `linux-release`, `linux-development`
-   `macos-release`, `macos-development`

To use presets:

```sh
cmake --preset <platform>-<build-type>
cmake --build build --preset <platform>-<build-type>
```

Example for Windows release build:

```sh
cmake --preset windows-release
cmake --build build --preset windows-release
```

### Using an IDE

You can also use an init script inside `config/` directory. Then open the IDE project inside `build/` and run!

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

## Known Issues

-   Cursor misalignment with multi-byte UTF-8 characters
-   Cursor position issues when word wrapping is active
-   Some planned features are not yet implemented (see TODO.md for details)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

# TODO: Missing Features

## Core Features

- [x] Implement logic for UP and DOWN arrow keys to navigate between lines.
- [ ] Add support for text selection and clipboard operations (cut, copy, paste).
- [ ] Enable saving and loading text files.
- [ ] Add undo and redo functionality.

## User Interface

- [ ] Display line numbers on the left side of the text editor.
- [ ] Add a status bar to show cursor position, file name, and text size.
- [ ] Implement a settings menu for customizing font, text size, and colors.

## Advanced Features

- [ ] Add syntax highlighting for programming languages.
- [ ] Implement search and replace functionality.
- [ ] Enable word wrap toggle.
- [ ] Drag and drop support for opening files.

## Performance

- [ ] Optimize rendering for large text files.
- [ ] Improve cursor rendering to handle variable-width fonts.

## Accessibility

- [ ] Add keyboard shortcuts for common actions (e.g., save, open, find).
- [ ] Support option to toggle dark and light mode.

## Bugs

- [x] When zooming forces wordWrap, the cursor position gets misaligned.
- [ ] Cursor misalignment with multi-byte UTF-8 characters (e.g., "ñ"), where the cursor treats individual bytes instead of whole characters.
- [ ] Cursor inside wrapped word jumps to end of prev line.

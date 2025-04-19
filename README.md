# A simple snake game written in C++ using SDL3.

Started as a way to learn the SDL3 library as well as correct CMake practices.

## Neovim LSP (clangd) setup cheatsheet:

Add this to CMakeLists.txt:
`set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`

Symlink `compile_commands.json` to root:

Linux/macOS:
`ln -s build/compile_commands.json compile_commands.json`

Windows Powershell:
`New-Item -ItemType SymbolicLink -Path compile_commands.json -Target build/compile_commands.json`

Windows cmd:
`mklink compile_commands.json build/compile_commands.json`

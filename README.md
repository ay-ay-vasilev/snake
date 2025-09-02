# A simple snake game written in C++ using SDL3.

Started as a way to learn the SDL3 library as well as correct CMake practices.
Brief list of features:
- Constants and various data can be set in the `res/data/constants.json` (for now is only used for maximum player name length and grid dimensions).
- Has a list of options that can be edited inside the game (resolution, fullscreen/windowed mode, game speed, snake color). Options have default values and custom user values that are stored in `res/config/options_presets.json` and `res/config/user_config.json` respectively.
- Highscores are visible in the game, and are stored in `res/data/highscores.dat`, which has trivial protection against editing.

Planned features:
- Multiplayer (local coop, AI controller, online).
- A particle system.

# Building instructions

The project uses **CMake presets** (requires **CMake 3.20+**) for configuration and building.
All commands must be run from the **project root directory** (not from inside a build folder).

---

## Available Presets

You can see available presets with:

```bash
cmake --list-presets
```

As of writing this, available presets are:
- `gcc-debug`
- `gcc-release`
- `gcc-mingw-debug`
- `gcc-mingw-release`
- `clang-debug`
- `clang-release`
- `msvc-debug`
- `msvc-release`
Some of the presets might not be available on certain platforms.

## Building

1. Choose the preset that matches your compiler and run:
```bash
cmake --preset <preset-name>
```
This will generate the build files in the corresponding folder (for example, `build/gcc-debug`).

2. Build using the same preset:
```bash
cmake --build --preset <preset-name>
```

3. Run the executable located inside the build directory, or open the Visual Studio solution and run the project from there.

# Neovim LSP (clangd) setup cheatsheet:

Add this to CMakeLists.txt:
`set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`

Symlink `compile_commands.json` to root:

Linux/macOS:
`ln -s build/compile_commands.json compile_commands.json`

Windows Powershell:
`New-Item -ItemType SymbolicLink -Path compile_commands.json -Target build/compile_commands.json`

Windows cmd:
`mklink compile_commands.json build/compile_commands.json`

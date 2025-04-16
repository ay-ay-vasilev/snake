# A simple snake game written in C++ using SDL3.

Started as a way to learn the SDL3 library as well as correct CMake practices.

## TODO:

- [x] 1. Move constants to a JSON file.
- [x] 2. Add snake collision and a game over state, as well as a reset game button.
	- [x] Snake collision
	- [x] Reset game button
	- [x] Game over state
- [x] 3. Add randomly generated food on the game world and its logic.
- [x] 4. Snake body collision.
- [ ] 5. Main menu + Options screen.
	- [x] Implement imgui
    - [x] Refactor UI
	- [ ] Main menu screen with imgui
        - [x] The screen itself is done
        - [ ] Add buttons that can be clicked
        - [ ] Add keyboard controls to button selection
        - [ ] Show the version on the screen
	- [ ] Options screen with imgui
	- [ ] imgui customization (fonts, colors, textures ?)
- [ ] 6. High score screen + table. Score serialization.
- [ ] 7. Multiplayer ?

## Additional TODO:

- [ ] 1. Read about CMake presets and implement to this project.
- [ ] 2. Write out instructions for compiling this project.
- [x] 3. Refactor GameObjects

Cheat sheet on how to enable clangd (C++ language server):

Add this to CMakeLists.txt:
`set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`

Run this:
`cmake -S . -G "Unix Makefiles" -B cmake`

Then create a `clangd` file in the root project folder with the following contents:
```
CompileFlags:
    CompilationDatabase: "cmake"
```

The cmake command needs to be run every time a new source file is added/removed from the project.

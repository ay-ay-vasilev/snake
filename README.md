# A simple snake game written in C++ using SDL3.

Started as a way to learn the SDL3 library as well as correct CMake practices.

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

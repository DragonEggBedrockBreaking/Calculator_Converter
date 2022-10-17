# Converter

This was originally meant to be a converter, and is now a full calculator + converter.
It is still very WIP. Feature completion checklist:

- [x] Calculations
- [ ] Conversions
- [ ] Graphs
- [ ] Hotkeys
- [ ] Mass calculation from files

## Compilation

### Prequisites

- [Cmake](https://cmake.org) (This is for compiling dependencies, not main project.)
- [Conan](https://conan.io) (Dependency manager.)
- [Meson](https://mesonbuild.com) (Build system.)
- [Ninja](https://ninja-build.org) (Actually compiles and links stuff.)
- A C++ compiler (e.g. [G++](https://gcc.gnu.org), [Clang++](https://clang.llvm.org))
- A C++ linker (compilers have [lld](https://lld.llvm.org) inbuilt, or you could install another, e.g. [mold](https://github.com/rui314/mold))

### Building

```cpp
mkdir build
cd build
conan install .. --build=missing
conan build ..
```

## Running

The binary will be in `dist/` and will be called `converter`.
(On Windows it is probably `converter.exe`, idrc...)

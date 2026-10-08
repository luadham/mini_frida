# JS Linux Process Inspector

A small C++ project for learning Linux process instrumentation, memory inspection, and ptrace-based debugging using JavaScript as the scripting layer.

This project explores how a process can be attached, inspected, and controlled at runtime using Linux primitives such as `ptrace` and `/proc/<pid>/maps`. It exposes a small JavaScript API through QuickJS so runtime behavior can be scripted without writing a full native command-line interface.

## What this project does

- attaches to a running process
- reads CPU register state
- reads process memory maps from `/proc/<pid>/maps`
- resolves library and module base addresses
- installs temporary software breakpoints
- inspects and modifies register values
- exposes the functionality through JavaScript bindings

## Main areas

- `src/ptrace/` — Linux `ptrace` helpers
- `src/core/linux/procfs/` — process memory map parsing
- `src/core/linux/breakpoint/` — breakpoint management
- `src/bindings/` — JavaScript binding layer to native C++ code
- `src/JSEngine/` — QuickJS integration and execution
- `src/Logger/` — logging utilities

## Why this project exists

This project is intended as a learning tool for understanding:

- Linux process memory layout
- ELF and module base resolution
- `ptrace`-based debugging workflows
- runtime code introspection
- low-level instrumentation in C++
- JavaScript-driven control over native instrumentation logic

## Build

```bash
make
```

Run the binary:

```bash
./build/main
```

## Notes

This is a research and learning project, not a production-grade debugger or security tool. The goal is to explore the internals of Linux process monitoring and runtime instrumentation in a practical way.

## Dependencies

- QuickJS
- GCC or Clang with C++20 support
- Linux (`ptrace`, `/proc`, `user_regs_struct`)

## License

This project is for educational purposes and is intended for learning low-level Linux internals and process instrumentation.

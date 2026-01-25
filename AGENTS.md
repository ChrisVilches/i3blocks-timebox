# Agent Guidelines for Timebox

## Build Commands
- `make` or `make i3` - Builds the i3 frontend with strict C++20 flags and sanitizers
- `make cli` - Builds the CLI frontend (placeholder)
- `make all` - Builds both frontends
- `make clean` - Removes all build artifacts from build/ directory
- Binaries are built to `build/timebox-i3` and `build/timebox-cli`

## Compiler Configuration
- C++20 with `-Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion`
- Additional warnings: `-Wsign-conversion -Wnull-dereference -Wold-style-cast -Woverloaded-virtual`
- Sanitizers: `-fsanitize=address,undefined`
- Thread support: `-pthread`

## Code Style
- **Header guards**: Use `#pragma once`
- **Naming**: snake_case for functions/variables, CamelCase for classes
- **Namespaces**: Lowercase (e.g., `utils::`)
- **Constants**: Use `static inline constexpr` for class constants
- **Formatting**: 2-space indentation, no tabs
- **Includes**: System includes first, then local includes
- **Error handling**: Use return codes, no exceptions (project doesn't use exceptions)
- **Thread safety**: Use `std::mutex` and `std::lock_guard` for synchronization
- **Move/copy**: Delete copy/move operations for classes managing resources (e.g., `Timer`)

## Project Structure
- Core logic source files in `src/` with `.cpp`/`.h` pairs
- Frontend-specific code in `frontends/` (i3, cli)
- Build output in `build/` (created automatically)
- i3blocks integration tool for timeboxing/pomodoro timer

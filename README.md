# Timebox

A modular timeboxing timer with i3blocks frontend.

Timeboxing is a time management technique that involves setting a time limit for working on a task. This helps improve focus, prevent procrastination, reduce stress.

The Pomodoro Technique is a popular variant of timeboxing. It involves working in 25-minute intervals (called "pomodoros") with short breaks in between. After four pomodoros, a longer break is taken.

## Architecture

The project is split into core timer logic (`src/`) and frontend implementations (`frontends/`). Currently available frontends:

- **i3 frontend**: For integration with i3 status bar (i3blocks)
- **CLI frontend**: Placeholder for future terminal interface

## Features

- **Mouse Interaction Support**: Adjust the timer interactively using mouse clicks and scroll wheel movements in the i3 status bar.
- **Notification Integration**: Compatible with any notification system installed on your machine, such as `notify-send`.

## Installation

### Compilation

Ensure you have `g++` and `make` installed. The project supports multiple frontends:

```sh
# Build i3 frontend (default)
make
# or explicitly:
make i3

# Build CLI frontend (placeholder)
make cli

# Build both frontends
make all

# Clean build artifacts
make clean
```

Binaries are generated in the `build/` directory:
- `build/timebox-i3` – i3blocks frontend
- `build/timebox-cli` – CLI frontend (placeholder)

## Usage

The following instructions refer to the i3 frontend (`timebox-i3`). The CLI frontend is currently a placeholder.

### Running the Timer

To start the timer manually and display a notification when time is up:

```sh
./build/timebox-i3 notify-send "Time's up" "Some message here"
```

This starts the timer in an inactive state. You can increase the time interactively using the mouse in the i3 status bar. In a terminal, you can simulate mouse button inputs by entering numbers 1 to 5, which the program reads from stdin.

### i3blocks Integration

To integrate Timebox with i3blocks, add the following to your i3blocks configuration file:

```
[timebox]
command=/path/to/timebox-i3 notify-send "Time's up" "Some message here"
interval=persist
```

Make sure to replace `/path/to/timebox-i3` with the actual path to the compiled `timebox-i3` binary.

### Alternative Notifications

You can use `i3-nagbar` instead of `notify-send`:

```sh
./build/timebox-i3 i3-nagbar -m "Time's up"
```

### Custom Scripts

You can execute a custom script when the timer ends. For example, if you want to send a notification and play a sound:

```sh
./build/timebox-i3 /path/to/your/script.sh
```

Ensure your script handles necessary actions, such as triggering notifications and playing sounds.

## Support

For any issues or feature requests, please open an issue in the repository.


# Timebox (i3blocks)

A Timeboxing Timer for i3blocks.

Timeboxing is a time management technique that involves setting a time limit for working on a task. This helps improve focus, prevent procrastination, and reduce stress.

The Pomodoro Technique is a popular variant of timeboxing. It involves working in 25-minute intervals (called "pomodoros") with short breaks in between. After four pomodoros, a longer break is taken.

## Features

- **Mouse Interaction Support**: Adjust the timer interactively using mouse clicks and scroll wheel movements in the i3 status bar.
- **Notification Integration**: Compatible with any notification system installed on your machine, such as `notify-send`.

## Installation

### Compilation

Ensure you have `g++` and `make` installed. To compile, run:

```sh
make
```

This will generate the `timebox` executable.

## Usage

### Running the Timer

To start the timer manually and display a notification when time is up:

```sh
./timebox notify-send "Time's up" "Some message here"
```

This starts the timer in an inactive state. You can increase the time interactively using the mouse in the i3 status bar. On a terminal, you can use numbers from 1 to 5 to simulate mouse buttons, which are read via stdin.

### i3blocks Integration

To integrate Timebox with i3blocks, add the following to your i3blocks configuration file:

```
[timebox]
command=/path/to/timebox notify-send "Time's up" "Some message here"
interval=persist
```

Make sure to replace `/path/to/timebox` with the actual path to the compiled `timebox` binary.

### Alternative Notifications

You can use `i3-nagbar` instead of `notify-send`:

```sh
./timebox i3-nagbar -m "Time's up"
```

### Custom Scripts

You can execute a custom script when the timer ends. For example, if you want to send a notification and play a sound:

```sh
./timebox /path/to/your/script.sh
```

Ensure your script handles necessary actions, such as triggering notifications and playing sounds.

## Notes

- The timer starts in an inactive state and must be adjusted using mouse interactions in the i3 status bar.
- For any issues or feature requests, please open an issue in the repository.


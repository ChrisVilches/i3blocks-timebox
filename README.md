# Timebox (i3blocks)

Timeboxing Timer for i3blocks.

Timeboxing is a time management technique that involves setting a time limit for working on a task. This helps improve focus, prevent procrastination, and reduce stress.

The Pomodoro Technique is a popular variant of timeboxing. It involves working in 25-minute intervals (called "pomodoros") with short breaks in between. After four pomodoros, a longer break is taken.

## Features

1. **Mouse Input Support**: Seamlessly processes mouse interactions, including clicks and scroll wheel movements, to enhance user interactivity.
2. **Notification Integration**: Fully compatible with any notification system installed on your machine, ensuring smooth and consistent communication.

## Compilation

```sh
make
```

## Execution and Installation

### Basic Usage

```sh
./timebox notify-send "Time's up" "Some message here"
```

This starts the timer in an off state and allows the user to increase the time interactively using the mouse in the i3 status bar to enable the timer.

To integrate it with i3blocks, add the following block to your i3blocks configuration file:

```
[timebox]
command=/path/to/timebox notify-send "Time's up" "Some message here"
interval=persist
```

You can use any command that triggers a notification (e.g. `notify-send` if it's installed).

### Other Usages

Using `i3-nagbar`:

```sh
./timebox i3-nagbar -m "Time's up"
```

You can use the custom `script.sh` to perform complex actions like sending a desktop notification with `notify-send` and playing a ringtone simultaneously:

```sh
./timebox /path/to/your/script.sh
```


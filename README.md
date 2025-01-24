# Timebox (i3blocks)

Timeboxing Timer for i3blocks.

Timeboxing is a time management technique that involves setting a time limit for working on a task. This helps to improve focus, prevent procrastination, and reduce stress.

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
./timebox 0 notify-send "Time's up" "Some message here"
```

This starts the timer in an off state, and allows the user to increase the time interactively using the mouse in the i3 status bar to enable the timer.

To integrate it with i3blocks, add the following block to your i3blocks configuration file:

```
[timebox]
command=/path/to/timebox 0 notify-send "Time's up" "Some message here"
interval=persist
```

You can use any command that triggers a notification (e.g. `notify-send` if it's installed).

### Basic Timer with `i3-nagbar` Notification

```sh
./timebox 300 i3-nagbar -m "Time's up"
```

This runs a 300-second (5-minute) timer and shows a message using `i3-nagbar` when the time is up.

### Basic Timer with `notify-send` Notification

```sh
./timebox 600 notify-send "Timer Finished" "Your 10-minute timer is up"
```

This runs a 600-second (10-minute) timer and shows a notification using `notify-send` when the timer ends.

### Custom Timer to Launch a Script

If you have a custom script to handle notifications, you can call it directly:

```sh
./timebox 1200 /path/to/your/script.sh
```

This runs a 1200-second (20-minute) timer and executes your custom script when the time is up.

You can use the custom `script.sh` to perform complex actions like sending a desktop notification with `notify-send` and playing a ringtone simultaneously.


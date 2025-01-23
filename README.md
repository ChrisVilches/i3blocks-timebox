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

## Installation

Add this block to your i3blocks configuration file:

```
[timebox]
command=THE_PATH/timebox i3-nagbar -m "Timebox ended!"
interval=persist
```

You can use any command that triggers a notification (e.g. `notify-send` if it's installed).

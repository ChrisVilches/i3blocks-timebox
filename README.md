# Timebox (i3blocks)

Timebox block for i3 with i3blocks.

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

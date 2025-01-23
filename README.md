# i3blocks Timebox

Timebox block for i3 with i3blocks.

## Compilation

```sh
make
```

## Installation

Add this block:

```
[timebox]
command=$THE_PATH/timebox i3-nagbar -m "Timebox ended!"
interval=persist
```

You can add any command that triggers a notification (e.g. `notify-send` if it's installed).

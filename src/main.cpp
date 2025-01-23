// TODO: This program is nice, maybe I should create a separate repository
// instead of here. I want to show this project somehow.

#include <unistd.h>

#include <cstdlib>
#include <functional>
#include <iostream>

#include "timer.h"
#include "utils.h"

enum class MouseInput {
  Left = 1,
  Middle = 2,
  Right = 3,
  WheelUp = 4,
  WheelDown = 5,
};

const int step_seconds_small = 5;
const int step_seconds_big = 60 * 5;

int main(const int argc, char* argv[]) {
  const std::function<void()> callback = [argc, argv]() {
    if (argc < 2) return;
    if (fork() != 0) return;

    // Having the program output here will ruin the output of the i3 block!
    // So it must be silenced.
    utils::redirect_to_dev_null();

    if (execvp(argv[1], argv + 1) == -1) {
      perror("execvp failed");
    }
  };

  // TODO: The only thing I don't know is how to join the thread at the end safely.
  // add a destructor to join or detach the thread, or something similar.
  Timer timer(callback);
  timer.start();

  int click;

  while (std::cin >> click) {
    switch (click) {
      case (int)MouseInput::Left:
        timer.inc(-step_seconds_small);
        break;
      case (int)MouseInput::Right:
        timer.inc(step_seconds_small);
        break;
      case (int)MouseInput::WheelUp:
        timer.inc(step_seconds_big);
        break;
      case (int)MouseInput::WheelDown:
        timer.inc(-step_seconds_big);
        break;
      case (int)MouseInput::Middle:
        timer.toggle_display_remaining();
        break;
    }
  }
}

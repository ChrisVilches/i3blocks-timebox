#include <unistd.h>

#include <cstdlib>
#include <functional>
#include <iostream>

#include "mouse_input.h"
#include "timer.h"
#include "utils.h"

const int step_seconds_small = 60;
const int step_seconds_big = 60 * 5;

static std::mutex print_mtx;

void print_line(const std::string& s) {
  std::lock_guard<std::mutex> lock(print_mtx);
  std::cout << s << std::endl;
}

int main(const int argc, char* argv[]) {
  const std::function<void()> end_cb = [argc, argv]() {
    if (argc < 3) return;
    if (fork() != 0) return;

    // Having the program output here will ruin the output of the i3 block!
    // So it must be silenced.
    utils::redirect_to_dev_null();

    if (execvp(argv[2], argv + 2) == -1) {
      perror("execvp failed");
    }
  };

  // TODO: The only thing I don't know is how to join the thread at the end safely.
  // add a destructor to join or detach the thread, or something similar.
  Timer timer(end_cb, print_line);
  timer.start();

  try {
    const int init_seconds = std::stoi(argv[1]);
    // TODO: Adding 4 seconds adds only 3. There's a problem with discrete math happening
    // somewhere in the timer logic (not necessarily here).

    if (init_seconds > 0) {
      timer.inc(init_seconds);
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error: Invalid integer format" << std::endl;
    return 1;
  }

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

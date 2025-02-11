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
  // TODO: Get the message as an object (not string) and
  // also print it with colors and a clock icon.
  std::lock_guard<std::mutex> lock(print_mtx);
  std::cout << s << std::endl;
}

// TODO: Weird: it's creating a new timer even though the one I had ended.
// I don't know if this problem is caused by i3 or by this C++ program.
// hard to debug lol.

void execute_notification(const int argc, char* argv[]) {
  if (argc < 3) return;
  if (fork() != 0) return;

  // Having the program output here will ruin the output of the i3 block!
  // So it must be silenced.
  utils::redirect_to_dev_null();

  if (execvp(argv[2], argv + 2) == -1) {
    // TODO: Change error message for a human-friendly one, although I never read it
    // really (because it never happens).
    perror("execvp failed");
  }
}

int main(const int argc, char* argv[]) {
  // TODO: The only thing I don't know is how to join the thread at the end safely.
  // add a destructor to join or detach the thread, or something similar.
  Timer timer([argc, argv]() { execute_notification(argc, argv); }, print_line);

  try {
    const int init_seconds = std::stoi(argv[1]);

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

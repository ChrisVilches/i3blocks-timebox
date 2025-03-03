#include <iostream>

#include "mouse_input.h"
#include "timer.h"
#include "utils.h"

const int step_seconds_small = 60;
const int step_seconds_big = 60 * 5;

static std::mutex print_mtx;

void print_message(const std::optional<TimerMessage> msg) {
  std::lock_guard<std::mutex> lock(print_mtx);

  if (!msg.has_value()) {
    std::cout << "Timebox" << std::endl;
    return;
  }

  if (msg->visible) {
    std::cout << "🕔 " << utils::format_seconds(msg->ms / 1000) << std::endl;
  } else {
    std::cout << "🕔 Timebox..." << std::endl;
  }
}

void execute_notification(const int argc, char* argv[]) {
  if (argc < 2) return;
  if (fork() != 0) return;

  // Having the program output here will ruin the output of the i3 block!
  // So it must be silenced.
  utils::redirect_to_file("/tmp/timebox-i3.log");

  if (execvp(argv[1], argv + 1) == -1) {
    perror("execvp failed");

    // NOTE: Prevents the child from staying alive and logging the default string (used as
    // i3 block UI) if exec fails.
    exit(1);
  }
}

void process(const int argc, char* argv[]) {
  Timer timer([argc, argv]() { execute_notification(argc, argv); }, print_message);

  int click;

  while (std::cin >> click) {
    switch (click) {
      case static_cast<int>(MouseInput::Left):
        timer.inc(-step_seconds_small);
        break;
      case static_cast<int>(MouseInput::Right):
        timer.inc(step_seconds_small);
        break;
      case static_cast<int>(MouseInput::WheelUp):
        timer.inc(step_seconds_big);
        break;
      case static_cast<int>(MouseInput::WheelDown):
        timer.inc(-step_seconds_big);
        break;
      case static_cast<int>(MouseInput::Middle):
        timer.toggle_display_remaining();
        break;
    }
  }

  // NOTE: When used as an i3 block, this program typically runs indefinitely.
  // However, you can simulate its termination by pressing CTRL+D in a terminal.

  std::lock_guard<std::mutex> lock(print_mtx);
  std::cerr << "📌 Input stream closed. Cleaning up resources... ⏳" << std::endl;
}

int main(const int argc, char* argv[]) {
  process(argc, argv);
  std::cerr << "🔹 Timer thread finished. Exiting. ✅" << std::endl;
}

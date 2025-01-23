// TODO: Maybe the prints should be delegated to the main. This should just be for logic.
#include "timer.h"

#include <thread>

#include "utils.h"

Timer::Timer(const std::function<void()> fn)
    : active(false), display_remaining(true), callback(fn) {}

void Timer::wait() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);
}

void Timer::print() {
  if (!active) {
    utils::print_line("Timebox");
    return;
  }
  if (display_remaining) {
    utils::print_line(utils::format_seconds(target.seconds_until()));
  } else {
    utils::print_line("Timebox...");
  }
}

void Timer::task() {
  while (true) {
    print();
    wait();
    while (active) {
      if (target.is_over()) {
        active = false;
        callback();
        break;
      }
      print();
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  }
}

void Timer::start() {
  th = std::thread([this]() { task(); });
}

void Timer::inc(const int s) {
  if (!active || target.is_over()) {
    target.set_to_now();
  }
  target.inc(s);
  if (target.is_over()) {
    active = false;
  } else {
    cv.notify_one();
    active = true;
  }
  print();
}

void Timer::toggle_display_remaining() { display_remaining = !display_remaining; }

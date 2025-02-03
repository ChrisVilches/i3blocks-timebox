#include "timer.h"

#include <thread>

#include "utils.h"

Timer::Timer(const std::function<void()> end_cb,
             const std::function<void(const std::string&)> msg_cb)
    : active(false),
      display_remaining(true),
      timer_finish_callback(end_cb),
      message_callback(msg_cb) {
  th = std::thread([this]() { task(); });
}

void Timer::wait() {
  if (active) return;

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);
}

void Timer::emit_message() {
  if (!active) {
    message_callback("Timebox");
    return;
  }
  if (display_remaining) {
    message_callback(utils::format_seconds(target.ms_until() / 1000));
  } else {
    message_callback("Timebox...");
  }
}

void Timer::task() {
  while (true) {
    emit_message();
    wait();
    while (active) {
      if (target.is_over()) {
        active = false;
        timer_finish_callback();
        break;
      }
      emit_message();
      std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }
  }
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
  emit_message();
}

// NOTE: The display will be changed in the next tick, not immediately (since it doesn't
// execute 'emit_message').
void Timer::toggle_display_remaining() { display_remaining = !display_remaining; }

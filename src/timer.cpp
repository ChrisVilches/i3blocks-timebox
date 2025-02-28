#include "timer.h"

#include <optional>
#include <thread>

Timer::Timer(const std::function<void()> end_cb,
             const std::function<void(const std::optional<TimerMessage>)> msg_cb)
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
  if (active) {
    message_callback(TimerMessage{target.ms_until(), display_remaining});
  } else {
    message_callback(std::nullopt);
  }
}

// TODO: UPDATE: I think this setup works correctly for all these situations.
// TODO: Verify using ChatGPT that my solution is sound and it's properly made.
// TODO: It's a bit complicated to quit this loop (which is waiting for signals).
// STDIN can be closed right away
// STDIN can be closed while a timer is on-going
// It can be executed with `echo 3 | program`
// It can be executed as terminal app, start a timer, and then close STDIN (ctrl+d)
// so there are several cases, and several places to put the stop_flag condition here.
Timer::~Timer() {
  stop_flag = true;
  cv.notify_one();
  if (th.joinable()) {
    th.join();
  }
}

void Timer::task() {
  while (!stop_flag) {
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

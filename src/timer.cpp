#include "timer.h"

#include <optional>
#include <thread>

Timer::Timer(const std::function<void()> end_cb,
             const std::function<void(const std::optional<TimerMessage>)> msg_cb)
    : timer_finish_callback(end_cb), message_callback(msg_cb) {
  th = std::thread([this]() { task(); });
}

void Timer::wait() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this]() { return instructions_stream_closed || active; });
}

void Timer::emit_message() {
  if (active) {
    message_callback(TimerMessage{target.ms_until(), display_remaining});
  } else {
    message_callback(std::nullopt);
  }
}

Timer::~Timer() {
  instructions_stream_closed = true;
  cv.notify_one();

  if (th.joinable()) {
    th.join();
  }
}

void Timer::task() {
  do {
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

  } while (!instructions_stream_closed);
}

void Timer::inc(const int s) {
  if (!active || target.is_over()) {
    target.set_to_now();
  }
  target.inc(s);
  if (target.is_over()) {
    active = false;
  } else {
    active = true;
    cv.notify_one();
  }
  emit_message();
}

// NOTE: The display will be changed in the next tick, not immediately (since it doesn't
// execute 'emit_message').
void Timer::toggle_display_remaining() { display_remaining = !display_remaining; }

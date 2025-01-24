#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

#include "time_target.h"

class Timer {
 private:
  static inline constexpr int SLEEP_TIME = 200;
  std::condition_variable cv;
  std::mutex mtx;
  // The usage of "active" is necessary to make a difference between
  // a timer stopped by the user and one that finished naturally.
  // Only the case without human interaction triggers the callback.
  std::atomic<bool> active;
  std::atomic<bool> display_remaining;
  std::thread th;
  std::function<void()> timer_finish_callback;
  std::function<void(const std::string&)> message_callback;
  TimeTarget target;

  void wait();
  void emit_message();
  void task();

 public:
  Timer(const std::function<void()>, const std::function<void(const std::string&)>);
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(Timer&&) = delete;

  void start();
  void inc(const int);
  void toggle_display_remaining();
};

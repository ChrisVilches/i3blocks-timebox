#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <thread>

#include "time_target.h"

struct TimerMessage {
  int ms;
  bool visible;
};

class Timer {
 private:
  static inline constexpr int SLEEP_TIME = 200;
  std::condition_variable cv;
  std::mutex mtx;
  // The usage of "active" is necessary to make a difference between
  // a timer stopped by the user and one that finished naturally.
  // Only the case without human interaction triggers the callback.
  std::atomic<bool> active{false};
  std::atomic<bool> display_remaining{true};
  std::atomic<bool> finished{false};
  std::thread th;
  std::function<void()> timer_finish_callback;
  std::function<void(const std::optional<TimerMessage>)> message_callback;
  TimeTarget target;

  void wait();
  void emit_message();
  void task();

 public:
  Timer(const std::function<void()>,
        const std::function<void(const std::optional<TimerMessage>)>);
  ~Timer();
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(Timer&&) = delete;

  void inc(const int);
  void toggle_display_remaining();
};

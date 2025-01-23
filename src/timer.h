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
  std::condition_variable cv;
  std::mutex mtx;
  std::mutex print_mtx;
  std::atomic<bool> active;
  std::atomic<bool> display_remaining;
  std::thread th;
  std::function<void()> callback;
  TimeTarget target;

  void wait();
  void print();
  void task();

 public:
  Timer(const std::function<void()> fn);
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(Timer&&) = delete;

  void start();
  void inc(const int s);
  void toggle_display_remaining();
};

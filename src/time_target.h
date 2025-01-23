#pragma once
#include <chrono>
#include <mutex>

class TimeTarget {
 private:
  std::chrono::time_point<std::chrono::system_clock> target;
  std::mutex mtx;

 public:
  int seconds_until();
  bool is_over();
  void inc(const int s);
  void set_to_now();
};

#pragma once
#include <chrono>
#include <mutex>

class TimeTarget {
 private:
  std::chrono::time_point<std::chrono::system_clock> target;
  std::mutex mtx;

 public:
  long long ms_until();
  bool is_over();
  void inc(const int);
  void set_to_now();
};

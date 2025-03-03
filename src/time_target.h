#pragma once
#include <chrono>

class TimeTarget {
 private:
  std::chrono::time_point<std::chrono::system_clock> target;

 public:
  long long ms_until();
  bool is_over();
  void inc(const int);
  void set_to_now();
};

#include "time_target.h"

int TimeTarget::ms_until() {
  std::lock_guard<std::mutex> lock(mtx);
  const auto diff = target - std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
}

bool TimeTarget::is_over() { return ms_until() <= 0; }

void TimeTarget::inc(const int s) {
  std::lock_guard<std::mutex> lock(mtx);
  target += std::chrono::seconds(s);
}

void TimeTarget::set_to_now() {
  std::lock_guard<std::mutex> lock(mtx);
  target = std::chrono::system_clock::now();
}

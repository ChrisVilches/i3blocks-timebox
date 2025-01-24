#include "time_target.h"

int TimeTarget::seconds_until() {
  std::lock_guard<std::mutex> lock(mtx);
  return std::chrono::duration_cast<std::chrono::seconds>(
             target - std::chrono::system_clock::now())
      .count();
}

// TODO: I'm not sure if the timer runs for X seconds or for X-1 seconds.
// See? discrete math is the most important math branch for programming.
bool TimeTarget::is_over() { return seconds_until() <= 0; }

void TimeTarget::inc(const int s) {
  std::lock_guard<std::mutex> lock(mtx);
  target += std::chrono::seconds(s);
}

void TimeTarget::set_to_now() {
  std::lock_guard<std::mutex> lock(mtx);
  target = std::chrono::system_clock::now();
}

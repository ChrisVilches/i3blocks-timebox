#include "time_target.h"

int TimeTarget::ms_until() {
  std::lock_guard<std::mutex> lock(mtx);
  const auto diff = target - std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
}

// TODO: I'm not sure if the timer runs for X seconds or for X-1 seconds.
// See? discrete math is the most important math branch for programming.
// NOTE: Fixed. I changed it to milliseconds_until so that it has more precision
// (the display is still formatted to just seconds though), but this means that
// when the number of seconds is between 0 and 1, the value will not be 0 (bc it includes
// all the ms in between) so this won't run off when the value is for example 999ms (which
// was being rounded to 0 in the previous implementation)
bool TimeTarget::is_over() { return ms_until() <= 0; }

void TimeTarget::inc(const int s) {
  std::lock_guard<std::mutex> lock(mtx);
  target += std::chrono::seconds(s);
}

void TimeTarget::set_to_now() {
  std::lock_guard<std::mutex> lock(mtx);
  target = std::chrono::system_clock::now();
}

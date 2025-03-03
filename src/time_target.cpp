#include "time_target.h"

long long TimeTarget::ms_until() {
  const auto diff = target - std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
}

bool TimeTarget::is_over() { return ms_until() <= 0; }

void TimeTarget::inc(const int s) { target += std::chrono::seconds(s); }

void TimeTarget::set_to_now() { target = std::chrono::system_clock::now(); }

//
// 乱数
//

#include "random.hpp"


Random::Random() :
  engine_(std::mt19937::default_seed),
  dist_zero_to_one_(0.0f, 1.0f)
{}


void Random::setSeed(const u_int new_seed) {
  engine_.seed(new_seed);
}
  
// [0, last) を返す
int Random::operator()(const int last) {
  return engine_() % last;
}

// [first, last] を返す
int Random::operator()(const int first, const int last) {
  return first + operator()(last - first + 1);
}

  
// [0.0f, 1.0f] を返す
float Random::operator()() {
  return dist_zero_to_one_(engine_);
}

// [first, last] を返す
float Random::operator()(const float first, const float last) {
  return first + (last - first) * operator()();
}

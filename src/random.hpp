
#pragma once

//
// 乱数
//

#include <random>


namespace {

class Random {
  std::mt19937 engine_;
  std::uniform_real_distribution<float> dist_zero_to_one_;

  
public:
  Random() :
    engine_(std::mt19937::default_seed),
    dist_zero_to_one_(0.0f, 1.0f)
  {}


  void setSeed(const u_int new_seed) {
    engine_.seed(new_seed);
  }
  
  // [0, last) を返す
  int fromZeroToLast(const int last) {
    return engine_() % last;
  }

  // [first, last] を返す
  int fromFirstToLast(const int first, const int last) {
    return first + fromZeroToLast(last - first + 1);
  }

  
  // [0.0f, 1.0f] を返す
  float fromZeroToOne() {
    return dist_zero_to_one_(engine_);
  }

  // [first, last] を返す
  float fromFirstToLast(const float first, const float last) {
    return first + (last - first) * fromZeroToOne();
  }
  
};

}

#pragma once

//
// カメラ(2D向け)
//

#include "defines.hpp"
#include <utility>
#include "vector.hpp"
#include "matrix.hpp"


class Camera2D {
  float z_;
  

public:
	Camera2D();
  
  std::pair<Mat4, Mat4> operator()(const Vec2f& view_size) const;
  
};

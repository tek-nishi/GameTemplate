#pragma once

//
// ベクトル定義
// FIXME:OpenGLに依存している
//

#include "defines.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/exterior_product.hpp>    // vec2の外積


using Vec2i = glm::ivec2;
using Vec2f = glm::vec2;
using Vec3f = glm::vec3;
using Vec4f = glm::vec4;


// 向きがランダムで長さが１のベクトルを作成
template<typename T>
T randomVector() {
  T v = T::Random();
  if (!v.squaredNorm()) {
    // 長さが０の場合はx成分を1にしておく
    v.x() = 1.0f;
  }
  return v.normalized();
}

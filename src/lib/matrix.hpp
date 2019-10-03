#pragma once

//
// 行列定義
// FIXME:OpenGLに依存している
//

#include "defines.hpp"
#include <utility>
#include "vector.hpp"


using Mat3 = glm::mat3;
using Mat4 = glm::mat4;


// 回転、スケーリング、平行移動から変換行列を生成(2D向け)
// rotate    回転量(ラジアン)
// transtate 平行移動量
// scaling   スケーリング
Mat4 transformMatrix2D(const float rotate_rad, const Vec3f& transrate, const Vec3f& scaling);

// 正投影行列を生成
// SOURCE:mesa
Mat4 orthoMatrix(const GLfloat left, const GLfloat right,
                    const GLfloat bottom, const GLfloat top,
                    const GLfloat nearval, const GLfloat farval);

// 透視投影行列を生成
// SOURCE:mesa
Mat4 frustumMatrix(const GLfloat left, const GLfloat right,
                      const GLfloat bottom, const GLfloat top,
                      const GLfloat nearval, const GLfloat farval);

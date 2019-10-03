//
// 行列定義
// FIXME:OpenGLに依存している
//

#include "matrix.hpp"
#include <glm/gtx/transform.hpp>



// 回転、スケーリング、平行移動から変換行列を生成(2D向け)
// rotate    回転量(ラジアン)
// transtate 平行移動量
// scaling   スケーリング
Mat4 transformMatrix2D(const float rotate_rad, const Vec3f& transrate, const Vec3f& scaling) {
  auto t = glm::translate(transrate);
  auto s = glm::scale(scaling);
  auto r = glm::rotate(rotate_rad, Vec3f(0, 0, 1));

  return t * r * s;
}


// 正投影行列を生成
// SOURCE:mesa
Mat4 orthoMatrix(const GLfloat left, const GLfloat right,
                 const GLfloat bottom, const GLfloat top,
                 const GLfloat nearval, const GLfloat farval) {
	Mat4 m;

	m[0][0] = 2.0f / (right-left);
	m[1][0] = 0.0f;
	m[2][0] = 0.0f;
	m[3][0] = -(right+left) / (right-left);

	m[0][1] = 0.0f;
	m[1][1] = 2.0f / (top-bottom);
	m[2][1] = 0.0f;
	m[3][1] = -(top+bottom) / (top-bottom);

	m[0][2] = 0.0f;
	m[1][2] = 0.0f;
	m[2][2] = -2.0f / (farval-nearval);
	m[3][2] = -(farval+nearval) / (farval-nearval);

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;

  return m;
}

// 透視投影行列を生成
// SOURCE:mesa
Mat4 frustumMatrix(const GLfloat left, const GLfloat right,
                   const GLfloat bottom, const GLfloat top,
                   const GLfloat nearval, const GLfloat farval) {
	GLfloat x, y, a, b, c, d;

	x = (2.0f * nearval) / (right-left);
	y = (2.0f * nearval) / (top-bottom);
	a = (right+left) / (right-left);
	b = (top+bottom) / (top-bottom);
	c = -(farval+nearval) / ( farval-nearval);
	d = -(2.0f * farval*nearval) / (farval-nearval);  /* error? */

	Mat4 m;
	m[0][0] = x;
	m[1][0] = 0.0f;
	m[2][0] = a;
	m[3][0] = 0.0f;
	 
	m[0][1] = 0.0f;
	m[1][1] = y;
	m[2][1] = b;
	m[3][1] = 0.0f;
	 
	m[0][2] = 0.0f;
	m[1][2] = 0.0f;
	m[2][2] = c;
	m[3][2] = d;
	 
	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = -1.0f;
	m[3][3] = 0.0f;

  return m;
}

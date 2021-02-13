
#pragma once

//
// 行列定義
// FIXME:OpenGLに依存している
//

#include "defines.hpp"
#include <deque>
#include <utility>
#include <Eigen/Geometry>
// #include <GLFW/glfw3.h>
#include "vector.hpp"


namespace {

typedef Eigen::Translation<float, 3> Translation;
typedef Eigen::Transform< GLfloat, 3, Eigen::Affine> Affinef;

// FIXME:コンストラクタでx,y,z全て渡さないと初期値が未定義になる
typedef Eigen::DiagonalMatrix<GLfloat, 3> Scaling; 

typedef Eigen::Matrix<GLfloat, 4, 4> Mat3f;
typedef Eigen::Matrix<GLfloat, 4, 4> Mat4f;


// 回転、スケーリング、平行移動から変換行列を生成(2D向け)
// rotate    回転量(ラジアン)
// transtate 平行移動量
// scaling   スケーリング
Affinef transformMatrix2D(const float rotate_rad, const Vec3f& transtate, const Vec3f& scaling) {
  Affinef matrix;

  Translation t(transtate);
  Scaling s(scaling);
  Quatf r(Eigen::AngleAxisf(rotate_rad, Vec3f::UnitZ()));

  matrix = t * r * s;
  
  return matrix;
}


// 正投影行列を生成
// SOURCE:mesa
Affinef orthoMatrix(const GLfloat left, const GLfloat right,
                    const GLfloat bottom, const GLfloat top,
                    const GLfloat nearval, const GLfloat farval) {
	Affinef m;

	m(0,0) = 2.0f / (right-left);
	m(0,1) = 0.0f;
	m(0,2) = 0.0f;
	m(0,3) = -(right+left) / (right-left);

	m(1,0) = 0.0f;
	m(1,1) = 2.0f / (top-bottom);
	m(1,2) = 0.0f;
	m(1,3) = -(top+bottom) / (top-bottom);

	m(2,0) = 0.0f;
	m(2,1) = 0.0f;
	m(2,2) = -2.0f / (farval-nearval);
	m(2,3) = -(farval+nearval) / (farval-nearval);

	m(3,0) = 0.0f;
	m(3,1) = 0.0f;
	m(3,2) = 0.0f;
	m(3,3) = 1.0f;

  return m;
}

// 透視投影行列を生成
// SOURCE:mesa
Affinef frustumMatrix(const GLfloat left, const GLfloat right,
                      const GLfloat bottom, const GLfloat top,
                      const GLfloat nearval, const GLfloat farval) {
	GLfloat x, y, a, b, c, d;

	x = (2.0f * nearval) / (right-left);
	y = (2.0f * nearval) / (top-bottom);
	a = (right+left) / (right-left);
	b = (top+bottom) / (top-bottom);
	c = -(farval+nearval) / ( farval-nearval);
	d = -(2.0f * farval*nearval) / (farval-nearval);  /* error? */

	Affinef m;
	m(0,0) = x;
	m(0,1) = 0.0f;
	m(0,2) = a;
	m(0,3) = 0.0f;
	 
	m(1,0) = 0.0f;
	m(1,1) = y;
	m(1,2) = b;
	m(1,3) = 0.0f;
	 
	m(2,0) = 0.0f;
	m(2,1) = 0.0f;
	m(2,2) = c;
	m(2,3) = d;
	 
	m(3,0) = 0.0f;
	m(3,1) = 0.0f;
	m(3,2) = -1.0f;
	m(3,3) = 0.0f;

  return m;
}

// 透視投影行列を生成
// SOURCE:mesa
Affinef perspectiveMatrix(const GLfloat fovy, const GLfloat aspect, const GLfloat zNear, const GLfloat zFar) {
	GLfloat sine, cotangent, deltaZ;
	GLfloat radians = fovy / 2.0f;

	deltaZ = zFar - zNear;
	sine = std::sin(radians);
	assert((deltaZ != 0.0f) && (sine != 0.0f) && (aspect != 0.0f));
	cotangent = std::cos(radians) / sine;

	Affinef m(Affinef::Identity());
	m(0,0) = cotangent / aspect;
	m(1,1) = cotangent;
	m(2,2) = -(zFar + zNear) / deltaZ;
	m(2,3) = -2.0f * zNear * zFar / deltaZ;
	m(3,2) = -1.0f;
	m(3,3) = 0.0f;

  return m;
}

// 視点移動行列を生成
// SOURCE:mesa
Affinef lookAtMatrix(const Vec3f& eye, const Vec3f& center, const Vec3f& up) {
	Vec3f forward;
	Vec3f side;
	Vec3f upv;

	forward = center - eye;
	forward.normalize();
	upv = up;

	side = forward.cross(upv);
	side.normalize();
	upv = side.cross(forward);

	Affinef m(Affinef::Identity());
	m(0,0) = side.x();
	m(0,1) = side.y();
	m(0,2) = side.z();

	m(1,0) = upv.x();
	m(1,1) = upv.y();
	m(1,2) = upv.z();

	m(2,0) = -forward.x();
	m(2,1) = -forward.y();
	m(2,2) = -forward.z();

  return m * Translation(-eye);
}


// 3D座標→投影座標
// SOURCE:mesa
std::pair<bool, Vec3f> pointProject(const Vec3f& pos, const Affinef& modelMatrix, const Affinef& projMatrix, const int viewport[4]) {
	Vec4f in(pos.x(), pos.y(), pos.z(), 1.0f);
	Vec4f out = modelMatrix * in;
	in = projMatrix * out;
	if (in(3) == 0.0f) {
    return std::make_pair(false, Vec3f());
  }

	/* Map x, y and z to range 0-1 */
	for (u_int i = 0; i < 3; ++i) {
		float a = in(i) / in(3);
		in(i) = a * 0.5f + 0.5f;
	}

	/* Map x,y to viewport */
	in(0) = in(0) * viewport[2] + viewport[0];
	in(1) = in(1) * viewport[3] + viewport[1];

  return std::make_pair(true, Vec3f(in.x(), in.y(), in.z()));
}

// 投影座標→3D座標
// SOURCE:mesa
std::pair<bool, Vec3f> pointUnProject(const Vec3f& pos, const Affinef& modelMatrix, const Affinef& projMatrix, const int viewport[4]) {
	Vec4f in(pos.x(), pos.y(), pos.z(), 1.0f);

	/* Map x and y from window coordinates */
	in(0) = (in(0) - viewport[0]) / viewport[2];
	in(1) = (in(1) - viewport[1]) / viewport[3];

	/* Map to range -1 to 1 */
	for (u_int i = 0; i < 3; ++i) {
		in(i) = in(i) * 2.0f - 1.0f;
	}

	// 座標に逆行列を掛けて完成
	Affinef finalMatrix =  projMatrix * modelMatrix;
	Vec4f out = finalMatrix.inverse() * in;
	if (out.w() == 0.0f) {
    return std::make_pair(false, Vec3f());
  }

	return std::make_pair(true,
                        Vec3f(out.x() / out.w(), out.y() / out.w(), out.z() / out.w()));
}

}

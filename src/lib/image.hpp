#pragma once

//
// stb_imageでの画像読み込み
//

#include <stb_image.h>
#include <string>
#include <vector>
#include "defines.hpp"


class Image {
	int type_;

  bool grayscale_;
  bool alpha_;
  
	int width_;
	int height_;

  std::vector<u_char> image_;


public:
  Image(const std::string& path);

  bool isGrayscale() const;
  bool hasAlpha() const;

  int width() const;
  int height() const;

  // ピクセルデータ
  const u_char* image() const;
  
};

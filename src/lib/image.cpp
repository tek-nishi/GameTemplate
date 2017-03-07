//
// stb_imageでの画像読み込み
//

#define STB_IMAGE_IMPLEMENTATION
#include "image.hpp"
#include <iostream>


Image::Image(const std::string& path) {
  int comp;
  unsigned char *data = stbi_load(path.c_str(), &width_, &height_, &comp, 0);

  // comp  1 grey
  //       2 grey, alpha
  //       3 red, green, blue
  //       4 red, green, blue, alpha
  grayscale_ = (comp == 1) || (comp == 2);
  alpha_ = (comp == 2) || (comp == 4);

  image_ = std::vector<u_char>(data, data + width_ * height_ * comp);

  DOUT << "image:" << width_ << "x" << height_ << " " << comp << "ch." << std::endl;
  
  stbi_image_free(data);
}

bool Image::isGrayscale() const {
  return grayscale_;
}

bool Image::hasAlpha() const {
  return alpha_;
}

int Image::width() const {
  return width_;
}

int Image::height() const {
  return height_;
}

  // ピクセルデータ
const u_char* Image::image() const {
  return &image_[0];
}

#pragma once

//
// テクスチャ管理
//
// NOTICE:コピーしても、新たなリソースを確保しないようになっています
// TODO:Textureの細かな設定
// 

#include "defines.hpp"
#include "glTexture.hpp"
#include <string>
#include <memory>


class Texture {
  std::shared_ptr<GlTexture> gl_texture_;

  int width_;
  int height_;

	
public:
  Texture();
  
	explicit Texture(const std::string& filename);

  // サイズを返す
  int width() const;
  int height() const;

  // OpenGLのコンテキストに拘束する
	void bind() const;

  // 拘束を解除
	void unbind() const;

  // 画素のフィルタリングを有効にする
  // TIPS:無効にすると拡大時にぼんやりした絵にならない
  void enableFilter(bool filtering);


private:
  // テクスチャの基本的なパラメーター設定を行う
  static void setupParam();
  
	void setupImage(const std::string& filename);
  
};

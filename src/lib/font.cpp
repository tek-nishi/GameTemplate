//
// フォント
//

#define FONTSTASH_IMPLEMENTATION
#include <cstdio>
#include <iostream>
#include "font.hpp"


int Font::create(void* userPtr, int width, int height) {
  Context* gl = (Context*)userPtr;

  gl->tex    = std::make_shared<GlTexture>();
  gl->width  = width;
  gl->height = height;

  gl->tex->bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, gl->width, gl->height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  return 1;
}

int Font::resize(void* userPtr, int width, int height) {

  return create(userPtr, width, height);
}

void Font::update(void* userPtr, int* rect, const unsigned char* data) {
  Context* gl = (Context*)userPtr;
  if (!gl->tex) return;

  int w = rect[2] - rect[0];
  int h = rect[3] - rect[1];

  gl->tex->bind();

  glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, gl->width);
  glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect[0]);
  glPixelStorei(GL_UNPACK_SKIP_ROWS, rect[1]);
  glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1], w, h, GL_ALPHA,GL_UNSIGNED_BYTE, data);
  glPopClientAttrib();
}

void Font::draw(void* userPtr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts) {
  Context* gl = (Context*)userPtr;
  if (!gl->tex) return;

  gl->tex->bind();

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(2, GL_FLOAT, sizeof(float) * 2, verts);
  glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 2, tcoords);
  glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(unsigned int), colors);

  glDrawArrays(GL_TRIANGLES, 0, nverts);

  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}


// コンストラクタ
// font_path フォントファイル(ttf,otf)
Font::Font(const std::string& path) {
  FONSparams params;

  memset(&params, 0, sizeof(params));
  params.width  = 1024;
  params.height = 1024;
  params.flags  = (unsigned char)FONS_ZERO_BOTTOMLEFT;

  params.renderCreate = Font::create;
  params.renderResize = Font::resize;
  params.renderUpdate = Font::update;
  params.renderDraw   = Font::draw;
  params.renderDelete = nullptr;

  params.userPtr = &gl_;

  context_ = fonsCreateInternal(&params);

  fonsClearState(context_);
  int handle = fonsAddFont(context_, "font", path.c_str());
  fonsSetFont(context_, handle);
  fonsSetSize(context_, DEFAULT_SIZE);
  // TIPS:下揃えにしておくと、下にはみ出す部分も正しく扱える
  fonsSetAlign(context_, FONS_ALIGN_BOTTOM);

  DOUT << "Font(" << path << ")" << std::endl;
}


// フォントサイズ指定
void Font::size(const int size) {
  fonsSetSize(context_, size);
}

// 描画した時のサイズを取得
Vec2f Font::drawSize(const std::string& text) {
  float bounds[4];
  fonsTextBounds(context_, 0, 0, text.c_str(), nullptr, bounds);

  return Vec2f{ bounds[2], bounds[3] };
}

// 描画
// text  表示文字列
// pos   表示位置
// color 表示色
void Font::draw(const std::string& text, const Vec2f& pos, const Color& color) {
  fonsSetColor(context_, color.rgba());
  fonsDrawText(context_, pos.x, pos.y, text.c_str(), nullptr);
}

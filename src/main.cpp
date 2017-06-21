//
// アプリ雛形
//
// VisualStudioでもコンパイルできるようにするため
// ソースコードをUTF-8(BOM付き)で用意:D
//

// Frameworkの全てをインクルード
#include "lib/framework.hpp"


// アプリのウインドウサイズ
enum Size {
  WIDTH  = 800,
  HEIGHT = 600
};

//
// メインプログラム
//
int main() {
  // アプリウインドウを生成
  // GLFWとOpenGLの初期化
  // TIPS:色々な型が依存しているので、最初に生成する事
  AppEnv env(Size::WIDTH, Size::HEIGHT);

  while (env.isOpen()) {
    // 開始
    env.begin();

    //
    // ここにアプリの処理を書く
    //

    // 終了
    env.end();
  }
}

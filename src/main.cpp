//
// アプリ雛形
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
  WIDTH = 800,
  HEIGHT = 600
};

bool On_Mouse(float x, float y, float width, float height,
  Vec2f mouse_pos) {
  if (mouse_pos.x() > x) {
    if (mouse_pos.x() < (x + width)) {
      if (mouse_pos.y() > y) {
        if (mouse_pos.y() < (y + height)) {
          return true;
        }
      }
    }
  }
  return false;
}

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
    false, true);
  while (1){
    // タイトル画面
    {
      Texture title_logo("res/title_logo.png");
      Texture title_push("res/title_push2.png");
      Texture back0("res/back0.png");

      // 演出用変数
      int blink = 0;

      while (1) {
        // アプリウインドウが閉じられたらプログラムを終了
        if (!app_env.isOpen()) return 0;

        // 進行や終了の処理
        if (app_env.isPushButton(Mouse::LEFT))	break;
        if (app_env.isPushKey(GLFW_KEY_ENTER)) break;
        if (app_env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

        // 描画準備
        app_env.setupDraw();

        // 描画
        // 背景
        drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
          0, 0, 512, 256,
          back0,
          Color(1, 1, 1));
        // タイトル名
        drawTextureBox((-Window::WIDTH / 2) + (Window::WIDTH - 520) / 2, Window::HEIGHT / 4, 520, 80,
          0, 0, 485, 75,
          title_logo,
          Color(1, 1, 1));

        // 「PUSH ENTER」を表示
        blink += 1;
        int value = (blink / 30) % 2;
        if (value) {
          drawTextureBox((-Window::WIDTH / 2) + (Window::WIDTH - 500) / 2, -Window::HEIGHT / 4, 500, 80,
            0, 0, 450, 70,
            title_push,
            Color(1, 1, 1));
        }

        // 画面更新
        app_env.update();
      }
      // フラッシュの更新
      app_env.flushInput();
    }

    // 読み込み待ち画面
  {
    Texture load("res/load.png");

    // 描画準備
    app_env.setupDraw();

    drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, 800, 600,
      0, 0, 512, 512,
      load,
      Color(1, 1, 1));

    // 画面更新
    app_env.update();
  }

  // 本編
  {
    Texture back0("res/back0.png");
    Texture back1("res/back1.png");
    Texture back2("res/back2.png");
    Texture back3("res/back3.png");
    Texture back4("res/back4.png");
    Texture back5("res/back5.png");
    Texture back6("res/back6.png");
    Texture back7("res/back7.png");
    Texture back8("res/back8.png");
    Texture back9("res/back9.png");
    Texture back10("res/back10.png");
    Texture back11("res/back11.png");
    Texture back12("res/back12.png");
    Texture back13("res/back13.png");
    Texture back14("res/back14.png");
    Texture back15("res/back15.png");
    Texture back16("res/back16.png");
    Texture back17("res/back17.png");
    Texture back18("res/back18.png");
    Texture back19("res/back19.png");
    Texture back20("res/back20.png");
    Texture back21("res/back21.png");
    Texture back22("res/back22.png");
    Texture back23("res/back23.png");
    Texture back24("res/back24.png");
    Texture back25("res/back25.png");
    Texture item("res/item.png");
    Texture heartkey("res/heartkey.png");
    Texture daiyakey("res/daiyakey.png");
    Texture spadekey("res/spadekey.png");
    Texture clubkey("res/clubkey.png");
    Texture starkey("res/starkey.png");
    Texture chair_leg("res/leg.png");
    Texture driver("res/driver.png");
    Texture coin("res/coin.png");
    Texture sikake("res/sikake.png");
    Texture hint_paper("res/paper.png");
    //Texture hint_paper2("res/paper2.png");
    //Texture hint_paper3("res/paper3.png");
    //Texture hint_paper4("res/paper4.png");
    Media item_get("res/item_get.wav");
    Media gaku_move("res/gaku_move.wav");

    // 背景の表示位置
    float x = (-Window::WIDTH / 2);
    float y = (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4);

    // アイテム関連変数
    int draw_switch = 0;
    int draw_switch2 = 0;
    int coin_switch = 0;
    int coin_switch2 = 0;
    int driver_switch = 0;
    int leg_switch = 0;
    int key_spade_switch = 0;
    int key_heart_switch = 0;
    int key_club_switch = 0;
    int key_daiya_switch = 0;
    int key_star_switch = 0;
    int fire_switch = 0;
    int gaku_leftup = 0;
    int gaku_leftdown = 0;
    int gaku_rightup = 0;
    int gaku_rightdown = 0;
    int gaku_ok = 0;
    bool get_coin = false;
    bool get_driver = false;
    bool get_leg = false;
    bool get_paper = false;
    bool get_paper2 = false;
    bool get_paper3 = false;
    bool get_paper4 = false;
    bool get_key_spade = false;
    bool get_key_heart = false;
    bool get_key_club = false;
    bool get_key_daiya = false;
    bool get_key_star = false;
    bool delete_club = false;
    bool delete_heart = false;
    bool delete_daiya = false;
    bool delete_spade = false;

    // 背景の切り替え変数
    bool zoom = false;

    // 脱出用変数
    bool exit = false;

    while (1) {
      // アプリウインドウが閉じられたらプログラムを終了
      if (!app_env.isOpen()) return 0;

      // 描画準備
      app_env.setupDraw();

      // マウスの位置の取得
      Vec2f Mouse_pos = app_env.mousePosition();

      // デバッグ
      if (app_env.isPushButton(Mouse::RIGHT)){
        get_key_star = true;
      }

      // 背景の表示
      bool on_under_box = On_Mouse(-Window::WIDTH / 2 + 25, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
        Window::WIDTH, 25, Mouse_pos);

      // スイッチ０
      bool zihanki = On_Mouse(-217, -45,
        494, 209, Mouse_pos);

      bool in_coin = On_Mouse(264, -147,
        40, 34, Mouse_pos);

      bool clock = On_Mouse(-230, 172,
        42, 33, Mouse_pos);

      bool clock_on = On_Mouse(-102, -64,
        274, 235, Mouse_pos);

      bool dustbox = On_Mouse(-257, -34,
        47, 68, Mouse_pos);

      bool zihanki_under = On_Mouse(-144, -60,
        423, 14, Mouse_pos);

      bool item_on4 = On_Mouse(0, 150,
        64, 64, Mouse_pos);

      bool wallpaper = On_Mouse(288, 66,
        42, 85, Mouse_pos);

      bool on_fire = On_Mouse(-269, 57,
        503, 128, Mouse_pos);

      bool kankisen = On_Mouse(254, 278,
        61, 16, Mouse_pos);

      bool item_on2 = On_Mouse(-59, 89,
        55, 78, Mouse_pos);

      bool on_club = On_Mouse(25, 83,
        40, 40, Mouse_pos);

      bool on_spade = On_Mouse(147, 80,
        40, 40, Mouse_pos);

      bool on_heart = On_Mouse(-228, 87,
        40, 40, Mouse_pos);

      bool on_daiya = On_Mouse(-112, 84,
        40, 40, Mouse_pos);

      // スイッチ１
      bool tv = On_Mouse(-12, -42,
        317, 240, Mouse_pos);

      bool sixfour = On_Mouse(-145, 54,
        73, 31, Mouse_pos);

      bool gaku = On_Mouse(-275, 197,
        34, 35, Mouse_pos);

      bool gaku_left_up = On_Mouse(-165, 187,
        88, 70, Mouse_pos);

      bool gaku_right_up = On_Mouse(106, 171,
        109, 96, Mouse_pos);

      bool gaku_left_down = On_Mouse(-195, -129,
        94, 86, Mouse_pos);

      bool gaku_right_down = On_Mouse(110, -137,
        103, 144, Mouse_pos);

      bool item_on3 = On_Mouse(-38, 13,
        121, 104, Mouse_pos);

      bool tv_under = On_Mouse(-21, -59,
        151, 18, Mouse_pos);

      bool chair_iron = On_Mouse(-356, -138,
        108, 82, Mouse_pos);

      bool chair_wood = On_Mouse(-188, -161,
        170, 135, Mouse_pos);

      bool chair_wood_leg = On_Mouse(-84, -50,
        91, 178, Mouse_pos);

      // スイッチ２
      bool hondana_wood = On_Mouse(-371, 103,
        243, 107, Mouse_pos);

      // スイッチ３
      bool blind = On_Mouse(-264, 67,
        372, 207, Mouse_pos);

      bool blind_on = On_Mouse(-361, -103,
        364, 365, Mouse_pos);

      bool item_on5 = On_Mouse(4, -69,
        84, 18, Mouse_pos);

      bool bed_under = On_Mouse(-362, -113,
        228, 19, Mouse_pos);

      // スイッチ４
      bool poster = On_Mouse(-268, 32,
        107, 131, Mouse_pos);

      bool poster_on = On_Mouse(37, -60,
        254, 310, Mouse_pos);

      bool item_on = On_Mouse(131, 39,
        74, 68, Mouse_pos);

      // スイッチ５
      bool hondana_iron = On_Mouse(-71, -5,
        218, 109, Mouse_pos);

      bool hondana_wood2 = On_Mouse(143, -12,
        97, 51, Mouse_pos);

      bool door_open = On_Mouse(238, -2,
        58, 201, Mouse_pos);

      // アイテム関連
      bool leg = On_Mouse(-85, -45,
        72, 172, Mouse_pos);

      bool leg_hint = On_Mouse(-280, -169,
        46, 168, Mouse_pos);

      bool paper = On_Mouse(39, -61,
        253, 307, Mouse_pos);

      bool use_heartkey = On_Mouse(-266, -300,
        133, 60, Mouse_pos);

      bool use_daiyakey = On_Mouse(-266, -240,
        133, 60, Mouse_pos);

      bool use_clubkey = On_Mouse(-400, -240,
        133, 60, Mouse_pos);

      bool use_spadekey = On_Mouse(-400, -300,
        133, 60, Mouse_pos);

      bool use_starkey = On_Mouse(-133, -240,
        133, 60, Mouse_pos);

      bool use_chair_leg = On_Mouse(-133, -300,
        133, 60, Mouse_pos);

      bool use_coin = On_Mouse(0, -240,
        133, 60, Mouse_pos);

      bool use_driver = On_Mouse(0, -300,
        133, 60, Mouse_pos);

      bool use_paper = On_Mouse(133, -240,
        133, 60, Mouse_pos);

      bool use_paper2 = On_Mouse(133, -300,
        133, 60, Mouse_pos);

      bool use_paper3 = On_Mouse(266, -240,
        133, 60, Mouse_pos);

      bool use_paper4 = On_Mouse(266, -300,
        133, 60, Mouse_pos);

      // クリックの判定
      bool Click = false;
      if (app_env.isPushButton(Mouse::LEFT)) {
        Click = true;
        // std::cout << Mouse_pos << std::endl;
        // フラッシュの更新
        app_env.flushInput();
      }


      /* スイッチ１　１～５　標準時の背景

       スイッチ２
       １　自販機
       ２　時計
       ３　ゴミ箱
       ４　自販機下
       ５　壁紙らしき物（ＦＩＲＥ）
       ６　ＴＶ
       ７　６４
       ８　額縁
       ９　ＴＶ下
       １０　鉄椅子
       １１　木椅子
       １２　木本棚
       １３　ブラインド
       １４　ベッド下
       １５　ポスター
       １６　鉄本棚
       １７　木本棚２
       １８　換気扇
       */
      // 未拡大時背景
      if (!zoom) {
        switch (draw_switch) {
        case 0:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back0,
            Color(1, 1, 1));
          if (Click) {
            if (zihanki) {
              draw_switch2 = 1;
              zoom = true;
            }
            if (clock) {
              draw_switch2 = 2;
              zoom = true;
            }
            if (dustbox) {
              draw_switch2 = 3;
              zoom = true;
            }
            if (zihanki_under) {
              draw_switch2 = 4;
              zoom = true;
            }
            if (wallpaper) {
              draw_switch2 = 5;
              zoom = true;
            }
            if (kankisen){
              draw_switch2 = 18;
              zoom = true;
            }
          }
          break;

        case 1:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back1,
            Color(1, 1, 1));
          if (Click){
            if (tv){
              draw_switch2 = 6;
              zoom = true;
            }
            if (sixfour){
              draw_switch2 = 7;
              zoom = true;
            }
            if (gaku){
              draw_switch2 = 8;
              zoom = true;
            }
            if (tv_under){
              draw_switch2 = 9;
              zoom = true;
            }
            if (chair_iron){
              draw_switch2 = 10;
              zoom = true;
            }
            if (chair_wood){
              draw_switch2 = 11;
              zoom = true;
            }
          }
          break;

        case 2:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back2,
            Color(1, 1, 1));
          if (Click){
            if (hondana_wood){
              draw_switch2 = 12;
              zoom = true;
            }
          }
          break;

        case 3:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back3,
            Color(1, 1, 1));
          if (Click){
            if (blind){
              draw_switch2 = 13;
              zoom = true;
            }
            if (bed_under){
              draw_switch2 = 14;
              zoom = true;
            }
          }
          break;

        case 4:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back4,
            Color(1, 1, 1));
          if (Click){
            if (poster){
              draw_switch2 = 15;
              zoom = true;
            }
          }
          break;

        case 5:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back5,
            Color(1, 1, 1));
          if (Click){
            if (hondana_iron){
              draw_switch2 = 16;
              zoom = true;
            }
            if (hondana_wood2){
              draw_switch2 = 17;
              zoom = true;
            }
            if (door_open && get_key_star && key_star_switch){
              exit = true;
            }
          }
          break;

        default:
          break;
          // do not
        }
      }
      if (exit){
        break;
      }
      // 拡大画面
      else {
        switch (draw_switch2) {
        case 0:
          switch (draw_switch) {
          case 0:
            drawTextureBox(x, y,
              800, 600 - Window::HEIGHT / 5,
              0, 0, 512, 256,
              back0,
              Color(1, 1, 1));
            break;

          case 1:
            drawTextureBox(x, y,
              800, 600 - Window::HEIGHT / 5,
              0, 0, 512, 256,
              back1,
              Color(1, 1, 1));
            break;

          case 2:
            drawTextureBox(x, y,
              800, 600 - Window::HEIGHT / 5,
              0, 0, 512, 256,
              back2,
              Color(1, 1, 1));
            break;

          case 3:
            drawTextureBox(x, y,
              800, 600 - Window::HEIGHT / 5,
              0, 0, 512, 256,
              back3,
              Color(1, 1, 1));
            break;

          case 4:
            drawTextureBox(x, y,
              800, 600 - Window::HEIGHT / 5,
              0, 0, 512, 256,
              back4,
              Color(1, 1, 1));
            break;

          case 5:
            drawTextureBox(x, y,
              800, 600 - Window::HEIGHT / 5,
              0, 0, 512, 256,
              back5,
              Color(1, 1, 1));
            break;

          default:
            break;
            // do not
          }
          break;

        case 1:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back14,
            Color(1, 1, 1));
          if (!coin_switch2 && get_coin && in_coin && Click){
            item_get.play();
            draw_switch2 = 24;
          }
          break;

        case 2:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back16,
            Color(1, 1, 1));
          if (Click && clock_on && get_driver && driver_switch && !get_key_spade){
            item_get.play();
            get_key_spade = true;
          }
          break;

        case 3:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back15,
            Color(1, 1, 1));
          break;

        case 4:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back19,
            Color(1, 1, 1));
          if (!get_coin && !coin_switch2){
            drawTextureBox(0, 150,
              64, 64,
              0, 0, 64, 64,
              item,
              Color(1, 1, 1, 0.4));
          }
          if (item_on4 && leg_switch && get_leg && Click && !coin_switch2){
            item_get.play();
            draw_switch2 = 23;
          }
          break;

        case 5:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back25,
            Color(1, 1, 1));
          if (Click && on_fire){
            fire_switch = 1;
          }
          if (fire_switch){
            drawTextureBox(-269, 57,
              503, 150,
              0, 0, 512, 256,
              sikake,
              Color(1, 1, 1));
            if (!delete_heart){
              drawTextureBox(-228, 87,
                40, 40,
                0, 0, 64, 64,
                item,
                Color(1, 1, 1));
            }
            if (!delete_daiya){
              drawTextureBox(-112, 84,
                40, 40,
                0, 0, 64, 64,
                item,
                Color(1, 1, 1));
            }
            if (!delete_club){
              drawTextureBox(25, 83,
                40, 40,
                0, 0, 64, 64,
                item,
                Color(1, 1, 1));
            }
            if (!delete_spade){
              drawTextureBox(147, 80,
                40, 40,
                0, 0, 64, 64,
                item,
                Color(1, 1, 1));
            }
          }
          if (get_key_club && key_club_switch && on_club && Click){
            delete_club = true;
          }
          if (get_key_heart && key_heart_switch && on_heart && Click){
            delete_heart = true;
          }
          if (get_key_daiya && key_daiya_switch && on_daiya && Click){
            delete_daiya = true;
          }
          if (get_key_spade && key_spade_switch && on_spade && Click){
            delete_spade = true;
          }
          if (delete_spade && delete_daiya && delete_club && delete_heart && !get_key_star){
            item_get.play();
            get_key_star = true;
          }
          break;

        case 6:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back10,
            Color(1, 1, 1));
          break;

        case 7:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back11,
            Color(1, 1, 1));
          break;

        case 8:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back12,
            Color(1, 1, 1));
          // 額の仕掛けクリック順番
          if (Click){
            if (gaku_leftup == 0 && gaku_leftdown == 0 && gaku_rightup == 0 && gaku_rightdown == 0 && gaku_left_up){
              gaku_leftup += 1;
              gaku_move.play();
            }
            else if (gaku_leftup == 1 && gaku_leftdown == 1 && gaku_rightup == 2 && gaku_rightdown == 1 && gaku_left_up){
              gaku_leftup += 1;
              gaku_move.play();
            }
            else if (gaku_leftup == 1 && gaku_leftdown == 0 && gaku_rightup == 2 && gaku_rightdown == 1 && gaku_left_down){
              gaku_leftdown += 1;
              gaku_move.play();
            }
            else if (gaku_leftup == 1 && gaku_leftdown == 0 && gaku_rightup == 0 && gaku_rightdown == 1 && gaku_right_up){
              gaku_rightup += 1;
              gaku_move.play();
            }
            else if (gaku_leftup == 1 && gaku_leftdown == 0 && gaku_rightup == 1 && gaku_rightdown == 1 && gaku_right_up){
              gaku_rightup += 1;
              gaku_move.play();
            }
            else if (gaku_leftup == 1 && gaku_leftdown == 0 && gaku_rightup == 0 && gaku_rightdown == 0 && gaku_right_down){
              gaku_rightdown += 1;
              gaku_move.play();
            }
            else if (gaku_left_up || gaku_left_down || gaku_right_up || gaku_right_down){
              gaku_leftup = 0;
              gaku_leftdown = 0;
              gaku_rightup = 0;
              gaku_rightdown = 0;
              gaku_move.play();
            }
            if (gaku_leftup == 2 && gaku_leftdown == 1 && gaku_rightup == 2 && gaku_rightdown == 1){
              gaku_ok = 1;
            }
          }
          if (gaku_ok && !get_key_daiya){
            drawTextureBox(-38, 13,
              121, 104,
              0, 0, 64, 64,
              item,
              Color(1, 1, 1));
          }
          if (Click && item_on3 && gaku_ok){
            item_get.play();
            get_key_daiya = true;
          }
          break;

        case 9:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back20,
            Color(1, 1, 1));
          break;

        case 10:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back23,
            Color(1, 1, 1));
          break;

        case 11:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back24,
            Color(1, 1, 1));
          if (Click){
            if (chair_wood_leg && !get_leg){
              item_get.play();
              get_leg = true;
            }
          }
          break;

        case 12:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back9,
            Color(1, 1, 1));
          break;

        case 13:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back7,
            Color(1, 1, 1));
          if (Click){
            if (blind_on){
              draw_switch2 = 19;
            }
          }
          break;

        case 14:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back21,
            Color(1, 1, 1));
          break;

        case 15:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back6,
            Color(1, 1, 1));
          if (Click){
            if (poster_on && !get_paper){
              draw_switch2 = 20;
            }
          }
          break;

        case 16:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back18,
            Color(1, 1, 1));
          break;

        case 17:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back17,
            Color(1, 1, 1));
          break;

        case 18:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back22,
            Color(1, 1, 1));
          if (!get_key_club){
            drawTextureBox(-59, 89,
              55, 78,
              0, 0, 64, 64,
              item,
              Color(1, 1, 1));
          }
          if (Click){
            if (item_on2 && !get_key_club){
              item_get.play();
              draw_switch2 = 21;
            }
          }
          break;

        case 19:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back8,
            Color(1, 1, 1));
          if (!get_driver){
            drawTextureBox(4, -69,
              84, 18,
              0, 0, 64, 64,
              item,
              Color(1, 1, 1));
          }
          if (Click){
            if (item_on5 && !get_driver){
              item_get.play();
              draw_switch2 = 22;
            }
          }
          break;

        case 20:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back6,
            Color(1, 1, 1));
          drawTextureBox(131, 39,
            74, 68,
            0, 0, 64, 64,
            item,
            Color(1, 1, 1));
          if (Click){
            if (item_on && !get_paper){
              item_get.play();
              draw_switch2 = 15;
              get_paper = true;
            }
          }
          break;

        case 21:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back22,
            Color(1, 1, 1));
          get_key_club = true;
          break;

        case 22:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back8,
            Color(1, 1, 1));
          get_driver = true;
          break;

        case 23:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back19,
            Color(1, 1, 1));
          if (!coin_switch2){
            get_coin = true;
          }
          break;

        case 24:
          drawTextureBox(x, y,
            800, 600 - Window::HEIGHT / 5,
            0, 0, 512, 256,
            back14,
            Color(1, 1, 1));
          get_coin = false;
          get_key_heart = true;
          coin_switch2 = 1;
          break;

        default:
          break;
          // do not
        }
        if (Click && on_under_box) {
          zoom = false;
          draw_switch2 = 0;
          Click = false;
        }
      }

      // アイテム欄の色を変える
      drawFillBox(-Window::WIDTH / 2, -Window::HEIGHT / 2,
        Window::WIDTH, Window::HEIGHT / 5,
        Color(0, 0, 0));

      // アイテム欄の座標
      float item_box_x = -Window::WIDTH / 2 + 1;
      float item_box_y = -Window::HEIGHT / 2;

      // アイテム欄のコマ分け
      drawBox(item_box_x, item_box_y + (Window::HEIGHT / 5 - 1),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x, item_box_y + (Window::HEIGHT / 5 - 1) - (Window::HEIGHT / 10),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6), item_box_y + (Window::HEIGHT / 5 - 1),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6), item_box_y + (Window::HEIGHT / 5 - 1) - (Window::HEIGHT / 10),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 2), item_box_y + (Window::HEIGHT / 5 - 1),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 2), item_box_y + (Window::HEIGHT / 5 - 1) - (Window::HEIGHT / 10),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 3), item_box_y + (Window::HEIGHT / 5 - 1),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 3), item_box_y + (Window::HEIGHT / 5 - 1) - (Window::HEIGHT / 10),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 4), item_box_y + (Window::HEIGHT / 5 - 1),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 4), item_box_y + (Window::HEIGHT / 5 - 1) - (Window::HEIGHT / 10),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 5), item_box_y + (Window::HEIGHT / 5 - 1),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      drawBox(item_box_x + (Window::WIDTH / 6 * 5), item_box_y + (Window::HEIGHT / 5 - 1) - (Window::HEIGHT / 10),
        Window::WIDTH / 6, -Window::HEIGHT / 10,
        2,
        Color(1, 0, 0));

      // 左右への移動のマーク
      if (!zoom){
        drawFillBox(-Window::WIDTH / 2, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
          25, Window::HEIGHT - Window::HEIGHT / 5,
          Color(0.5, 0.5, 1, 0.5));

        drawFillBox(Window::WIDTH / 2 - 25, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
          25, Window::HEIGHT - Window::HEIGHT / 5,
          Color(0.5, 0.5, 1, 0.5));
      }
      // 画面を引く
      if (zoom){
        drawFillBox(-Window::WIDTH / 2, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
          Window::WIDTH, 25,
          Color(0.5, 1, 0.5, 0.7));
      }
      if (on_under_box && zoom){
        drawFillBox(-Window::WIDTH / 2, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
          Window::WIDTH, 25,
          Color(0.2, 1, 0.2, 0.7));
      }

      // マークの上でクリックしたら左右に画面を移動
      // 左に移動
      bool on_left_box = On_Mouse(-Window::WIDTH / 2, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
        25, Window::HEIGHT - Window::HEIGHT / 5, Mouse_pos);
      // マウスカーソルが上に乗ったら変化
      if (on_left_box && !zoom) {
        drawFillBox(-Window::WIDTH / 2, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
          25, Window::HEIGHT - Window::HEIGHT / 5,
          Color(0.2, 0.2, 1, 0.5));
        // クリックしたら画面切り替え
        if (Click && !zoom) {
          draw_switch -= 1;
          Click = false;
          if (draw_switch < 0) {
            draw_switch = 5;
          }
        }
      }
      // 右に移動
      bool on_right_box = On_Mouse(Window::WIDTH / 2 - 25, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
        25, Window::HEIGHT - Window::HEIGHT / 5, Mouse_pos);
      // マウスカーソルが上に乗ったら変化
      if (on_right_box && !zoom) {
        drawFillBox(Window::WIDTH / 2 - 25, (Window::HEIGHT / 2) - (Window::HEIGHT / 5 * 4),
          25, Window::HEIGHT - Window::HEIGHT / 5,
          Color(0.2, 0.2, 1, 0.5));
        // クリックしたら画面切り替え
        if (Click && !zoom) {
          draw_switch += 1;
          Click = false;
          if (draw_switch > 5) {
            draw_switch = 0;
          }
        }
      }
      Color Icon;

      // アイテムの使用
      if (Click){
        if (use_clubkey && get_key_club){
          Icon = Color(0, 0, 1, 0.8);
          key_club_switch = true;
        }
        else{
          Icon = Color(0, 0, 0, 1);
        }
        drawFillBox(-399, -240, 133, 58, Icon);
        if (use_spadekey && get_key_spade){
          drawFillBox(-399, -300, 133, 58, Color(0, 0, 1, 0.8));
          key_spade_switch = true;
        }
        if (use_daiyakey && get_key_daiya){
          drawFillBox(-266, -240, 133, 58, Color(0, 0, 1, 0.8));
          key_daiya_switch = true;
        }
        if (use_heartkey && get_key_heart){
          drawFillBox(-266, -300, 133, 58, Color(0, 0, 1, 0.8));
          key_heart_switch = true;
        }
        if (use_starkey && get_key_star){
          drawFillBox(-133, -240, 133, 58, Color(0, 0, 1, 0.8));
          key_star_switch = true;
        }
        if (use_chair_leg && get_leg){
          Icon = Color(0, 0, 1, 0.8);
          leg_switch = true;
        }
        else{
          Icon = Color(0, 0, 0, 1);
        }
        drawFillBox(-133, -300, 133, 58, Icon);
        if (use_coin && get_coin){
          drawFillBox(0, -240, 133, 58, Color(0, 0, 1, 0.8));
          coin_switch = true;
        }
        if (use_driver && get_driver){
          drawFillBox(0, -300, 133, 58, Color(0, 0, 1, 0.8));
          driver_switch = true;
        }
        /*
        if (use_paper){
        }
        if (use_paper2){
        }
        if (use_paper3){
        }
        if (use_paper4){
        }
        */
      }

      // アイテム表示
      if (get_key_club){
        drawTextureBox(-390, -230,
          120, 60,
          0, 0, 512, 256,
          clubkey,
          Color(1, 1, 1));
      }
      if (get_key_daiya){
        drawTextureBox(-257, -230,
          120, 60,
          0, 0, 512, 256,
          daiyakey,
          Color(1, 1, 1));
      }
      if (get_key_heart){
        drawTextureBox(-257, -290,
          120, 60,
          0, 0, 512, 256,
          heartkey,
          Color(1, 1, 1));
      }
      if (get_key_spade){
        drawTextureBox(-390, -290,
          120, 60,
          0, 0, 512, 256,
          spadekey,
          Color(1, 1, 1));
      }
      if (get_key_star){
        drawTextureBox(-124, -230,
          140, 60,
          0, 0, 512, 256,
          starkey,
          Color(1, 1, 1));
      }
      if (get_leg){
        drawTextureBox(-124, -290,
          150, 60,
          0, 0, 512, 256,
          chair_leg,
          Color(1, 1, 1));
      }
      if (get_coin){
        drawTextureBox(50, -230,
          120, 60,
          0, 0, 512, 256,
          coin,
          Color(1, 1, 1));
      }
      if (get_driver){
        drawTextureBox(3, -295,
          150, 60,
          0, 0, 512, 256,
          driver,
          Color(1, 1, 1));
      }
      if (get_paper){
        drawTextureBox(140, -235,
          120, 50,
          0, 0, 512, 256,
          hint_paper,
          Color(1, 1, 1));
      }
      /*if (get_paper2){
      drawTextureBox(136, -290,
      150, 60,
      0, 0, 512, 256,
      hint_paper2,
      Color(1, 1, 1));
      }
      if (get_paper3){
      drawTextureBox(269, -230,
      150, 60,
      0, 0, 512, 256,
      hint_paper3,
      Color(1, 1, 1));
      }
      if (get_paper4){
      drawTextureBox(269, -290,
      150, 60,
      0, 0, 512, 256,
      hint_paper4,
      Color(1, 1, 1));
      }*/

      // 画面更新
      app_env.update();
    }
  }

  // クリア画面
  {
    // 画像の読み込み
    Texture back5("res/back5.png");
    Texture clear("res/clear.png");

    // 背景の表示位置
    float x = (-Window::WIDTH / 2);
    float y = (-Window::HEIGHT / 2);

    while (1) {
      // アプリウインドウが閉じられたらプログラムを終了
      if (!app_env.isOpen()) return 0;

      // 進行や終了の処理
      if (app_env.isPushButton(Mouse::LEFT))	break;
      if (app_env.isPushKey(GLFW_KEY_ENTER)) break;
      if (app_env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

      // 描画準備
      app_env.setupDraw();

      // 描画
      // 背景
      drawTextureBox(x, y,
        800, 600,
        0, 0, 512, 256,
        back5,
        Color(1, 1, 1));
      // クリア
      drawTextureBox(-256, 150,
        512, 150,
        0, 0, 425, 50,
        clear,
        Color(1, 1, 1));
      // 画面更新
      app_env.update();
    }
  }
  app_env.flushInput();
  }
  // アプリ終了
}

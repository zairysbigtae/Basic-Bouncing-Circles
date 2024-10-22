#include <raylib.h>
#include "ball.hpp"
#include <vector>

int main() {
  const int screen_width = 680;
  const int screen_height = 480;
  int fps = 30;

  InitWindow(screen_width, screen_height, "Bouncing Balls Collision With Each Other");
  SetTargetFPS(fps);

  std::vector<Ball> balls;

  for(int i=0;i<5;i++) {
    balls.emplace_back(
      0,
      0,
      1,
      1,
      20,
      WHITE
    );
  }

  std::tuple<int, int> circle_center = std::make_tuple(
        screen_width - screen_width/2, screen_height - screen_height/2);
  float circle_radius = screen_width/48;

  while(!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    for(auto& ball : balls) {
      ball.draw();
      ball.update(std::make_tuple(std::get<0>(circle_center), std::get<1>(circle_center)), circle_radius);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
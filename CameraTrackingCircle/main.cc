#include <raylib.h>
#include "ball.hpp"
#include <vector>
#include <stdio.h>

int main() {
  const int screen_width = 680;
  const int screen_height = 480;

  InitWindow(screen_width, screen_height, "Camera Tracking Circle");
  SetTargetFPS(30);

  Camera2D camera = { 0 };
  camera.target = (Vector2){screen_width / 2 + 1000, screen_height / 2};
  camera.offset = (Vector2){screen_width / 2, screen_height / 2};
  camera.rotation = 45.0f;
  camera.zoom = 4.5f;

  std::vector<Ball> balls;
  std::vector<Color> colors = { BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA };

  for(int i = 0; i < 10; i++) {
    balls.emplace_back(
      GetRandomValue(0, screen_width),
      GetRandomValue(0, screen_height),
      10.0f,
      1.0f,
      1.0f,
      colors[GetRandomValue(0, colors.size() - 1)]
    );
  }

  std::tuple<int,int> circle_center = std::make_tuple(screen_width / 2, screen_height / 2);
  float circle_radius = 100.0f;
  float gravity = 0.2f;

  while(!WindowShouldClose()) {
    camera.target = (Vector2){balls[0].x + 5, balls[0].y + 5};

    printf("Camera target: (%f, %f)\n", camera.target.x, camera.target.y);
    printf("Camera offset: (%f, %f)\n", camera.offset.x, camera.offset.y);
    printf("Camera zoom: %f\n", camera.zoom);


    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);

    DrawCircle(std::get<0>(circle_center), std::get<1>(circle_center), circle_radius, WHITE);

    for(auto& ball : balls) {
      ball.draw();
      ball.update(std::make_tuple(std::get<0>(circle_center), std::get<1>(circle_center)), circle_radius, gravity);
    }
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
#pragma once
#include <raylib.h>
#include <tuple>

class Ball{
  public:
  float x, y, vx, vy, radius;
  Color color;

  Ball(float x, float y, float vx, float vy, float radius, Color color) : x(x), y(y), vx(vx), vy(vy), radius(radius), color(color) {};

  void update(std::tuple<float,float> zone, float &zoneRadius) {
    x += vx;
    y += vy;
  }

  void draw() {
    DrawCircle(x,y,radius,color);
  }
};
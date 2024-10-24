#pragma once
#include <raylib.h>
#include <tuple>
#include <cmath>

class Ball{
  public:
  float x, y, vx, vy, radius;
  Color color;

  Ball(float x, float y, float vx, float vy, float radius, Color color) : x(x), y(y), vx(vx), vy(vy), radius(radius), color(color) {};

  void update(std::tuple<float,float> zone, float &zoneRadius, float gravity) {
    x += vx;
    y += vy;

    float dx = std::get<0>(zone);
    float dy = std::get<1>(zone);
    float distance = std::sqrt(dx*dx+dy*dy);

    if(distance+radius > zoneRadius) {
      float normal_x = dx/distance;
      float normal_y = dy/distance;

      float dot_product = vx * normal_x + vy * normal_y;
      vx -= 2.f * dot_product * normal_x;
      vy -= 2.f * dot_product * normal_y;

      float overlap = distance - (zoneRadius - radius);
      x -= overlap * normal_x;
      y -= overlap * normal_y;
    }
  }

  void draw() {
    DrawCircle(x,y,radius,color);
  }
};
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
    vy += gravity;

    x += vx;
    y += vy;
  }

  bool checkCollision(Ball& other) {
    float dx = x - other.x;
    float dy = y - other.y;
    float distance = std::sqrt(dx*dx+dy*dy);

    return distance < radius + other.radius;
  }

  void resolveCollision(Ball& other) {
    float dx = x - other.x;
    float dy = y - other.y;
    float distance = std::sqrt(dx*dx+dy*dy);

    if(distance==0) return;

    float normal_x = dx/distance;
    float normal_y = dy/distance;

    // Calculate relative velocity
    float relative_x = vx - other.vx;
    float relative_y = vy - other.vy;

    float dot_product = vx * normal_x + vy * normal_y;
    if(dot_product > 0) return;

    float impulse = 2 * dot_product / (radius + other.radius);
    vx += impulse * normal_x/2;
    vy += impulse * normal_y/2;
    other.vx += impulse * normal_x/2;
    other.vy += impulse * normal_y/2;
  }

  void draw() {
    DrawCircle(x,y,radius,color);
  }
};
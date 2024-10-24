#pragma once
#include <raylib.h>
#include <tuple>
#include <cmath>
#include <iostream>

class Ball {
public:
  float x, y, vx, vy, radius;
  Color color;
  Sound ping_sfx;
  Sound ping_sfx2;

  Ball(float x, float y, float vx, float vy, float radius, Color color, Sound ping_sfx, Sound ping_sfx2)
      : x(x), y(y), vx(vx), vy(vy), radius(radius), color(color), ping_sfx(ping_sfx), ping_sfx2(ping_sfx2) {};


  void modify_velocity(float& vx, float&vy) {
      vx += 1.0f;
      vx *= -1.f;
      vy += 1.0f;
      vy *= -1.f;
  }

  void update(std::tuple<float, float> zone, float& zoneRadius, float gravity) {
      vy += gravity;

      x += vx;
      y += vy;

      float dx = x - std::get<0>(zone);
      float dy = y - std::get<1>(zone);
      float distance = std::sqrt(dx*dx+dy*dy);

      if (distance + radius > zoneRadius) {
          play_ping_sfx(ping_sfx, ping_sfx2);

          float normal_x = dx/distance;
          float normal_y = dy/distance;

          float dot_product = vx * normal_x + vy * normal_y;
          vx -= 2.f * dot_product * normal_x;
          vy -= 2.f * dot_product * normal_y;

          float overlap = distance - (zoneRadius - radius);
          x -= overlap * normal_x;
          y -= overlap * normal_y;

          zoneRadius *= 1.01f;
          radius *= 1.01f;
          std::cout << vx << vy << std::endl;
      }
  }

  void play_ping_sfx(Sound ping_sfx, Sound ping_sfx2) {
      if(!IsSoundPlaying(ping_sfx)) {
          PlaySound(ping_sfx);
      } else {
          PlaySound(ping_sfx2);
      }
  }

  void draw() {
      DrawCircle(x, y, radius, color);
  }
};

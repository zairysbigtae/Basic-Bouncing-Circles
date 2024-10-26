#pragma once
#include <raylib.h>
#include <tuple>
#include <cmath>
#include <chrono>
#include <thread>
#include <cstdio>

class Ball{
  public:
  float x, y, vx, vy, radius, cor, lastCorModificationTime;
  Color color;

  Ball(float x, float y, float vx, float vy, float radius, Color color) : x(x), y(y), vx(vx), vy(vy), radius(radius), cor(1.0f), color(color), lastCorModificationTime(0.0f) {};

  void update(std::tuple<float,float> zone, float &zoneRadius, float gravity) {
    vy += gravity;

    x += vx;
    y += vy;

    float dx = x - std::get<0>(zone);
    float dy = y - std::get<1>(zone);
    float distance = std::sqrt(dx*dx+dy*dy);

    if(distance+radius > zoneRadius) {
      // dx and dy are the components of the vector from the center of the ball to the center of the zone
      float normal_x = dx/distance;
      float normal_y = dy/distance;

      // dot_product is the projection of the velocity vector onto the normal vector
      // It is negative if the ball is moving towards the center of the zone
      // and positive if it is moving away from it
      float dot_product = vx * normal_x + vy * normal_y;
      vx -= 2.f * dot_product * normal_x;
      vy -= 2.f * dot_product * normal_y;
      
      // The 'overlap' variable calculates how much the ball has exceeded the boundary of the zone.
      // It is the difference between the current distance from the center of the zone to the edge of the ball
      // and the maximum allowed distance (zoneRadius - radius).
      // This value is used to adjust the position of the ball to prevent it from being inside the zone's boundary.
      float overlap = distance - (zoneRadius - radius);
      x -= overlap * normal_x;
      y -= overlap * normal_y;
    }
  }

  void checkCollisionBetweenEachCircles(Ball &other) {
    float dx = x - other.x - radius;
    float dy = y - other.y - radius;
    float distance = std::sqrt(dx*dx+dy*dy);

    if(distance < radius + other.radius) {
      // Calculate the collision normal and tangent
      float normalX = dx / distance;
      float normalY = dy / distance;
      float tangentX = -normalY;
      float tangentY = normalX;

      // Calculate the velocity of each circle along the collision normal and tangent
      float v1n = vx * normalX + vy * normalY;
      float v2n = other.vx * normalX + other.vy * normalY;
      float v1t = vx * tangentX + vy * tangentY;
      float v2t = other.vx * tangentX + other.vy * tangentY;

      // Update the velocities of the circles after the collision
      vx = (v1n * cor) * normalX + v1t * tangentX;
      vy = (v1n * cor) * normalY + v1t * tangentY;
      other.vx = (v2n * cor) * normalX + v2t * tangentX;
      other.vy = (v2n * cor) * normalY + v2t * tangentY;

      // Move the circles to the correct position after the collision
      x += (radius + other.radius - distance) * normalX;
      y += (radius + other.radius - distance) * normalY;
      other.x -= (radius + other.radius - distance) * normalX;
      other.y -= (radius + other.radius - distance) * normalY;

    }
    modifyCor(cor);
    seeCorValue(cor);
  }

  void modifyCor(float& cor) {
    float currentTime = GetTime();

    if(IsKeyDown(KEY_DOWN)) {
      if(currentTime - lastCorModificationTime >= .1f) {
        cor-=0.01f;
        lastCorModificationTime = currentTime;
      }
    } 
    
    else if(IsKeyDown(KEY_UP)) {
      if(currentTime - lastCorModificationTime >= .1f) {
        cor+=0.01f;
        lastCorModificationTime = currentTime;
      }
    }
  }

  void seeCorValue(float& cor) {
    char corStr[10];
    sprintf(corStr, "%f", cor);
    DrawText(corStr, 10, 10, 20, RED);
  }

  void draw() {
    DrawCircle(x,y,radius,color);
  }
};
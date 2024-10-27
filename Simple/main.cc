#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <tuple>
#include <vector>
#include <random>
#include "ball.hpp"

auto get_random_seed() -> std::seed_seq {
    std::random_device source;

    unsigned int random_data[10];
    for(auto& elem : random_data) {
        elem = source();
    }

    return std::seed_seq(random_data+0, random_data+10);
}

float random_number(float min, float max) {
    static auto seed = get_random_seed();
    static std::default_random_engine rng(seed);
    std::uniform_real_distribution<float> dist(min,max);
    return dist(rng);
}

int main() {
    const int screen_width = 680;
    const int screen_height = 480;
    InitWindow(screen_width, screen_height, "Bouncing Balls erererer");
    InitAudioDevice();
    SetTargetFPS(30);

    std::vector<Ball> balls;

    Sound ping_sfx = LoadSound("Ping.mp3");
    Sound ping_sfx2 = LoadSound("Ping.mp3");

    std::vector<Color> colors = { BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, WHITE };

    for(int i=0;i<2;i++) {
        if(i==1) {
            balls.emplace_back(
                random_number(0, screen_width),
                random_number(0, screen_height),
                2.0f,
                2.0f,
                6.0f,
                YELLOW,
                ping_sfx,
                ping_sfx2);
        } else {
            balls.emplace_back(
                random_number(0, screen_width),
                random_number(0, screen_height),
                2.0f,
                2.0f,
                6.0f,
                YELLOW,
                ping_sfx,
                ping_sfx2);
        }
    }

    std::tuple<int, int> circle_center = std::make_tuple(
        screen_width - screen_width/2, screen_height - screen_height/2);
    float circle_radius = screen_width/48;


    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(std::get<0>(circle_center), std::get<1>(circle_center), circle_radius, WHITE);

        for(auto& ball : balls) {
            ball.draw();
            ball.update(std::make_tuple(std::get<0>(circle_center), std::get<1>(circle_center)), circle_radius, 0.f);
        }
        EndDrawing();
    }

    UnloadSound(ping_sfx);
    UnloadSound(ping_sfx2);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

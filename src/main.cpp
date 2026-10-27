#include "raylib.h"
#include <algorithm>
#include "gameconfig.hpp"
#include "player.hpp"


int main()
{   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(GameConfig::BASE_W, GameConfig::BASE_H, "Swarm");
    SetTargetFPS(60);


    ChangeDirectory(TextFormat("%s../assets/images", GetApplicationDirectory()));

    Texture2D background = LoadTexture("Floor.png");
    Texture2D walls = LoadTexture("Walls.png");
    Texture2D playerTex = LoadTexture("survivor-idle_shotgun_0.png");

    RenderTexture2D canvas = LoadRenderTexture(GameConfig::BASE_W, GameConfig::BASE_H);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);

    float mapW = (float)background.width;
    float mapH = (float)background.height;
    float halfW = GameConfig::BASE_W * 0.5f;
    float halfH = GameConfig::BASE_H * 0.5f;

    Player player(&playerTex);
    player.SetPosition({mapW * 0.5f, mapH * 0.5f});

    Camera2D camera = {};
    camera.zoom = 1.0f;
    camera.target = player.GetPosition();
    camera.offset = {halfW, halfH};


    while (!WindowShouldClose())
    {   
        if(IsKeyDown(KEY_Q)) Sprite::showDebug = !Sprite::showDebug;

        float dt = GetFrameTime();

        float movex = (IsKeyDown(KEY_D) ? 1.0f : 0.0f) - (IsKeyDown(KEY_A) ? 1.0f : 0.0f);
        float movey = (IsKeyDown(KEY_S) ? 1.0f : 0.0f) - (IsKeyDown(KEY_W) ? 1.0f : 0.0f);

        player.Update({movex, movey}, dt);

        camera.target = player.GetPosition();

        camera.target.x = std::clamp(camera.target.x, halfW, mapW - halfW);
        camera.target.y = std::clamp(camera.target.y, halfW, mapH - halfH);

        BeginTextureMode(canvas);
        ClearBackground(BLACK);
        BeginMode2D(camera);
          DrawTexture(background, 0, 0, WHITE);
          player.Draw();
          DrawTexture(walls, 0, 0, WHITE);
        EndMode2D();
        DrawRectangle(0, GameConfig::BASE_H - 32, GameConfig::BASE_W, 32, ColorAlpha(DARKBLUE, 0.6f));
        DrawText(TextFormat("Player: %.0f,%.0f", player.GetPosition().x, player.GetPosition().y), 12, GameConfig::BASE_H - 24, 20, LIME);
        DrawText(TextFormat("Camera: %.0f,%.0f", camera.target.x, camera.target.y), 256, GameConfig::BASE_H - 24, 20, LIME);
        DrawText(TextFormat("Map: %.0f,%.0f", mapW, mapH), 512, GameConfig::BASE_H - 24, 20, LIME);
        EndTextureMode();

        float scale = std::min(
          (float)GetScreenWidth() / GameConfig::BASE_W,
          (float)GetScreenHeight() / GameConfig::BASE_H
        );

        float offsetX = (GetScreenWidth() - GameConfig::BASE_W * scale) * 0.5f;
        float offsetY = (GetScreenHeight() - GameConfig::BASE_H * scale) * 0.5f;

        Rectangle src = {0, 0, (float)GameConfig::BASE_W, -float(GameConfig::BASE_H)};
        Rectangle dest = {offsetX, offsetY, GameConfig::BASE_W* scale, GameConfig::BASE_H * scale};

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(canvas.texture, src, dest, {0,0}, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(walls);
    UnloadTexture(playerTex);
    UnloadRenderTexture(canvas);
    CloseWindow();
    return 0;
}
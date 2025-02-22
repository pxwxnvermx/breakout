#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define WINDOW_W 800
#define WINDOW_H 800

#define WINDOW_TITLE "Breakout"

#define HITTER_W 64
#define HITTER_H 8

#define BALL_RADIUS 8

#define ROWS 20
#define COLS 4
#define BREAKBLOCK_W 32
#define BREAKBLOCK_H 8
#define BREAKBLOCK_PADDING 4

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE);

  Vector2 ball_pos = {(float)(WINDOW_W - BALL_RADIUS) / 2, WINDOW_H - 40};
  Vector2 ball_vel = {-1, -1};
  Rectangle hitter = {
      .x = (float)(WINDOW_W - 64) / 2,
      .y = WINDOW_H - 20,
      .width = HITTER_W,
      .height = HITTER_H,
  };
  int blocks[ROWS][COLS] = {0};

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();
    if (IsKeyDown(KEY_A))
      hitter.x -= 5;
    else if (IsKeyDown(KEY_D))
      hitter.x += 5;
    hitter.x = (int)Clamp(hitter.x, 20, WINDOW_W - HITTER_W - 20);

    if (20 >= ball_pos.x - 4 || ball_pos.x - 4 >= WINDOW_W - 20) {
      ball_vel.x *= -1;
    }
    if (20 >= ball_pos.y - 4 ||
        CheckCollisionCircleRec(ball_pos, BALL_RADIUS, hitter)) {
      ball_vel.y *= -1;
    }
    ball_pos = Vector2Add(ball_pos, ball_vel);

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      DrawRectangle(0, 0, 20, WINDOW_H, BLACK);
      DrawRectangle(0, 0, WINDOW_W, 20, BLACK);
      DrawRectangle(WINDOW_W - 20, 0, 20, WINDOW_H, BLACK);

      for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
          if (blocks[row][col] == 1)
            continue;
          Rectangle block = {
              .x = 40 + (BREAKBLOCK_W + BREAKBLOCK_PADDING) * row,
              .y = 40 + (BREAKBLOCK_H + BREAKBLOCK_PADDING) * col,
              .width = BREAKBLOCK_W,
              .height = BREAKBLOCK_H,
          };
          if (CheckCollisionCircleRec(ball_pos, BALL_RADIUS, block)) {
            blocks[row][col] = 1;
            ball_vel.y *= -1;
          }
          DrawRectangleRec(block, RED);
        }
      }
      DrawCircleV(ball_pos, BALL_RADIUS, GREEN);
      DrawRectangle(hitter.x, WINDOW_H - 20, HITTER_W, HITTER_H, BLUE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

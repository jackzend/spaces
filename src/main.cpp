#include "raylib.h"
#include "spaces_defs.h"
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include "room.h"
#include "spaces_camera.h"
#include "game.h"
#include <iostream>
#include <random>

using namespace spaces_defs;

int main()
{
   // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
   InitWindow(SPACES_SCREEN_WIDTH, SPACES_SCREEN_HEIGHT, "spaces poc");

   Game gm("Hello World");

   SpacesCamera cam;
   SetTargetFPS(60);
   while (!WindowShouldClose())
   {
      gm.gameLoop();
   }
   CloseWindow();
}

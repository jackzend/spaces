#include "raylib.h"
#include "spaces_defs.h"
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include "room.h"
#include "spaces_camera.h"
#include <iostream>
#include <random>

using namespace spaces_defs;

int main()
{
   InitWindow(SPACES_SCREEN_WIDTH, SPACES_SCREEN_HEIGHT, "spaces poc");

   auto backgroundColor = SPACES_GREEN.getColor();

   std::shared_ptr<Room> room1 = std::make_shared<Room>("Jack's Room");
   std::shared_ptr<Room> room2 = std::make_shared<Room>("Ellie's Room");
   room2->setRoomColor(SPACES_ELLIES_PURPLE);
   room2->setRoomOutlineColor(SPACES_ELLIES_BLUE);
   room2->setRoomNameColor(SPACES_ELLIES_BLUE);
   std::shared_ptr<Room> room3 = std::make_shared<Room>("Griff's Room");
   std::shared_ptr<Room> room4 = std::make_shared<Room>("Elyza's Room");
   std::shared_ptr<Room> busterRoom = std::make_shared<Room>("Buster's Room!");
   std::shared_ptr<Room> teddysRoom = std::make_shared<Room>("Teddy's Room");
   room4->setRoomColor(SPACES_DARK_MINT);
   room4->setRoomOutlineColor(SPACES_MINT);
   room4->setRoomNameColor(SPACES_MINT);
   room1->setNeighbor(room2, SpacesNeighbors::LEFT); // will also make room1 the neighbor of room 2
   room1->setNeighbor(room3, SpacesNeighbors::RIGHT);
   room3->setNeighbor(room4, SpacesNeighbors::UP);
   room1->setNeighbor(busterRoom, SpacesNeighbors::DOWN);
   busterRoom->setNeighbor(teddysRoom, SpacesNeighbors::LEFT);
   std::shared_ptr<Room> triviaBillsRoom = std::make_shared<Room>("Bill Siney's Room");
   room4->setNeighbor(triviaBillsRoom, SpacesNeighbors::RIGHT);
   triviaBillsRoom->setRoomColor(DARKGREEN);
   triviaBillsRoom->setRoomOutlineColor(GREEN);
   triviaBillsRoom->setRoomNameColor(GREEN);

   std::shared_ptr<Room> chestersRoom = std::make_shared<Room>("Chester's Room");
   room2->setNeighbor(chestersRoom, SpacesNeighbors::LEFT);
   chestersRoom->setRoomColor(BROWN);
   chestersRoom->setRoomOutlineColor(DARKBROWN);
   chestersRoom->setRoomNameColor(DARKBROWN);

   std::shared_ptr<Room> wesleysRoom = std::make_shared<Room>("Wesley's Room");
   chestersRoom->setNeighbor(wesleysRoom, SpacesNeighbors::UP);
   wesleysRoom->setRoomColor(DARKBROWN);
   wesleysRoom->setRoomOutlineColor(BROWN);
   wesleysRoom->setRoomNameColor(BROWN);

   // room1->setNeighbor( room3, SpacesNeighbors::LEFT ); // should induce an error message since alreadt has left neighbor

   SpacesCamera cam;
   SetTargetFPS(60);
   while (!WindowShouldClose())
   {
      if (IsKeyPressed(KEY_F11))
      {
         ToggleFullscreen();
      }

      if (IsKeyDown(KEY_UP))
      {
         if (IsKeyDown(KEY_LEFT))
         {
            cam.decrementX();
         }
         else if (IsKeyDown(KEY_RIGHT))
         {
            cam.incrementX();
         }
         cam.decrementY();
      }
      else if (IsKeyDown(KEY_DOWN))
      {
         if (IsKeyDown(KEY_LEFT))
         {
            cam.decrementX();
         }
         else if (IsKeyDown(KEY_RIGHT))
         {
            cam.incrementX();
         }
         cam.incrementY();
      }
      else if (IsKeyDown(KEY_LEFT))
      {
         cam.decrementX();
      }
      else if (IsKeyDown(KEY_RIGHT))
      {
         cam.incrementX();
      }
      // std::cout << cam.getOffset().x << " " << cam.getOffset().y << std::endl;
      auto offset = cam.getOffset();
      room1->updateLocationWithCameraOffset(offset);
      room2->updateLocationWithCameraOffset(offset);
      room3->updateLocationWithCameraOffset(offset);
      room4->updateLocationWithCameraOffset(offset);
      busterRoom->updateLocationWithCameraOffset(offset);
      teddysRoom->updateLocationWithCameraOffset(offset);
      triviaBillsRoom->updateLocationWithCameraOffset(offset);
      chestersRoom->updateLocationWithCameraOffset(offset);
      wesleysRoom->updateLocationWithCameraOffset(offset);

      BeginDrawing();

      ClearBackground(backgroundColor);

      room1->drawRoom();
      room2->drawRoom();
      room3->drawRoom();
      room4->drawRoom();
      busterRoom->drawRoom();
      teddysRoom->drawRoom();
      triviaBillsRoom->drawRoom();
      chestersRoom->drawRoom();
      wesleysRoom->drawRoom();
      cam.drawSprite();
      DrawText("Testing", 10, 10, 20, DARKGREEN);
      DrawFPS(10, 50);
      EndDrawing();
   }
   CloseWindow();
}

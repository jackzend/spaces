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

using room_ptr = std::shared_ptr<Room>;

int main()
{
   InitWindow( SPACES_SCREEN_WIDTH, SPACES_SCREEN_HEIGHT, "spaces poc" );

   Game gm( "Hello World" );
   // room1->setNeighbor( room3, SpacesNeighbors::LEFT ); // should induce an error message since alreadt has left neighbor

   SpacesCamera cam;
   SetTargetFPS( 60 );
   while ( !WindowShouldClose() )
   {
      gm.gameLoop();
      /*
      auto offset = cam.getOffset();
      griffsRoom->updateLocationWithCameraOffset( offset );
      jacksRoom->updateLocationWithCameraOffset( offset );

      BeginDrawing();
      griffsRoom->drawRoom();
      jacksRoom->drawRoom();

      ClearBackground( backgroundColor );

      cam.drawSprite();
      DrawText( "Testing", 10, 10, 20, DARKGREEN );
      DrawFPS( 10, 50 );
      EndDrawing();*/
   }
   CloseWindow();
}

#include "raylib.h"
#include "spaces_defs.h"
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include "room.h"
#include <iostream>
#include <random>

using namespace spaces_defs;

int main()
{
   std::random_device rd;
   std::mt19937 gen( rd() );
   std::uniform_int_distribution<> distr( 0, 255 );

   InitWindow( SPACES_SCREEN_WIDTH, SPACES_SCREEN_HEIGHT, "spaces poc" );

   auto backgroundColor = SPACES_GREEN.getColor();

   std::shared_ptr<Room> room1 = std::make_shared<Room>();

   SetTargetFPS( 60 );

   while ( !WindowShouldClose() )
   {
      if ( IsKeyPressed( KEY_F11 ) )
      {
         ToggleFullscreen();
      }

      ColorWrap temp1( distr( gen ), distr( gen ), distr( gen ), 255 );
      ColorWrap temp2( distr( gen ), distr( gen ), distr( gen ), 255 );

      room1->setRoomColor( temp1 );
      room1->setRoomOutlineColor( temp2 );

      BeginDrawing();

      ClearBackground( backgroundColor );
      DrawRectangleRec( room1->getShape(), room1->getRoomColor() );
      DrawRectangleLinesEx( room1->getShape(), 10.0f, room1->getRoomOutlineColor() );
      DrawText( "Testing", 10, 10, 20, DARKGREEN );
      EndDrawing();
   }
   CloseWindow();
}

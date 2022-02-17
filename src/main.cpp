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
   std::random_device rd;
   std::mt19937 gen( rd() );
   std::uniform_int_distribution<> distr( 0, 255 );

   InitWindow( SPACES_SCREEN_WIDTH, SPACES_SCREEN_HEIGHT, "spaces poc" );

   auto backgroundColor = SPACES_GREEN.getColor();

   std::shared_ptr<Room> room1 = std::make_shared<Room>();

   SpacesCamera cam;

   SetTargetFPS( 60 );
   while ( !WindowShouldClose() )
   {
      if ( IsKeyDown( KEY_UP ) )
      {
         cam.decrementY();
      }
      else if ( IsKeyDown( KEY_DOWN ) )
      {
         cam.incrementY();
      }
      else if ( IsKeyDown( KEY_LEFT ) )
      {
         cam.decrementX();
      }
      else if ( IsKeyDown( KEY_RIGHT ) )
      {
         cam.incrementX();
      }
      std::cout << cam.getOffset().x << " " << cam.getOffset().y << std::endl;
      room1->setLocation( cam.getOffset() );
      BeginDrawing();

      ClearBackground( backgroundColor );
      room1->drawRoom();
      DrawText( "Testing", 10, 10, 20, DARKGREEN );
      EndDrawing();
   }
   CloseWindow();
}

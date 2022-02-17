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
   std::shared_ptr<Room> room2 = std::make_shared<Room>();
   std::shared_ptr<Room> room3 = std::make_shared<Room>();
   std::shared_ptr<Room> room4 = std::make_shared<Room>();
   room1->setNeighbor( room2, SpacesNeighbors::LEFT ); // will also make room1 the neighbor of room 2
   room1->setNeighbor( room3, SpacesNeighbors::RIGHT );
   room3->setNeighbor( room4, SpacesNeighbors::UP );

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

      room1->updateLocationWithCameraOffset( cam.getOffset() );
      room2->updateLocationWithCameraOffset( cam.getOffset() );
      room3->updateLocationWithCameraOffset( cam.getOffset() );
      room4->updateLocationWithCameraOffset( cam.getOffset() );

      BeginDrawing();

      ClearBackground( backgroundColor );
      room1->drawRoom();
      room2->drawRoom();
      room3->drawRoom();
      room4->drawRoom();
      DrawText( "Testing", 10, 10, 20, DARKGREEN );
      EndDrawing();
   }
   CloseWindow();
}

#include "raylib.h"
#include "spaces_defs.h"
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include <iostream>

using namespace spaces_defs;

template<typename ShapeStruct>
inline ShapeStruct resizeShape( const ShapeStruct &s )
{
   ShapeStruct ret;
   ret.x      = s.x * ( ( float )GetRenderWidth() / ( float )spaces_defs::SPACES_SCREEN_WIDTH );
   ret.y      = s.y * ( ( float )GetRenderHeight() / ( float )spaces_defs::SPACES_SCREEN_HEIGHT );
   ret.width  = s.width * ( ( float )GetRenderWidth() / ( float )spaces_defs::SPACES_SCREEN_WIDTH );
   ret.height = s.height * ( ( float )GetRenderHeight() / ( float )spaces_defs::SPACES_SCREEN_HEIGHT );

   return ret;
}
int main()
{
   SetConfigFlags( FLAG_WINDOW_RESIZABLE );   // Window configuration flags
   InitWindow( SPACES_SCREEN_WIDTH, SPACES_SCREEN_HEIGHT, "spaces poc" );

   auto backgroundColor = SPACES_GREEN.getColor();
   auto roomRect        = resizeShape( SPACES_ROOM.getShape() );

   SetTargetFPS( 60 );

   while ( !WindowShouldClose() )
   {
      if ( IsKeyPressed( KEY_F11 ) )
      {
         ToggleFullscreen();
      }
      roomRect = resizeShape( SPACES_ROOM.getShape() );

      BeginDrawing();
      //std::cout << GetRenderHeight() << std::endl;
      std::cout << roomRect.width << " " << roomRect.height << std::endl;

      ClearBackground( backgroundColor );
      DrawRectangleRec( roomRect, SPACES_MINT.getColor() );
      DrawRectangleLinesEx( roomRect, 10.0f, SPACES_DARK_MINT.getColor() );
      DrawText( "Testing", 10, 10, 20, DARKGREEN );
      EndDrawing();
   }
   CloseWindow();

}

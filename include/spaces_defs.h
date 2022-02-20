#ifndef SPACES_DEFS_H
#define SPACES_DEFS_H
#include <memory>
#include <raylib.h>
#include "utils/color_wrapper.h"
#include "utils/shape_wrapper.h"

namespace spaces_defs
{
   // uncomment for linux?
   // constexpr int SPACES_SCREEN_WIDTH = 1920;
   // constexpr int SPACES_SCREEN_HEIGHT = 1080;

   using rectangle_ptr = std::unique_ptr<ShapeWrap<Rectangle>>;
   constexpr int SPACES_SCREEN_WIDTH = 1792;
   constexpr int SPACES_SCREEN_HEIGHT = 1120;

   constexpr float SPACES_ROOM_WIDTH = (2.0f / 3.0f) * SPACES_SCREEN_WIDTH;
   constexpr float SPACES_ROOM_HEIGHT = (2.0f / 3.0f) * SPACES_SCREEN_HEIGHT;

   constexpr ColorWrap SPACES_GREEN = ColorWrap(186u, 218u, 85u, 255u);
   constexpr ColorWrap SPACES_MINT = ColorWrap(182u, 252u, 213u, 255u);
   constexpr ColorWrap SPACES_DARK_MINT = ColorWrap(91u, 126u, 106u, 255u);
   constexpr ColorWrap SPACES_ELLIES_PURPLE = ColorWrap(102u, 103u, 171u, 255u);
   constexpr ColorWrap SPACES_ELLIES_BLUE = ColorWrap(74u, 140u, 255u, 255u);

   constexpr ShapeWrap<Rectangle> SPACES_ROOM = ShapeWrap<Rectangle>(((float)SPACES_SCREEN_WIDTH / 2.0f) - (SPACES_ROOM_WIDTH / 2.0f), ((float)SPACES_SCREEN_HEIGHT / 2.0f) - (SPACES_ROOM_HEIGHT / 2.0f), SPACES_ROOM_WIDTH, SPACES_ROOM_HEIGHT);

   constexpr float SPACES_SPRITE_HEIGHT = 50.0f;
   constexpr ShapeWrap<Rectangle> SPACES_SPRITE = ShapeWrap<Rectangle>(((float)SPACES_SCREEN_WIDTH / 2.0f) - (SPACES_SPRITE_HEIGHT / 2.0f), ((float)SPACES_SCREEN_HEIGHT / 2.0f) - (SPACES_SPRITE_HEIGHT / 2.0f), SPACES_SPRITE_HEIGHT, SPACES_SPRITE_HEIGHT);

   constexpr float SPACES_WALL_THICKNESS = 20.0f;
   constexpr float SPACES_TEXT_HEIGHT = 30.0f;
   constexpr float SPACES_DOOR_HEIGHT = 100.0f;

   constexpr float SPACES_DOOR_LEFT_X_OFFSET = ((float)SPACES_SCREEN_WIDTH / 2.0f) - (SPACES_ROOM_WIDTH / 2.0f);
   constexpr float SPACES_DOOR_LEFT_Y_OFFSET = ((float)SPACES_SCREEN_HEIGHT / 2.0f) - (SPACES_DOOR_HEIGHT / 2.0f);

   constexpr ShapeWrap<Rectangle> SPACES_DOOR_LEFT = ShapeWrap<Rectangle>(SPACES_DOOR_LEFT_X_OFFSET, SPACES_DOOR_LEFT_Y_OFFSET, SPACES_WALL_THICKNESS, SPACES_DOOR_HEIGHT);

   constexpr float SPACES_DOOR_RIGHT_X_OFFSET = SPACES_DOOR_LEFT_X_OFFSET + SPACES_ROOM_WIDTH - SPACES_WALL_THICKNESS;
   constexpr float SPACES_DOOR_RIGHT_Y_OFFSET = SPACES_DOOR_LEFT_Y_OFFSET;

   constexpr ShapeWrap<Rectangle> SPACES_DOOR_RIGHT = ShapeWrap<Rectangle>(SPACES_DOOR_RIGHT_X_OFFSET, SPACES_DOOR_RIGHT_Y_OFFSET, SPACES_WALL_THICKNESS, SPACES_DOOR_HEIGHT);

   constexpr float SPACES_DOOR_UP_X_OFFSET = ((float)SPACES_SCREEN_WIDTH / 2.0f) - (SPACES_DOOR_HEIGHT / 2.0f);
   constexpr float SPACES_DOOR_UP_Y_OFFSET = ((float)SPACES_SCREEN_HEIGHT / 2.0f) - (SPACES_ROOM_HEIGHT / 2.0f);

   constexpr ShapeWrap<Rectangle> SPACES_DOOR_UP = ShapeWrap<Rectangle>(SPACES_DOOR_UP_X_OFFSET, SPACES_DOOR_UP_Y_OFFSET, SPACES_DOOR_HEIGHT, SPACES_WALL_THICKNESS);

   constexpr float SPACES_DOOR_DOWN_X_OFFSET = SPACES_DOOR_UP_X_OFFSET;
   constexpr float SPACES_DOOR_DOWN_Y_OFFSET = SPACES_DOOR_UP_Y_OFFSET + SPACES_ROOM_HEIGHT - SPACES_WALL_THICKNESS;

   constexpr ShapeWrap<Rectangle> SPACES_DOOR_DOWN = ShapeWrap<Rectangle>(SPACES_DOOR_DOWN_X_OFFSET, SPACES_DOOR_DOWN_Y_OFFSET, SPACES_DOOR_HEIGHT, SPACES_WALL_THICKNESS);

   enum class SpacesNeighbors
   {
      LEFT = 0,
      RIGHT = 1,
      UP = 2,
      DOWN = 3
   };

   const float SPACES_CAMERA_INCREMENT_X = 8.0f;
   const float SPACES_CAMERA_INCREMENT_Y = 8.0f;

   constexpr int SPACES_MAX_RENDER_ROOMS = 50;

} // spaces_defs

/*template<typename ShapeStruct>
inline ShapeStruct resizeShape( const ShapeStruct &s )
{
   ShapeStruct ret;
   ret.x      = s.x * ( ( float )GetRenderWidth() / ( float )spaces_defs::SPACES_SCREEN_WIDTH );
   ret.y      = s.y * ( ( float )GetRenderHeight() / ( float )spaces_defs::SPACES_SCREEN_HEIGHT );
   ret.width  = s.width * ( ( float )GetRenderWidth() / ( float )spaces_defs::SPACES_SCREEN_WIDTH );
   ret.height = s.height * ( ( float )GetRenderHeight() / ( float )spaces_defs::SPACES_SCREEN_HEIGHT );

   return ret;
}*/

template <typename T>
inline bool is_uninitialized(std::weak_ptr<T> const &weak)
{
   using wt = std::weak_ptr<T>;
   return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

#endif // SPACES_DEFS_H

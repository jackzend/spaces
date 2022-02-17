#ifndef SPACES_DEFS_H
#define SPACES_DEFS_H

#include <raylib.h>
#include "utils/color_wrapper.h"
#include "utils/shape_wrapper.h"

namespace spaces_defs
{
   constexpr int SPACES_SCREEN_WIDTH  = 1920;
   constexpr int SPACES_SCREEN_HEIGHT = 1080;

   constexpr ColorWrap SPACES_GREEN     = ColorWrap( 186u, 218u, 85u, 255u );
   constexpr ColorWrap SPACES_MINT      = ColorWrap( 182u, 252u, 213u, 255u );
   constexpr ColorWrap SPACES_DARK_MINT = ColorWrap( 91u, 126u, 106u, 255u );

   constexpr ShapeWrap<Rectangle> SPACES_ROOM = ShapeWrap<Rectangle>( ( ( float )SPACES_SCREEN_WIDTH / 2.0f ) - ( 1500.0f / 2.0f ), ( ( float )SPACES_SCREEN_HEIGHT / 2.0f ) - ( 750.0f / 2.0f ), 1500.0f, 750.0f );

} // spaces_defs

#endif // SPACES_DEFS_H

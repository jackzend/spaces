#ifndef COLOR_WRAPPER_H
#define COLOR_WRAPPER_H
#include <raylib.h>

// this class lets us construct constant colors at compile time and can also be used as a runtime wrapper for the Color raylib struct
class ColorWrap
{
   Color color;

   public:
      constexpr ColorWrap() : color()
      {
         color.a = 0;
         color.b = 0;
         color.g = 0;
         color.r = 0;
      }
      constexpr ColorWrap( const ColorWrap & ) = default;

      constexpr ColorWrap( const Color &c ) : color( c ) {}
      constexpr ColorWrap( const unsigned char r,
                           const unsigned char g,
                           const unsigned char b,
                           const unsigned char a ) : color()
      {
         color.r = r;
         color.g = g;
         color.b = b;
         color.a = a;
      }

      constexpr Color getColor() const { return color; }

};

#endif // COLOR_WRAPPER_H

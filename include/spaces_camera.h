#ifndef SPACES_CAMERA_H
#define SPACES_CAMERA_H

#include <raylib.h>
#include "spaces_defs.h"
#include "utils/shape_wrapper.h"
class SpacesCamera
{
   Vector2 _mLocation;
   ShapeWrap<Rectangle> _mSprite;

public:
   SpacesCamera();
   Vector2 getOffset(); // this is what we update our room locations with
   void incrementX();
   void incrementY();
   void decrementX();
   void decrementY();
   void drawSprite();
};

#endif // CAMERA_H

#include "spaces_camera.h"

SpacesCamera::SpacesCamera()
   :
   _mLocation()
{
   _mLocation.x = 0;
   _mLocation.y = 0;
}

Vector2 SpacesCamera::getOffset()
{
   Vector2 ret;
   ret.x = -_mLocation.x;
   ret.y = -_mLocation.y;
   return ret;
}

void SpacesCamera::incrementX() { _mLocation.x += spaces_defs::SPACES_CAMERA_INCREMENT_X; }
void SpacesCamera::incrementY() { _mLocation.y += spaces_defs::SPACES_CAMERA_INCREMENT_Y; }
void SpacesCamera::decrementX() { _mLocation.x -= spaces_defs::SPACES_CAMERA_INCREMENT_X; }
void SpacesCamera::decrementY() { _mLocation.y -= spaces_defs::SPACES_CAMERA_INCREMENT_Y; }

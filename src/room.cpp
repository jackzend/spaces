#include "room.h"

Room::Room()
    : _mRoomShape_ptr(nullptr),
      _mRoomColor_ptr(nullptr),
      _mRoomOutline_ptr(nullptr),
      _mRoomNameColor_ptr(nullptr),
      _mNeighbors(std::vector<std::weak_ptr<Room>>(4)),
      _mLocation(),
      _mOrigin(),
      _mName("Empty!"),
      _mEnableDoors(std::vector<bool>(4, false)),
      _mID(0)
{
   _mLeftDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_LEFT);
   _mRightDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_RIGHT);
   _mUpDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_UP);
   _mDownDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_DOWN);

   _mRoomShape_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_ROOM);
   _mRoomColor_ptr = std::make_unique<ColorWrap>(SPACES_MINT);
   _mRoomOutline_ptr = std::make_unique<ColorWrap>(SPACES_DARK_MINT);
   _mRoomNameColor_ptr = std::make_unique<ColorWrap>(SPACES_DARK_MINT);
   setOrigin(0.0f, 0.0f);
}
Room::Room(const std::string aName)
    : _mRoomShape_ptr(nullptr),
      _mRoomColor_ptr(nullptr),
      _mRoomOutline_ptr(nullptr),
      _mNeighbors(std::vector<std::weak_ptr<Room>>(4)),
      _mLocation(),
      _mOrigin(),
      _mName(aName),
      _mEnableDoors(std::vector<bool>(4, false)),
      _mID(0)
{
   // we can move these into the constructor list later

   _mLeftDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_LEFT);
   _mRightDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_RIGHT);
   _mUpDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_UP);
   _mDownDoor_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_DOOR_DOWN);

   _mRoomShape_ptr = std::make_unique<ShapeWrap<Rectangle>>(SPACES_ROOM);
   _mRoomColor_ptr = std::make_unique<ColorWrap>(SPACES_MINT);
   _mRoomOutline_ptr = std::make_unique<ColorWrap>(SPACES_DARK_MINT);
   _mRoomNameColor_ptr = std::make_unique<ColorWrap>(SPACES_DARK_MINT);
   setOrigin(0.0f, 0.0f);
}

void Room::drawRoom()
{
   DrawRectangleRec(getShape(), getRoomColor());
   DrawRectangleLinesEx(getShape(), SPACES_WALL_THICKNESS, getRoomOutlineColor());
   DrawText(_mName.c_str(),
            ((int)(_mLocation.x + ((float)SPACES_SCREEN_WIDTH / 2.0f)) - ((float)MeasureText(_mName.c_str(), SPACES_TEXT_HEIGHT)) / 2.0f), // calculates offset from current location
            (int)(_mLocation.y + ((float)SPACES_SCREEN_HEIGHT / 2.0f)) - SPACES_TEXT_HEIGHT / 2.0f,
            (int)SPACES_TEXT_HEIGHT,
            _mRoomNameColor_ptr->getColor());

   if (_mEnableDoors[static_cast<size_t>(SpacesNeighbors::LEFT)])
   {
      DrawRectangleRec(_mLeftDoor_ptr->getShape(), getRoomColor());
   }
   if (_mEnableDoors[static_cast<size_t>(SpacesNeighbors::RIGHT)])
   {
      DrawRectangleRec(_mRightDoor_ptr->getShape(), getRoomColor());
   }
   if (_mEnableDoors[static_cast<size_t>(SpacesNeighbors::UP)])
   {
      DrawRectangleRec(_mUpDoor_ptr->getShape(), getRoomColor());
   }
   if (_mEnableDoors[static_cast<size_t>(SpacesNeighbors::DOWN)])
   {
      DrawRectangleRec(_mDownDoor_ptr->getShape(), getRoomColor());
   }
}

void Room::setOrigin(const float _x, const float _y)
{
   _mOrigin.x = _x;
   _mOrigin.y = _y;
   _mLocation = _mOrigin;
   fixInternalShape();
}

void Room::setOrigin(const Vector2 &loc)
{
   _mOrigin = loc;
   _mLocation = _mOrigin;
   fixInternalShape();
}

void Room::updateLocationWithCameraOffset(const Vector2 &offset)
{
   _mLocation.x = _mOrigin.x + offset.x;
   _mLocation.y = _mOrigin.y + offset.y;
   fixInternalShape();
}

void Room::fixInternalShape() // fix invariants // todo, change these to the offsets defined in spaces_defs
{
   auto temp = _mRoomShape_ptr->getShape();
   temp.x = _mLocation.x + ((float)SPACES_SCREEN_WIDTH / 2.0f) - (SPACES_ROOM_WIDTH / 2.0f); // gets the corner position
   temp.y = _mLocation.y + ((float)SPACES_SCREEN_HEIGHT / 2.0f) - (SPACES_ROOM_HEIGHT / 2.0f);
   _mRoomShape_ptr->setShape(temp);

   auto temp1 = _mLeftDoor_ptr->getShape();
   temp1.x = _mLocation.x + SPACES_DOOR_LEFT_X_OFFSET; // gets the corner position
   temp1.y = _mLocation.y + SPACES_DOOR_LEFT_Y_OFFSET;
   _mLeftDoor_ptr->setShape(temp1);

   auto temp2 = _mRightDoor_ptr->getShape();
   temp2.x = _mLocation.x + SPACES_DOOR_RIGHT_X_OFFSET; // gets the corner position
   temp2.y = _mLocation.y + SPACES_DOOR_RIGHT_Y_OFFSET;
   _mRightDoor_ptr->setShape(temp2);

   auto temp3 = _mUpDoor_ptr->getShape();
   temp3.x = _mLocation.x + SPACES_DOOR_UP_X_OFFSET; // gets the corner position
   temp3.y = _mLocation.y + SPACES_DOOR_UP_Y_OFFSET;
   _mUpDoor_ptr->setShape(temp3);

   auto temp4 = _mDownDoor_ptr->getShape();
   temp4.x = _mLocation.x + SPACES_DOOR_DOWN_X_OFFSET; // gets the corner position
   temp4.y = _mLocation.y + SPACES_DOOR_DOWN_Y_OFFSET;
   _mDownDoor_ptr->setShape(temp4);
}

void Room::addDoor(const SpacesNeighbors i)
{
   _mEnableDoors[static_cast<size_t>(i)] = true;
}

bool Room::setNeighbor(std::shared_ptr<Room> nbor, SpacesNeighbors i)
{
   if (is_uninitialized(_mNeighbors[static_cast<size_t>(i)]))
   {
      _mNeighbors[static_cast<size_t>(i)] = nbor;
      _mEnableDoors[static_cast<size_t>(i)] = true;

      switch (i)
      {
      case SpacesNeighbors::LEFT:
         nbor->setOne(shared_from_this(), SpacesNeighbors::RIGHT);
         nbor->setOrigin(this->_mOrigin.x - SPACES_ROOM_WIDTH, this->_mOrigin.y);
         nbor->addDoor(SpacesNeighbors::RIGHT);
         break;
      case SpacesNeighbors::RIGHT:
         nbor->setOne(shared_from_this(), SpacesNeighbors::LEFT);
         nbor->setOrigin(this->_mOrigin.x + SPACES_ROOM_WIDTH, this->_mOrigin.y);
         nbor->addDoor(SpacesNeighbors::LEFT);
         break;

      case SpacesNeighbors::UP:
         nbor->setOne(shared_from_this(), SpacesNeighbors::DOWN);
         nbor->setOrigin(this->_mOrigin.x, this->_mOrigin.y - SPACES_ROOM_HEIGHT);
         nbor->addDoor(SpacesNeighbors::DOWN);

         break;
      case SpacesNeighbors::DOWN:
         nbor->setOne(shared_from_this(), SpacesNeighbors::UP);
         nbor->setOrigin(this->_mOrigin.x, this->_mOrigin.y + SPACES_ROOM_HEIGHT);
         nbor->addDoor(SpacesNeighbors::UP);

         break;

      default:
         break;
      }
      return true;
   }
   else
   {
      std::cout << "ERROR: THIS ROOM ALREADY HAS A NEIGHBOR THERE" << std::endl;
      return false;
   }
}

void Room::setOne(std::shared_ptr<Room> nbor, SpacesNeighbors i)
{
   if (is_uninitialized(_mNeighbors[static_cast<size_t>(i)]))
   {
      _mNeighbors[static_cast<size_t>(i)] = nbor;
   }
}

std::vector<size_t> Room::getNeighborIDs()
{
   std::vector<size_t> ret;
   for (auto &nbor : _mNeighbors)
   {
      if (!is_uninitialized(nbor))
      {
         ret.emplace_back(nbor.lock()->getID());
      }
   }
   return ret;
}

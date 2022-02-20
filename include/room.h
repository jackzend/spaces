#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <raylib.h>
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include "spaces_defs.h"
#include <vector>
#include <iostream>
#include <string>

using namespace spaces_defs;

class Room : public std::enable_shared_from_this<Room>
{
   rectangle_ptr _mRoomShape_ptr;

   rectangle_ptr _mLeftDoor_ptr;
   rectangle_ptr _mRightDoor_ptr;
   rectangle_ptr _mUpDoor_ptr;
   rectangle_ptr _mDownDoor_ptr;

   std::unique_ptr<ColorWrap> _mRoomColor_ptr;
   std::unique_ptr<ColorWrap> _mRoomOutline_ptr;
   std::unique_ptr<ColorWrap> _mRoomNameColor_ptr;
   std::vector<std::weak_ptr<Room>> _mNeighbors;
   Vector2 _mLocation;
   Vector2 _mOrigin;
   std::string _mName;
   size_t _mID;

   std::vector<bool> _mEnableDoors;

   void fixInternalShape();

public:
   Room(); // default yes
   Room(const std::string aName);
   // add custom one that just specifies its colors and name
   Room(const Room &&) = delete; // implement move ctor later if we need it

   Room &operator=(const Room &) = delete;
   Room(const Room &) = delete;

   Rectangle getShape() { return _mRoomShape_ptr->getShape(); }
   Color getRoomColor() { return _mRoomColor_ptr->getColor(); }
   Color getRoomOutlineColor() { return _mRoomOutline_ptr->getColor(); }
   std::shared_ptr<Room> getNeighbor(SpacesNeighbors i)
   {
      if (is_uninitialized(_mNeighbors[static_cast<size_t>(i)]))
      {
         return nullptr;
      }
      return _mNeighbors[static_cast<size_t>(i)].lock();
   }
   std::string getRoomName() { return _mName; }

   Vector2 getLocation() { return _mLocation; }
   Vector2 getOrigin() { return _mOrigin; }

   bool getDoorStatus(SpacesNeighbors i) { return _mEnableDoors[static_cast<size_t>(i)]; }
   size_t getID() { return _mID; }

   std::vector<size_t> getNeighborIDs();

   void setRoomColor(const ColorWrap &c) { _mRoomColor_ptr = std::make_unique<ColorWrap>(c); }
   void setRoomColor(const Color &c) { _mRoomColor_ptr = std::make_unique<ColorWrap>(c); }
   void setRoomOutlineColor(const ColorWrap &c) { _mRoomOutline_ptr = std::make_unique<ColorWrap>(c); }
   void setRoomOutlineColor(const Color &c) { _mRoomOutline_ptr = std::make_unique<ColorWrap>(c); }
   void setRoomShape(const ShapeWrap<Rectangle> &s) { _mRoomShape_ptr = std::make_unique<ShapeWrap<Rectangle>>(s); }
   void setRoomName(const std::string &aName) { _mName = aName; }
   void setRoomNameColor(const ColorWrap &c) { _mRoomNameColor_ptr = std::make_unique<ColorWrap>(c); }
   void setRoomNameColor(const Color &c) { _mRoomNameColor_ptr = std::make_unique<ColorWrap>(c); }

   bool setNeighbor(std::shared_ptr<Room> nbor,
                    SpacesNeighbors i);

   void setOne(std::shared_ptr<Room> nbor,
               SpacesNeighbors i);

   void setOrigin(const Vector2 &loc);
   void setOrigin(const float _x,
                  const float _y);

   void setID(size_t i) { _mID = i; }

   void updateLocationWithCameraOffset(const Vector2 &offset);

   void drawRoom();

   void addDoor(const SpacesNeighbors i);
};

#endif // ROOM_H

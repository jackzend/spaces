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

class Room : public std::enable_shared_from_this<Room>
{
   std::unique_ptr<ShapeWrap<Rectangle> > _mRoomShape_ptr;
   std::unique_ptr<ColorWrap> _mRoomColor_ptr;
   std::unique_ptr<ColorWrap> _mRoomOutline_ptr;
   std::vector<std::weak_ptr<Room> > _mNeighbors;
   Vector2 _mLocation;
   Vector2 _mOrigin;
   std::string _mName;

   void fixInternalShape();

   public:
      Room();                         // default yes
      Room( const std::string aName );
      // add custom one that just specifies its colors and name
      Room( const Room && ) = delete; // implement move ctor later if we need it

      Room &operator=( const Room & ) = delete;
      Room( const Room & )            = delete;

      Rectangle getShape() { return _mRoomShape_ptr->getShape(); }
      Color getRoomColor() { return _mRoomColor_ptr->getColor(); }
      Color getRoomOutlineColor() { return _mRoomOutline_ptr->getColor(); }
      std::shared_ptr<Room> getNeighbor( spaces_defs::SpacesNeighbors i ) { return _mNeighbors[static_cast<size_t>( i )].lock(); }
      std::string getRoomName() { return _mName; }

      void setRoomColor( const ColorWrap &c ) { _mRoomColor_ptr = std::make_unique<ColorWrap>( c ); }
      void setRoomOutlineColor( const ColorWrap &c ) { _mRoomOutline_ptr = std::make_unique<ColorWrap>( c ); }
      void setRoomShape( const ShapeWrap<Rectangle> &s ) { _mRoomShape_ptr = std::make_unique<ShapeWrap<Rectangle> >( s ); }
      void setRoomName( const std::string &aName ) { _mName = aName; }

      void setNeighbor( std::shared_ptr<Room>        nbor,
                        spaces_defs::SpacesNeighbors i );

      void setOne( std::shared_ptr<Room>        nbor,
                   spaces_defs::SpacesNeighbors i );

      void setOrigin( const Vector2 &loc );
      void setOrigin( const float _x,
                      const float _y );

      void updateLocationWithCameraOffset( const Vector2 &offset );

      void drawRoom();
};

#endif // ROOM_H

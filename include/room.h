#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <raylib.h>
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include <vector>

class Room
{
   std::unique_ptr<ShapeWrap<Rectangle> > _mRoomShape_ptr;
   std::unique_ptr<ColorWrap> _mRoomColor_ptr;
   std::unique_ptr<ColorWrap> _mRoomOutline_ptr;
   std::vector<std::shared_ptr<Room> > _mNeighbors;
   Vector2 _mLocation;

   void fixInternalShape();

   public:
      Room();                         // default yes
      Room( const Room && ) = delete; // implement move ctor later if we need it
      Room( std::vector<std::shared_ptr<Room> > &aNeighbors,
            ShapeWrap<Rectangle>                &aRoomShape,
            ColorWrap                           &aRoomColor,
            ColorWrap                           &aRoomOutline,
            Vector2                             &aLocation );
      Room &operator=( const Room & ) = delete;
      Room( const Room & )            = delete;

      Rectangle getShape() { return _mRoomShape_ptr->getShape(); }
      Color getRoomColor() { return _mRoomColor_ptr->getColor(); }
      Color getRoomOutlineColor() { return _mRoomOutline_ptr->getColor(); }
      std::shared_ptr<Room> getNeighbor( size_t i ) { return _mNeighbors[i]; }

      void setRoomColor( const ColorWrap &c ) { _mRoomColor_ptr = std::make_unique<ColorWrap>( c ); }
      void setRoomOutlineColor( const ColorWrap &c ) { _mRoomOutline_ptr = std::make_unique<ColorWrap>( c ); }
      void setRoomShape( const ShapeWrap<Rectangle> &s ) { _mRoomShape_ptr = std::make_unique<ShapeWrap<Rectangle> >( s ); }
      void setNeighbor( std::shared_ptr<Room> &r, size_t i ) { _mNeighbors[i] = r; }
      void setLocation( const Vector2 &loc );
      void setLocation( const float _x,
                        const float _y );

      void drawRoom();
};

#endif // ROOM_H

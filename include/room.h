#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <raylib.h>
#include "utils/shape_wrapper.h"
#include "utils/color_wrapper.h"
#include "spaces_defs.h"
#include <vector>

class Room : public std::enable_shared_from_this<Room>
{
   std::unique_ptr<ShapeWrap<Rectangle> > _mRoomShape_ptr;
   std::unique_ptr<ColorWrap> _mRoomColor_ptr;
   std::unique_ptr<ColorWrap> _mRoomOutline_ptr;
   std::vector<std::weak_ptr<Room> > _mNeighbors;
   Vector2 _mLocation;
   Vector2 _mOrigin;

   void fixInternalShape();

   public:
      Room();                         // default yes
      Room( const Room && ) = delete; // implement move ctor later if we need it
      Room( std::vector<std::weak_ptr<Room> > &aNeighbors,
            ShapeWrap<Rectangle>              &aRoomShape,
            ColorWrap                         &aRoomColor,
            ColorWrap                         &aRoomOutline,
            Vector2                           &aLocation );
      Room &operator=( const Room & ) = delete;
      Room( const Room & )            = delete;

      Rectangle getShape() { return _mRoomShape_ptr->getShape(); }
      Color getRoomColor() { return _mRoomColor_ptr->getColor(); }
      Color getRoomOutlineColor() { return _mRoomOutline_ptr->getColor(); }
      std::shared_ptr<Room> getNeighbor( spaces_defs::SpacesNeighbors i ) { return _mNeighbors[static_cast<size_t>( i )].lock(); }

      void setRoomColor( const ColorWrap &c ) { _mRoomColor_ptr = std::make_unique<ColorWrap>( c ); }
      void setRoomOutlineColor( const ColorWrap &c ) { _mRoomOutline_ptr = std::make_unique<ColorWrap>( c ); }
      void setRoomShape( const ShapeWrap<Rectangle> &s ) { _mRoomShape_ptr = std::make_unique<ShapeWrap<Rectangle> >( s ); }

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

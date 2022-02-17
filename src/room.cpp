#include "room.h"
#include "spaces_defs.h"

Room::Room()
   :
   _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mNeighbors( std::vector<std::shared_ptr<Room> >( 4, nullptr ) )
{
   _mRoomShape_ptr   = std::make_unique<ShapeWrap<Rectangle> >( spaces_defs::SPACES_ROOM );
   _mRoomColor_ptr   = std::make_unique<ColorWrap>( spaces_defs::SPACES_MINT );
   _mRoomOutline_ptr = std::make_unique<ColorWrap>( spaces_defs::SPACES_DARK_MINT );
}

Room::Room( std::vector<std::shared_ptr<Room> > &aNeighbors,
            ShapeWrap<Rectangle>                &aRoomShape,
            ColorWrap                           &aRoomColor,
            ColorWrap                           &aRoomOutline )
   :
   _mRoomShape_ptr( std::make_unique<ShapeWrap<Rectangle> >( aRoomShape ) ),
   _mRoomColor_ptr( std::make_unique<ColorWrap>( aRoomColor ) ),
   _mRoomOutline_ptr( std::make_unique<ColorWrap>( aRoomOutline ) ),
   _mNeighbors( std::move( aNeighbors ) )
{
}

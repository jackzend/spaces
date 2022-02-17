#include "room.h"
#include "spaces_defs.h"

Room::Room()
   :
   _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mNeighbors( std::vector<std::shared_ptr<Room> >( 4, nullptr ) ),
   _mLocation()
{
   _mRoomShape_ptr   = std::make_unique<ShapeWrap<Rectangle> >( spaces_defs::SPACES_ROOM );
   _mRoomColor_ptr   = std::make_unique<ColorWrap>( spaces_defs::SPACES_MINT );
   _mRoomOutline_ptr = std::make_unique<ColorWrap>( spaces_defs::SPACES_DARK_MINT );
   setLocation( 0.0f, 0.0f );
}

Room::Room( std::vector<std::shared_ptr<Room> > &aNeighbors,
            ShapeWrap<Rectangle>                &aRoomShape,
            ColorWrap                           &aRoomColor,
            ColorWrap                           &aRoomOutline,
            Vector2                             &aLocation )
   :
   _mRoomShape_ptr( std::make_unique<ShapeWrap<Rectangle> >( aRoomShape ) ),
   _mRoomColor_ptr( std::make_unique<ColorWrap>( aRoomColor ) ),
   _mRoomOutline_ptr( std::make_unique<ColorWrap>( aRoomOutline ) ),
   _mNeighbors( std::move( aNeighbors ) ),
   _mLocation( aLocation )
{
   fixInternalShape();
}

void Room::drawRoom()
{
   DrawRectangleRec( getShape(), getRoomColor() );
   DrawRectangleLinesEx( getShape(), 10.0f, getRoomOutlineColor() );
}

void Room::setLocation( const float _x, const float _y )
{
   _mLocation.x = _x;
   _mLocation.y = _y;
   fixInternalShape();
}

void Room::setLocation( const Vector2 &loc )
{
   _mLocation = loc;
   fixInternalShape();
}

void Room::fixInternalShape() // fix invariants
{
   // ( ( float )SPACES_SCREEN_WIDTH / 2.0f ) - ( 1500.0f / 2.0f ), ( ( float )SPACES_SCREEN_HEIGHT / 2.0f ) - ( 750.0f / 2.0f )
   auto temp = _mRoomShape_ptr->getShape();
   temp.x = _mLocation.x + ( ( float )spaces_defs::SPACES_SCREEN_WIDTH / 2.0f ) - ( 1500.0f / 2.0f );
   temp.y = _mLocation.y + ( ( float )spaces_defs::SPACES_SCREEN_HEIGHT / 2.0f ) - ( 750.0f / 2.0f );
   _mRoomShape_ptr->setShape( temp );
}

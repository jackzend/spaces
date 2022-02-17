#include "room.h"

Room::Room()
   :
   _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mNeighbors( std::vector<std::weak_ptr<Room> >( 4 ) ),
   _mLocation(),
   _mOrigin()
{
   _mRoomShape_ptr   = std::make_unique<ShapeWrap<Rectangle> >( spaces_defs::SPACES_ROOM );
   _mRoomColor_ptr   = std::make_unique<ColorWrap>( spaces_defs::SPACES_MINT );
   _mRoomOutline_ptr = std::make_unique<ColorWrap>( spaces_defs::SPACES_DARK_MINT );
   setOrigin( 0.0f, 0.0f );
}

Room::Room( std::vector<std::weak_ptr<Room> > &aNeighbors,
            ShapeWrap<Rectangle>              &aRoomShape,
            ColorWrap                         &aRoomColor,
            ColorWrap                         &aRoomOutline,
            Vector2                           &aLocation )
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

void Room::setOrigin( const float _x, const float _y )
{
   _mOrigin.x = _x;
   _mOrigin.y = _y;
   _mLocation = _mOrigin;
   fixInternalShape();
}

void Room::setOrigin( const Vector2 &loc )
{
   _mOrigin   = loc;
   _mLocation = _mOrigin;
   fixInternalShape();
}

void Room::updateLocationWithCameraOffset( const Vector2 &offset )
{
   _mLocation.x = _mOrigin.x + offset.x;
   _mLocation.y = _mOrigin.y + offset.y;
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

void Room::setNeighbor( std::shared_ptr<Room> nbor, spaces_defs::SpacesNeighbors i )
{
   _mNeighbors[static_cast<size_t>( i )] = nbor;

   switch ( i )
   {
      case spaces_defs::SpacesNeighbors::LEFT:
         nbor->setOne( shared_from_this(), spaces_defs::SpacesNeighbors::RIGHT );
         nbor->setOrigin( this->_mLocation.x - 1500.0f, this->_mLocation.y );
         break;
      case spaces_defs::SpacesNeighbors::RIGHT:
         nbor->setOne( shared_from_this(), spaces_defs::SpacesNeighbors::LEFT );
         nbor->setOrigin( this->_mLocation.x + 1500.0f, this->_mLocation.y );
         break;

      case spaces_defs::SpacesNeighbors::UP:
         nbor->setOne( shared_from_this(), spaces_defs::SpacesNeighbors::DOWN );
         nbor->setOrigin( this->_mLocation.x, this->_mLocation.y - 750.0f );
         break;
      case spaces_defs::SpacesNeighbors::DOWN:
         nbor->setOne( shared_from_this(), spaces_defs::SpacesNeighbors::UP );
         nbor->setOrigin( this->_mLocation.x, this->_mLocation.y + 750.0f );
         break;

      default:
         break;
   }

}

void Room::setOne( std::shared_ptr<Room> nbor, spaces_defs::SpacesNeighbors i )
{
   _mNeighbors[static_cast<size_t>( i )] = nbor;
}

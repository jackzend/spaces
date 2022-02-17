#include "room.h"

Room::Room()
   :
   _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mNeighbors( std::vector<std::weak_ptr<Room> >( 4 ) ),
   _mLocation(),
   _mOrigin(),
   _mName( "Empty!" )
{
   _mRoomShape_ptr   = std::make_unique<ShapeWrap<Rectangle> >( spaces_defs::SPACES_ROOM );
   _mRoomColor_ptr   = std::make_unique<ColorWrap>( spaces_defs::SPACES_MINT );
   _mRoomOutline_ptr = std::make_unique<ColorWrap>( spaces_defs::SPACES_DARK_MINT );
   setOrigin( 0.0f, 0.0f );
}
Room::Room( const std::string aName )
   :
   _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mNeighbors( std::vector<std::weak_ptr<Room> >( 4 ) ),
   _mLocation(),
   _mOrigin(),
   _mName( aName )
{
   _mRoomShape_ptr   = std::make_unique<ShapeWrap<Rectangle> >( spaces_defs::SPACES_ROOM );
   _mRoomColor_ptr   = std::make_unique<ColorWrap>( spaces_defs::SPACES_MINT );
   _mRoomOutline_ptr = std::make_unique<ColorWrap>( spaces_defs::SPACES_DARK_MINT );
   setOrigin( 0.0f, 0.0f );
}

void Room::drawRoom()
{
   DrawRectangleRec( getShape(), getRoomColor() );
   DrawRectangleLinesEx( getShape(), 10.0f, getRoomOutlineColor() );
   DrawText( _mName.c_str(),
             ( int )( _mLocation.x + ( ( float )spaces_defs::SPACES_SCREEN_WIDTH / 2.0f ) ), // calculates offset from current location
             ( int )( _mLocation.y + ( ( float )spaces_defs::SPACES_SCREEN_HEIGHT / 2.0f ) ),
             20,
             DARKGREEN );
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
   if ( is_uninitialized( _mNeighbors[static_cast<size_t>( i )] ) )
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
   else
   {
      std::cout << "ERROR: THIS ROOM ALREADY HAS A NEIGHBOR THERE" << std::endl;
   }

}

void Room::setOne( std::shared_ptr<Room> nbor, spaces_defs::SpacesNeighbors i )
{
   if ( is_uninitialized( _mNeighbors[static_cast<size_t>( i )] ) )
   {
      _mNeighbors[static_cast<size_t>( i )] = nbor;
   }
}

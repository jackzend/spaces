#include "room.h"

Room::Room()
   : _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mRoomNameColor_ptr( nullptr ),
   _mNeighbors( std::vector<std::weak_ptr<Room> >( 4 ) ),
   _mLocation(),
   _mOrigin(),
   _mName( "Empty!" )
{
   _mRoomShape_ptr     = std::make_unique<ShapeWrap<Rectangle> >( SPACES_ROOM );
   _mRoomColor_ptr     = std::make_unique<ColorWrap>( SPACES_MINT );
   _mRoomOutline_ptr   = std::make_unique<ColorWrap>( SPACES_DARK_MINT );
   _mRoomNameColor_ptr = std::make_unique<ColorWrap>( SPACES_DARK_MINT );
   setOrigin( 0.0f, 0.0f );
}
Room::Room( const std::string aName )
   : _mRoomShape_ptr( nullptr ),
   _mRoomColor_ptr( nullptr ),
   _mRoomOutline_ptr( nullptr ),
   _mNeighbors( std::vector<std::weak_ptr<Room> >( 4 ) ),
   _mLocation(),
   _mOrigin(),
   _mName( aName )
{
   // we can move these into the constructor list later
   _mRoomShape_ptr     = std::make_unique<ShapeWrap<Rectangle> >( SPACES_ROOM );
   _mRoomColor_ptr     = std::make_unique<ColorWrap>( SPACES_MINT );
   _mRoomOutline_ptr   = std::make_unique<ColorWrap>( SPACES_DARK_MINT );
   _mRoomNameColor_ptr = std::make_unique<ColorWrap>( SPACES_DARK_MINT );
   setOrigin( 0.0f, 0.0f );
}

void Room::drawRoom()
{
   DrawRectangleRec( getShape(), getRoomColor() );
   DrawRectangleLinesEx( getShape(), SPACES_WALL_THICKNESS, getRoomOutlineColor() );
   DrawText( _mName.c_str(),
             ( ( int )( _mLocation.x + ( ( float )SPACES_SCREEN_WIDTH / 2.0f ) ) - ( ( float )MeasureText( _mName.c_str(), SPACES_TEXT_HEIGHT ) ) / 2.0f ), // calculates offset from current location
             ( int )( _mLocation.y + ( ( float )SPACES_SCREEN_HEIGHT / 2.0f ) ) - SPACES_TEXT_HEIGHT / 2.0f,
             ( int )SPACES_TEXT_HEIGHT,
             _mRoomNameColor_ptr->getColor() );
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
   auto temp = _mRoomShape_ptr->getShape();
   temp.x = _mLocation.x + ( ( float )SPACES_SCREEN_WIDTH / 2.0f ) - ( SPACES_ROOM_WIDTH / 2.0f );
   temp.y = _mLocation.y + ( ( float )SPACES_SCREEN_HEIGHT / 2.0f ) - ( SPACES_ROOM_HEIGHT / 2.0f );
   _mRoomShape_ptr->setShape( temp );
}

bool Room::setNeighbor( std::shared_ptr<Room> nbor, SpacesNeighbors i )
{
   if ( is_uninitialized( _mNeighbors[static_cast<size_t>( i )] ) )
   {
      _mNeighbors[static_cast<size_t>( i )] = nbor;

      switch ( i )
      {
         case SpacesNeighbors::LEFT:
            nbor->setOne( shared_from_this(), SpacesNeighbors::RIGHT );
            nbor->setOrigin( this->_mOrigin.x - SPACES_ROOM_WIDTH, this->_mOrigin.y );
            break;
         case SpacesNeighbors::RIGHT:
            nbor->setOne( shared_from_this(), SpacesNeighbors::LEFT );
            nbor->setOrigin( this->_mOrigin.x + SPACES_ROOM_WIDTH, this->_mOrigin.y );
            break;

         case SpacesNeighbors::UP:
            nbor->setOne( shared_from_this(), SpacesNeighbors::DOWN );
            nbor->setOrigin( this->_mOrigin.x, this->_mOrigin.y - SPACES_ROOM_HEIGHT );
            break;
         case SpacesNeighbors::DOWN:
            nbor->setOne( shared_from_this(), SpacesNeighbors::UP );
            nbor->setOrigin( this->_mOrigin.x, this->_mOrigin.y + SPACES_ROOM_HEIGHT );
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

void Room::setOne( std::shared_ptr<Room> nbor, SpacesNeighbors i )
{
   if ( is_uninitialized( _mNeighbors[static_cast<size_t>( i )] ) )
   {
      _mNeighbors[static_cast<size_t>( i )] = nbor;
   }
}

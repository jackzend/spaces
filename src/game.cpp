#include "game.h"

Game::Game( const std::string aSeedName )
   :
   _mSpaces(),
   _mCurrentRoom( nullptr ),
   _mNextId( 0u ),
   _mCam(),
   _mBackgroundColor( SPACES_GREEN.getColor() )
{
   generateOrigin( aSeedName,
                   SPACES_MINT.getColor(),
                   SPACES_DARK_MINT.getColor(),
                   SPACES_DARK_MINT.getColor() );
}

void Game::generateOrigin( const std::string &aName,
                           const Color       &aRoomColor,
                           const Color       &aRoomOutlineColor,
                           const Color       &aRoomNameColor
                           )
{
   _mCurrentRoom = std::make_shared<Room>( aName );
   _mCurrentRoom->setRoomColor( aRoomColor );
   _mCurrentRoom->setRoomOutlineColor( aRoomOutlineColor );
   _mCurrentRoom->setRoomNameColor( aRoomNameColor );

   _mSpaces[_mNextId++] = _mCurrentRoom;
}

void Game::generateRoom( const std::string     &aName,
                         const Color           &aRoomColor,
                         const Color           &aRoomOutlineColor,
                         const Color           &aRoomNameColor,
                         const SpacesNeighbors i )
{
   room_ptr new_room = std::make_shared<Room>( aName );
   new_room->setRoomColor( aRoomColor );
   new_room->setRoomOutlineColor( aRoomOutlineColor );
   new_room->setRoomNameColor( aRoomNameColor );
   if ( _mCurrentRoom->setNeighbor( new_room, i ) )
   {
      _mSpaces[_mNextId++] = new_room;
   }
}

void Game::resetCurrentRoom( const Vector2 aCameraPos )
{
   for ( auto & [k, v] : _mSpaces )
   {
      std::cout << "Checking room: " << k << std::endl;
      if ( isInRoom( aCameraPos, v->getOrigin() ) )
      {
         std::cout << "Is in room: " << k << std::endl;
         _mCurrentRoom = v;
         return;
      }
   }
}

bool Game::isInRoom( const Vector2 aCameraPos, const Vector2 aRoomOrigin )
{
   bool checkPosX = ( aCameraPos.x <= ( aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f ) );
   bool checkNegX = ( aCameraPos.x >= ( aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f ) );

   bool checkPosY = ( aCameraPos.y <= ( aRoomOrigin.y + SPACES_ROOM_WIDTH / 2.0f ) );
   bool checkNegY = ( aCameraPos.y >= ( aRoomOrigin.y - SPACES_ROOM_WIDTH / 2.0f ) );

   if ( checkPosX and checkNegX and checkPosY and checkNegY )
   {
      return true;
   }
   else
   {
      return false;
   }
}

void Game::gameLoop()
{
   checkInputs();
   updateStep();
   drawObjects();
}

void Game::checkInputs()
{
   if ( IsKeyPressed( KEY_F11 ) )
   {
      ToggleFullscreen();
   }

   if ( IsKeyDown( KEY_UP ) )
   {
      if ( IsKeyDown( KEY_LEFT ) )
      {
         _mCam.decrementX();
      }
      else if ( IsKeyDown( KEY_RIGHT ) )
      {
         _mCam.incrementX();
      }
      _mCam.decrementY();
   }
   else if ( IsKeyDown( KEY_DOWN ) )
   {
      if ( IsKeyDown( KEY_LEFT ) )
      {
         _mCam.decrementX();
      }
      else if ( IsKeyDown( KEY_RIGHT ) )
      {
         _mCam.incrementX();
      }
      _mCam.incrementY();
   }
   else if ( IsKeyDown( KEY_LEFT ) )
   {
      _mCam.decrementX();
   }
   else if ( IsKeyDown( KEY_RIGHT ) )
   {
      _mCam.incrementX();
   }

   if ( IsKeyPressed( KEY_A ) )
   {
      std::string test = "Test Room";
      generateRoom( test, GREEN, DARKGREEN, DARKGREEN, SpacesNeighbors::LEFT );
   }
   else if ( IsKeyPressed( KEY_D ) )
   {
      std::string test = "Test Room";
      generateRoom( test, BLUE, DARKBLUE, DARKBLUE, SpacesNeighbors::RIGHT );
   }
   else if ( IsKeyPressed( KEY_W ) )
   {
      std::string test = "Test Room";
      generateRoom( test, PURPLE, DARKPURPLE, DARKPURPLE, SpacesNeighbors::UP );
   }
   else if ( IsKeyPressed( KEY_S ) )
   {
      std::string test = "Test Room";
      generateRoom( test, GRAY, DARKGRAY, DARKGRAY, SpacesNeighbors::DOWN );
   }

}

void Game::drawObjects()
{
   BeginDrawing();
   for ( auto &[k, v] : _mSpaces )
   {
      v->drawRoom();
   }
   ClearBackground( _mBackgroundColor );
   _mCam.drawSprite();
   DrawText( "Testing", 10, 10, 20, DARKGREEN );
   DrawFPS( 10, 50 );
   EndDrawing();
}

void Game::updateStep()
{
   resetCurrentRoom( _mCam.getLocation() );
   auto offset = _mCam.getOffset();
   for ( auto & [k, v] : _mSpaces )
   {
      v->updateLocationWithCameraOffset( offset );
   }
}

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <unordered_map>
#include "room.h"
#include "spaces_camera.h"
#include "spaces_defs.h"

using namespace spaces_defs;
using room_ptr = std::shared_ptr<Room>;
class Game
{
   std::unordered_map<size_t, std::shared_ptr<Room> > _mSpaces; // this may need to be a shared pointer actuall
   std::shared_ptr<Room> _mCurrentRoom;
   size_t _mNextId;
   SpacesCamera _mCam;
   Color _mBackgroundColor;

   void generateOrigin( const std::string &aName,
                        const Color       &aRoomColor,
                        const Color       &aRoomOutlineColor,
                        const Color       &aRoomNameColor
                        );
   bool isInRoom( const Vector2 aCameraPos,
                  const Vector2 aRoomOrigin );
   bool isTouchingWallLR( const Vector2 aCameraPos,
                          const Vector2 aRoomOrigin ); // touching sidewalls
   bool isTouchingWallUD( const Vector2 aCameraPos,
                          const Vector2 aRoomOrigin ); // touching top or bottom walls
   public:
      Game() = delete;
      Game( const std::string aSeedName );
      void generateRoom( const std::string     &aName,
                         const Color           &aRoomColor,
                         const Color           &aRoomOutlineColor,
                         const Color           &aRoomNameColor,
                         const SpacesNeighbors i );

      void resetCurrentRoom( const Vector2 aCameraPos );

      void gameLoop();

      void checkInputs();

      void drawObjects();

      void updateStep();
};

#endif //GAME_H

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <unordered_map>
#include "room.h"
#include "spaces_camera.h"
#include "spaces_defs.h"
#include <string>
#include <queue>
using namespace spaces_defs;
using room_ptr = std::shared_ptr<Room>;
class Game
{
   std::unordered_map<size_t, std::shared_ptr<Room>> _mSpaces; // this may need to be a shared pointer actuall
   std::shared_ptr<Room> _mCurrentRoom;
   size_t _mNextId;
   SpacesCamera _mCam;
   Color _mBackgroundColor;
   size_t _mCurrentID;

   // random color suppport
   std::random_device _mRd;
   std::mt19937 _mGen;
   std::uniform_int_distribution<> _mDist;

   void generateOrigin(const std::string &aName,
                       const Color &aRoomColor,
                       const Color &aRoomOutlineColor,
                       const Color &aRoomNameColor);
   bool isInRoom(const Vector2 aCameraPos,
                 const Vector2 aRoomOrigin);

   bool isTouchingLeftWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin);
   bool isTouchingRightWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin);
   bool isTouchingDownWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin);
   bool isTouchingUpWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin);

   bool isWithinDoorBoundsLR(const Vector2 aCameraPos, const Vector2 aRoomOrigin);
   bool isWithinDoorBoundsUD(const Vector2 aCameraPos, const Vector2 aRoomOrigin);

   void checkInputs();
   void drawObjects();
   void updateStep();
   void generateRoom(const std::string &aName,
                     const Color &aRoomColor,
                     const Color &aRoomOutlineColor,
                     const Color &aRoomNameColor,
                     const SpacesNeighbors i);

   void resetCurrentRoom(const Vector2 aCameraPos);

   void drawNearbyRooms();

public:
   Game() = delete;
   Game(const std::string aSeedName);

   void gameLoop();
};

#endif // GAME_H

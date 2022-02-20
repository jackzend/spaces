#include "game.h"

Game::Game(const std::string aSeedName)
    : _mSpaces(),
      _mCurrentRoom(nullptr),
      _mNextId(0u),
      _mCam(),
      _mBackgroundColor(SPACES_GREEN.getColor()),
      _mRd(),
      _mGen(_mRd()),
      _mDist(0, 255),
      _mCurrentID(0)
{
   generateOrigin(aSeedName,
                  SPACES_MINT.getColor(),
                  SPACES_DARK_MINT.getColor(),
                  SPACES_DARK_MINT.getColor());
}

void Game::generateOrigin(const std::string &aName,
                          const Color &aRoomColor,
                          const Color &aRoomOutlineColor,
                          const Color &aRoomNameColor)
{
   _mCurrentRoom = std::make_shared<Room>(aName);
   _mCurrentRoom->setRoomColor(aRoomColor);
   _mCurrentRoom->setRoomOutlineColor(aRoomOutlineColor);
   _mCurrentRoom->setRoomNameColor(aRoomNameColor);
   _mCurrentRoom->setID(_mNextId);

   _mSpaces[_mNextId++] = _mCurrentRoom;
}

void Game::generateRoom(const std::string &aName,
                        const Color &aRoomColor,
                        const Color &aRoomOutlineColor,
                        const Color &aRoomNameColor,
                        const SpacesNeighbors i)
{
   room_ptr new_room = std::make_shared<Room>(aName);
   new_room->setRoomColor(aRoomColor);
   new_room->setRoomOutlineColor(aRoomOutlineColor);
   new_room->setRoomNameColor(aRoomNameColor);
   new_room->setID(_mNextId);
   if (_mCurrentRoom->setNeighbor(new_room, i))
   {
      _mSpaces[_mNextId++] = new_room;
   }
}

void Game::resetCurrentRoom(const Vector2 aCameraPos)
{
   for (auto &[k, v] : _mSpaces)
   {
      if (isInRoom(aCameraPos, v->getOrigin()))
      {
         _mCurrentRoom = v;
         _mCurrentID = k;
         return;
      }
   }
}

bool Game::isInRoom(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkPosX = (aCameraPos.x <= (aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f));
   bool checkNegX = (aCameraPos.x >= (aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f));

   bool checkPosY = (aCameraPos.y <= (aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f));
   bool checkNegY = (aCameraPos.y >= (aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f));

   if (checkPosX and checkNegX and checkPosY and checkNegY)
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Game::isWithinDoorBoundsLR(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool doorCheckDown = (int)(aCameraPos.y) + (SPACES_SPRITE_HEIGHT / 2.0f) <= (int)(aRoomOrigin.y + SPACES_DOOR_HEIGHT / 2.0f);
   bool doorCheckUp = (int)(aCameraPos.y) - (SPACES_SPRITE_HEIGHT / 2.0f) >= (int)(aRoomOrigin.y - SPACES_DOOR_HEIGHT / 2.0f);

   if (doorCheckDown and doorCheckUp)
   {
      return true;
   }
   return false;
}

bool Game::isWithinDoorBoundsUD(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool doorCheckRight = (int)(aCameraPos.x) + (SPACES_SPRITE_HEIGHT / 2.0f) <= (int)(aRoomOrigin.x + SPACES_DOOR_HEIGHT / 2.0f);
   bool doorCheckLeft = (int)(aCameraPos.x) - (SPACES_SPRITE_HEIGHT / 2.0f) >= (int)(aRoomOrigin.x - SPACES_DOOR_HEIGHT / 2.0f);

   if (doorCheckLeft and doorCheckRight)
   {
      return true;
   }
   return false;
}
/*bool Game::isTouchingWallLR(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkRight = (int)(aCameraPos.x + (SPACES_SPRITE_HEIGHT / 2.0f)) >= (int)((aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f) - SPACES_WALL_THICKNESS);
   bool checkLeft = (int)(aCameraPos.x - (SPACES_SPRITE_HEIGHT / 2.0f)) <= (int)((aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f) + SPACES_WALL_THICKNESS);

   if (checkRight)
   {
      _mCam.setLocation((aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f), aCameraPos.y);
      return true;
   }
   else if (checkLeft)
   {
      _mCam.setLocation((aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f), aCameraPos.y);
      return true;
   }

   return false;
}*/

bool Game::isTouchingLeftWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkLeft = (int)(aCameraPos.x - (SPACES_SPRITE_HEIGHT / 2.0f)) <= (int)((aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f) + SPACES_WALL_THICKNESS);
   if (checkLeft)
   {
      return true;
   }
   return false;
}
bool Game::isTouchingRightWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkRight = (int)(aCameraPos.x + (SPACES_SPRITE_HEIGHT / 2.0f)) >= (int)((aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f) - SPACES_WALL_THICKNESS);
   if (checkRight)
   {
      return true;
   }
   return false;
}
bool Game::isTouchingDownWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkDown = (int)(aCameraPos.y + (SPACES_SPRITE_HEIGHT / 2.0f)) >= (int)((aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f) - SPACES_WALL_THICKNESS);
   if (checkDown)
   {
      return true;
   }
   return false;
}
bool Game::isTouchingUpWall(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkUp = (int)(aCameraPos.y - (SPACES_SPRITE_HEIGHT / 2.0f)) <= (int)((aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f) + SPACES_WALL_THICKNESS);
   if (checkUp)
   {
      return true;
   }
   return false;
}

/*bool Game::isTouchingWallUD(const Vector2 aCameraPos, const Vector2 aRoomOrigin)
{
   bool checkDown = (int)(aCameraPos.y + (SPACES_SPRITE_HEIGHT / 2.0f)) >= (int)((aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f) - SPACES_WALL_THICKNESS);
   bool checkUp = (int)(aCameraPos.y - (SPACES_SPRITE_HEIGHT / 2.0f)) <= (int)((aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f) + SPACES_WALL_THICKNESS);
   if (checkDown or checkUp)
   {
      if (checkDown)
      {
         _mCam.setLocation(aCameraPos.x, (aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f));
      }
      else if (checkUp)
      {
         _mCam.setLocation(aCameraPos.x, (aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f));
      }

      return true;
   }
   return false;
} */

void Game::gameLoop()
{
   checkInputs();
   updateStep();
   drawObjects();
}

void Game::checkInputs()
{
   if (IsKeyPressed(KEY_F11))
   {
      ToggleFullscreen();
   }

   if (IsKeyDown(KEY_UP))
   {
      if (IsKeyDown(KEY_LEFT))
      {
         _mCam.decrementX();
      }
      else if (IsKeyDown(KEY_RIGHT))
      {
         _mCam.incrementX();
      }
      _mCam.decrementY();
   }
   else if (IsKeyDown(KEY_DOWN))
   {
      if (IsKeyDown(KEY_LEFT))
      {
         _mCam.decrementX();
      }
      else if (IsKeyDown(KEY_RIGHT))
      {
         _mCam.incrementX();
      }
      _mCam.incrementY();
   }
   else if (IsKeyDown(KEY_LEFT))
   {
      if (IsKeyDown(KEY_DOWN))
      {
         _mCam.incrementY();
      }
      else if (IsKeyDown(KEY_UP))
      {
         _mCam.decrementY();
      }
      _mCam.decrementX();
   }
   else if (IsKeyDown(KEY_RIGHT))
   {
      if (IsKeyDown(KEY_DOWN))
      {
         _mCam.incrementY();
      }
      else if (IsKeyDown(KEY_UP))
      {
         _mCam.decrementY();
      }
      _mCam.incrementX();
   }
   auto aRoomOrigin = _mCurrentRoom->getOrigin();
   auto aCameraPos = _mCam.getLocation();

   auto isInLeftRightDoor = isWithinDoorBoundsLR(aCameraPos, aRoomOrigin);
   auto isInUpDownDoor = isWithinDoorBoundsUD(aCameraPos, aRoomOrigin);

   auto hasLeftDoor = _mCurrentRoom->getDoorStatus(SpacesNeighbors::LEFT);
   auto hasRightDoor = _mCurrentRoom->getDoorStatus(SpacesNeighbors::RIGHT);
   auto hasUpDoor = _mCurrentRoom->getDoorStatus(SpacesNeighbors::UP);
   auto hasDownDoor = _mCurrentRoom->getDoorStatus(SpacesNeighbors::DOWN);

   if (isTouchingLeftWall(aCameraPos, aRoomOrigin))
   {
      if (!(hasLeftDoor and isInLeftRightDoor))
      {
         _mCam.setLocation((aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f), aCameraPos.y);
      }
   }
   if (isTouchingRightWall(aCameraPos, aRoomOrigin))
   {
      if (!(hasRightDoor and isInLeftRightDoor))
      {
         _mCam.setLocation((aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f), aCameraPos.y);
      }
   }
   if (isTouchingUpWall(aCameraPos, aRoomOrigin))
   {
      if (!(hasUpDoor and isInUpDownDoor))
      {
         _mCam.setLocation(aCameraPos.x, (aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f));
      }
   }
   if (isTouchingDownWall(aCameraPos, aRoomOrigin))
   {
      if (!(hasDownDoor and isInUpDownDoor))
      {
         _mCam.setLocation(aCameraPos.x, (aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f));
      }
   }

   if (isTouchingLeftWall(aCameraPos, aRoomOrigin) and isTouchingUpWall(aCameraPos, aRoomOrigin))
   {
      _mCam.setLocation((aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f), (aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f));
   }
   if (isTouchingRightWall(aCameraPos, aRoomOrigin) and isTouchingUpWall(aCameraPos, aRoomOrigin))
   {
      _mCam.setLocation((aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f), (aRoomOrigin.y - SPACES_ROOM_HEIGHT / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f));
   }
   if (isTouchingLeftWall(aCameraPos, aRoomOrigin) and isTouchingDownWall(aCameraPos, aRoomOrigin))
   {
      _mCam.setLocation((aRoomOrigin.x - SPACES_ROOM_WIDTH / 2.0f) + SPACES_WALL_THICKNESS + (SPACES_SPRITE_HEIGHT / 2.0f), (aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f));
   }
   if (isTouchingRightWall(aCameraPos, aRoomOrigin) and isTouchingDownWall(aCameraPos, aRoomOrigin))
   {
      _mCam.setLocation((aRoomOrigin.x + SPACES_ROOM_WIDTH / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f), (aRoomOrigin.y + SPACES_ROOM_HEIGHT / 2.0f) - SPACES_WALL_THICKNESS - (SPACES_SPRITE_HEIGHT / 2.0f));
   }

   ColorWrap randomColor1(_mDist(_mGen), _mDist(_mGen), _mDist(_mGen), 255);
   ColorWrap randomColor2(_mDist(_mGen), _mDist(_mGen), _mDist(_mGen), 255);

   if (IsKeyPressed(KEY_A))
   {
      std::string test = "Test Room";
      generateRoom(test, randomColor1.getColor(), randomColor2.getColor(), randomColor2.getColor(), SpacesNeighbors::LEFT);
   }
   else if (IsKeyPressed(KEY_D))
   {
      std::string test = "Test Room";
      generateRoom(test, randomColor1.getColor(), randomColor2.getColor(), randomColor2.getColor(), SpacesNeighbors::RIGHT);
   }
   else if (IsKeyPressed(KEY_W))
   {
      std::string test = "Test Room";
      generateRoom(test, randomColor1.getColor(), randomColor2.getColor(), randomColor2.getColor(), SpacesNeighbors::UP);
   }
   else if (IsKeyPressed(KEY_S))
   {
      std::string test = "Test Room";
      generateRoom(test, randomColor1.getColor(), randomColor2.getColor(), randomColor2.getColor(), SpacesNeighbors::DOWN);
   }
}

void Game::drawNearbyRooms()
{
   std::vector<bool> visited(_mSpaces.size(), false);
   std::queue<size_t> room_queue;
   room_queue.push(_mCurrentID);

   int num_drawn = 0;
   while (!room_queue.empty() and num_drawn <= SPACES_MAX_RENDER_ROOMS)
   {
      size_t s = room_queue.front();
      room_queue.pop();
      visited[s] = true;
      _mSpaces[s]->drawRoom();
      num_drawn++;

      auto nbors = _mSpaces[s]->getNeighborIDs();
      std::cout << "Current ID: " << _mSpaces[s]->getID() << std::endl;
      std::cout << "Neighbors: ";
      for (auto &i : nbors)
      {
         std::cout << i << " ";
         if (!visited[i])
         {
            room_queue.push(i);
         }
      }
      std::cout << std::endl;
   }
   DrawText(std::string("Room Render Count: " + std::to_string(num_drawn)).c_str(), 10, 110, 20, DARKGREEN);
}

void Game::drawObjects()
{
   BeginDrawing();
   drawNearbyRooms();
   ClearBackground(_mBackgroundColor);
   _mCam.drawSprite();
   DrawText("Testing", 10, 10, 20, DARKGREEN);
   DrawText(std::string("Room Count: " + std::to_string(_mNextId)).c_str(), 10, 80, 20, DARKGREEN);
   DrawFPS(10, 50);
   EndDrawing();
}

void Game::updateStep()
{
   resetCurrentRoom(_mCam.getLocation());
   auto offset = _mCam.getOffset();
   for (auto &[k, v] : _mSpaces)
   {
      v->updateLocationWithCameraOffset(offset);
   }
}

/// \file
/// \brief Interface file for game class -- game.h
//
/// Game Interface class 

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class Player;
class GameMap;

typedef string PlayerName;

/// Game Interface class specifies the bahavior of the game object
class Game {
  public:
   virtual ~Game() {}

   //accessors
   /// \return all the system Players
   virtual std::vector<Player> systemPlayers() const =0;

   /// \return all the regular Players
   virtual std::vector<Player> players() const =0;

   /// \return if the game has winner and who it is
   virtual Player* winner() const =0;

   /// \return the player which has the current turn
   virtual Player* currentTurn() const =0;

   /// \return the GameMap of the current game.
   virtual GameMap* currentGame() const =0;
   
   //mutators
   /// \param all the players playing this game
   //
   /// \post perfoems all operations needed to play a game
   virtual void SetupGame(std::vector<PlayerName>) =0;
   
};

#endif

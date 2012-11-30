#include "defaultgame.h"

DefaultGame::DefaultGame(GameMap * g=NULL):gMap(g){}

DefaultGame::~DefaultGame() {}

DefaultGame::playerlist DefaultGame::systemPlayers() const{}

/// \return all the regular Players
DefaultGame::playerlist DefaultGame::players() const{}

/// \return if the game has winner and who it is
// cppcheck-suppress unusedFunction 
Player* DefaultGame::winner() const{}

/// \return the player which has the current turn
// cppcheck-suppress unusedFunction
Player* DefaultGame::currentTurn() const{}

/// \return the GameMap of the current game.
// cppcheck-suppress unusedFunction
GameMap* DefaultGame::currentGame() const{}
   
//mutators
/// \param playerlist -- all the players playing this game
//
/// performs all operations needed to initialize game state
void DefaultGame::SetupGame( std::vector< PlayerName > playernames ){}

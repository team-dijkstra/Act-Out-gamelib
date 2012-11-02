#ifndef ___GAME_H
#define ___GAME_H

class Game {
   List<Player> systemPlayers() =0;
   List<Player> players() =0;
   SetupGame(List<PlayerNames>) =0;
   Player winner() =0;
   Player currentTurn() =0;
   GameMap currentGame() =0;
   
};

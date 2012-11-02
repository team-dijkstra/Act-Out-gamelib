#ifndef GAME_H
#define GAME_H

class Game {
   virtaul List<Player> systemPlayers() =0;
   virtual List<Player> players() =0;
   virtual SetupGame(List<PlayerNames>) =0;
   virtual Player winner() =0;
   virtual Player currentTurn() =0;
   virtual GameMap currentGame() =0;
   
};

#endif

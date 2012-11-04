/// \file
/// \brief Interface file for GameMap Class -- gamemap.h
//
/// GameMap interface, specifies behaviour for game maps

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <string>

class Player;
class Territory;

typedef string TerritoryName;
typedef string operation; // <-unsure what operations there are, will define opeations later
typedef string check; // <-unsure what checks there should be, will define opeations later

/// The GameMap interface class.
//
/// This class is reponsible for representing the collection of Territories in the
/// game, returning relevant information and performing operations on specified territories 
class GameMap {
  public:
   virtual ~GameMap() {}

   //accessors
   /// Finds the specified Territory
   //
   /// \param a string representing the TerritoryName
   /// \return the specified Territory
   virtual Territory find(TerritoryName) const =0;

   /// Finds all Territories that are adjacent to the specified Territory
   //
   /// \param reference to a Territory object
   /// \return all Territories that are adjacent to the specified Territory
   virtual std::vector<Territory> adjacencies(Territory *) const =0;

   /// Finds all Territories that are owned by the specified Player
   //
   /// \param reference to a Player object
   /// \return all Territories owned by the given player
   virtual std::vector<Territory> players(Player *) const =0;

   //mutators
   /// Traverses all territories and performs the specified operation
   //
   /// \param operation to be performed
   /// \param check to see if operation should be performed on specific Territory
   /// \param Territory to start with
   //
   /// \return a list of Territories which have been operated on
   virtual std::vector<Territory> traverse(operation, check, Territory * start) =0;
   
};

#endif

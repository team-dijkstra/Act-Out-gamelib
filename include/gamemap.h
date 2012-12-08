/*
Act-Out! game library - implements generic game logic.
Copyright (C) 2012 Rio Lowry, Chris Pinter, Matt Voroney

This file is part of Act-Out!

Act-Out! is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Act-Out! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Act-Out!.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * \file gamemap.h -- Interface file for GameMap Interface
 *
 * GameMap interface, specifies behaviour for GameMap implementations.
 */
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <utility>
#include <string>

class Player;
class Territory;
class TerritoryOperation;


typedef std::string TerritoryName; ///<  string of name of Territory

/**
 * \interface GameMap
 *
 * Implementations are responsible for managing the collection of Territory
 * objects in the game, returning relevant information and performing 
 * operations on the managed set of Territory objects.
 *
 * \note Implementations should assume ownership of any contained Territory
 *  objects and delete them when thier destructor is called. Any different 
 *  behavior should be explicitly noted.
 */
class GameMap {
  public:

   typedef std::vector<Territory*> TerritoryList; ///<  vector of pointers to territories

   typedef std::pair<Territory*, Territory*> Adjacency; ///<  pair of pointers to territories

   typedef std::vector<Adjacency> AdjacencyList; ///<  vector of adjacencies

   /**
    * Virtual base constructor. Implementations must override this.
    */
   virtual ~GameMap() {}
    
   //constants
   
   /**
    * \return a sentinel node. Used to indicate non-existent values in
    *   search operations.
    */
   static const Territory* end() {return NULL;}

   //accessors
   
   /**
    * \return the start territory. Which territory this is is implementation
    *   defined.
    */
   virtual Territory* begin() const =0;
   
   /**
    * Finds the specified Territory
    *
    * \param fn -- string representing the TerritoryName
    * \return the specified Territory, or a sentinel if not found.
    *
    * \see StlGameMap::end the sentinel node of this class.
    */
   virtual Territory* find(TerritoryName fn) const =0;

   /**
    * Finds all Territories that are adjacent to the specified Territory
    *
    * \param t -- The Territory to find the adjacencies of.
    * \return all Territories that are adjacent to the specified Territory
    */
   virtual TerritoryList adjacencies(const Territory * t) const =0;

   /**
    * Finds all Territories that are owned by the specified Player
    *
    * \param p -- pointer to a Player object
    * \return all Territories owned by the given player
    *
    * \deprecated The same functionality can be trivially achieved with
    * the following code:
    *
    * \code{.cpp}
    * FilterByTerritoryOwner predicate("Fred");
    * GameMap::TerritoryList tl = filter(&predicate);
    * \endcode
    *
    * \see filter() for a more general variant of this method.
    */
   virtual TerritoryList players(Player * p) const =0;

   /**
    * Retrieves all Territories that match the specified predicate.
    * This method is intended to provide a variant of the visitor pattern.
    *
    * \param predicate -- A TerritoryOperation to use as a selection predicate
    *   for the returned list of territories. All and only the Territories that
    *   this predicate returns \c true for will be in the returned list.
    *
    * \return the list of Territory objects selected by the supplied \c 
    *   predicate.
    *
    * \see http://en.wikipedia.org/wiki/Visitor_pattern
    * \see traverse() for a variant of this method suitable for implementing
    *   transformations.
    */
   virtual TerritoryList filter(TerritoryOperation * predicate) const =0;

   //mutators
   
   /**
    * Traverses all territories and performs the specified operation on each.
    * This method is intended to provide a variant of the visitor pattern.
    * 
    * \param op -- operation to be performed
    * \param start -- Territory to start with.
    *
    * \see http://en.wikipedia.org/wiki/Visitor_pattern
    * \see filter() for a variant of this method suitable for subset extraction.
    */
   virtual void traverse(TerritoryOperation * op, Territory * start) =0;

};

#endif

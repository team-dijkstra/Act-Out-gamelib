
#include "territory.h"
#include "stlgamemap.h"

StlGameMap::StlGameMap(const TerritoryList & tl, const TerritoryConnections & c) {
    /// \todo build graph.
}

StlGameMap::~StlGameMap() {}

Territory* StlGameMap::find(TerritoryName) const {
   return NULL; 
}


TerritoryList StlGameMap::adjacencies(Territory *) const {
   return TerritoryList();
}


TerritoryList StlGameMap::players(Player *) const {
   return TerritoryList(); 
}


void StlGameMap::traverse(TerritoryOperation * op, Territory * start) {
   //foo
}


TerritoryList StlGameMap::filter(TerritoryOperation * op) const {
   return TerritoryList(); 
}


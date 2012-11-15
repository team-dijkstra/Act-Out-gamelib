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

#include <map>
#include <utility>
#include <algorithm>
#include "territory.h"
#include "stlgamemap.h"

StlGameMap::StlGameMap(const AdjacencyList & tal) {
    typedef MapNode::first_type key_t;
    typedef MapNode::second_type value_t;
    typedef std::map<key_t, value_t> map_t;
    /// \todo define a comparator for this map.
    map_t tmap;

    // build adjacency lists for each node.
    for (AdjacencyList::const_iterator it = tal.begin(); it != tal.end(); it++) {
        
        // establish bidirectional relationships.
        tmap[it->first].push_back(it->second);
        tmap[it->second].push_back(it->first);
    }

    // copy out the results in sorted order.
    for (map_t::iterator it = tmap.begin(); it != tmap.end(); it++) {
        /// \todo need to implement comparator for unique
        value_t & vt = it->second;
        value_t::iterator res = std::unique(vt.begin(), vt.end());
        vt.resize(res - vt.begin());

        territories.push_back(std::make_pair(it->first, vt));
    }
}

StlGameMap::~StlGameMap() {}

Territory* StlGameMap::begin() const {
    return NULL;
}

Territory* StlGameMap::find(TerritoryName) const {
   return NULL; 
}


GameMap::TerritoryList StlGameMap::adjacencies(Territory *) const {
   return TerritoryList();
}


GameMap::TerritoryList StlGameMap::players(Player *) const {
   return TerritoryList(); 
}


void StlGameMap::traverse(TerritoryOperation * op, Territory * start) {
   //foo
}


GameMap::TerritoryList StlGameMap::filter(TerritoryOperation * op) const {
   return TerritoryList(); 
}


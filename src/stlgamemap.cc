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
#include <functional>
#include <utility>
#include <algorithm>
#include <string>
#include "territory.h"
#include "stlgamemap.h"
#include "compare.h"
#include "functional.h"

StlGameMap::StlGameMap(const AdjacencyList & tal) {
    typedef MapNode::first_type key_t;
    typedef MapNode::second_type value_t;
    typedef Compare<Territory, std::string, &Territory::name> cmp_t;
    typedef std::map<key_t, value_t, std::less<cmp_t> > map_t;
    
    map_t tmap;

    // build adjacency lists for each node.
    for (AdjacencyList::const_iterator it = tal.begin(); it != tal.end(); it++) {
        
        // establish bidirectional relationships.
        tmap[it->first].push_back(it->second);
        tmap[it->second].push_back(it->first);
    }

    // copy out the results in sorted order.
    for (map_t::iterator it = tmap.begin(); it != tmap.end(); it++) {
        /// \todo need to change comparator to delete elements that compare
        /// equal to prevent memory leaks.
        value_t & vt = it->second;
        value_t::iterator res = std::unique(vt.begin(), vt.end(), std::equal_to<cmp_t>());
        vt.resize(res - vt.begin());

        territories.push_back(std::make_pair(it->first, vt));
    }
}

/// Cleans up all Territory objects on delete.
StlGameMap::~StlGameMap() {
   std::vector<MapNode::first_type> del;
   std::vector<MapNode::first_type> rem;

   for (MapType::iterator it = territories.begin(); it != territories.end(); it++) {
      MapNode::second_type & adj = it->second;
      
      for (MapNode::second_type::iterator jt = adj.begin(); jt != adj.end(); jt++) {
         delete *jt;
         del.push_back(*jt);
      }
      rem.push_back(it->first);
   }

   /// \todo there shouldn't be any straglers... verify that this is so.
   // since there is overlap between parent nodes and their adjacencies, we
   // need to remove the overlap to identify any remaining straglers that still 
   // need to be deleted.
   std::vector<MapNode::first_type> straglers;

   /// NB: it is important to ensure that these operations use sorting by pointer value.
   /// otherwise, this will not work.
   std::sort(rem.begin(), rem.end());
   std::sort(del.begin(), del.end());
   std::set_difference(rem.begin(), rem.end(), del.begin(), del.end(), straglers.begin());
   
   for(std::vector<MapNode::first_type>::iterator it = straglers.begin(); it != straglers.end(); it++) {
      delete *it;
   }
}

Territory* StlGameMap::begin() const {
   return (territories.begin())->first;
}

Territory* StlGameMap::find(TerritoryName tname) const {
/*
using namespace function;
   using namespace typelist;
   using namespace util;

   typedef Territory element_t;
   typedef unary::map<
      cons<member<element_t, std::string, &Territory::name>,
      cons<dereference<element_t> > > 
   > territory_name_t;

   typedef unary::map<
      cons<territory_name_t,
      cons<first<MapNode> > >
   > mapnode_first_attr_t;

   territory_name_t()(territories.begin()->first);
*/
   /*
   first2<Territory*, std::vector<Territory*> >()(*territories.begin());
   first<const std::pair<Territory*, std::vector<Territory*> > >()(*territories.begin());
   //mapnode_first_attr_t()(*territories.begin());
   */
   /*
   typedef binary::map<
      std::less<std::string>,
      mapnode_first_attr_t> cmp_t;
    
   // do binary search.
   MapType::iterator pos = std::lower_bound(
      territories.begin(), 
      territories.end(), 
      tname,
      cmp_t()
   ); 

   // check results.
   if (pos->first->name() == tname) {
       return pos->first; 
   } else {
       GameMap::end();
   }
   */

   return NULL;
}

GameMap::TerritoryList StlGameMap::adjacencies(const Territory *) const {
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


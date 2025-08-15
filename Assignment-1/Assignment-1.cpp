
//===- SVF-Teaching Assignment 1-------------------------------------//
//
//     SVF: Static Value-Flow Analysis Framework for Source Code
//
// Copyright (C) <2013->
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//

/*
 // SVF-Teaching Assignment 1 : Graph Traversal
 //
 // 
 */


#include "Assignment-1.h"
using namespace std;

/// TODO: print each path once this method is called, and
/// add each path as a string into std::set<std::string> paths
/// Print the path in the format "START: 1->2->4->5->END", where -> indicate an edge connecting two node IDs
void GraphTraversal::printPath(std::vector<const Node *> &path)
{
    //Step 0: Handle null pointer case
    if (path.empty()) {
        return; // No path to print
    }

    //Step 1: Start building our String
    std::string pathStr = "START: "; 

    //Step 2: Go through each node in the path
    for (int i = 0; i < path.size(); ++i) {

        // Check for null node pointer
        if (!path[i]) {
            return; // Skip this path if any node is null
        }
        
        //Step 3 Add the node's ID number
        pathStr += std::to_string(path[i]->getNodeID());

        //Step 4: Add arrow only if this is not the last node
        if (i < path.size() - 1) {
            pathStr += "->";
        }
    }
    
    // Step 5: Add "END" at the end
    pathStr += "->END";

    // Step 6: Save this string to our collection
    paths.insert(pathStr);

};

/// TODO: Implement your depth first search here to traverse each program path (once for any loop) from src to dst
void GraphTraversal::DFS(set<const Node *> &visited, vector<const Node *> &path, const Node *src, const Node *dst)
{
    // Add null pointer check
    if (!src || !dst) {
        return;
    }

    //Step 1: Mark this node as visited (so that we do not visit it again)
    visited.insert(src);

    //Step 2: Add this node to our current path
    path.push_back(src);

    //Step 3: Check if we have reached our destionation
    if (src == dst){
        //Step 4: We found a complete path! Print it!
        printPath(path);
    } 
    else {
        //Step 5: We are not at the destination yet, so explore neighbours
        //Get all roads (edges) going out from this city (node)
        std::set<const Edge *> edges = src->getOutEdges();

        //Step 6: Look at each road (edge) going out from this city (node)
        for (const Edge *edge : edges) {

            // Check for null edge
            if (!edge) continue;

            //Step 7: Get the destination city (node) of this road (edge)
            const Node *neighbour = edge->getDst();

            // Check for null neighbour
            if (!neighbour) continue;

            //Step 8: Only go to this neighbour if we have not visited it yet
            if(visited.find(neighbour) == visited.end()) {
                //Step 9: Go to this neighbour
                DFS(visited, path, neighbour, dst);
            }
        }   
    }
    //Step 10: Backtrack, remove this node so other paths can use it
    visited.erase(src);
    path.pop_back();
}

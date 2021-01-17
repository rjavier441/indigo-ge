// PROJECT:         Indigo
// Author:          R. Javier
// File:            DirectedNode.hpp
// Created:         2021-01-16
// Last Modified:   2021-01-16
// Details:
//                  Defines an interface for nodes of a directed graph.
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <string>
#include <unordered_set>

namespace Indigo {
  
  // @abstract        DirectedNode
  // @description     Abstract class for nodes of a dreicted graph.
  class DirectedNode {
    public:
      // @functions
      virtual std::unordered_set<DirectedNode*>* getAncestors() = 0;
      virtual std::unordered_set<DirectedNode*>* getDescendants() = 0;
      virtual bool addAncestor( DirectedNode* ptr ) = 0;
      virtual DirectedNode* getAncestor( std::string name ) = 0;
      virtual bool addDescendant( DirectedNode* ptr ) = 0;
      virtual DirectedNode* getDescendant( std::string name ) = 0;
      virtual bool removeAncestor( std::string name ) = 0;
      virtual bool removeDescendant( std::string name ) = 0;
  };
}
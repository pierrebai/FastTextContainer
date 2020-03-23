#pragma once

#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <vector>

namespace FastTextContainer
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A simple binary tree, each node is held with a smart pointer.

   struct SimpleTree
   {
      struct Node
      {
         std::unique_ptr<Node> Left;
         std::unique_ptr<Node> Right;
      };

      std::unique_ptr<Node> Root;

      std::unique_ptr<Node> CreateNode() { return std::make_unique<Node>(); }
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // A binary tree, each node is held with a direct pointer.
   // All nodes of a tree are held privately by the tree.

   struct FastTree
   {
      struct Node
      {
         Node* Left = nullptr;
         Node* Right = nullptr;
      };

      Node* Root = nullptr;

      Node* CreateNode() { _nodes.emplace_back(); return &_nodes.back(); }

   private:
      std::deque<Node> _nodes;
   };

}

#endif

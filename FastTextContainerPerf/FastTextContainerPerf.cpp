#include "TextHolder.h"
#include "Tree.h"
#include "Benchmark.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;
using namespace FastTextContainer;

////////////////////////////////////////////////////////////////////////////
//
// Text holder perf when copying full text.

static constexpr int NUMBER_OF_HOLDER_COPIES = 100;

template <class HOLDER>
void CopyHolder(const HOLDER& holder)
{
   for (int i = 0; i < NUMBER_OF_HOLDER_COPIES; ++i)
   {
      HOLDER other(holder);
   }
}

////////////////////////////////////////////////////////////////////////////
//
// Text holder perf when copying a subset of lines.

static constexpr int NUMBER_OF_HOLDER_SUBSETS = 100;

template <class HOLDER>
void SelectSomeLines(const HOLDER& holder, int seed)
{
   for (int i = 0; i < NUMBER_OF_HOLDER_SUBSETS; ++i)
   {
      default_random_engine rnd_engine(seed+i);
      uniform_int_distribution rnd(0, 1);

      HOLDER other;
      other.Share(holder);

      for (const auto& line : holder.Lines)
      {
         if (rnd(rnd_engine))
         {
            other.Lines.emplace_back(line);
         }
      }
   }
}


////////////////////////////////////////////////////////////////////////////
//
// Tree perf when creating a deep tree.

static constexpr int NUMBER_OF_DEEP_TREES = 10000;
static constexpr int NUMBER_OF_NODES_PER_DEEP_TREE = 10000;

template <class TREE>
void CreateDeepTree(int seed)
{
   for (int i = 0; i < NUMBER_OF_DEEP_TREES; ++i)
   {
      default_random_engine rnd_engine(seed + i);
      uniform_int_distribution rnd(0, 1);

      TREE tree;
      tree.Root = tree.CreateNode();
      typename TREE::Node* current = &*tree.Root;

      for (int nodes = 0; nodes < NUMBER_OF_NODES_PER_DEEP_TREE; ++nodes)
      {
         auto newNode = tree.CreateNode();
         if (rnd(rnd_engine))
         {
            current->Left = newNode;
         }
         else
         {
            current->Right = newNode;
         }
         current = &*newNode;
      }
   }
}

////////////////////////////////////////////////////////////////////////////
//
// Tree perf when creating a wide tree.

static constexpr int NUMBER_OF_WIDE_TREES = 10000;
static constexpr int WIDTH_OF_WIDE_TREE = 12;

template <class TREE>
void CreateWideTree(TREE& tree, typename TREE::Node* current, int depth)
{
   if (depth < 0)
      return;

   current->Left = tree.CreateNode();
   CreateWideTree(tree, &*current->Left, depth - 1);

   current->Right = tree.CreateNode();
   CreateWideTree(tree, &*current->Right, depth - 1);
}

template <class TREE>
void CreateWideTree()
{
   for (int i = 0; i < NUMBER_OF_WIDE_TREES; ++i)
   {
      TREE tree;
      tree.Root = tree.CreateNode();

      CreateWideTree(tree, &*tree.Root, WIDTH_OF_WIDE_TREE);
   }
}

////////////////////////////////////////////////////////////////////////////
//
// Call each perf code.

int main(int argc, const char** argv)
{
   if (argc < 4)
      return -1;

   filesystem::path filename = argv[1];
   const int seed = atoi(argv[2]);
   const char* holder_type = argv[3];

   {
      VectorOfWStringTextHolder holder;
      {
         wifstream stream(filename);
         holder.ReadLines(stream);
      }

      PrintBenchmarkCode(L"Select some lines, vector of wstring", [holder, seed]()
      {
         //CopyHolder(holder);
         SelectSomeLines(holder, seed);
      });
   }

   {
      DequeOfWStringTextHolder holder;
      {
         wifstream stream(filename);
         holder.ReadLines(stream);
      }

      PrintBenchmarkCode(L"Select some lines, deque of wstring", [holder, seed]()
      {
         //CopyHolder(holder);
         SelectSomeLines(holder, seed);
      });
   }

   {
      VectorOfSharedBuffersTextHolder holder;
      {
         wifstream stream(filename);
         holder.ReadLines(stream);
      }

      PrintBenchmarkCode(L"Select some lines, vector of shared buffers", [holder, seed]()
      {
         //CopyHolder(holder);
         SelectSomeLines(holder, seed);
      });
   }

   {
      PrintBenchmarkCode(L"Simple tree, create and destroy deep tree", [seed]()
      {
         CreateDeepTree<SimpleTree>(seed);
      });
   }

   {
      PrintBenchmarkCode(L"Faster tree, create and destroy deep tree", [seed]()
      {
         CreateDeepTree<FastTree>(seed);
      });
   }

   {
      PrintBenchmarkCode(L"Simple tree, create and destroy wide tree", []()
      {
         CreateWideTree<SimpleTree>();
      });
   }

   {
      PrintBenchmarkCode(L"Faster tree, create and destroy wide tree", []()
      {
         CreateWideTree<FastTree>();
      });
   }

   return 0;
}


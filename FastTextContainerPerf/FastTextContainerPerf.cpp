#include "TextHolder.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;
using namespace FastTextContainer;

template <class HOLDER>
void CopyHolder(const HOLDER& holder)
{
   for (int i = 0; i < 100; ++i)
   {
      HOLDER other(holder);
   }
}

template <class HOLDER>
void SelectSomeLines(const HOLDER& holder, int seed)
{
   for (int i = 0; i < 100; ++i)
   {
      default_random_engine rnd_engine(seed);
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

int main(int argc, const char** argv)
{
   if (argc < 4)
      return -1;

   filesystem::path filename = argv[1];
   const int seed = atoi(argv[2]);
   const char* holder_type = argv[3];

   if (string("vs") == holder_type)
   {
      VectorOfWStringTextHolder holder;
      {
         wifstream stream(filename);
         holder.ReadLines(stream);
      }
      //CopyHolder(holder);
      SelectSomeLines(holder, seed);
   }
   if (string("ds") == holder_type)
   {
      DequeOfWStringTextHolder holder;
      {
         wifstream stream(filename);
         holder.ReadLines(stream);
      }
      //CopyHolder(holder);
      SelectSomeLines(holder, seed);
   }
   if (string("vb") == holder_type)
   {
      VectorOfSharedBuffersTextHolder holder;
      {
         wifstream stream(filename);
         holder.ReadLines(stream);
      }
      //CopyHolder(holder);
      SelectSomeLines(holder, seed);
   }

   return 0;
}


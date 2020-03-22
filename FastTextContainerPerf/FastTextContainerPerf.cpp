#include "TextHolder.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <random>
#include <functional>

using namespace std;
using namespace FastTextContainer;

struct BenchmarkInterval
{
   BenchmarkInterval() : _start(chrono::steady_clock::now()) { }

   void Restart() { _start = chrono::steady_clock::now(); }
   void Stop() { _end = chrono::steady_clock::now(); }

   chrono::microseconds GetDuration() const
   {
      return chrono::duration_cast<chrono::microseconds>(_end - _start);
   }

private:
   chrono::steady_clock::time_point _start;
   chrono::steady_clock::time_point _end;
};

chrono::microseconds BenchmarkCode(const function<void()>& func)
{
   BenchmarkInterval benchmark;
   func();
   benchmark.Stop();
   return benchmark.GetDuration();
}

chrono::microseconds PrintBenchmarkCode(const wchar_t* label, const function<void()>& func)
{
   auto dur = BenchmarkCode(func);
   wcout << label << " benchmark: " << dur.count() << "us" << endl;
   return dur;
}

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

   return 0;
}


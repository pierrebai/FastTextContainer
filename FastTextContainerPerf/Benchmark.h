#pragma once

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <functional>
#include <iostream>

using BenchClock = std::chrono::steady_clock;
using Secs = std::chrono::duration<double, std::ratio<1, 1>>;
using FuncToBench = std::function<void()>;

struct BenchmarkInterval
{
   BenchmarkInterval() : _start(BenchClock::now()) { }

   void Restart() { _start = BenchClock::now(); }
   void Stop() { _end = BenchClock::now(); }
   auto GetDuration() const { return std::chrono::duration_cast<Secs>(_end - _start); }

private:
   BenchClock::time_point _start;
   BenchClock::time_point _end;
};

Secs BenchmarkCode(const FuncToBench& func)
{
   BenchmarkInterval benchmark;
   func();
   benchmark.Stop();
   return benchmark.GetDuration();
}

Secs PrintBenchmarkCode(const wchar_t* label, const FuncToBench& func)
{
   auto dur = BenchmarkCode(func);
   std::wcout << label << " benchmark: " << dur.count() << "s" << std::endl;
   return dur;
}

#endif

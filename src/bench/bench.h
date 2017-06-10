// Copyright (c) 2015 The Bitcoin Core developers

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef IoP_BENCH_BENCH_H
#define IoP_BENCH_BENCH_H

#include <map>
#include <string>

#include <boost/function.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

// Simple micro-benchmarking framework; API mostly matches a subset of the Google Benchmark
// framework (see https://github.com/google/benchmark)
// Wny not use the Google Benchmark framework? Because adding Yet Another Dependency
// (that uses cmake as its build system and has lots of features we don't need) isn't
// worth it.

/*
 * Usage:

static void CODE_TO_TIME(benchmark::State& state)
{
    ... do any setup needed...
    while (state.KeepRunning()) {
       ... do stuff you want to time...
    }
    ... do any cleanup needed...
}

BENCHMARK(CODE_TO_TIME);

 */
 
namespace benchmark {

    class State {
        std::string name;
        double maxElapsed;
        double beginTime;
        double lastTime, minTime, maxTime, countMaskInv;
        int64_t count;
        int64_t countMask;
    public:
        State(std::string _name, double _maxElapsed) : name(_name), maxElapsed(_maxElapsed), count(0) {
            minTime = std::numeric_limits<double>::max();
            maxTime = std::numeric_limits<double>::min();
            countMask = 1;
            countMaskInv = 1./(countMask + 1);
        }
        bool KeepRunning();
    };

    typedef boost::function<void(State&)> BenchFunction;

    class BenchRunner
    {
        static std::map<std::string, BenchFunction> benchmarks;

    public:
        BenchRunner(std::string name, BenchFunction func);

        static void RunAll(double elapsedTimeForOne=1.0);
    };
}

// BENCHMARK(foo) expands to:  benchmark::BenchRunner bench_11foo("foo", foo);
#define BENCHMARK(n) \
    benchmark::BenchRunner BOOST_PP_CAT(bench_, BOOST_PP_CAT(__LINE__, n))(BOOST_PP_STRINGIZE(n), n);

#endif // IoP_BENCH_BENCH_H

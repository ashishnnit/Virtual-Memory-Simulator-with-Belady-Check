#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include "PageReplacementAlgo.h"
#include "FIFO.h"
#include "LRU.h"
#include "LFU.h"
#include "Optimal.h"
#include "Utils.h"

int main() {
    int frames;
    std::string line;

    std::cout << "Enter number of frames: ";
    std::cin >> frames;
    std::cin.ignore();

    std::cout << "Enter page reference string: ";
    std::getline(std::cin, line);
    std::vector<int> pages = parsePages(line);

    std::vector<std::unique_ptr<PageReplacementAlgo>> algos;
    algos.emplace_back(new FIFO(pages, frames));
    algos.emplace_back(new LRU(pages, frames));
    algos.emplace_back(new LFU(pages, frames));
    algos.emplace_back(new Optimal(pages, frames));

    std::vector<std::pair<std::string,int>> results;
    for (auto& algo : algos) {
        std::cout << "===== " << algo->name() << " Simulation =====\n";
        int faults = algo->simulate(std::cout);
        results.emplace_back(algo->name(), faults);
    }

    std::sort(results.begin(), results.end(),
              [](auto& a, auto& b){ return a.second < b.second; });

    std::cout << "===== Final Comparison =====\n"
              << std::left << std::setw(12) << "Algorithm"
              << "| Faults\n"
              << "------------|--------\n";
    for (auto& r : results) {
        std::cout << std::left << std::setw(12) << r.first
                  << "| " << r.second << "\n";
    }
    std::cout << "\nBest: " << results.front().first
              << "\n2nd Best: " << results[1].first << "\n";

    return 0;
}

#ifndef OPTIMAL_H
#define OPTIMAL_H

#include "PageReplacementAlgo.h"

class Optimal : public PageReplacementAlgo {
public:
    Optimal(const std::vector<int>& pages, int frames)
        : PageReplacementAlgo(pages, frames) {}

    int simulate(std::ostream& out) override;
    std::string name() const override { return "Optimal"; }
};

#endif // OPTIMAL_H

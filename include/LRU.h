#ifndef LRU_H
#define LRU_H

#include "PageReplacementAlgo.h"

class LRU : public PageReplacementAlgo {
public:
    LRU(const std::vector<int>& pages, int frames)
        : PageReplacementAlgo(pages, frames) {}

    int simulate(std::ostream& out) override;
    std::string name() const override { return "LRU"; }
};

#endif // LRU_H

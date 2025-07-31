#ifndef LFU_H
#define LFU_H

#include "PageReplacementAlgo.h"

class LFU : public PageReplacementAlgo {
public:
    LFU(const std::vector<int>& pages, int frames)
        : PageReplacementAlgo(pages, frames) {}

    int simulate(std::ostream& out) override;
    std::string name() const override { return "LFU"; }
};

#endif // LFU_H

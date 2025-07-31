#ifndef FIFO_H
#define FIFO_H

#include "PageReplacementAlgo.h"

class FIFO : public PageReplacementAlgo {
public:
    FIFO(const std::vector<int>& pages, int frames)
        : PageReplacementAlgo(pages, frames) {}

    int simulate(std::ostream& out) override;
    std::string name() const override { return "FIFO"; }
};

#endif // FIFO_H

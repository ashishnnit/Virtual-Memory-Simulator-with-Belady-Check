#ifndef PAGE_REPLACEMENT_ALGO_H
#define PAGE_REPLACEMENT_ALGO_H

#include <vector>
#include <string>
#include <ostream>

class PageReplacementAlgo {
protected:
    std::vector<int> pages;
    int frames;

public:
    PageReplacementAlgo(const std::vector<int>& pages, int frames)
        : pages(pages), frames(frames) {}

    virtual int simulate(std::ostream& out) = 0;
    virtual std::string name() const = 0;
    virtual ~PageReplacementAlgo() = default;
};

#endif // PAGE_REPLACEMENT_ALGO_H

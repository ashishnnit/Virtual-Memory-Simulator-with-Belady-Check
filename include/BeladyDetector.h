#ifndef BELADY_DETECTOR_H
#define BELADY_DETECTOR_H

#include <vector>
#include <iostream>
#include <iomanip>

class BeladyDetector {
public:
    BeladyDetector(const std::vector<int>& pages);
    void detect();

private:
    std::vector<int> referenceString;
    int simulateFIFO(int frameCount);
};

#endif

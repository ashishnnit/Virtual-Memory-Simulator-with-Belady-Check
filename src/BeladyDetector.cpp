#include "../include/BeladyDetector.h"
#include <unordered_set>
#include <queue>

BeladyDetector::BeladyDetector(const std::vector<int>& pages) : referenceString(pages) {}

int BeladyDetector::simulateFIFO(int frameCount) {
    std::unordered_set<int> frames;
    std::queue<int> fifo;
    int faults = 0;

    for (int page : referenceString) {
        if (frames.find(page) == frames.end()) {
            if (frames.size() == frameCount) {
                int front = fifo.front(); fifo.pop();
                frames.erase(front);
            }
            frames.insert(page);
            fifo.push(page);
            faults++;
        }
    }
    return faults;
}

void BeladyDetector::detect() {
    std::cout << "\n\n=== Belady's Anomaly Detection (FIFO Only) ===\n";
    std::cout << "Frame Size | Page Faults\n";
    std::cout << "-------------------------\n";

    std::vector<int> faults;
    bool anomaly = false;

    for (int f = 3; f <= 6; ++f) {
        int pf = simulateFIFO(f);
        faults.push_back(pf);
        std::cout << std::setw(9) << f << " | " << std::setw(12) << pf;
        if (f > 3 && pf > faults[f - 4]) {
            std::cout << "  ← Anomaly Detected!";
            anomaly = true;
        }
        std::cout << "\n";
    }

    if (!anomaly)
        std::cout << "No anomaly detected in FIFO for frame sizes 3 to 6.\n";
}

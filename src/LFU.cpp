#include "LFU.h"
#include "Utils.h"
#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>

int LFU::simulate(std::ostream& out) {
    out << " Page |  f1 |  f2 |  f3 | Result                             | Next Victim\n";
    out << "---------------------------------------------------------------\n";

    std::map<int, int> freq;
    std::vector<int> frame;
    int faults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int p = pages[i];
        ++freq[p];

        auto it = std::find(frame.begin(), frame.end(), p);
        bool hit = it != frame.end();
        int evicted = -1;

        if (!hit) {
            ++faults;
            if ((int)frame.size() == frames) {
                int idx = 0, minf = INT_MAX;
                for (int j = 0; j < (int)frame.size(); ++j) {
                    if (freq[frame[j]] < minf) {
                        minf = freq[frame[j]];
                        idx = j;
                    }
                }
                evicted = frame[idx];
                frame[idx] = p;
            } else {
                frame.push_back(p);
            }
        }

        int nextVictim = 0, minf = INT_MAX;
        if (!frame.empty()) {
            for (int v : frame) {
                if (freq[v] < minf) {
                    minf = freq[v];
                    nextVictim = v;
                }
            }
        }

        out << std::setw(5) << p << " | ";
        for (int j = 0; j < frames; ++j) {
            if (j < (int)frame.size()) {
                out << std::setw(4) << frame[j];
            } else {
                out << std::setw(4) << "-";
            }
            out << " | ";
        }

        std::stringstream resultText;
        if (hit) {
            resultText << "Hit";
        } else {
            resultText << "Fault";
            if (evicted != -1)
                resultText << ", evict " << evicted;
        }

        std::string resStr = resultText.str();
        int currentCursor = 7 + (frames * 6); // cursor after frames
        int victimCol = 57;
        int gap = victimCol - currentCursor - (int)resStr.length();
        if (gap < 1) gap = 1;

        out << resStr << std::string(gap, ' ') << "| " << std::setw(7) << nextVictim << "\n";
    }

    out << "\nTotal " << name() << " faults: " << faults << "\n\n";
    return faults;
}

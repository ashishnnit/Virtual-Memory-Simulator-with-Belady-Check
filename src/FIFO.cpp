#include "FIFO.h"
#include "Utils.h"
#include <queue>
#include <unordered_set>
#include <iomanip>
#include <sstream>

int FIFO::simulate(std::ostream& out) {
    out << " Page |  f1 |  f2 |  f3 | Result                             | Next Victim\n";
    out << "---------------------------------------------------------------\n";

    std::queue<int> q;
    std::unordered_set<int> inFrame;
    int faults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int p = pages[i];
        bool hit = inFrame.count(p);
        int evicted = -1;

        if (!hit) {
            ++faults;
            if ((int)inFrame.size() == frames) {
                evicted = q.front(); q.pop();
                inFrame.erase(evicted);
            }
            inFrame.insert(p);
            q.push(p);
        }

        int nextVictim = q.empty() ? 0 : q.front();

        out << std::setw(5) << p << " | ";

        std::queue<int> tmp = q;
        for (int f = 0; f < frames; ++f) {
            if (!tmp.empty()) {
                out << std::setw(4) << tmp.front();
                tmp.pop();
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
        int currentCursor = 7 + (frames * 6); // Adjusted for " f1 | f2 | f3 " style
        int victimCol = 57;
        int gap = victimCol - currentCursor - (int)resStr.length();
        if (gap < 1) gap = 1;

        out << resStr << std::string(gap, ' ') << "| " << std::setw(7) << nextVictim << "\n";
    }

    out << "\nTotal " << name() << " faults: " << faults << "\n\n";
    return faults;
}

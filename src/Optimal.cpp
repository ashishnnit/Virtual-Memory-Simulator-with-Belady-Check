#include "Optimal.h"
#include "Utils.h"
#include <algorithm>
#include <iomanip>

int Optimal::simulate(std::ostream& out) {
    out << std::left << std::setw(7) << "Page" << "|";
    for (int i = 0; i < frames; ++i)
        out << " " << std::setw(10) << ("F" + std::to_string(i + 1)) << "|";
    out << " " << std::setw(25) << "Result" << "| " << "Next Victim\n";

    out << std::string(10 + 13 * frames + 30, '-') << "\n";

    std::vector<int> frame;
    int faults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int p = pages[i];
        bool hit = std::find(frame.begin(), frame.end(), p) != frame.end();
        int evicted = -1;

        if (!hit) {
            ++faults;
            if ((int)frame.size() == frames) {
                int victimIdx = -1, farthest = -1;
                for (int j = 0; j < frames; ++j) {
                    int idx = -1;
                    for (size_t k = i + 1; k < pages.size(); ++k) {
                        if (pages[k] == frame[j]) {
                            idx = k;
                            break;
                        }
                    }
                    if (idx == -1) {
                        victimIdx = j;
                        break;
                    } else if (idx > farthest) {
                        farthest = idx;
                        victimIdx = j;
                    }
                }
                evicted = frame[victimIdx];
                frame[victimIdx] = p;
            } else {
                frame.push_back(p);
            }
        }

        int nextVictim = -1, farthest = -1;
        if ((int)frame.size() == frames) {
            for (int j = 0; j < frames; ++j) {
                int idx = -1;
                for (size_t k = i + 1; k < pages.size(); ++k) {
                    if (pages[k] == frame[j]) {
                        idx = k;
                        break;
                    }
                }
                if (idx == -1) {
                    nextVictim = frame[j];
                    break;
                } else if (idx > farthest) {
                    farthest = idx;
                    nextVictim = frame[j];
                }
            }
        }

        // Print current page
        out << std::left << std::setw(7) << p << "|";

        // Print frame contents
        for (int j = 0; j < frames; ++j) {
            if (j < (int)frame.size())
                out << " " << std::setw(10) << frame[j] << "|";
            else
                out << " " << std::setw(10) << "-" << "|";
        }

        // Print result
        if (hit) {
            out << " " << std::setw(25) << "Hit" << "| ";
        } else {
            std::ostringstream result;
            result << "Fault";
            if (evicted != -1)
                result << ", evict " << evicted;
            out << " " << std::setw(25) << result.str() << "| ";
        }

        if (nextVictim != -1)
            out << std::setw(10) << nextVictim;
        else
            out << std::setw(10) << "-";

        out << "\n";
    }

    out << "\nTotal " << name() << " faults: " << faults << "\n\n";
    return faults;
}

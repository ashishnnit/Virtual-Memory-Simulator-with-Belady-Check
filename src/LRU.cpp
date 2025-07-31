#include "LRU.h"
#include "Utils.h"
#include <list>
#include <unordered_map>
#include <iomanip>
#include <sstream>

int LRU::simulate(std::ostream& out) {
   
    out << " Page |   f1   |   f2   |   f3   |        Result        | Next Victim\n";
    out << "-----------------------------------------------------------------------\n";

    std::list<int> cache;
    std::unordered_map<int, std::list<int>::iterator> mp;
    int faults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int p = pages[i];
        bool hit = mp.count(p);
        int evicted = -1;

        if (hit) {
            cache.erase(mp[p]);
            cache.push_front(p);
            mp[p] = cache.begin();
        } else {
            ++faults;
            if ((int)cache.size() == frames) {
                evicted = cache.back();
                mp.erase(evicted);
                cache.pop_back();
            }
            cache.push_front(p);
            mp[p] = cache.begin();
        }

        int nextVictim = (int)cache.size() == frames ? cache.back() : 0;

        // Page number
        out << std::setw(5) << p << " |";

        // Frame content
        std::vector<int> frameSnapshot;
        for (int val : cache) {
            frameSnapshot.push_back(val);
        }

        while ((int)frameSnapshot.size() < frames) {
            frameSnapshot.push_back(-1);
        }

        for (int j = 0; j < frames; ++j) {
            if (frameSnapshot[j] == -1)
                out << std::setw(7) << "-" << " |";
            else
                out << std::setw(7) << frameSnapshot[j] << " |";
        }

        // Result column - fixed width (22 characters)
        std::ostringstream result;
        if (hit) {
            result << "Hit";
        } else {
            result << "Fault";
            if (evicted != -1) result << ", evict " << evicted;
        }

        out << std::setw(22) << std::left << result.str() << std::right;

        // Next victim column (always aligned)
        out << "| " << std::setw(11) << nextVictim << "\n";

        // if ( i + 1 < pages.size()) {
        //     out << "\n"; // Just one empty line, not 5
        // }
    }

    out << "\nTotal " << name() << " faults: " << faults << "\n\n";
    return faults;
}

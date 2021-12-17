#ifndef SINGLEPP_PROCESS_FEATURES_HPP
#define SINGLEPP_PROCESS_FEATURES_HPP

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace singlepp {

typedef std::vector<std::pair<int, int> > Intersection;

template<typename Id>
Intersection intersect_features(size_t mat_n, const Id* mat_id, size_t ref_n, const Id* ref_id) {
    std::unordered_map<Id, std::pair<int, int> > intersection;
    intersection.reserve(mat_n);
    for (size_t i = 0; i < mat_n; ++i) {
        intersection[mat_id[i]] = std::make_pair<int, int>(i, -1);
    }

    for (size_t i = 0; i < ref_n; ++i) {
        auto it = intersection.find(ref_id[i]);
        if (it != intersection.end()) {
            (it->second).second = i;
        }
    }

    Intersection pairings;
    pairings.reserve(intersection.size());
    for (const auto& x : intersection) {
        if ((x->second).second >= 0) {
            pairings.push_back(x->second);
        }
    }

    std::sort(pairings.begin(), pairings.end());
    return pairings;
}

typedef std::vector<std::vector<std::vector<int> > > Markers;

inline void subset_markers(Intersection& intersection, Markers& markers, int top) {
    std::unordered_set<int> available;
    available.reserve(intersection.size());
    for (const auto& in : intersection) {
        available.insert(in.second);
    }

    // Figuring out the top markers to retain, that are _also_ in the intersection.
    std::unordered_set<int> all_markers;
    all_markers.reserve(intersection.size());
    for (size_t i = 0; i < markers.size(); ++i) {
        for (size_t j = 0; j < markers[i].size(); ++j) {
            if (i == j) {
                continue;
            }

            const auto& current = markers[i][j];
            int sofar = 0;
            for (size_t k = 0; k < current.size() && sofar < top; ++k) {
                if (available.find(current[k]) != available.end()) {
                    all_markers.insert(current[k]);
                    ++sofar;
                }
            }
        }
    }

    // Subsetting the intersection down to the chosen set of markers.
    std::unordered_map<int, int> mapping;
    mapping.reserve(intersection.size());
    {
        size_t counter = 0;
        for (size_t i = 0; i < intersection.size(); ++i) {
            if (all_markers.find(intersection[i].second) != all_markers.end()) {
                intersection[counter] = intersection[i];
                mapping[intersection[i].second] = counter;
                ++counter;
            }
        }
        intersection.resize(counter);
    }

    // Finally, reindexing the markers.
    for (size_t i = 0; i < markers.size(); ++i) {
        for (size_t j = 0; j < markers[i].size(); ++j) {
            if (i == j) {
                continue;
            }

            auto& current = markers[i][j];
            size_t counter = 0;
            for (size_t k = 0; k < current.size(); ++k) {
                auto it = mapping.find(current[k]);
                if (it != mapping.end()) {
                    current[counter] = it->second;
                    ++counter;
                }
            }
            current.resize(counter);
        }
    }

    return;
}

}

#endif
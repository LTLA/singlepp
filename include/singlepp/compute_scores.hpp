#ifndef SINGLEPP_COMPUTE_SCORES_HPP
#define SINGLEPP_COMPUTE_SCORES_HPP

#include <vector>
#include <algorithm>
#include <limits>

namespace singlepp {

inline double correlations_to_scores (std::vector<double>& correlations, double quantile) {
    const size_t ncells=all_correlations.size();
    if (ncells==0) {
        return std::numeric_limits<double>::quiet_NaN();
    } else if (quantile==1 || ncells==1) {
        return *std::max_element(all_correlations.begin(), all_correlations.end());
    } else {
        // See logic in .find_nearest_quantile().
        const double denom=ncells-1;
        const size_t qn=std::floor(denom * quantile) + 1;

        // Technically, I should do (qn-1)+1, with the first -1 being to get zero-indexed values
        // and the second +1 to obtain the ceiling. But they cancel out, so I won't.
        std::nth_element(all_correlations.begin(), all_correlations.begin()+qn, all_correlations.end());
        const double rightval=all_correlations[qn];

        // Do NOT be tempted to do the second nth_element with the end at begin()+qn;
        // this does not handle ties properly.
        std::nth_element(all_correlations.begin(), all_correlations.begin()+qn-1, all_correlations.end());
        const double leftval=all_correlations[qn-1];

        const double rightweight=quantile - ((qn-1)/denom);
        const double leftweight=(qn/denom) - quantile;
        return (rightval * rightweight + leftval * leftweight)/(rightweight + leftweight);
    }
}

}

#endif

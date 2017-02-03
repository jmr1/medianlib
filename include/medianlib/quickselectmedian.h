#ifndef QUICKSELECTMEDIAN_H
#define QUICKSELECTMEDIAN_H

#include "sort/quicksort.h"

namespace medianlib {

/// Finding median in unsorted array.
/// The input array is being used as a buffer for quick select algorithm
/// Run-time complexity - average: O(n). Space: O(n).
template <typename T>
class QuickSelectMedian
{
public:
    /// Find the median
    ///
    /// @param[in] vec input array
    /// @param[in] size size of the input array
    /// @return median value
    static double find(T *vec, size_t size)
    {
        return median(vec, size);
    }

private:
    static double median(T *vec, size_t size)
    {
        if (size % 2 == 0) // Even number of elements, median is average of middle two
            return (quick_select(vec, size / 2, size) + quick_select(vec, size / 2 - 1, size / 2)) / 2.;
        else // select middle element
            return quick_select(vec, size / 2, size);
    }

    // Return the k-th smallest item
    static T quick_select(T *vec, int k, size_t size)
    {
        int left{};
        int right = size - 1;
        int pos{};

        while (left < right)
        {
            const auto pivot = vec[k];
            swap(vec[k], vec[right]);
            for (auto i = pos = left; i < right; ++i)
            {
                if (vec[i] < pivot)
                {
                    swap(vec[i], vec[pos]);
                    pos++;
                }
            }
            swap(vec[right], vec[pos]);
            if (pos == k)
                break;
            if (pos < k)
                left = pos + 1;
            else
                right = pos - 1;
        }
        return vec[k];
    }
};

} // medianlib

#endif // QUICKSELECTMEDIAN_H

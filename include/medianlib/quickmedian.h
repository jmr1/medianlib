#ifndef QUICKMEDIAN_H
#define QUICKMEDIAN_H

#include "sort/quicksort.h"

namespace medianlib {

/// Finding median in unsorted array.
/// The class is first sorting input array and then finds median value.
/// The input array is being used as a buffer for quicksort algorithm (sorting in-place)
/// Run-time complexity - average: O(nlogn), worst: O(n2). Space: O(n).
template <typename T>
class QuickMedian
{
public:
    /// Find the median
    ///
    /// @param[in] vec input array
    /// @param[in] size size of the input array
    /// @return median value
    static double find(T *vec, size_t size)
    {
        quicksort(vec, 0, size-1);
        return median(vec, size);
    }

private:
    static double median(T *vec, size_t size)
    {
        return size % 2 ? vec[size/2] : 0.5 * (vec[size/2] + vec[size/2-1]);
    }
};

} // medianlib

#endif // QUICKMEDIAN_H
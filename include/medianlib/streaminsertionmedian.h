#ifndef STREAMINSERTIONMEDIAN_H
#define STREAMINSERTIONMEDIAN_H

#include <memory>
#include <functional>


namespace medianlib {


/// Finding median of stream of numbers received so far
/// Complexity of finding median is O(n2)
template <typename T>
class StreamInsertionMedian
{
public:
    StreamInsertionMedian(int max_heap_size)
      : items(new T[max_heap_size])
    {}

    /// Find the median
    /// Return middle element for odd array elements,
    /// an average of 2 middle elements otherwise
    ///
    /// @param[in] value next input value
    /// @return median value
    double find(const T &value)
    {
        addNumber(value);
        if(size % 2 == 0)
            return average(items[size/2], items[size/2-1]);
        else
            return items[size/2];
    }

private:
    void addNumber(const T &value)
    {
        int holePosition = size;

        // check if previous number is larger than value to be inserted
        while (holePosition > 0 && items[holePosition-1] > value)
        {
            items[holePosition] = items[holePosition-1];
            --holePosition;
        }

        items[holePosition] = value;
        ++size;
    }

private:
    int size{};
    std::unique_ptr<T[]> items;
};

} // medianlib

#endif // STREAMINSERTIONMEDIAN_H
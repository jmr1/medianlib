#ifndef STREAMHEAPMEDIAN_H
#define STREAMHEAPMEDIAN_H

#include <memory>
#include <functional>


namespace medianlib {

decltype(auto) greater = [](auto a, auto b){return a > b;};
decltype(auto) smaller = [](auto a, auto b){return a < b;};
decltype(auto) average = [](auto a, auto b) {return (a + b) / 2.;};

template <typename T>
class Heap
{
public:
    Heap(int max_heap_size, std::function<bool(T, T)> cmp_func)
      : max_size(max_heap_size)
      , items(new T[max_heap_size])
      , comp(cmp_func)
    {}

    T top() const
    {
        return items[0];
    }

    T pop()
    {
        int currentSize = size;
        T deletedValue = -1;

        if(currentSize < 1)
        {
            return -1;
        }
        else
        {
            deletedValue = items[0];
            swap(0, currentSize-1);
            currentSize--;
            heapify(0, currentSize);
        }
        size = currentSize;
        return deletedValue;
    }

    void insert(T value)
    {
        items[size++] = value;
        moveUp();
    }

    int length() const
    {
        return size;
    }

private:
    int parent (int i) const
    {
        return (i-1)/2;
    }

    int leftChild(int i) const
    {
        return (i*2)+1;
    }

    int rightChild(int i) const
    {
        return (2*i)+2;
    }

    void swap(int index1, int index2)
    {
        T temp = items[index1];
        items[index1] = items[index2];
        items[index2] = temp;
    }

    void moveUp()
    {
        int current = size-1;
        int p = parent(size);

        while(p >=0 && comp(items[p], items[current]))
        {
            swap(p, current);
            // move up the tree.
            current = p;
            p = parent(current);
        }
    }

    void heapify(int i, int length)
    {
        int largest_smallest = i;
        int left  = leftChild(i);
        int right = rightChild(i);

        if(left < length && comp(items[i], items[left]))
            largest_smallest = left;
        if(right < length && comp(items[largest_smallest], items[right]))
            largest_smallest = right;
        if(largest_smallest != i)
        {
            swap(i, largest_smallest);
            heapify(largest_smallest, length);
        }
    }

private:
    int size{};
    const int max_size{};
    std::unique_ptr<T[]> items;
    std::function<bool(T, T)> comp;
};


/// Finding median of stream of numbers received so far
/// Complexity of finding median is O(1), insertion O(log n)
template <typename T>
class StreamHeapMedian
{
public:
    StreamHeapMedian(int max_heap_size)
      : maxHeap(max_heap_size, smaller)
      , minHeap(max_heap_size, greater)
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
        if(maxHeap.length() == minHeap.length())
            return average(maxHeap.top(), minHeap.top());
        else
            return maxHeap.length() > minHeap.length() ? maxHeap.top() : minHeap.top();
    }

private:
    void addNumber(const T &value)
    {
        maxHeap.insert(value);

        // If difference between two heap size is more than 1
        // or the maximum element in more than least element in min heap
        // then remove from max heap and add to min heap
        if(maxHeap.length() - minHeap.length() > 1 || minHeap.length() != 0 && maxHeap.top() > minHeap.top())
            minHeap.insert(maxHeap.pop());

        // If difference between two heap size is more than 1
        if(minHeap.length() != 0 && minHeap.length() - maxHeap.length() > 1)
            maxHeap.insert(minHeap.pop());
    }

private:
    Heap<T> maxHeap;
    Heap<T> minHeap;
};

} // medianlib

#endif // STREAMHEAPMEDIAN_H
#ifndef QUICKSORT_H
#define QUICKSORT_H

namespace medianlib {

template <typename T>
void swap(T &value1, T &value2)
{
   T temp = value1;
   value1 = value2;
   value2 = temp;
}

template <typename T>
int partition(T *vec, int left, int right, int pivot)
{
    int leftPointer = left -1;
    int rightPointer = right;

    while(true)
    {
        while(vec[++leftPointer] < pivot);
        while(rightPointer > 0 && vec[--rightPointer] > pivot);

        if(leftPointer >= rightPointer)
            break;
        swap(vec[leftPointer], vec[rightPointer]);
    }

    swap(vec[leftPointer], vec[right]);
    return leftPointer;
}

template <typename T>
void quicksort(T *vec, int left, int right)
{
    if(right-left <= 0)
        return;

    int pivot = vec[right];
    int partitionPoint = partition(vec, left, right, pivot);
    quicksort(vec, left, partitionPoint-1);
    quicksort(vec, partitionPoint+1, right);
}

} // medianlib

#endif
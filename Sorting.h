#ifndef __SORTING_H__
#define __SORTING_H__
#include "util.h"

using namespace std;

template <typename T>
bool EsMayorR(const T& a, const T& b){
    return a.GetRating() > b.GetRating();
}

template <typename T>
bool EsMenorR(const T& a, const T& b){
    return a.GetRating() < b.GetRating();
}

template <typename T>
bool EsMayorF(const T& a, const T& b){
    return a.getOferta() > b.getOferta();
}

template <typename T, typename Compare>
void bubbleSort(T* arr, int n, Compare comp) {
    if (n <= 1) 
        return;
    for (TI i = 0; i < n - 1; ++i) {
        for (TI j = 0; j < n - i - 1; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T, typename Func>
TI particionar(T* arr, TI first, TI last, Func func) {
    T pivote = arr[last];
    TI i = (first - 1);

    for (TI j = first; j <= last - 1; j++) {
        if ( func(arr[j], pivote) ){
            ++i; swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[last]);
    return (i + 1);
}

template <typename T, typename Func>
void QuickSortR(T* arr, TI first, TI last, Func func) {
    if (first < last) {
        TI pi = particionar(arr, first, last, func);
        QuickSortR(arr, first, pi - 1, func);
        QuickSortR(arr, pi + 1, last, func);
    }
}

template <typename T, typename Func>
void quickSort(T* arr, TI n, Func func){
    if (n <= 1) return;
    QuickSortR(arr, 0, n - 1, func);
}


template <typename T, typename Func>
void Merge(T* arr, TI left, TI mid, TI right, Func func) {

    TI subArrayOne = mid - left + 1;
    TI subArrayTwo = right - mid;
    
    T *leftArray   = new T[subArrayOne],
      *rightArray  = new T[subArrayTwo];

    for (size_t i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (size_t j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    TI indXOne = 0, indXTwo = 0;
    TI indXMerge = left;

    while (indXOne < subArrayOne && indXTwo < subArrayTwo) {
        if ( func(rightArray[indXOne], leftArray[indXTwo]) ) {
            arr[indXMerge] = leftArray[indXOne];
            indXOne++;
        } else {
            arr[indXMerge] = rightArray[indXTwo];
            indXTwo++;
        }
        indXMerge++;
    }

    while (indXOne < subArrayOne) {
        arr[indXMerge] = leftArray[indXOne];
        indXOne++;
        indXMerge++;
    }

    while (indXTwo < subArrayTwo) {
        arr[indXMerge] = rightArray[indXTwo];
        indXTwo++;
        indXMerge++;
    }

    delete[] leftArray;
    delete[] rightArray;
}


template <typename T, typename Func>
void MergeSortR( T* arr, TI begin, TI end, Func func) {
    if(begin < end){
        TI mid = begin + (end - begin) / 2;
        MergeSortR(arr, begin, mid, func);
        MergeSortR(arr, mid + 1, end, func);
        Merge(arr, begin, mid, end, func);
    }
}

template <typename T, typename Func>
void mergeSort(T* arr, TI n, Func func) {
    if (n <= 1) 
        return;
    MergeSortR(arr, 0, n - 1, func);
}

#endif //__SORTING_H__
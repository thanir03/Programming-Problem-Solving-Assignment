#include <vector>
#include <cmath>
#include "../type.h"
using namespace std;

void quick_sort(vector<covid_19_stats> &arr, int start, int end);

// sort the vector in ascending order
// Time complexity : O(n log n)
// Space complexity : O(log n)
void quick_sort(vector<covid_19_stats> &arr, int start, int end)
{
    if (start >= end)
        return;
    double left = start;
    double right = end;
    double pivot = floor((left + right) / 2);
    swap(arr[left], arr[pivot]);
    left++;
    pivot = start;
    while (left <= right)
    {
        if (arr[left].quantity > arr[pivot].quantity && arr[right].quantity < arr[pivot].quantity)
            swap(arr[left], arr[right]);
        if (arr[left].quantity <= arr[pivot].quantity)
            left++;
        if (arr[right].quantity >= arr[pivot].quantity)
            right--;
    }
    swap(arr[pivot], arr[right]);
    quick_sort(arr, start, right - 1);
    quick_sort(arr, left, end);
}
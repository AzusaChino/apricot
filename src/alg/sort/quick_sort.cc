#include <vector>

using namespace std;

void quick_sort(vector<int> &arr, int b, int e)
{

    if (b >= e)
    {
        return;
    }
    int i = b - 1;
    for (int k = b; k < e; k++)
    {
        if (arr[k] < arr[e])
        {
            swap(arr[++i], arr[k]);
        }
    }
    swap(arr[++i], arr[e]);

    quick_sort(arr, b, i - 1);
    quick_sort(arr, i + 1, e);
}
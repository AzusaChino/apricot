#include <stack>
#include <vector>

using namespace std;

int partition(vector<int> &arr, int b, int e, bool *sorted)
{
    if (b > e || b == e)
        return -1;

    int i = b - 1;
    for (int j = b; j < e; j++)
    {
        if (arr[j] < arr[e])
        {
            *sorted = false;
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[++i], arr[e]);

    return i;
}

void quick_sort(vector<int> &arr)
{
    int size = arr.size();
    if (size == 0 || size == 1)
        return;

    stack<pair<int, int>> tasks;
    tasks.push(pair<int, int>(0, size - 1));

    int b = 0;

    while (!tasks.empty())
    {
        auto top = tasks.top();
        tasks.pop();

        bool sorted = true;
        int p = partition(arr, top.first, top.second, &sorted);

        if (sorted)
        {
            continue;
        }
        else
        {
            tasks.push(pair<int, int>(p + 1, top.second));
            tasks.push(pair<int, int>(top.first, p - 1));
        }
    }
}
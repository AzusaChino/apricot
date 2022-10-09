#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v;
    for (auto i = 0; i < 40; i++)
    {
        v.push_back(i);
        // when _finish == _end => grow capacity
        cout << "vector cap: " << v.capacity() << " vector size: " << v.size() << endl;
    }
}

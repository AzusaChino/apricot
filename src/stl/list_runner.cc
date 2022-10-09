#include <list>
#include <iostream>

using namespace std;

int main()
{
    list<int> l;
    for (auto i = 0; i < 40; i++)
    {
        l.push_back(i);
    }
}
#include <iostream>


#include "thread_pool.h"

using namespace std;

int main() {
    ThreadPool pool(1);
    std::future<int> r;
    r = pool.submit([] {
        cout << "The flower of Apricot" << endl;
        return 0;
    });
    return r.get();
}

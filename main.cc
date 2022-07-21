#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

/**
 * @brief Print number & sleep
 * 
 * @param sec sleep seconds
 */
void print_sleep(int sec) {
    for (int32_t i = 0; i < 5; ++i) {
        cout << "Hello " << i << endl;
        this_thread::sleep_for(chrono::seconds(sec)); 
    }
}

int main()
{
    cout << "The flower of Apricot" << endl;
    thread t(print_sleep);
    t.join();
    cout << "Dawn is coming" << endl;
    return 0;
}

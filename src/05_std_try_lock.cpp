#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;


int my_amount = 0;
mutex m1;
mutex m2;

void add_1000_money() {
    for (int i = 0; i < 1000; ++i) {
        if (try_lock(m1, m2) == -1) {
            ++my_amount;
            m1.unlock();
            // m2.unlock();
        }
    }
}

int main() {

    // m2.lock();
    thread t1(add_1000_money);
    thread t2(add_1000_money);

    t1.join();
    t2.join();

    cout << my_amount << "\n";
    
	return 0;
}

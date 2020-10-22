#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;


int my_amount = 0;
mutex m;

void add_1000_money() {
    for (int i = 0; i < 1000; ++i) {
        if (m.try_lock()) {
            ++my_amount;
            m.unlock();
        }
    }
}

int main() {

    thread t1(add_1000_money);
    thread t2(add_1000_money);

    t1.join();
    t2.join();

    cout << my_amount << "\n";
    
	return 0;
}

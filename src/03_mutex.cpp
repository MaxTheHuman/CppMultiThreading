#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;


int my_amount = 0;
mutex m;

void add_money() {
    m.lock();
    ++my_amount;
    m.unlock();
}

int main() {

    thread t1(add_money);
    thread t2(add_money);

    t1.join();
    t2.join();

    cout << my_amount << "\n";
    
    return 0;
}

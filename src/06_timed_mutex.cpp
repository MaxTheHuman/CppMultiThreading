#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;


int my_amount = 0;
timed_mutex m;

void increment(int i) {
    auto now = steady_clock::now();
    // if (m.try_lock_for(seconds(1))) {
    if (m.try_lock_until(now + seconds(2))) {
        ++my_amount;
        this_thread::sleep_for(seconds(1));
        cout << "Thread " << i << " Entered\n";
        m.unlock();
    } else {
        cout << "Thread " << i << " Couldn't Enter\n";
    }
}

int main() {

    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();

    cout << my_amount << "\n";
    
    return 0;
}

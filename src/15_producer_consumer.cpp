#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <thread>

using namespace std;


std::mutex m;
std::condition_variable cv;
deque<int> buffer;
const unsigned int max_buffer_size = 64;

void producer(int val) {
    while (val > 0) {
        std::unique_lock<std::mutex> locker(m);
        cv.wait(locker, [](){return buffer.size() < max_buffer_size;});
        buffer.push_back(val);
        cout << "Produced: " << val << "\n";
        cout.flush();
        val--;
        locker.unlock();
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> locker(m);
        cv.wait(locker, [](){return buffer.size() > 0;});
        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumed: " << val << "\n";
        cout.flush();
        locker.unlock();
        cv.notify_one();
    }
}

int main() {

    std::thread t1(producer, 100);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}

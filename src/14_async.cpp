#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;
typedef long long int ull;


ull findOdd(ull start, ull end) {
    ull odd_sum = 0;
    cout << "ThreadID of findOdd: " << std::this_thread::get_id() << "\n";
    for (ull i = start; i <= end; ++i) {
        if (i % 2 == 1) {
            odd_sum += i;
        }
    }

    return odd_sum;
}

int main() {

    ull start = 0, end = 1900000000;
    cout << "ThreadID of main: " << std::this_thread::get_id() << "\n";
    cout << "Thread created only if policy is std::launch::async\n";
    // std::future<ull> odd_sum = std::async(std::launch::deferred, findOdd, start, end);
    std::future<ull> odd_sum = std::async(std::launch::async, findOdd, start, end);

    this_thread::sleep_for(seconds(3));
    cout << "Wait for result\n";
    cout << "OddSum: " << odd_sum.get() << "\n";
    cout << "Completed\n";

    return 0;
}

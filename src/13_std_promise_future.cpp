#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;
typedef long long int ull;


void findOdd(std::promise<ull>&& OddSumPromise, ull start, ull end) {
    ull odd_sum = 0;
    for (ull i = start; i <= end; ++i) {
        if (i % 2 == 1) {
            odd_sum += i;
        }
    }
    OddSumPromise.set_value(odd_sum);
}

int main() {

    ull start = 0, end = 1900000000;

    std::promise<ull> odd_sum;
    std::future<ull> odd_future = odd_sum.get_future();

    cout << "Create thread\n";
    std::thread t1(findOdd, std::move(odd_sum), start, end);

    this_thread::sleep_for(seconds(5));
    cout << "Wait for result\n";
    cout << "OddSum: " << odd_future.get() << "\n";
    cout << "Completed\n";

    t1.join();

    return 0;
}

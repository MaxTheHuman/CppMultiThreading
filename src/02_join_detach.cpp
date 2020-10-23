#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;


typedef unsigned long long ull;

ull even_sum = 0;
ull odd_sum = 0;

void find_sum_of_even(ull start, ull end) {
    for (ull i = start; i < end; ++i) {
        if (i % 2 == 0) {
            even_sum += i;
        }
    }
}

void find_sum_of_odd(ull start, ull end) {
    for (ull i = start; i < end; ++i) {
        if (i % 2 == 1) {
            odd_sum += i;
        }
    }
}

int main() {

    ull start = 0, end = 1900000000;

    auto start_time = high_resolution_clock::now();
    
    thread p1(find_sum_of_even, start, end);
    thread p2(find_sum_of_odd, start, end);

    p1.join();
    if (p1.joinable()) {
        p1.detach();
    }
    p2.detach();

    // find_sum_of_even(start, end);
    // find_sum_of_odd(start, end);
    
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_time - start_time);

    cout << "Odd sum = " << odd_sum << "\n";
    cout << "Even sum = " << even_sum << "\n";
    cout << "Time spent: " << duration.count() << " microseconds\n";
    return 0;
}

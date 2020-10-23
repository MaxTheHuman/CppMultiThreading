#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;


std::condition_variable cv;
std::mutex m;
long long int balance = 0;

void addMoney(int money) {
    std::lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount added. Current balance: " << balance << "\n";
    cv.notify_one();
    // this_thread::sleep_for(seconds(2));
}

void withdrawMoney(int money) {
    std::unique_lock<mutex> ul(m);
    cv.wait(ul, [] {return (balance > 0) ? true : false;});

    if (balance >= money) {
        balance -= money;
        cout << "Amount defucted: " << money << "\n";
    } else {
        cout << "Balance is less then " << money << "\n";
    }

    cout << "Current balance is: " << balance << "\n";
}

int main() {

    // thread t1(withdrawMoney, 500);
    thread t2(addMoney, 500);
    // this_thread::sleep_for(seconds(1));
    thread t1(withdrawMoney, 500);

    t1.join();
    t2.join();
    
    return 0;
}

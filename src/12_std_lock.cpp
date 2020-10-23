#include <iostream>
#include <mutex>
#include <thread>

using namespace std;


std::mutex m1;
std::mutex m2;
std::mutex m3;
std::mutex m4;

void thread1() {
    std::lock(m1, m2);
    cout << "Critical section of thread one\n";
    m1.unlock();
    m2.unlock();
}

void thread2() {
    std::lock(m1, m2);
    cout << "Critical section of thread two\n";
    m1.unlock();
    m2.unlock();
}

void thread3() {
    std::lock(m1, m2, m3, m4);
    cout << "Critical section of thread three\n";
    m1.unlock();
    m2.unlock();
    m3.unlock();
    m4.unlock();
}

void thread4() {
    std::lock(m3, m4);
    std::lock(m1, m2);
    cout << "Critical section of thread four\n";
    m1.unlock();
    m2.unlock();
    m3.unlock();
    m4.unlock();
}

void thread5() {
    std::lock(m1, m2);
    std::lock(m3, m4);
    cout << "Critical section of thread five\n";
    m1.unlock();
    m2.unlock();
    m3.unlock();
    m4.unlock();
}

int main() {

// example 1
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();

// example 2
    thread t3(thread3);
    thread t4(thread4);
    t3.join();
    t4.join();

// example 3 - this may deadlock
    thread t5(thread5);
    thread t6(thread4);
    t5.join();
    t6.join();

    return 0;
}

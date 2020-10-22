#include <iostream>
#include <mutex>
#include <thread>

using namespace std;


std::mutex m1;
std::mutex m2;

void thread1() {
    m1.lock();
    m2.lock();
    cout << "Critical section of thread one\n";
    m2.unlock();
    m1.unlock();
}

void thread2() {
    m2.lock();
    m1.lock();
    cout << "Critical section of thread two\n";
    m1.unlock();
    m2.unlock();
}

int main() {

    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();
    
	return 0;
}

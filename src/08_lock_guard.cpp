#include <iostream>
#include <mutex>
#include <thread>

using namespace std;


std::mutex m1;
int buffer = 0;

void task(const char* thread_name, int loop_for) {
    // m1.lock();
    std::lock_guard<mutex> lock(m1);
    for (int i = 0; i < loop_for; ++i) {
        buffer++;
        cout << thread_name << ": " << buffer << "\n";
    }
    cout.flush();
    // m1.unlock();
}

int main() {

    thread t1(task, "T1", 10);
    thread t2(task, "T2", 10);

    t1.join();
    t2.join();
    
	return 0;
}

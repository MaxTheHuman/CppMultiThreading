#include <iostream>
#include <mutex>
#include <thread>

using namespace std;


std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loop_for) {
    if (loop_for < 0) {
        return;
    }

    m1.lock();

    cout << c << " " << buffer++ << "\n";
    cout.flush();
    recursion(c, --loop_for);

    m1.unlock();
}

int main() {

    thread t1(recursion, '1', 10);
    thread t2(recursion, '2', 10);

    t1.join();
    t2.join();
    
	return 0;
}

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

mutex mtx;
condition_variable cv;
int barrier_count = 0;
const int num_threads = 5;

void thread_task(int id) {
    {
        unique_lock<mutex> lock(mtx);
        barrier_count++;
        if (barrier_count < num_threads) {
            cv.wait(lock);
        } else {
            cv.notify_all();
        }
    }

    cout << "Thread " << id << " passed the barrier." << endl;
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(thread_task, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

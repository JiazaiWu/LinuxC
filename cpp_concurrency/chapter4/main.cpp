#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

bool stop = false;
mutex mut;
vector<int> iv;
condition_variable data_cond;

void prepare_fun() {
    int counter = 0;
    while (!stop) {
        counter++;
        unique_lock<mutex> lk(mut);
        cout << "prapare val " <<counter<<endl; 
        iv.push_back(counter);
        data_cond.notify_one();
        lk.unlock();
        cout << "sleep..... " <<endl; 
        this_thread::sleep_for(chrono::seconds(2));
        cout << "wakeUp..... " <<endl; 
    }
}

void process_fun() {
    while(!stop) {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, []{return !iv.empty();});
        cout << "get notify" <<endl;
        const int val = iv.back();
        iv.pop_back();
        cout << "get val " << val << endl;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    thread ithread(prepare_fun);
    thread hthread(process_fun);
    cin >> stop;
    return 0;
}

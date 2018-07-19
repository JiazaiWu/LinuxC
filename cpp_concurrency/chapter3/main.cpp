#include<thread>
#include<iostream>
#include<algorithm>
#include<mutex>
#include<vector>
#include<functional>

using namespace std;

mutex print_mutex;

void do_print_work(int x = 0) {
    lock_guard<mutex> guard(print_mutex);
    cout << "print " << x << endl;
}

int main(int argc, char const *argv[])
{
    cout << "multi thread print" << endl;

    vector<thread> threads;
    for (int i=0; i<10; i++) {
        threads.push_back(thread(do_print_work, i));
    }
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    return 0;
}

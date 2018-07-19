#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>

using namespace std;

void do_some_else() {
    cout << "do some else" << endl;
}

void do_some_work() {
    cout << "do some work" << endl;
}

class background_task{
public:
    void operator()(int i=0) const {
        cout << "input " << i << endl;
        do_some_work();
        do_some_else();
    }

    void do_lengthy_work(int i=2) {
        cout << "lengthy work " <<i<<endl;
    }
};

int main(int argc, char const *argv[])
{
    cout << "my PC support " << thread::hardware_concurrency << endl;
    cout << "main thread id " << this_thread::get_id() << endl;
    cout << "arg is func" <<endl;
    thread mythread1(do_some_work);
    mythread1.join();

    cout << "arg is callable class" << endl;
    background_task bt;
    thread mythread2(bt, 1);
    mythread2.join();

    cout << "do lengthy work" << endl;
    background_task bt2;
    thread mythread3(&background_task::do_lengthy_work, &bt2, 2);
    mythread3.join();

    cout << "create multi thread and manage them with vector" << endl;
    vector<thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.push_back(thread{background_task(), i});
    }
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    return 0;
}

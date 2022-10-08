#include <iostream>
#include<thread>
#include<chrono>
#include<future>
#include<string>
#include<exception>

using namespace std;

//低级接口
namespace jj01 {

    void func(const char *s) {

        thread t([]() {
            this_thread::sleep_for(chrono::duration<int, ratio<1, 1>>(10));
            cout << "inner thread: " << this_thread::get_id() << endl;
        });

        cout << "input: " << s << endl;
        this_thread::sleep_for(chrono::duration<int, ratio<1, 1>>(3));
        cout << "func thread: " << this_thread::get_id() << endl;


        t.detach();


    }


    void test() {
        //创建线程，传入函数对象与参数
        thread t(func, "hello");

        this_thread::sleep_for(chrono::duration<int, ratio<1, 1>>(2));
        cout << "main thread: " << this_thread::get_id() << endl;
        //主线程完成后直接销毁了子线程
        //阻塞子线程直到结束
        t.join();
        //分离子线程
//        t.detach();
    }
}

//高级接口async
namespace jj02 {
    void test() {

        auto start = chrono::steady_clock::now();
        auto f = async([]() {
            this_thread::sleep_for(chrono::seconds(3));
            cout << "func thread: " << this_thread::get_id() << endl;
            return 0;
        });

//        f.wait();

        this_thread::sleep_for(chrono::seconds(3));
        cout << "main thread: " << this_thread::get_id() << endl;

        cout << "get data: " << f.get() << endl;
        auto end = chrono::steady_clock::now();

        cout << "time spend: " << chrono::duration_cast<chrono::seconds>(end - start).count() << endl;

    }
}

//shard_async
namespace jj03 {

    int queryNum() {
        int num{0};

        cout << "input num: " << endl;
        cin >> num;

        if (!cin) {
            throw runtime_error("input empty!");
        }
        return num;
    }

    void doSomething(char c, shared_future<int> &sf) {
        try {
            int num = sf.get();
            for (int i = 0; i < num; ++i) {
                this_thread::sleep_for(chrono::milliseconds(100));
                cout.put(c).flush();
            }
        }
        catch (const exception &e) {
            cout << "thread: " << this_thread::get_id() << ", err: " << e.what() << endl;
        }
    }

    void test() {
        auto f = async(queryNum).share();

        auto f1 = async(doSomething, '+', ref(f));
        auto f2 = async(doSomething, '-', ref(f));

        f1.get();
        f2.get();


    }
}


//promise
namespace jj04 {
    void doSomething(promise<string> &p) {

        try {
            cout << "read char :";
            char c = cin.get();
            if (c == 'x') {
                throw runtime_error(string("char ") + c + " exception!");
            }
            string s = string("char ") + c + " processed!";
            p.set_value(std::move(s));
        }
        catch (...) {
            p.set_exception(std::current_exception());
        }
    }

    void test() {
        try {
            promise<string> p;
            thread t(doSomething, ref(p));
            t.detach();

            future<string> f(p.get_future());

            cout << "result: " << f.get() << endl;
        }
        catch (const exception &e) {
            cerr << "Exception: " << e.what() << endl;
        }
        catch (...) {
            cerr << "Exception!" << endl;
        }
    }
}

//packaged_task
namespace jj05 {
    int doSomething(int d) {
        this_thread::sleep_for(chrono::seconds(2));
        return d;
    }

    void test() {
        packaged_task<int(int)> task(doSomething);

        auto f = task.get_future();

        task(1);

        cout << f.get() << endl;

    }

}



int main() {
    jj05::test();
    return 0;
}

// ThreadExperiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using namespace std;

class IWorker
{
    virtual void run() = 0;
};

class WorkerClass
{
public:
    void operator() () const
    {
        cout << "\nInside thread Workerclass \n";
    }
};


void worker2()
{
    cout << "\nInside worker2" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void worker()
{
    std::cout << "Inside worker" << endl;
    std::thread t1(&worker2);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::thread t3{ WorkerClass() };

    t1.join();
    t3.join();

}

string dummy(int x)
{
    return to_string(x);
}

class threadGuard
{
    std::thread _t;
public:
    threadGuard(std::thread&& t):_t(std::move(t))
    {
        if (!_t.joinable())
        {
            throw "Not joinable thread";
        }
    }
    ~threadGuard()
    {
        if (_t.joinable())
        {
            std::thread::id id = _t.get_id();
            _t.join();
            cout << "\n Joining thread id = " << id <<"\n";
        }
    }
    threadGuard() = default;
    threadGuard(threadGuard const&) = delete;
    threadGuard& operator=(threadGuard const&) = delete;
    threadGuard(threadGuard && other)
    {
        _t.swap(other._t);
    }
    threadGuard& operator=(threadGuard && t)
    {
        if (&t == this)
        {
            return *this;
        }
        _t.swap(t._t);

        return *this;

    }

};
int main()
{
    cout << "Hardware threads = " << std::thread::hardware_concurrency() << endl;
    std::cout << "Hello World!\n";
    //std::thread t1(&worker);
    //t1.join();
    //cout << "Thread finished" << endl;
    vector<threadGuard> threads(10);
    for (int j = 0; j < 10; j++)
    {
        threads[j] = std::move( threadGuard(std::thread(
            []()
		    {
				cout << "\nExecuting current thread id = " << std::this_thread::get_id() << "\n";
				int k = 0;
				for (int i = 0; i < 100000; i++)
				{
					k = i;
				}
		    }
		    )));
    }
    cout << "end of main\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

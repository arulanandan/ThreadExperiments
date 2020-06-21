// ThreadExperiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class IWorker
{
    virtual void run() = 0;
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

    t1.join();

}
int main()
{
    cout << "Hardware threads = " << std::thread::hardware_concurrency() << endl;
    std::cout << "Hello World!\n";
    std::thread t1(&worker);
    t1.join();
    cout << "Thread finished" << endl;

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

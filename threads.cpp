#include <thread>
#include <iostream>
#include <vector>
using namespace std;

void foo(int id, int th1) {

        int number = 0;
        while(number != th1) {

        number = rand() % 10000;

    }

        cout << "Thread " << id << "completed" << endl;
}

int main(int argc, char* argv[]) {

    int results;
    int id; 

    int i = atoi(argv[1]);

    vector<thread> vec1;
   // vec.push_back(std::thread(foo));

    for (int j =0; j < 10; j++){

        vec1.push_back(thread(foo, j, i));

    }

    for(auto& th1: vec1) {

         th1.join();
    }

    cout << "All threads have finished finding numbers." <<endl;

    return 0;
}

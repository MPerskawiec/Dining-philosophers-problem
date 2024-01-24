#include <vector>
#include "philosopher.h"


int main() {
    const int Amount = 5;

    std::vector<std::mutex> forkAvailable(Amount);
    std::mutex mx1;
    std::mutex mx2;

    Philosopher P1{1, mx1, mx2};
    Philosopher P2{2, mx1, mx2};


    std::thread t1{&Philosopher::work, &P1};
    std::thread t2{&Philosopher::work, &P2};

    
    t1.join();
    t2.join();
    

    return 0;
}
#include <vector>
#include "philosopher.h"

int main() {
    const int amount = 5;

    std::vector<std::mutex> forkAvailable(amount);
    std::vector<Philosopher> philosophers;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < amount; i++) {
        if (i == 0) {
            philosophers.emplace_back(i + 1, forkAvailable[amount - 1], forkAvailable[0]);
        } else {
            philosophers.emplace_back(i + 1, forkAvailable[i - 1], forkAvailable[i]);
        }
    }

    for (size_t i = 0; i < amount; i++) {
        threads.emplace_back(&Philosopher::work, &philosophers[i]);
    }

    while (1) {
        std::vector<PhilosopherState> st(amount);
        for (size_t i = 0; i < amount; i++) {
            st[i] = philosophers[i].getPhState();
        }

        for (size_t i = 0; i < amount; i++) {
            if (st[i] == PhilosopherState::Idle) {
                std::cout << i + 1 << ": Idle     ";
            } else if (st[i] == PhilosopherState::Resting) {
                std::cout << i + 1 << ": Resting     ";
            } else if (st[i] == PhilosopherState::WaitingForForks) {
                std::cout << i + 1 << ": Waiting     ";
            }else if (st[i] == PhilosopherState::Eating) {
                std::cout << i + 1 << ": Eating     ";
            }
        }
        std::cout <<"\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    for (auto&& th : threads) {
        th.join();
    }

    return 0;
}
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

enum class PhilosopherState {
    Idle,
    Resting,
    WaitingForForks,
    Eating
};

class Philosopher {
public:
    Philosopher(size_t id, std::mutex& leftFork, std::mutex& rightFork)
        : id_(id), leftFork_(leftFork), rightFork_(rightFork), PhState_(PhilosopherState::Idle) {}

    void work() {
        while (1) {
            PhState_ = PhilosopherState::WaitingForForks;
            {
                std::cout<< id_ << ": czekam za widelcem \n";
                std::scoped_lock lock{leftFork_, rightFork_};
                std::cout<< id_ << ": jem \n";
                eating();
            }
            std::cout<< id_ << ": odpoczywam \n";
            resting();

        }
    }

    size_t getId() const {
        return id_ ;
    }
    
    PhilosopherState getPhState() const {
        return PhState_;
    }



private:
    size_t id_;
    std::mutex& leftFork_;
    std::mutex& rightFork_;
    PhilosopherState PhState_;

    void resting() {
        PhState_ = PhilosopherState::Resting;
        auto time = randTime();
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }

    void eating() {
        PhState_ = PhilosopherState::Eating;
        auto time = randTime();
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }

    size_t randTime() {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(2, 10);

        return distribution(generator);
    }
};

int main() {
    const int Amount = 5;

    std::vector<std::mutex> forkAvailable(Amount);
    std::mutex mx1;
    std::mutex mx2;

    Philosopher P1{1, mx1, mx2};
    Philosopher P2{2, mx1, mx2};

.\
    std::thread t1{&Philosopher::work, &P1};
    std::thread t2{&Philosopher::work, &P2};

    
    t1.join();
    t2.join();
    

    return 0;
}
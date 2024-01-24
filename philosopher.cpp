#include "philosopher.h"

void Philosopher::work() {
    while (1) {
        PhState_ = PhilosopherState::WaitingForForks;
        {
            std::scoped_lock lock{leftFork_, rightFork_};
            eating();
        }
        resting();
    }
}

size_t Philosopher::getId() const {
    return id_;
}

PhilosopherState Philosopher::getPhState() const {
    return PhState_;
}

void Philosopher::resting() {
    PhState_ = PhilosopherState::Resting;
    auto time = randTime();
    std::this_thread::sleep_for(std::chrono::seconds(time));
}

void Philosopher::eating() {
    PhState_ = PhilosopherState::Eating;
    auto time = randTime();
    std::this_thread::sleep_for(std::chrono::seconds(time));
}

size_t Philosopher::randTime() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(2, 10);

    return distribution(generator);
}

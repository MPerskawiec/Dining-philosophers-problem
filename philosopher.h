#pragma once
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

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

    void work();
    size_t getId() const;
    PhilosopherState getPhState() const;

private:
    size_t id_;
    std::mutex& leftFork_;
    std::mutex& rightFork_;
    PhilosopherState PhState_;

    void resting();
    void eating();
    size_t randTime();
};

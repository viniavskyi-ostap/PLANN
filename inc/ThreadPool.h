#ifndef PLANN_THREADPOOL_H
#define PLANN_THREADPOOL_H

#include <queue>
#include <atomic>
#include <mutex>
#include <thread>
#include <functional>
#include <iostream>

template <typename T>
class ThreadSafeQueue {
    std::queue<T> queue;
    std::mutex mutex;

public:
    ThreadSafeQueue() = default;


    void push(T new_obj) {
        std::lock_guard<std::mutex> guard(mutex);
        queue.push(new_obj);
    }

    bool try_pop(T& obj) {
        std::lock_guard<std::mutex> guard(mutex);
        if (queue.empty())
            return false;
        obj = queue.front();
        queue.pop();
        return true;
    }

};

class Joiner {
    std::vector<std::thread>& threads;

public:
    explicit Joiner(std::vector<std::thread>& given_threads): threads(given_threads) {};

    ~Joiner() {
        for (auto &thread: threads) {
            thread.join();
        }
    }
};


using task_function = std::function<void()>;

class ThreadPool {

    std::atomic_bool done;
    ThreadSafeQueue<std::function<void()>> work_queue;
    std::vector<std::thread> threads;
    Joiner joiner;

    void worker_thread() {
        while(!done) {
            task_function task;
            if (work_queue.try_pop(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }

public:
    ThreadPool(): done(false), joiner(threads) {
        unsigned const thread_count = std::thread::hardware_concurrency();

        for (unsigned i = 0; i < thread_count; ++i) {
            threads.emplace_back(&ThreadPool::worker_thread, this);
        }

    }

    ~ThreadPool() {
        done = true;
    }

    template<typename FunctionType>
    void submit(FunctionType f) {
        work_queue.push(task_function(f));
    }
};




#endif //PLANN_THREADPOOL_H

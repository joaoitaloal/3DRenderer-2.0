#include "ThreadPool.h"

ThreadPool::ThreadPool(int num_threads, function<void(JobData)> fn_){
    fn = fn_;
    active_jobs = 0;

    for(int i = 0; i < num_threads; i++){
        thread([this] { worker(); }).detach();
    }
}

void ThreadPool::add_job(JobData job){
    {
        lock_guard<mutex> lock(mtx);
        jobs_queue.push(move(job));
    }
    sync_c.notify_one();
}

void ThreadPool::await_jobs(){
    unique_lock<mutex> lock(mtx);
    done_c.wait(lock, [this] {
        return jobs_queue.empty() && active_jobs == 0;
    });
}

void ThreadPool::worker(){
    unique_lock<mutex> lock(mtx);

    while(true){
        sync_c.wait(lock, [this] {
            return !jobs_queue.empty();
        });

        JobData job = move(jobs_queue.front());
        jobs_queue.pop();
        active_jobs++;

        lock.unlock();

        fn(job);

        lock.lock();

        active_jobs--;

        if(jobs_queue.empty() && active_jobs == 0){
            done_c.notify_all();
        }
    }
}
#ifndef RENDERER_THREADPOOL_H
#define RENDERER_THREADPOOL_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

using namespace std;

// TODO: Mudar o job_data pra um generics, pra tentar deixar essa classe mais geral
// Adicionar uma forma de parar as threads tbm

struct JobData{
    int i, n;
};

class ThreadPool{
    public:
        ThreadPool(int num_threads, function<void(JobData)> fn_);

        void add_job(JobData job);

        void await_jobs();
    private:
        queue<JobData> jobs_queue;

        function<void(JobData)> fn;

        mutex mtx;
        condition_variable sync_c;
        condition_variable done_c;

        int active_jobs;

        void worker();
};

#endif // RENDERER_THREADPOOL_H
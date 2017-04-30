#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H
#include<QThread>
class thread_queue : public QThread
{
public:
    thread_queue();
    void bfs();
    void dfs();
};

#endif // THREAD_QUEUE_H

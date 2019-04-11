#include <pthread.h>

class ScopedLock {
public:
    ScopedLock(phtread_mutex_t* mutex) : _mutex(mutex) {
        pthread_mutex_lock(_mutex);
    }
    
    ~ScopedLock() {
        pthread_mutex_unlock(_mutex);
    }

private:
    phtread_mutex_t* _mutex;
};


class CountDownLatch {
public:
    explicit CountDownLatch(int count);
    
    ~CountDownLatch();
    
    void wait();

    void count_down();

private:
    int _count;
    pthread_mutex_t _mutex;
    pthread_cont_t _cond;
};

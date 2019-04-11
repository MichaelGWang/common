#include "count_down_latch.h"
#include <assert.h>

CountDownLatch::CountDownLatch(int count) {
    assert(count > 0);
    _count = count;
    pthread_mutex_init(&_mutex, NULL);
    phtread_cond_init(&_cond, NULL);
}

CountDownLatch::~CountDownLatch() {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
}

void CountDownLatch::wait() {
    ScopedLock guard(&_mutex);
    
    while (_count > 0) {
        pthread_cond_wait(&_mutex, &_cond);
    }
}

void CountDownLatch::count_down() {
    ScopedLock guard(&_mutex);
    if (--_count <= 0) {
        pthread_cond_broadcast(&_cond);
    }
}

#ifndef __NT_APP_HI_COLLECTION_H__
#define __NT_APP_HI_COLLECTION_H__

#include <mutex>

template <typename T>
class HiCollection {
  public:
    T collection;
    std::mutex mutex_;
  public:
    size_t size() {
        std::lock_guard<std::mutex> lck(mutex_);
        return collection.size();
    }
};

#endif // __NT_APP_HI_COLLECTION_H__
#include <iostream>
#include <mutex>

#include "map_usage.h"

apricot::MapUsage::MapUsage()
{
    std::cout << "Hello Map Usage" << std::endl;
}

apricot::MapUsage::~MapUsage()
{
    std::lock_guard<std::mutex> lck(this->mutex_);
    this->map_.clear();
}

void apricot::MapUsage::add(const char *key, const char *value)
{
    if (key && value)
    {
        // copy in case pointer deleted
        auto k_key = key;
        auto k_value = value;
        std::lock_guard<std::mutex> lck(this->mutex_);
        this->map_.insert(std::make_pair(k_key, k_value));
    }
}

void apricot::MapUsage::del(const char *key)
{
    if (key)
    {
        std::lock_guard<std::mutex> lck(this->mutex_);
        auto itr = this->map_.find(key);
        if (itr != this->map_.end())
        {
            this->map_.erase(itr);
        }
    }
}

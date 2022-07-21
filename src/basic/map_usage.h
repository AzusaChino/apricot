#ifndef _MAP_USAGE_H_
#define _MAP_USAGE_H_

#include <map>
#include <mutex>

namespace apricot
{
    /**
     * @brief Map Usage Demo
     */
    class MapUsage
    {
    public:
        MapUsage();
        ~MapUsage();
        void add(const char*, const char*);
        void del(const char*);
    private:
        std::map<const char*, const char*> map_;
        std::mutex mutex_;
    };
}

#endif

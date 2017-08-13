#include <chrono>
#include <utility>

namespace 
{
    template<typename Units = std::chrono::milliseconds>
    struct timer
    {
        template<typename Func, typename ...Args>
        static auto timeit(Func&& f, Args&&... args)
        {
            auto start = std::chrono::steady_clock::now();
            std::forward<decltype(f)>(f)(std::forward<Args>(args)...);
            return std::chrono::duration_cast<Units>(std::chrono::steady_clock::now() - start).count();
        }
    };
}

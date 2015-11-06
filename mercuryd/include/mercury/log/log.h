#ifndef __MERCURY_LOG_LOG_H__
#define __MERCURY_LOG_LOG_H__

#include "mercury/config.h"

#include <boost/format.hpp>
#include <llog/llog.h>

#include <string>

namespace mercury { namespace log { typedef llog::logger<> log_t; }}
namespace mercury { namespace log { namespace detail {

inline boost::format& format_impl(boost::format& f)
{
    return f;
}

template<typename Head, typename... Rest>
inline boost::format& format_impl(boost::format& f, const Head& h, Rest&&... rest)
{
    return format_impl(f % h, std::forward<Rest>(rest)...);
}

template<typename... Args>
inline std::string format(const std::string& fmt, Args&&... args)
{
    boost::format f(std::move(fmt));
    return detail::format_impl(f, std::forward<Args>(args)...).str();
}

#define __I(fmt, ...) _I(mercury::log::detail::format(fmt, ## __VA_ARGS__))
#define __W(fmt, ...) _W(mercury::log::detail::format(fmt, ## __VA_ARGS__))
#define __E(fmt, ...) _E(mercury::log::detail::format(fmt, ## __VA_ARGS__))
#define __PANIC(fmt, ...) _P(mercury::log::detail::format(fmt, ## __VA_ARGS__))

}}} // namespace detail/log/mercury

#endif // __MERCURY_LOG_LOG_H__

#pragma once
#include <functional>
#include <ranges>

template <typename F>
struct pipable_fn {
    F f;
    template <typename R>
    decltype(auto) operator()(R&& r) const {
        return f(std::forward<R>(r));
    }
};

template <std::ranges::input_range R, typename F>
decltype(auto) operator|(R&& r, const pipable_fn<F>& pf) {
    return pf(std::forward<R>(r));
}

template <typename F, typename... Args>
constexpr auto pipe(F&& f, Args&&... args) {
    return pipable_fn{
        [f = std::forward<F>(f), ... args = std::forward<Args>(args)](auto&& range) -> decltype(auto) {
            return std::invoke(f, std::forward<decltype(range)>(range), args...);
        }};
}

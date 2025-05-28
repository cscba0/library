#pragma once
#include <ranges>

template <typename F>
struct pipe_fn {
    F f;
    template <typename R>
    decltype(auto) operator()(R&& r) const {
        return f(std::forward<R>(r));
    }
};

template <std::ranges::input_range R, typename F>
decltype(auto) operator|(R&& r, const pipe_fn<F>& pf) {
    return pf(std::forward<R>(r));
}

template <typename F>
constexpr auto pipe(F&& f) {
    return pipe_fn<std::decay_t<F>>{std::forward<F>(f)};
}

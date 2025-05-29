#pragma once
#include <functional>
#include <ranges>

template <typename F>
struct piable_fn_ {
    F f;

    template <typename R>
    decltype(auto) operator()(R&& r) const {
        return f(std::forward<R>(r));
    }
};

template <typename F>
struct curried_pipable {
    F f;

    template <typename... Args>
    auto operator()(Args&&... args) const {
        return piable_fn_{
            [f = f, ... args = std::forward<Args>(args)](auto&& range) -> decltype(auto) {
                return std::invoke(f, std::forward<decltype(range)>(range), args...);
            }};
    }
};

template <std::ranges::input_range R, typename F>
decltype(auto) operator|(R&& r, const piable_fn_<F>& pf) {
    return pf(std::forward<R>(r));
}

struct as_pipe_t {
    template <typename F>
    constexpr auto operator|(F&& f) const {
        return curried_pipable<std::decay_t<F>>{std::forward<F>(f)};
    }

    template <typename F, typename... Args>
    constexpr auto operator()(F&& f, Args&&... args) const {
        return piable_fn_{
            [f = std::forward<F>(f), ... args = std::forward<Args>(args)](auto&& range) -> decltype(auto) {
                return std::invoke(f, std::forward<decltype(range)>(range), args...);
            }};
    }
};

inline constexpr as_pipe_t as_pipe;

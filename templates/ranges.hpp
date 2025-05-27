#pragma once
#include <algorithm>
#include <ranges>

namespace _ranges {

template <typename Container>
struct to_t {
    template <std::ranges::input_range R>
    Container operator()(R&& r) const {
        Container result;
        std::ranges::copy(r, std::inserter(result, result.end()));
        return result;
    }
};

template <template <typename...> class Template>
struct to_template_t {
    template <std::ranges::input_range R>
    auto operator()(R&& r) const {
        using T = std::ranges::range_value_t<R>;
        return to_t<Template<T>>{}(std::forward<R>(r));
    }
};

template <std::ranges::input_range R, typename Container>
auto operator|(R&& r, const to_t<Container>& f) {
    return f(std::forward<R>(r));
}

template <std::ranges::input_range R, template <typename...> class Template>
auto operator|(R&& r, const to_template_t<Template>& f) {
    return f(std::forward<R>(r));
}

template <typename Container>
constexpr auto to() {
    return to_t<Container>{};
}

template <template <typename...> class Template>
constexpr auto to() {
    return to_template_t<Template>{};
}
}  // namespace _ranges

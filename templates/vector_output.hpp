#pragma once
#include <string>
#include <vector>

template <typename T>
struct vector_output {
    std::vector<T> v;
    std::string s;
    vector_output(std::vector<T> _v, std::string _s) : v(_v), s(_s) {}
    vector_output(std::vector<T> _v, char c) : v(_v), s{c} {}
};
template <typename T>
vector_output<T> operator+(const std::vector<T>& v, const std::string& s) {
    return vector_output(v, s);
}
template <typename T>
vector_output<T> operator+(const std::vector<T>& v, char c) {
    return vector_output(v, c);
}

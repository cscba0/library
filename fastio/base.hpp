#pragma once
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <tuple>

struct FASTIO {
    static constexpr int buffer_size = 1 << 20;
    char output_buffer[buffer_size];
    char *ipos, *obegin, *oend, *opos;
    explicit FASTIO() : obegin(output_buffer),
                        oend(output_buffer + buffer_size),
                        opos(output_buffer) {
        struct stat st;
        fstat(0, &st);
        ipos = (char *)malloc(st.st_size + 64);
        memset(ipos + st.st_size, ' ', 64);
        ipos = (char *)mmap(ipos, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
    }
    ~FASTIO() noexcept { this->flush(); }

    inline void seek() noexcept {
        while (*ipos <= ' ') [[unlikely]] {
            ++ipos;
        }
    }

    inline void flush() noexcept {
        std::ignore = ::write(1, obegin, opos - obegin);
        opos = obegin;
    }

    inline void reserve(int x) noexcept {
        if (oend - opos < x) [[unlikely]] {
            flush();
        }
    }
} FIO;

#define cin FIO
#define cout FIO

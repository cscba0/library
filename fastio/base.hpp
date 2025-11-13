#pragma once
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <tuple>

struct FASTIO {
    static constexpr int buffer_size = 1 << 20;
    char input_buffer[buffer_size];
    char output_buffer[buffer_size];
    char *ibegin, *iend, *ipos;
    char *obegin, *oend, *opos;

    explicit FASTIO()
        : ibegin(input_buffer),
          iend(input_buffer),
          ipos(input_buffer),
          obegin(output_buffer),
          oend(output_buffer + buffer_size),
          opos(output_buffer) {
#ifndef LOCAL
        struct stat st;
        fstat(0, &st);
        if (S_ISREG(st.st_mode)) {
            ipos = (char *)mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0);
            iend = ipos + st.st_size;
        } else {
            ssize_t n = ::read(0, input_buffer, buffer_size);
            ipos = input_buffer;
            iend = input_buffer + (n > 0 ? n : 0);
        }
#else
        ipos = input_buffer;
        iend = input_buffer;
#endif
    }

    ~FASTIO() noexcept { flush(); }

    inline void flush() noexcept {
        if (opos != obegin) {
            std::ignore = ::write(1, obegin, opos - obegin);
            opos = obegin;
        }
    }

    inline void reserve(int x) noexcept {
        if (oend - opos < x) [[unlikely]]
            flush();
    }

    inline void seek() noexcept {
        while (ipos < iend && *ipos <= ' ') [[unlikely]]
            ++ipos;
#ifdef LOCAL
        if (ipos == iend) refill();
#endif
    }

#ifdef LOCAL
    inline void refill() noexcept {
        ssize_t n = ::read(0, input_buffer, buffer_size);
        if (n <= 0) {
            input_buffer[0] = ' ';
            iend = input_buffer + 1;
        } else {
            ibegin = input_buffer;
            iend = input_buffer + n;
        }
        ipos = ibegin;
    }
#endif
};

FASTIO FIO;
#define cin FIO
#define cout FIO

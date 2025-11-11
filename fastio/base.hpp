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
        if (S_ISREG(st.st_mode)) {
            ipos = (char *)malloc(st.st_size + 64);
            memset(ipos + st.st_size, ' ', 64);
            ipos = (char *)mmap(ipos, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0);
        } else {
            constexpr size_t BUF = 1 << 20;
            size_t total = 0;
            char *buf = (char *)malloc(BUF);
            for (;;) {
                ssize_t n = ::read(0, buf + total, BUF);
                if (n <= 0) break;
                total += n;
                buf = (char *)realloc(buf, total + BUF);
            }
            memset(buf + total, ' ', 64);
            ipos = buf;
        }
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

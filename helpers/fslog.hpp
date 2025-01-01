#pragma once

#include <time.h>
#include <inttypes.h>

#include <string>
#include <array>
#include <typeinfo>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#else
#error "Unsupported platform :("
#endif

#if defined(_MSC_VER)
#define INLINE __forceinline
#define FS_FUNC __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
#define INLINE __attribute__((always_inline)) inline
#define FS_FUNC __PRETTY_FUNCTION__
#else
#define INLINE inline
#error "Unsupported compiler :("
#endif

// Private macros

#define _FS_LINE                     __LINE__
#define _FSLOG_PROCESS               inline std::string process
#define _FSLOG_PROCESS_DEFAULT(type) _FSLOG_PROCESS(type arg) { return std::to_string(arg); }

// Configuration

#define FSLOG_UPPER_HEX             0
#define FSLOG_IGNORE_WRITE_ERROR    1

namespace fslog {
    namespace types { // Edit this as shown below for custom types
        _FSLOG_PROCESS_DEFAULT(int32_t)
            _FSLOG_PROCESS_DEFAULT(uint32_t)
            _FSLOG_PROCESS_DEFAULT(int64_t)
            _FSLOG_PROCESS_DEFAULT(uint64_t)
            _FSLOG_PROCESS_DEFAULT(double)
            _FSLOG_PROCESS_DEFAULT(float)
            _FSLOG_PROCESS_DEFAULT(long)
            _FSLOG_PROCESS_DEFAULT(unsigned long)
            _FSLOG_PROCESS_DEFAULT(uint16_t)

            _FSLOG_PROCESS(bool arg) { return std::string(arg ? "true" : "false"); }
        _FSLOG_PROCESS(const std::string& arg) { return arg; }
        _FSLOG_PROCESS(const char* arg) { return arg; }

        _FSLOG_PROCESS(void* arg) {
            if (arg == nullptr) {
                return "0x0";
            }

            uintptr_t value = reinterpret_cast<uintptr_t>(arg);
#if FSLOG_UPPER_HEX
            const char hex_digits[] = "0123456789ABCDEF";
#else
            const char hex_digits[] = "0123456789abcdef";
#endif

            char result[20] = { '\0' };
            int pos = sizeof(result) / sizeof(char) - 2;

            do {
                result[pos--] = hex_digits[value % 16];
                value /= 16;
            } while (value != 0);

            result[pos--] = 'x';
            result[pos--] = '0';

            return std::string(result + pos + 1);
        }

        // _FSLOG_PROCESS(const CustomType& arg) { return std::string(arg.integer_member); }
        // _FSLOG_PROCESS(Unity::System_String* arg) { return arg->ToString(); }

        template <typename T>
        _FSLOG_PROCESS(const T& arg) {
            static_assert(!std::is_pointer<T>::value, "_FSLOG_PROCESS: Unknown pointer type");
            static_assert(!std::is_array<T>::value, "_FSLOG_PROCESS: Unknown array type");
            static_assert(!std::is_enum<T>::value, "_FSLOG_PROCESS: Unknown enum type");
            static_assert(!std::is_class<T>::value, "_FSLOG_PROCESS: Unknown class type");
            static_assert(!std::is_union<T>::value, "_FSLOG_PROCESS: Unknown union type");
            static_assert(!std::is_reference<T>::value, "_FSLOG_PROCESS: Unknown reference type");
            static_assert(!std::is_void<T>::value, "_FSLOG_PROCESS: Unknown void type");
            static_assert(!std::is_function<T>::value, "_FSLOG_PROCESS: Unknown function type");
            static_assert(!std::is_floating_point<T>::value, "_FSLOG_PROCESS: Unknown floating point type");
            static_assert(!std::is_integral<T>::value, "_FSLOG_PROCESS: Unknown integral type");
            return "unknown_type";
        }
    } // types
}

// Testing

#ifdef FSLOG_TEST
#include "fslog_test.h"

#define _FSLOG_EXP_STYLE_FMT       1  // Use experimental, C# style formatting
#define _FSLOG_EXP_OPTIMIZED_FMT   1  // Use experimental, optimized formatting
#endif

// Public macros

// Used for logging call info. fslog::<loggingfunc>(FS_META, ...)
#define FS_META  fslog::CallInfo{__fs_get_file_name(__FILE__), _FS_LINE}
// Used for logging where the function was called. fslog::<loggingfunc>(FS_POINT)
#define FS_POINT FS_META, "{}", FS_FUNC

// FSLog start

INLINE std::string __fs_get_file_name(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    return (pos != std::string::npos) ? path.substr(pos + 1) : path;
}

enum class FsColor {
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    GRAY = 90,
    BRIGHT_BLACK = 90,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97
};

namespace fslog {
    struct LogColors {
        FsColor bracket = FsColor::WHITE;
        FsColor prefix = FsColor::WHITE;
        FsColor text = FsColor::WHITE;

        LogColors(FsColor _bracket, FsColor _prefix, FsColor _text)
            : bracket(_bracket), prefix(_prefix), text(_text) {}
    };
    struct CallInfo {
        std::string file;
        int line;
    };

    // You can edit these as you like.
    inline LogColors debug_colors(FsColor::GRAY, FsColor::BLUE, FsColor::WHITE);
    inline LogColors info_colors(FsColor::GRAY, FsColor::CYAN, FsColor::WHITE);
    inline LogColors warn_colors(FsColor::GRAY, FsColor::YELLOW, FsColor::WHITE);
    inline LogColors error_colors(FsColor::GRAY, FsColor::RED, FsColor::WHITE);

    inline bool has_setup = false;
    inline void* console_handle = nullptr;

    inline void setup() {
#if defined(_WIN32) || defined(_WIN64)
        if (!has_setup) {
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hOut == INVALID_HANDLE_VALUE) {
                printf("fslog.h: Unable to get console handle\n");
                return;
            }

            DWORD dwMode = 0;
            if (!GetConsoleMode(hOut, &dwMode)) {
                printf("fslog.h: Unable to get console mode\n");
                return;
            }

            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (!SetConsoleMode(hOut, dwMode)) {
                printf("fslog.h: Unable to set console mode\n");
                return;
            }

            has_setup = true;
            console_handle = hOut;
        }
#elif defined(__linux__)
        has_setup = true;
#endif
    }

    namespace fmt {
        template<typename... Args>
        std::string _format(const std::string& fmt, Args&&... args) {
            const size_t num_args = sizeof...(args);
            const size_t fmt_size = fmt.length();
            if (!num_args) return fmt;

            std::string result;
            result.reserve(fmt_size + num_args * 5);
            const std::array<std::string, sizeof...(args)> fmt_args = {
                types::process(std::forward<Args>(args))...
            };

            size_t arg_index = 0;
            for (size_t i = 0; i < fmt_size; ++i) {
                if (fmt[i] == '{') {
                    if (i + 1 < fmt_size && fmt[i + 1] == '}') {
                        if (arg_index < num_args) {
                            result += fmt_args[arg_index++];
                            i++;
                        }
                        else {
                            result += "{";
                        }
                    }
                    else {
                        result += "{";
                    }
                }
                else {
                    result += fmt[i];
                }
            }

            return result;
        }

        template<typename... Args>
        INLINE std::string format(const std::string& fmt, Args&&... args) {
#ifdef _FSLOG_EXP_STYLE_FMT
            return fslog::exp_fmt::_format(fmt, std::forward<Args>(args)...);
#else
            return fslog::fmt::_format(fmt, std::forward<Args>(args)...);
#endif
        }
    } // fmt

    namespace {
        INLINE bool _fs_write(const char* str, size_t length) {
#if defined(_WIN32) || defined(_WIN64)
            return WriteFile(console_handle, str, static_cast<DWORD>(length), nullptr, nullptr);
#elif defined(__linux__)
            return write(STDOUT_FILENO, str, length) != -1;
#endif
        }

        INLINE std::string setcolor(FsColor color) {
            return "\033[" + std::to_string(static_cast<int>(color)) + "m";
        }

        INLINE void fs_localtime(const time_t* t, struct tm* timeinfo) {
#if defined(_WIN32) || defined(_WIN64)
            localtime_s(timeinfo, t);
#elif defined(__linux__)
            localtime_r(t, timeinfo);
#endif
        }

        inline std::string get_time() {
            char buf[64] = { 0 };
            time_t now_time;
            time(&now_time);

            struct tm timeinfo;
            fs_localtime(&now_time, &timeinfo);
            strftime(buf, sizeof(buf), "%H:%M:%S", &timeinfo);

            return buf;
        }

        INLINE std::string p_brackets(const std::string& fmt, const LogColors& colors) {
            return fslog::fmt::_format("{}[{}{}{}]{}",
                fslog::setcolor(colors.bracket), fslog::setcolor(colors.prefix), fmt, fslog::setcolor(colors.bracket), fslog::setcolor(FsColor::WHITE)
            );
        }
    } // details

    INLINE bool fs_write(const std::string& str) {
        return _fs_write(str.c_str(), str.length());
    }

    template<typename... Args>
    void log(const std::string& type, const LogColors& colors, const std::string& fmt, Args&&... args) {
        if (!has_setup) { fslog::setup(); }
        const std::string formatted = fslog::fmt::_format("{} {} {}{}\n",
            p_brackets(get_time(), colors), p_brackets(type, colors), fslog::setcolor(colors.text), fslog::fmt::format(fmt, std::forward<Args>(args)...)
        );

        bool success = _fs_write(formatted.data(), formatted.length());
#if !FSLOG_IGNORE_WRITE_ERROR
        if (!success)
            printf("fslog.h: Unable to write to console\n");
#endif
    }
    template<typename... Args>
    void log(const std::string& type, const CallInfo& call, const LogColors& colors, const std::string& fmt, Args&&... args) {
        if (!has_setup) { fslog::setup(); }
        const std::string formatted = fslog::fmt::_format("{} {} {} {}{}\n",
            p_brackets(get_time(), colors), p_brackets(type, colors), p_brackets(fslog::fmt::_format("{}:{}", call.file, call.line), colors),
            fslog::setcolor(colors.text), fslog::fmt::format(fmt, std::forward<Args>(args)...)
        );

        bool success = _fs_write(formatted.data(), formatted.length());
#if !FSLOG_IGNORE_WRITE_ERROR
        if (!success)
            printf("fslog.h: Unable to write to console\n");
#endif
    }

    template<typename... Args> void debug(const std::string& fmt, Args&&... args) {
        log("DEBUG", debug_colors, fmt, std::forward<Args>(args)...);
    }
    template<typename... Args> void debug(const CallInfo& call, const std::string& fmt, Args&&... args) {
        log("DEBUG", call, debug_colors, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args> void info(const std::string& fmt, Args&&... args) {
        log("INFO", info_colors, fmt, std::forward<Args>(args)...);
    }
    template<typename... Args> void info(const CallInfo& call, const std::string& fmt, Args&&... args) {
        log("INFO", call, info_colors, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args> void warn(const std::string& fmt, Args&&... args) {
        log("WARN", warn_colors, fmt, std::forward<Args>(args)...);
    }
    template<typename... Args> void warn(const CallInfo& call, const std::string& fmt, Args&&... args) {
        log("WARN", call, warn_colors, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args> void error(const std::string& fmt, Args&&... args) {
        log("ERROR", error_colors, fmt, std::forward<Args>(args)...);
    }
    template<typename... Args> void error(const CallInfo& call, const std::string& fmt, Args&&... args) {
        log("ERROR", call, error_colors, fmt, std::forward<Args>(args)...);
    }
} // fslog

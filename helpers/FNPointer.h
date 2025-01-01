#pragma once

template <typename T>
class Pointer;

template <typename R, typename... Args>
class Pointer<R(Args...)>
{
public:
    Pointer() = default;
    explicit Pointer(uintptr_t offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
    }

    explicit Pointer(void* offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
    }

    inline Pointer& operator=(uintptr_t offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
        return *this;
    }

    inline Pointer& operator=(void* offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
        return *this;
    }

    inline R operator()(Args... args) {
        return m_Function(std::forward<Args>(args)...);
    }

private:
    R(*m_Function)(Args...);
};
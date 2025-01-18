#pragma once
#include <type_traits>

namespace tsg {

    template<typename T>
    class adapter {
    public:
        inline T* const get_adaptee() { return m_adaptee; }
    protected:
        T* m_adaptee;
    };

    class non_copyable {
    public:
        non_copyable() = default;
        ~non_copyable() = default;
        non_copyable(const non_copyable&) = delete;
        non_copyable& operator=(const non_copyable&) = delete;
    };

    class object {
    public:
        object() = default;
        ~object() = default;
    };

    template <typename T, typename = std::enable_if_t<std::is_same<T, int>::value>>
    static constexpr bool is_ice(T v) {
        return true;
    };

    static constexpr bool is_ice(int& v){
        return false;
    }
};

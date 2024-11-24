#pragma once

namespace tsg{
    template <typename T, typename ...Args>
    static T& get_istance(Args... args){
        static T istance{args...};
        return istance;
    }

    template <typename T>
    class singleton {
    public:
        singleton(const singleton&) = delete;
        singleton& operator=(const singleton&) = delete;

        // template <typename ...Args>
        // static T * const get_istance(Args... args){
        //     static T istance{args...};
        //     return &istance;
        // }

        template <typename ...Args>
        static T& get_istance(Args... args){
            static T istance{args...};
            return istance;
        }

        T* const get_istance(){
            return m_istance;
        }
    protected:
        singleton() = default;
        ~singleton() = default;
        T* m_istance{this};
    };

}
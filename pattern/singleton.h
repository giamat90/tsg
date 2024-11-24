#pragma once

#include "../types.h"

namespace tsg{
    template <typename T, typename ...Args>
    static T& get_istance(Args... args){
        static T istance{args...};
        return istance;
    }

    template <typename T>
    class singleton : public non_copyable {
    public:
        template <typename ...Args>
        static T& get_istance(Args... args){
            static T istance{args...};
            return istance;
        }

        T* const get_istance(){
            return m_istance;
        }
    protected:
        T* m_istance{this};
    };

}
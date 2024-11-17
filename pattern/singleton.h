#pragma once

namespace tsg{
    class singleton{
    public:
        template <typename T, typename ...Args>
        static T& get_istance(Args... args){
            static T istance{args...};
            return istance;
        }
    };
}
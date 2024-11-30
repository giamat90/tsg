#pragma once

#include "../types.h"
#include "../io/io.h"

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
            if(singleton<T>::m_istance){
                tsg::print("m_istance already exist!");
                return *m_istance;
            } else {
                static T istance{args...};
                singleton<T>::m_istance = &istance;
                tsg::print("m_istance = {}", singleton<T>::m_istance);
                return istance;
            }
        }        

        static T& get_istance(){
            if(singleton<T>::m_istance){
                tsg::print("m_istance already exist!");
                return *m_istance;
            } else {
                static T istance;
                singleton<T>::m_istance = &istance;
                tsg::print("creating a new istance = {}", singleton<T>::m_istance);
                return istance;
            }
        }
    private:
        static T* m_istance;
    };

    template<typename T>
    T* singleton<T>::m_istance = nullptr;
}
#pragma once

#include <cstdint>
#include <cassert>

#include "io.h"

namespace tsg{
    using factorial_t = uint64_t;

    template <size_t N>
    inline factorial_t factorial(){
        return N * factorial<N-1>();
    }

    template<>
    inline factorial_t factorial<0u>(){
        return 1U;
    }

    inline factorial_t factorial(const int n){
        if(0 == n){
            return 1;
        } else {
            return n*factorial(n-1);
        }
    }

    /* Computing N° tartaglia number */
    using tartaglia_t = uint64_t;

    template<size_t N>
    inline void get_tartaglia_numbers(tartaglia_t values[N+1]){
        values[0] = 1;
        values[N] = 1;
        tartaglia_t previous[N];
        get_tartaglia_numbers<N-1>(previous);
        for(int i = 1; i < N; ++i){
            values[i] = previous[i] + previous[i-1]; 
        }
    }

    template<>
    inline void get_tartaglia_numbers<0U>(tartaglia_t values[1]){
            values[0] = 1;
    }

    template<>
    inline void get_tartaglia_numbers<1U>(tartaglia_t values[2]){
            values[0] = 1;
            values[1] = 1;
    }
  
    template<typename T>
    inline constexpr T pow(const T base, const T exp){
        return exp > 0 ? base * pow(base, exp-1) : 1;
    }

    template <typename T, T M>
    class module {
    public:
        module(const T value) {
            if (value > M) {
                m_value += T(0);
            }
            if (value < 0) {
                m_value -= T(0);
            }
        }
        inline module<T,M>& operator+=(const module<T, M>& other) {
            m_value += other.m_value;
            if (m_value > M) {
                m_value -= M;
            }
        }
        inline friend module<T, M> operator+(module<T, M> lhs, const module<T, M>& rhs) {
            lhs += rhs;
            return lhs;
        }
        inline module<T, M>& operator-=(const module<T, M>& other) {
            m_value -= other.m_value;
            if (m_value < T(0)) {
                m_value = M - m_value;
            }
        }
        inline friend module<T, M> operator-(module<T, M> lhs, const module<T, M>& rhs) {
            lhs -= rhs;
            return lhs;
        }
    protected:
        T m_value;
    };

    template <typename T>
    class degree : public module<T, T(360)>{};

    /* Vector class */

	template<typename T, std::size_t Dim>
	class vector {
	public:
		vector() {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = T();
			}
		}

		vector(const T k) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = k;
			}
		}

		vector(const std::initializer_list<T>& list) {
			assert(Dim == list.size());
			auto it = list.begin();
			for (std::size_t i{}; i < Dim, it != list.end(); ++i, ++it) {
				m_v[i] = *it;
			}
		}

		/*
		* It is possible create a vector from another one of minor size
		*/
		template <size_t S, std::enable_if_t<S < Dim, void>>
		explicit vector(const vector<T, S> other) {
			static_assert(S < Dim);
			for (size_t i{}; i < S; ++i) {
				m_v[i] = other.m_v[i];
			}
			for (size_t j = S; j < Dim; ++j) {
				m_v[j] = T{};
			}
		}

		vector(const vector<T, Dim>& other) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				m_v[i] = other.m_v[i];
			}
		}
	public:
		T get_norm() const {
			T value{};
			for (std::size_t i = 0u; i < Dim; ++i) {
				value += m_v[i] * m_v[i];
			}
			return sqrt(value);
		}
		vector<T, Dim> get_normalized() {
			T norm = get_norm();
			if (norm > T(0)) {
				T inverse_norm = T(1) / norm;
				return inverse_norm * (*this);
			}
			throw;
		}
		void normalize() {
			T norm = get_norm();
			if (norm > T(0)) {
				T inverse_norm{ T(1) / norm };
				for (std::size_t i = 0u; i < Dim; ++i) {
					m_v[i] *= inverse_norm;
				}
			}
			else {
				throw;
			}
		};
	public:
		// getters
		template <std::size_t axes>
		inline T get() {
			static_assert(axes < Dim);
			return m_v[axes];
		}
	public:
		/* Special cases */
		void zero() {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = T();
			}
			m_type = TYPE::ZERO;
		}
		bool is_zero() {
			for (size_t i = 0u; i < Dim; ++i) {
				if (m_v[i] > T() || m_v[i] < T()) {
					return false;
				}
			}
			m_type = TYPE::ZERO;
			return true;
		}
		void one() {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = T(1);
			}
			m_type = TYPE::ONE;
		}
		bool is_one() {
			auto acc = T(1);
			for (size_t i = 0u; i < Dim; ++i) {
				if ((acc *= m_v[i]) != T(1)) {
					return false;
				}
			}
			m_type = TYPE::ONE;
			return true;
		}
	public:
		/* Operator overloading */
		// operator[]
		inline T& operator[](const std::size_t a) {
			if (a < Dim) {
				return m_v[a];
			}
			else {
				throw(std::numeric_limits<T>::infinity());
			}
		}
		inline const T& operator[](const std::size_t a) const {
			if (a < Dim) {
				return m_v[a];
			}
			else {
				throw(std::numeric_limits<T>::infinity());
			}
		}
		// sum between vectors
		inline vector<T, Dim>& operator+=(const vector<T, Dim>& other) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] += other.m_v[i];
			}
			return *this;
		}
		inline friend vector<T, Dim> operator+(vector<T, Dim> lhs, const vector<T, Dim>& rhs) {
			lhs += rhs;
			return lhs;
		}
		inline vector<T, Dim>& operator-=(const vector<T, Dim>& other) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] -= other.m_v[i];
			}
			return *this;
		}
		inline friend vector<T, Dim> operator-(vector<T, Dim> lhs, const vector<T, Dim>& rhs) {
			lhs -= rhs;
			return lhs;
		}
		// multiply for a T lhs
		/* for k * vec */
		inline vector<T, Dim> operator*(const T k) {
			vector<T, Dim> ret(T(1));
			for (size_t i = 0u; i < Dim; ++i) {
				ret.m_v[i] = m_v[i] * k;
			}
			return ret;
		}
		/* for vec * k */
		inline friend vector<T, Dim> operator*(const T k, vector<T, Dim> vec) {
			return  vec.operator*(k);
		};

		static T dot(vector<T, Dim> lhs, vector<T, Dim> rhs) {
			T value{ T(0) };
			for (std::size_t i = 0u; i < Dim; ++i) {
				value += lhs.m_v[i] * rhs.m_v[i];
			}
			return value;
		}

		static vector<T, Dim> cross() {
			/*TODO*/
			throw;
		}

		T get_angle(const vector<T, Dim>& other) {
			if (TYPE::ONE == m_type) {
				return arccos(*this->dot(other) / other.get_norm());
			}
			else if (TYPE::ONE == other.m_type) {
				return arccos(*this->dot(other) / get_norm());
			}
			else if (TYPE::ONE == m_type && TYPE::ONE == other.m_type) {
				return arccos(*this->dot(other));
			}
			else {
				return arccos(*this->dot(other) / (get_norm() * other.get_norm()));
			}
		}
	private:
		enum class TYPE {
			NONE,
			ZERO,
			ONE
		};
	private:
		T m_v[Dim];
		TYPE m_type{ TYPE::NONE };
	};

	/* Matrix class */
    template<typename T, size_t Row, size_t Col>
	class matrix {
	public:
		enum class TYPE {
			ZERO,
			ONCE,
			IDENTICAL
		};
	public:
		// ctors and dtors
		matrix() = default;
		~matrix() = default;
		matrix(const TYPE t) {
			constexpr std::size_t min_size = std::min(Row, Col);
			switch (t)
			{
			case(TYPE::ONCE):
				for (std::size_t i = 0u; i < Row; ++i) {
					for (std::size_t j = 0u; j < Col; ++j) {
						m_d[i][j] = T(1);
					}
				}
				break;
			case(TYPE::IDENTICAL):
				for (std::size_t k = 0u; k < min_size; ++k) {
					m_d[k][k] = T(1);
				}
				break;
			case(TYPE::ZERO):
			default:
				for (std::size_t i = 0u; i < Row; ++i) {
					for (std::size_t j = 0u; j < Col; ++j) {
						m_d[i][j] = T(0);
					}
				}
				break;
			}
		}
	public:
		template <std::size_t C>
		vector<T, Row> get_col() {
			vector<T, Row> ret;
			for (std::size_t i = 0u; i < Row; ++i) {
				ret[i] = m_d[i][C];
			}
			return ret;
		};

		template <std::size_t R>
		vector<T, Col> get_row() {
			return m_d[R];
		};
	public:
		// operators
		/* Old syle operator m(i,j) */
		inline T& operator()(const T r, const T c) {
			static_assert(r < Row&& c < Col);
			return m_d[r][c];
		}
		inline const T& operator()(const T r, const T c) const {
			static_assert(r < Row&& c < Col);
			return m_d[r][c];
		}
#if __cplusplus >= 202302L
		/* c++23 style operator m[i,j] */
		inline T& operator[](const std::size_t i, const std::size_t j) {
			static_assert(i < Row&& j < Col);
			return m_d[i][j];
		}
		inline const T& operator[](const std::size_t i, const std::size_t j) {
			static_assert(i < Row&& j < Col);
			return m_d[i][j];
		}
#endif
		// operator += and +
		inline matrix<T, Row, Col>& operator+=(const matrix<T, Row, Col>& other) {
			for (std::size_t i = 0u; i < Row; ++i) {
				for (std::size_t j = 0u; j < Col; ++j) {
					m_d[i][j] += other.m_d[i][j];
				}
			}
			return *this;
		}
		inline friend matrix<T, Row, Col>& operator+(matrix<T, Row, Col>& lhs, const matrix<T, Row, Col>& rhs) {
			return lhs += rhs;
		}
	private:
		T m_d[Row][Col];
	};

}
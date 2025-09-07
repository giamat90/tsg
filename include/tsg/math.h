#pragma onceT

#include <cstdint>
#include <cassert>
#include <concepts>
#include <type_traits>
#include <expected>
#include "types.h"

#include "io.h"

namespace tsg{
	template<typename T> 
	concept Numeric = std::is_arithmetic_v<T>;

	template<std::size_t D1, std::size_t D2>
	concept DimensionLessThan = D1 < D2;

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
  
    template<typename Numeric>
    inline constexpr Numeric pow(const Numeric base, const std::size_t exp){
        return exp > 0 ? base * pow(base, exp-1) : 1;
    }

    template <typename Numeric, Numeric M>
    class module {
    public:
        module(const Numeric value) {
            if (value > M) {
                m_value += Numeric(0);
            }
            if (value < 0) {
                m_value -= Numeric(0);
            }
        }
        inline module<Numeric,M>& operator+=(const module<Numeric, M>& other) {
            m_value += other.m_value;
            if (m_value > M) {
                m_value -= M;
            }
        }
        inline friend module<Numeric, M> operator+(module<Numeric, M> lhs, const module<Numeric, M>& rhs) {
            lhs += rhs;
            return lhs;
        }
        inline module<Numeric, M>& operator-=(const module<Numeric, M>& other) {
            m_value -= other.m_value;
            if (m_value < Numeric(0)) {
                m_value = M - m_value;
            }
        }
        inline friend module<Numeric, M> operator-(module<Numeric, M> lhs, const module<Numeric, M>& rhs) {
            lhs -= rhs;
            return lhs;
        }
    protected:
		Numeric m_value;
    };

    template <typename Numeric>
    class degree : public module<Numeric, Numeric(360)>{};

    /* Vector class */

	template<typename Numeric, std::size_t Dim>
	class vector : public tsg::stringable {
	public:
		vector() {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = Numeric();
			}
		}
		vector(const Numeric k) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = k;
			}
		}
		vector(const std::initializer_list<Numeric>& list) {
			assert(Dim >= list.size());
			auto it = list.begin();
			for (std::size_t i{}; i < list.size(), it != list.end(); ++i, ++it) {
				m_v[i] = *it;
			}
			for (std::size_t i{}; i < Dim - list.size(); ++i) {
				m_v[i + list.size()] = Numeric();
			}
		}
		vector(const Numeric array[Dim]) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				m_v[i] = array[i];
			}
		}
		/*
		* It is possible create a vector from another one of minor size
		*/
		template <size_t S> requires DimensionLessThan<S, Dim>
		explicit vector(vector<Numeric, S>& other) {
			static_assert(S < Dim);
			for (size_t i{}; i < S; ++i) {
				m_v[i] = other[i];
			}
			for (size_t j = S; j < Dim; ++j) {
				m_v[j] = Numeric{};
			}
		}

		vector(const vector<Numeric, Dim>& other) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				m_v[i] = other.m_v[i];
			}
		}
	public:
		/* Norm */
		Numeric get_norm() const {
			Numeric value{};
			for (std::size_t i = 0u; i < Dim; ++i) {
				value += m_v[i] * m_v[i];
			}
			if constexpr (std::is_same_v<Numeric, float>) {
				return std::sqrtf(value);
			}
			else if constexpr (std::is_same_v<Numeric, double>) {
				return std::sqrt(value);
			}
			else if constexpr (std::is_same_v<Numeric, long double>) {
				return std::sqrtl(value);
			}
			else {
				// Generic sqrt for other types: make compiler choose the right one
				return std::sqrt(value);
			};
		}
		vector<Numeric, Dim> get_normalized() {
			Numeric norm = get_norm();
			if (norm > Numeric(0)) {
				Numeric inverse_norm = Numeric(1) / norm;
				return inverse_norm * (*this);
			}
			throw;
		}
		void normalize() {
			Numeric norm = get_norm();
			if (norm > Numeric(0)) {
				Numeric inverse_norm{ Numeric(1) / norm };
				for (std::size_t i = 0u; i < Dim; ++i) {
					m_v[i] *= inverse_norm;
				}
			}
			else {
				throw;
			}
		};
		/* Reciprocal */
		std::expected<vector<Numeric, Dim>, bool> reciprocal() const {
			vector<Numeric, Dim> reciproc(Numeric(1));
			for (std::size_t i = 0u; i < Dim; ++i) {
				if (0 == m_v[i]) {
					return std::unexpected(false);
				}
				else {
					reciproc.m_v[i] = Numeric(1) / m_v[i];
				}
			}
			return reciproc;
		}
		/* Scaling */
		void scale(const Numeric k) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				m_v[i] *= k;
			}
		}
		void scale(const vector<Numeric, Dim> vk) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				m_v[i] *= vk[i];
			}
		}
		template <typename T> // SFINAE
		vector<Numeric, Dim> get_scalarized(const T k) {
			vector<Numeric, Dim> ret(*this);
			ret.scale(k);
			return ret;
		}
		/* translation */
		void translate(const vector<Numeric, Dim>& t) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				m_v[i] += t.m_v[i];
			}
		}
	public:
		// getters
		template <std::size_t axes>
		inline Numeric get() {
			//static_assert(axes < Dim);
			return m_v[axes];
		}
	public:
		/* Special cases */
		void zero() {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = Numeric();
			}
			m_type = TYPE::ZERO;
		}
		bool is_zero() {
			for (size_t i = 0u; i < Dim; ++i) {
				if (m_v[i] > Numeric() || m_v[i] < Numeric()) {
					return false;
				}
			}
			m_type = TYPE::ZERO;
			return true;
		}
		void one() {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] = Numeric(1);
			}
			m_type = TYPE::ONE;
		}
		bool is_one() {
			auto acc = Numeric(1);
			for (size_t i = 0u; i < Dim; ++i) {
				if ((acc *= m_v[i]) != Numeric(1)) {
					return false;
				}
			}
			m_type = TYPE::ONE;
			return true;
		}
		bool is_nan() {
			bool is_nan{ false };
			try {
				for (size_t i{}; i < Dim; ++i) {
					is_nan |= std::isnan(m_v[i]);
				}
				return is_nan;
			}
			catch (...) {
				assert(0);
			}
		}
	public:
		/* Operator overloading */
		// operator= with another vector
		inline vector<Numeric, Dim> operator=(const vector<Numeric, Dim>& other) {
			for (std::size_t i = 0u; i < Dim; ++i) {
				this->m_v[i] = other.m_v[i];
			}
			return *this;
		}
		// operator= with an initlist
		inline vector<Numeric, Dim>& operator=(const std::initializer_list<Numeric> list) {
			assert(Dim == list.size());
			auto it = list.begin();
			for (std::size_t i{}; i < Dim, it != list.end(); ++i, ++it) {
				m_v[i] = *it;
			}
			return *this;
		}
		// operator[]
		inline Numeric& operator[](const std::size_t a) {
			if (a < Dim) {
				return m_v[a];
			}
			else {
				assert(0);
			}
		}
		inline const Numeric& operator[](const std::size_t a) const {
			if (a < Dim) {
				return m_v[a];
			}
			else {
				throw(std::numeric_limits<Numeric>::infinity());
			}
		}
		// sum between vectors
		inline vector<Numeric, Dim>& operator+=(const vector<Numeric, Dim>& other) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] += other.m_v[i];
			}
			return *this;
		}
		inline friend vector<Numeric, Dim> operator+(vector<Numeric, Dim> lhs, const vector<Numeric, Dim>& rhs) {
			lhs += rhs;
			return lhs;
		}
		inline vector<Numeric, Dim>& operator-=(const vector<Numeric, Dim>& other) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] -= other.m_v[i];
			}
			return *this;
		}
		inline friend vector<Numeric, Dim> operator-(vector<Numeric, Dim> lhs, const vector<Numeric, Dim>& rhs) {
			lhs -= rhs;
			return lhs;
		}
		// multiply for a Numeric lhs
		inline vector<Numeric, Dim>& operator*=(const Numeric k) {
			for (size_t i = 0u; i < Dim; ++i) {
				m_v[i] *= k;
			}
			return *this;
		}
		/* for vec*k */
		inline friend vector<Numeric, Dim> operator*(vector<Numeric, Dim> vec, const Numeric k) {
			return  vec *= k;
		};
		/* for k*vec */
		inline friend vector<Numeric, Dim> operator*(const Numeric k, vector<Numeric, Dim> vec) {
			return  vec *= k;
		};
		/*
		* equality operator
		*/
		inline bool operator==(const vector<Numeric, Dim>& other) const {
			for (std::size_t i = 0u; i < Dim; ++i) {
				if (m_v[i] != other.m_v[i]) {
					return false;
				}
			}
			return true;
		}
	public:
		static Numeric dot(vector<Numeric, Dim> lhs, vector<Numeric, Dim> rhs) {
			Numeric value{ Numeric(0) };
			for (std::size_t i = 0u; i < Dim; ++i) {
				value += lhs.m_v[i] * rhs.m_v[i];
			}
			return value;
		}
		/* 
		* Valid only for 3-dimensional vectors
		*/
		static vector<Numeric, Dim> cross(const vector<Numeric, Dim>& lhs, const vector<Numeric, Dim>& rhs) {
			static_assert(Dim == 3);
			return {
				lhs.m_v[1] * rhs.m_v[2] - lhs.m_v[2] * rhs.m_v[1],
				lhs.m_v[2] * rhs.m_v[0] - lhs.m_v[0] * rhs.m_v[2],
				lhs.m_v[0] * rhs.m_v[1] - lhs.m_v[1] * rhs.m_v[0],
			};
		}

		void wedge(void) const {
			/* TODO */
			assert(false);
		}

		Numeric get_angle(const vector<Numeric, Dim>& other) {
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
public:
	tsg::string to_string() override {
		tsg::string ret{ "("};
		for (std::size_t i{}; i < Dim; ++i) {
			ret += i;
			ret += ",";
		}
		ret += ")";
		return ret;
	}
private:
		enum class TYPE {
			NONE,
			ZERO,
			ONE
		};
	private:
		Numeric m_v[Dim];
		TYPE m_type{ TYPE::NONE };
	};

	/* Matrix class */
    template<typename Numeric, size_t Row, size_t Col>
	class matrix {
		using row_t = std::size_t;
		using col_t = std::size_t;
	public:
		enum class TYPE {
			ZERO,
			ONE,
			IDENTITY,
			DIAGONAL,
			UNKNOWN
		};
	public:
		// ctors and dtors
		matrix() = default;
		~matrix() = default;
		matrix(const TYPE t, const Numeric value = Numeric(1)) {
			constexpr std::size_t min_size = std::min(Row, Col);
			switch (t)
			{
			case(TYPE::ONE):
				for (std::size_t i = 0u; i < Row; ++i) {
					for (std::size_t j = 0u; j < Col; ++j) {
						m_d[i][j] = Numeric(1);
					}
				}
				m_type = TYPE::ONE;
				break;
			case(TYPE::IDENTITY):
				for (std::size_t i = 0u; i < Row; ++i) {
					for (std::size_t j = 0u; j < Col; ++j) {
						m_d[i][j] = (i == j) ? Numeric(1) : Numeric(0);
					}
				}
				m_type = TYPE::IDENTITY;
				break;
			case(TYPE::DIAGONAL):
				for (std::size_t i = 0u; i < Row; ++i) {
					for (std::size_t j = 0u; j < Col; ++j) {
						m_d[i][j] = (i == j) ? value : Numeric(0);
					}
				}
				m_type = TYPE::DIAGONAL;
				break;
			case(TYPE::ZERO):
			default:
				for (std::size_t i = 0u; i < Row; ++i) {
					for (std::size_t j = 0u; j < Col; ++j) {
						m_d[i][j] = Numeric(0);
					}
				}
				m_type = TYPE::ZERO;
				break;
			}
		};
	public:
		bool is_one() const { return TYPE::ONE == m_type; };
		bool is_zero() const { return TYPE::ZERO == m_type; };
		bool is_diagonal() const { return TYPE::DIAGONAL == m_type; };
		bool is_identity() const { return TYPE::IDENTITY == m_type; };
	public:
		template <std::size_t J>
		vector<Numeric, Row> get_col() {
			vector<Numeric, Row> ret;
			for (std::size_t i = 0u; i < Row; ++i) {
				ret[i] = m_d[i][J];
			}
			return ret;
		};

		vector<Numeric, Row> get_col(const std::size_t j) {
			vector<Numeric, Row> ret;
			for (std::size_t i = 0u; i < Row; ++i) {
				ret[i] = m_d[i][j];
			}
			return ret;
		};

		template <std::size_t I>
		const vector<Numeric, Col>& get_row() const {
			return m_d[I];
		};

		vector<Numeric, Col> get_row(const std::size_t i) const {
			return m_d[i];
		};
	public:
		// operators
		/* Old syle operator m(i,j) */
		inline Numeric& operator()(const std::size_t r, const std::size_t c) {
			assert(r < Row && c < Col);
			return m_d[r][c];
		}
		inline const Numeric& operator()(const Numeric r, const Numeric c) const {
			static_assert(r < Row && c < Col);
			return m_d[r][c];
		}
		// operator += and +
		inline matrix<Numeric, Row, Col>& operator+=(const matrix<Numeric, Row, Col>& other) {
			for (std::size_t i = 0u; i < Row; ++i) {
				for (std::size_t j = 0u; j < Col; ++j) {
					m_d[i][j] += other.m_d[i][j];
				}
			}
			return *this;
		}
		inline friend matrix<Numeric, Row, Col>& operator+(matrix<Numeric, Row, Col>& lhs, const matrix<Numeric, Row, Col>& rhs) {
			return lhs += rhs;
		}
		// operator *= and * with other matrix
		template<std::size_t N>
		inline matrix<Numeric, Row, N>& operator*=(const matrix<Numeric, Col, N>& other) {
			matrix<Numeric, Row, N> res(TYPE::ZERO);
			for (std::size_t i = 0u; i < Row; ++i) {
				for (std::size_t j = 0u; j < N; ++j) {
					for (std::size_t k = 0u; k < Col; ++k) {
						res[i][j] += m_d[i][k] * other.m_d[k][j];
					}
				}
			}
			return res;
		}
		// operator * and *= with a scalar
		inline matrix<Numeric, Row, Col>& operator*=(const Numeric value) {
			for (std::size_t i = 0u; i < Row; ++i) {
				for (std::size_t j = 0u; j < Col; ++j) {
					m_d[i][j] *= value;
				}
			}
			return *this;
		}
		inline friend matrix<Numeric, Row, Col>& operator*(matrix<Numeric, Row, Col>& matrix, const Numeric value) {
			return matrix *= value;
		}
	private:
		Numeric m_d[Row][Col];
		TYPE m_type{ TYPE::UNKNOWN };
	};

}
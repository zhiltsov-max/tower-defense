#ifndef GAME_ENGINE_POINT_H
#define GAME_ENGINE_POINT_H

#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <initializer_list>

#include "GameEngine/Utility/defs.h"
#include "GameEngine/Utility/exception.h"


namespace GE {

namespace Graphics {

bool isPointInRect(int pointX, int pointY, int rectX1, int rectY1, int rectX2, int rectY2);


template< typename T, size_t dims >
class Point
{
private:
    std::array<T, dims> data;

public:
    Point() { data.fill(T()); }
    Point(const std::initializer_list<T>& il) :
        data()
    { std::copy(il.begin(), il.end(), data.begin()); }

    const T& operator[](size_t index) const {
#if defined(_DEBUG)
        ASSERT(index < dims, "Point data index is out of bounds.")
#endif
        return data[index];
    }
    T& operator[](size_t index) {
#if defined(_DEBUG)
        ASSERT(index < dims, "Point data index is out of bounds.")
#endif
        return data[index];
    }

    operator string() const {
        string res("(");
        res.reserve(dims * 3);
        for(size_t i = 0; i < dims; ++i) {
            res += std::to_string(data[i]);
            if (i != dims - 1) { res += ", "; }
        }
        res += ")";
        return res;
    }

    operator wstring() const {
        wstring res(L"(");
        res.reserve(dims * 3);
        for(size_t i = 0; i < dims; ++i) {
            res += std::to_wstring(data[i]);
            if (i != dims - 1) { res += L", "; }
        }
        res += L")";
        return res;
    }
};


template< class T, size_t dims >
std::ostream& operator << (std::ostream& os, const Point<T, dims>& point) {
    return os << static_cast<string>(point);
}

template< class T, size_t dims >
std::wostream& operator << (std::wostream& os, const Point<T, dims>& point) {
    return os << static_cast<wstring>(point);
}


template< class T, size_t dims >
Point<T, dims> abs(const Point<T, dims>& point) {
    Point<T, dims> res;
    for(size_t i = 0; i < dims; ++i) {
        res[i] = std::abs(point[i]);
    }
    return res;
}


#define DEF_BINARY_OPERATOR(OP) \
    template< class T, size_t dims > \
    Point<T, dims> operator OP (const Point<T, dims>& p1, const Point<T, dims>& p2) { \
        Point<T, dims> res; \
        for(size_t i = 0; i < dims; ++i) { \
            res[i] = p1[i] OP p2[i]; \
        } \
        return res;     \
    }

#define DEF_BINARY_OPERATOR_WITH_NUMBER(OP) \
    template< class T, size_t dims, class T2 > \
    Point<T, dims> operator OP (const Point<T, dims>& p, const T2& value) { \
        Point<T, dims> res; \
        for(size_t i = 0; i < dims; ++i) { \
            res[i] = p[i] OP value; \
        } \
        return res; \
    } \
    template< class T, size_t dims, class T2 > \
    Point<T, dims> operator OP (const T2& value, const Point<T, dims>& p) { \
        return operator OP (p, value); \
    }

DEF_BINARY_OPERATOR(+)
DEF_BINARY_OPERATOR(-)
DEF_BINARY_OPERATOR(*)
DEF_BINARY_OPERATOR(/)

DEF_BINARY_OPERATOR_WITH_NUMBER(+)
DEF_BINARY_OPERATOR_WITH_NUMBER(-)
DEF_BINARY_OPERATOR_WITH_NUMBER(*)
DEF_BINARY_OPERATOR_WITH_NUMBER(/)

#undef DEF_BINARY_OPERATOR
#undef DEF_BINARY_OPERATOR_WITH_NUMBER

#define DEF_UNARY_OPERATOR(OP) \
    template< class T, size_t dims > \
    Point<T, dims>& operator OP (Point<T, dims>& p1, const Point<T, dims>& p2) { \
        for(size_t i = 0; i < dims; ++i) { \
            p1[i] OP p2[i]; \
        } \
        return p1;     \
    }

#define DEF_UNARY_OPERATOR_WITH_NUMBER(OP) \
    template< class T, size_t dims, class T2 > \
    Point<T, dims>& operator OP (Point<T, dims>& p, const T2& value) { \
        for(size_t i = 0; i < dims; ++i) { \
            p[i] OP value; \
        } \
        return p; \
    } \
    template< class T, size_t dims, class T2 > \
    Point<T, dims>& operator OP (const T2& value, const Point<T, dims>& p) { \
        return operator OP (p, value); \
    }

DEF_UNARY_OPERATOR(+=)
DEF_UNARY_OPERATOR(-=)
DEF_UNARY_OPERATOR(*=)
DEF_UNARY_OPERATOR(/=)

DEF_UNARY_OPERATOR_WITH_NUMBER(+=)
DEF_UNARY_OPERATOR_WITH_NUMBER(-=)
DEF_UNARY_OPERATOR_WITH_NUMBER(*=)
DEF_UNARY_OPERATOR_WITH_NUMBER(/=)


#undef DEF_UNARY_OPERATOR
#undef DEF_UNARY_OPERATOR_WITH_NUMBER

#define DEF_BOOL_OPERATOR(OP) \
    template< class T, size_t dims > \
    bool operator OP (const Point<T, dims>& p1, const Point<T, dims>& p2) { \
        size_t i = 0; \
        while ((i < dims) && (p1[i] OP p2[i])) { \
            ++i; \
        } \
        return (i == dims); \
    }

DEF_BOOL_OPERATOR(==)

template< class T, size_t dims >
bool operator != (const Point<T, dims>& p1, const Point<T, dims>& p2) {
    return !(p1 == p2);
}


DEF_BOOL_OPERATOR(<=)
DEF_BOOL_OPERATOR(>=)
DEF_BOOL_OPERATOR(<)
DEF_BOOL_OPERATOR(>)

#undef DEF_BOOL_OPERATOR


#if defined(SFML)
    #include "SFML/System.hpp"
#endif


template< typename T >
class Point<T, 2> 
{
public:
    union {
        struct {
            T x;
            T y;
        };
        std::array<T, 2> data;
    };


    Point() = default;
    Point(const T& x, const T& y) : x(x), y(y) {}

#if defined(SFML)
    Point(const sf::Vector2<T>& vec) : x(vec.x), y(vec.y) {}
    operator sf::Vector2<T> () const { return sf::Vector2<T>(x, y); }
#endif

    const T& operator[](size_t index) const {
#if defined(_DEBUG)
        ASSERT(index < 2, "Point data index is out of bounds.")
#endif
        return data[index];
	}
    T& operator[](size_t index) {
#if defined(_DEBUG)
        ASSERT(index < 2, "Point data index is out of bounds.")
#endif
		return data[index];
	}

    operator string() const {
        return "(" + std::to_string(data[0]) + ", " + std::to_string(data[1]) + ")";
	}

    operator wstring() const {
        return L"(" + std::to_wstring(data[0]) + ", " + std::to_wstring(data[1]) + L")";
    }

	bool isInRect(const Point& p1, const Point& p2) const {
        return isPointInRect(x, y, p1.x, p1.y, p2.x, p2.y);
    }
};


using Point2c = Point<char, 2>;
using Point2uc = Point<uchar, 2>;
using Point2s = Point<short, 2>;
using Point2us = Point<ushort, 2>;
using Point2i = Point<int, 2>;
using Point2ui = Point<uint, 2>;
using Point2f = Point<float, 2>;
using Point2d = Point<double, 2>;

template< class T, int Dims >
using Vec = Point<T, Dims>;
using Vec2c = Vec<char, 2>;
using Vec2uc = Vec<uchar, 2>;
using Vec2s = Vec<short, 2>;
using Vec2us = Vec<ushort, 2>;
using Vec2i = Vec<int, 2>;
using Vec2ui = Vec<uint, 2>;
using Vec2f = Vec<float, 2>;
using Vec2d = Vec<double, 2>;

enum class NormType {
	NORM_USUAL,
	NORM_SQUARED
};


template< typename T >
T sqr(const T& value) { return value * value; }


template< class T, size_t dims >
double norm(const Point<T, dims>& p1, const Point<T, dims>& p2, NormType normType = NormType::NORM_USUAL) {
	double res = 0.0;
	for(size_t i = 0; i != dims; ++i) {
        res += sqr(p1[i] - p2[i]);
	}
	switch (normType) {
    case NormType::NORM_SQUARED:
        break;

    case NormType::NORM_USUAL:
        res = std::pow(res, 0.5);
        break;

    default: {/*none*/}
	};
	return res;
}
template< class T, size_t dims >
double norm(const Point<T, dims>& p, NormType normType = NormType::NORM_USUAL) {
	double res = 0.0;
	for(size_t i = 0; i != dims; ++i) {
        res += sqr(p[i]);
	}
	switch (normType) {
    case NormType::NORM_SQUARED:
        break;

    case NormType::NORM_USUAL:
        res = std::pow(res, 0.5);
        break;

    default: {/*none*/}
	};
	return res;
}

} // namespace Graphics

} // namespace GE

#endif // GAME_ENGINE_POINT_H

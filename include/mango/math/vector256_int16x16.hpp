/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "vector.hpp"

namespace mango
{

    template <>
    struct Vector<int16, 16>
    {
        using VectorType = simd::int16x16;
        using ScalarType = int16;
        enum { VectorSize = 16 };

        union
        {
            VectorType m;
            DeAggregate<ScalarType> component[VectorSize];
        };

        ScalarType& operator [] (size_t index)
        {
            assert(index < VectorSize);
            return component[index].data;
        }

        ScalarType operator [] (size_t index) const
        {
            assert(index < VectorSize);
            return component[index].data;
        }

        explicit Vector() {}
        ~Vector() {}

        Vector(int16 s)
            : m(simd::int16x16_set1(s))
        {
        }

        Vector(simd::int16x16 v)
            : m(v)
        {
        }

        Vector& operator = (simd::int16x16 v)
        {
            m = v;
            return *this;
        }

        Vector& operator = (int16 s)
        {
            m = simd::int16x16_set1(s);
            return *this;
        }

        operator simd::int16x16 () const
        {
            return m;
        }

#ifdef int256_is_hardware_vector
        operator simd::int16x16::vector () const
        {
            return m.data;
        }
#endif
    };

    static inline const Vector<int16, 16> operator + (Vector<int16, 16> v)
    {
        return v;
    }

    static inline Vector<int16, 16> operator - (Vector<int16, 16> v)
    {
        return simd::sub(simd::int16x16_zero(), v);
    }

    static inline Vector<int16, 16>& operator += (Vector<int16, 16>& a, Vector<int16, 16> b)
    {
        a = simd::add(a, b);
        return a;
    }

    static inline Vector<int16, 16>& operator -= (Vector<int16, 16>& a, Vector<int16, 16> b)
    {
        a = simd::sub(a, b);
        return a;
    }

    static inline Vector<int16, 16> operator + (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::add(a, b);
    }

    static inline Vector<int16, 16> operator - (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::sub(a, b);
    }

    static inline Vector<int16, 16> nand(Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::bitwise_nand(a, b);
    }

    static inline Vector<int16, 16> operator & (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::bitwise_and(a, b);
    }

    static inline Vector<int16, 16> operator | (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::bitwise_or(a, b);
    }

    static inline Vector<int16, 16> operator ^ (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::bitwise_xor(a, b);
    }

    static inline Vector<int16, 16> adds(Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::adds(a, b);
    }

    static inline Vector<int16, 16> subs(Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::subs(a, b);
    }

    static inline Vector<int16, 16> min(Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::min(a, b);
    }

    static inline Vector<int16, 16> max(Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::max(a, b);
    }

    static inline mask16x16 operator > (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::compare_gt(a, b);
    }

    static inline mask16x16 operator < (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::compare_gt(b, a);
    }

    static inline mask16x16 operator == (Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::compare_eq(a, b);
    }

    static inline Vector<int16, 16> select(mask16x16 mask, Vector<int16, 16> a, Vector<int16, 16> b)
    {
        return simd::select(mask, a, b);
    }

    static inline Vector<int16, 16> operator << (Vector<int16, 16> a, int b)
    {
        return simd::sll(a, b);
    }

    static inline Vector<int16, 16> operator >> (Vector<int16, 16> a, int b)
    {
        return simd::sra(a, b);
    }

} // namespace mango

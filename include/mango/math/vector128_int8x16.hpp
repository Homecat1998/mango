/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "vector.hpp"

namespace mango
{

    template <>
    struct Vector<int8, 16>
    {
        using VectorType = simd::int8x16;
        using ScalarType = int8;
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

        Vector(int8 s)
            : m(simd::int8x16_set1(s))
        {
        }

        Vector(int8 s0, int8 s1, int8 s2, int8 s3, int8 s4, int8 s5, int8 s6, int8 s7, int8 s8, int8 s9, int8 s10, int8 s11, int8 s12, int8 s13, int8 s14, int8 s15)
            : m(simd::int8x16_set16(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15))
        {
        }

        Vector(simd::int8x16 v)
            : m(v)
        {
        }

        Vector& operator = (simd::int8x16 v)
        {
            m = v;
            return *this;
        }

        Vector& operator = (int8 s)
        {
            m = simd::int8x16_set1(s);
            return *this;
        }

        operator simd::int8x16 () const
        {
            return m;
        }

#ifdef int128_is_hardware_vector
        operator simd::int8x16::vector () const
        {
            return m.data;
        }
#endif
    };

    template <>
    inline Vector<int8, 16> load_low<int8, 16>(const int8 *source)
    {
        return simd::int8x16_load_low(source);
    }

    static inline void store_low(int8 *dest, Vector<int8, 16> v)
    {
        simd::int8x16_store_low(dest, v);
    }

    static inline const Vector<int8, 16> operator + (Vector<int8, 16> v)
    {
        return v;
    }

    static inline Vector<int8, 16> operator - (Vector<int8, 16> v)
    {
        return simd::sub(simd::int8x16_zero(), v);
    }

    static inline Vector<int8, 16>& operator += (Vector<int8, 16>& a, Vector<int8, 16> b)
    {
        a = simd::add(a, b);
        return a;
    }

    static inline Vector<int8, 16>& operator -= (Vector<int8, 16>& a, Vector<int8, 16> b)
    {
        a = simd::sub(a, b);
        return a;
    }

    static inline Vector<int8, 16> operator + (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::add(a, b);
    }

    static inline Vector<int8, 16> operator - (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::sub(a, b);
    }

    static inline Vector<int8, 16> nand(Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::bitwise_nand(a, b);
    }

    static inline Vector<int8, 16> operator & (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::bitwise_and(a, b);
    }

    static inline Vector<int8, 16> operator | (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::bitwise_or(a, b);
    }

    static inline Vector<int8, 16> operator ^ (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::bitwise_xor(a, b);
    }

    static inline Vector<int8, 16> operator ~ (Vector<int8, 16> a)
    {
        return simd::bitwise_not(a);
    }

    static inline Vector<int8, 16> abs(Vector<int8, 16> a)
    {
        return simd::abs(a);
    }

    static inline Vector<int8, 16> adds(Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::adds(a, b);
    }

    static inline Vector<int8, 16> subs(Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::subs(a, b);
    }

    static inline Vector<int8, 16> min(Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::min(a, b);
    }

    static inline Vector<int8, 16> max(Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::max(a, b);
    }

    static inline Vector<int8, 16> clamp(Vector<int8, 16> a, Vector<int8, 16> amin, Vector<int8, 16> amax)
    {
        return simd::clamp(a, amin, amax);
    }

    static inline mask8x16 operator > (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::compare_gt(a, b);
    }

    static inline mask8x16 operator >= (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::compare_ge(a, b);
    }

    static inline mask8x16 operator < (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::compare_lt(a, b);
    }

    static inline mask8x16 operator <= (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::compare_le(a, b);
    }

    static inline mask8x16 operator == (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::compare_eq(a, b);
    }

    static inline mask8x16 operator != (Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::compare_neq(a, b);
    }

    static inline Vector<int8, 16> select(mask8x16 mask, Vector<int8, 16> a, Vector<int8, 16> b)
    {
        return simd::select(mask, a, b);
    }

} // namespace mango

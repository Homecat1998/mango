/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "vector.hpp"

namespace mango
{

    template <>
    struct Vector<int32, 8>
    {
        using VectorType = simd::int32x8;
        using ScalarType = int32;
        enum { VectorSize = 8 };

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

        Vector(int32 s)
            : m(simd::int32x8_set1(s))
        {
        }

        Vector(int32 s0, int32 s1, int32 s2, int32 s3, int32 s4, int32 s5, int32 s6, int32 s7)
            : m(simd::int32x8_set8(s0, s1, s2, s3, s4, s5, s6, s7))
        {
        }

        Vector(simd::int32x8 v)
            : m(v)
        {
        }

        Vector& operator = (simd::int32x8 v)
        {
            m = v;
            return *this;
        }

        Vector& operator = (int32 s)
        {
            m = simd::int32x8_set1(s);
            return *this;
        }

        operator simd::int32x8 () const
        {
            return m;
        }

#ifdef int256_is_hardware_vector
        operator simd::int32x8::vector () const
        {
            return m.data;
        }
#endif
    };

    static inline const Vector<int32, 8> operator + (Vector<int32, 8> v)
    {
        return v;
    }

    static inline Vector<int32, 8> operator - (Vector<int32, 8> v)
    {
        return simd::sub(simd::int32x8_zero(), v);
    }

    static inline Vector<int32, 8>& operator += (Vector<int32, 8>& a, Vector<int32, 8> b)
    {
        a = simd::add(a, b);
        return a;
    }

    static inline Vector<int32, 8>& operator -= (Vector<int32, 8>& a, Vector<int32, 8> b)
    {
        a = simd::sub(a, b);
        return a;
    }

    static inline Vector<int32, 8> operator + (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::add(a, b);
    }

    static inline Vector<int32, 8> operator - (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::sub(a, b);
    }

    static inline Vector<int32, 8> nand(Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::bitwise_nand(a, b);
    }

    static inline Vector<int32, 8> operator & (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::bitwise_and(a, b);
    }

    static inline Vector<int32, 8> operator | (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::bitwise_or(a, b);
    }

    static inline Vector<int32, 8> operator ^ (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::bitwise_xor(a, b);
    }

    static inline Vector<int32, 8> adds(Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::adds(a, b);
    }

    static inline Vector<int32, 8> subs(Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::subs(a, b);
    }

    static inline Vector<int32, 8> min(Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::min(a, b);
    }

    static inline Vector<int32, 8> max(Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::max(a, b);
    }

    static inline mask32x8 operator > (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::compare_gt(a, b);
    }

    static inline mask32x8 operator < (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::compare_gt(b, a);
    }

    static inline mask32x8 operator == (Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::compare_eq(a, b);
    }

    static inline Vector<int32, 8> select(mask32x8 mask, Vector<int32, 8> a, Vector<int32, 8> b)
    {
        return simd::select(mask, a, b);
    }

    static inline Vector<int32, 8> operator << (Vector<int32, 8> a, int b)
    {
        return simd::sll(a, b);
    }

    static inline Vector<int32, 8> operator >> (Vector<int32, 8> a, int b)
    {
        return simd::sra(a, b);
    }

    static inline Vector<int32, 8> operator << (Vector<int32, 8> a, uint32x8 b)
    {
        return simd::sll(a, b);
    }

    static inline Vector<int32, 8> operator >> (Vector<int32, 8> a, uint32x8 b)
    {
        return simd::sra(a, b);
    }

} // namespace mango

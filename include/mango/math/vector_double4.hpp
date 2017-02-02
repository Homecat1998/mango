/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2016 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "vector.hpp"

namespace mango
{

    // ------------------------------------------------------------------
    // Vector<double, 4>
    // ------------------------------------------------------------------

    template <>
    struct Vector<double, 4> : VectorBase<double, 4>
    {
        template <int Index>
        struct ScalarAccessor
        {
            simd::float64x4 m;

            operator double () const
            {
                return simd::float64x4_get_component<Index>(m);
            }

            ScalarAccessor& operator = (double s)
            {
                m = simd::float64x4_set_component<Index>(m, s);
                return *this;
            }

            ScalarAccessor& operator += (double s)
            {
                *this = double(*this) + s;
                return *this;
            }

            ScalarAccessor& operator -= (double s)
            {
                *this = double(*this) - s;
                return *this;
            }

            ScalarAccessor& operator *= (double s)
            {
                *this = double(*this) * s;
                return *this;
            }

            ScalarAccessor& operator /= (double s)
            {
                *this = double(*this) / s;
                return *this;
            }
        };

        template <int X, int Y>
        struct Permute2
        {
            simd::float64x4 m;

            operator Vector<double, 2> () const
            {
                const double x = simd::float64x4_get_component<X>(m);
                const double y = simd::float64x4_get_component<Y>(m);
                return Vector<double, 2>(x, y);
            }
        };

        template <int X, int Y, int Z>
        struct Permute3
        {
            simd::float64x4 m;

            operator Vector<double, 3> () const
            {
                const double x = simd::float64x4_get_component<X>(m);
                const double y = simd::float64x4_get_component<Y>(m);
                const double z = simd::float64x4_get_component<Z>(m);
                return Vector<double, 3>(x, y, z);
            }
        };

        template <int X, int Y, int Z, int W>
        struct Permute4
        {
            simd::float64x4 m;

            operator simd::float64x4 () const
            {
                return simd::float64x4_shuffle<X, Y, Z, W>(m);
            }
        };

        union
        {
            simd::float64x4 m;

            ScalarAccessor<0> x;
            ScalarAccessor<1> y;
            ScalarAccessor<2> z;
            ScalarAccessor<3> w;

            Permute2<0, 0> xx;
            Permute2<1, 0> yx;
            Permute2<2, 0> zx;
            Permute2<3, 0> wx;
            Permute2<0, 1> xy;
            Permute2<1, 1> yy;
            Permute2<2, 1> zy;
            Permute2<3, 1> wy;
            Permute2<0, 2> xz;
            Permute2<1, 2> yz;
            Permute2<2, 2> zz;
            Permute2<3, 2> wz;
            Permute2<0, 3> xw;
            Permute2<1, 3> yw;
            Permute2<2, 3> zw;
            Permute2<3, 3> ww;

            Permute3<0, 0, 0> xxx;
            Permute3<1, 0, 0> yxx;
            Permute3<2, 0, 0> zxx;
            Permute3<3, 0, 0> wxx;
            Permute3<0, 1, 0> xyx;
            Permute3<1, 1, 0> yyx;
            Permute3<2, 1, 0> zyx;
            Permute3<3, 1, 0> wyx;
            Permute3<0, 2, 0> xzx;
            Permute3<1, 2, 0> yzx;
            Permute3<2, 2, 0> zzx;
            Permute3<3, 2, 0> wzx;
            Permute3<0, 3, 0> xwx;
            Permute3<1, 3, 0> ywx;
            Permute3<2, 3, 0> zwx;
            Permute3<3, 3, 0> wwx;
            Permute3<0, 0, 1> xxy;
            Permute3<1, 0, 1> yxy;
            Permute3<2, 0, 1> zxy;
            Permute3<3, 0, 1> wxy;
            Permute3<0, 1, 1> xyy;
            Permute3<1, 1, 1> yyy;
            Permute3<2, 1, 1> zyy;
            Permute3<3, 1, 1> wyy;
            Permute3<0, 2, 1> xzy;
            Permute3<1, 2, 1> yzy;
            Permute3<2, 2, 1> zzy;
            Permute3<3, 2, 1> wzy;
            Permute3<0, 3, 1> xwy;
            Permute3<1, 3, 1> ywy;
            Permute3<2, 3, 1> zwy;
            Permute3<3, 3, 1> wwy;
            Permute3<0, 0, 2> xxz;
            Permute3<1, 0, 2> yxz;
            Permute3<2, 0, 2> zxz;
            Permute3<3, 0, 2> wxz;
            Permute3<0, 1, 2> xyz;
            Permute3<1, 1, 2> yyz;
            Permute3<2, 1, 2> zyz;
            Permute3<3, 1, 2> wyz;
            Permute3<0, 2, 2> xzz;
            Permute3<1, 2, 2> yzz;
            Permute3<2, 2, 2> zzz;
            Permute3<3, 2, 2> wzz;
            Permute3<0, 3, 2> xwz;
            Permute3<1, 3, 2> ywz;
            Permute3<2, 3, 2> zwz;
            Permute3<3, 3, 2> wwz;
            Permute3<0, 0, 3> xxw;
            Permute3<1, 0, 3> yxw;
            Permute3<2, 0, 3> zxw;
            Permute3<3, 0, 3> wxw;
            Permute3<0, 1, 3> xyw;
            Permute3<1, 1, 3> yyw;
            Permute3<2, 1, 3> zyw;
            Permute3<3, 1, 3> wyw;
            Permute3<0, 2, 3> xzw;
            Permute3<1, 2, 3> yzw;
            Permute3<2, 2, 3> zzw;
            Permute3<3, 2, 3> wzw;
            Permute3<0, 3, 3> xww;
            Permute3<1, 3, 3> yww;
            Permute3<2, 3, 3> zww;
            Permute3<3, 3, 3> www;

            Permute4<0, 0, 0, 0> xxxx;
            Permute4<1, 0, 0, 0> yxxx;
            Permute4<2, 0, 0, 0> zxxx;
            Permute4<3, 0, 0, 0> wxxx;
            Permute4<0, 1, 0, 0> xyxx;
            Permute4<1, 1, 0, 0> yyxx;
            Permute4<2, 1, 0, 0> zyxx;
            Permute4<3, 1, 0, 0> wyxx;
            Permute4<0, 2, 0, 0> xzxx;
            Permute4<1, 2, 0, 0> yzxx;
            Permute4<2, 2, 0, 0> zzxx;
            Permute4<3, 2, 0, 0> wzxx;
            Permute4<0, 3, 0, 0> xwxx;
            Permute4<1, 3, 0, 0> ywxx;
            Permute4<2, 3, 0, 0> zwxx;
            Permute4<3, 3, 0, 0> wwxx;
            Permute4<0, 0, 1, 0> xxyx;
            Permute4<1, 0, 1, 0> yxyx;
            Permute4<2, 0, 1, 0> zxyx;
            Permute4<3, 0, 1, 0> wxyx;
            Permute4<0, 1, 1, 0> xyyx;
            Permute4<1, 1, 1, 0> yyyx;
            Permute4<2, 1, 1, 0> zyyx;
            Permute4<3, 1, 1, 0> wyyx;
            Permute4<0, 2, 1, 0> xzyx;
            Permute4<1, 2, 1, 0> yzyx;
            Permute4<2, 2, 1, 0> zzyx;
            Permute4<3, 2, 1, 0> wzyx;
            Permute4<0, 3, 1, 0> xwyx;
            Permute4<1, 3, 1, 0> ywyx;
            Permute4<2, 3, 1, 0> zwyx;
            Permute4<3, 3, 1, 0> wwyx;
            Permute4<0, 0, 2, 0> xxzx;
            Permute4<1, 0, 2, 0> yxzx;
            Permute4<2, 0, 2, 0> zxzx;
            Permute4<3, 0, 2, 0> wxzx;
            Permute4<0, 1, 2, 0> xyzx;
            Permute4<1, 1, 2, 0> yyzx;
            Permute4<2, 1, 2, 0> zyzx;
            Permute4<3, 1, 2, 0> wyzx;
            Permute4<0, 2, 2, 0> xzzx;
            Permute4<1, 2, 2, 0> yzzx;
            Permute4<2, 2, 2, 0> zzzx;
            Permute4<3, 2, 2, 0> wzzx;
            Permute4<0, 3, 2, 0> xwzx;
            Permute4<1, 3, 2, 0> ywzx;
            Permute4<2, 3, 2, 0> zwzx;
            Permute4<3, 3, 2, 0> wwzx;
            Permute4<0, 0, 3, 0> xxwx;
            Permute4<1, 0, 3, 0> yxwx;
            Permute4<2, 0, 3, 0> zxwx;
            Permute4<3, 0, 3, 0> wxwx;
            Permute4<0, 1, 3, 0> xywx;
            Permute4<1, 1, 3, 0> yywx;
            Permute4<2, 1, 3, 0> zywx;
            Permute4<3, 1, 3, 0> wywx;
            Permute4<0, 2, 3, 0> xzwx;
            Permute4<1, 2, 3, 0> yzwx;
            Permute4<2, 2, 3, 0> zzwx;
            Permute4<3, 2, 3, 0> wzwx;
            Permute4<0, 3, 3, 0> xwwx;
            Permute4<1, 3, 3, 0> ywwx;
            Permute4<2, 3, 3, 0> zwwx;
            Permute4<3, 3, 3, 0> wwwx;
            Permute4<0, 0, 0, 1> xxxy;
            Permute4<1, 0, 0, 1> yxxy;
            Permute4<2, 0, 0, 1> zxxy;
            Permute4<3, 0, 0, 1> wxxy;
            Permute4<0, 1, 0, 1> xyxy;
            Permute4<1, 1, 0, 1> yyxy;
            Permute4<2, 1, 0, 1> zyxy;
            Permute4<3, 1, 0, 1> wyxy;
            Permute4<0, 2, 0, 1> xzxy;
            Permute4<1, 2, 0, 1> yzxy;
            Permute4<2, 2, 0, 1> zzxy;
            Permute4<3, 2, 0, 1> wzxy;
            Permute4<0, 3, 0, 1> xwxy;
            Permute4<1, 3, 0, 1> ywxy;
            Permute4<2, 3, 0, 1> zwxy;
            Permute4<3, 3, 0, 1> wwxy;
            Permute4<0, 0, 1, 1> xxyy;
            Permute4<1, 0, 1, 1> yxyy;
            Permute4<2, 0, 1, 1> zxyy;
            Permute4<3, 0, 1, 1> wxyy;
            Permute4<0, 1, 1, 1> xyyy;
            Permute4<1, 1, 1, 1> yyyy;
            Permute4<2, 1, 1, 1> zyyy;
            Permute4<3, 1, 1, 1> wyyy;
            Permute4<0, 2, 1, 1> xzyy;
            Permute4<1, 2, 1, 1> yzyy;
            Permute4<2, 2, 1, 1> zzyy;
            Permute4<3, 2, 1, 1> wzyy;
            Permute4<0, 3, 1, 1> xwyy;
            Permute4<1, 3, 1, 1> ywyy;
            Permute4<2, 3, 1, 1> zwyy;
            Permute4<3, 3, 1, 1> wwyy;
            Permute4<0, 0, 2, 1> xxzy;
            Permute4<1, 0, 2, 1> yxzy;
            Permute4<2, 0, 2, 1> zxzy;
            Permute4<3, 0, 2, 1> wxzy;
            Permute4<0, 1, 2, 1> xyzy;
            Permute4<1, 1, 2, 1> yyzy;
            Permute4<2, 1, 2, 1> zyzy;
            Permute4<3, 1, 2, 1> wyzy;
            Permute4<0, 2, 2, 1> xzzy;
            Permute4<1, 2, 2, 1> yzzy;
            Permute4<2, 2, 2, 1> zzzy;
            Permute4<3, 2, 2, 1> wzzy;
            Permute4<0, 3, 2, 1> xwzy;
            Permute4<1, 3, 2, 1> ywzy;
            Permute4<2, 3, 2, 1> zwzy;
            Permute4<3, 3, 2, 1> wwzy;
            Permute4<0, 0, 3, 1> xxwy;
            Permute4<1, 0, 3, 1> yxwy;
            Permute4<2, 0, 3, 1> zxwy;
            Permute4<3, 0, 3, 1> wxwy;
            Permute4<0, 1, 3, 1> xywy;
            Permute4<1, 1, 3, 1> yywy;
            Permute4<2, 1, 3, 1> zywy;
            Permute4<3, 1, 3, 1> wywy;
            Permute4<0, 2, 3, 1> xzwy;
            Permute4<1, 2, 3, 1> yzwy;
            Permute4<2, 2, 3, 1> zzwy;
            Permute4<3, 2, 3, 1> wzwy;
            Permute4<0, 3, 3, 1> xwwy;
            Permute4<1, 3, 3, 1> ywwy;
            Permute4<2, 3, 3, 1> zwwy;
            Permute4<3, 3, 3, 1> wwwy;
            Permute4<0, 0, 0, 2> xxxz;
            Permute4<1, 0, 0, 2> yxxz;
            Permute4<2, 0, 0, 2> zxxz;
            Permute4<3, 0, 0, 2> wxxz;
            Permute4<0, 1, 0, 2> xyxz;
            Permute4<1, 1, 0, 2> yyxz;
            Permute4<2, 1, 0, 2> zyxz;
            Permute4<3, 1, 0, 2> wyxz;
            Permute4<0, 2, 0, 2> xzxz;
            Permute4<1, 2, 0, 2> yzxz;
            Permute4<2, 2, 0, 2> zzxz;
            Permute4<3, 2, 0, 2> wzxz;
            Permute4<0, 3, 0, 2> xwxz;
            Permute4<1, 3, 0, 2> ywxz;
            Permute4<2, 3, 0, 2> zwxz;
            Permute4<3, 3, 0, 2> wwxz;
            Permute4<0, 0, 1, 2> xxyz;
            Permute4<1, 0, 1, 2> yxyz;
            Permute4<2, 0, 1, 2> zxyz;
            Permute4<3, 0, 1, 2> wxyz;
            Permute4<0, 1, 1, 2> xyyz;
            Permute4<1, 1, 1, 2> yyyz;
            Permute4<2, 1, 1, 2> zyyz;
            Permute4<3, 1, 1, 2> wyyz;
            Permute4<0, 2, 1, 2> xzyz;
            Permute4<1, 2, 1, 2> yzyz;
            Permute4<2, 2, 1, 2> zzyz;
            Permute4<3, 2, 1, 2> wzyz;
            Permute4<0, 3, 1, 2> xwyz;
            Permute4<1, 3, 1, 2> ywyz;
            Permute4<2, 3, 1, 2> zwyz;
            Permute4<3, 3, 1, 2> wwyz;
            Permute4<0, 0, 2, 2> xxzz;
            Permute4<1, 0, 2, 2> yxzz;
            Permute4<2, 0, 2, 2> zxzz;
            Permute4<3, 0, 2, 2> wxzz;
            Permute4<0, 1, 2, 2> xyzz;
            Permute4<1, 1, 2, 2> yyzz;
            Permute4<2, 1, 2, 2> zyzz;
            Permute4<3, 1, 2, 2> wyzz;
            Permute4<0, 2, 2, 2> xzzz;
            Permute4<1, 2, 2, 2> yzzz;
            Permute4<2, 2, 2, 2> zzzz;
            Permute4<3, 2, 2, 2> wzzz;
            Permute4<0, 3, 2, 2> xwzz;
            Permute4<1, 3, 2, 2> ywzz;
            Permute4<2, 3, 2, 2> zwzz;
            Permute4<3, 3, 2, 2> wwzz;
            Permute4<0, 0, 3, 2> xxwz;
            Permute4<1, 0, 3, 2> yxwz;
            Permute4<2, 0, 3, 2> zxwz;
            Permute4<3, 0, 3, 2> wxwz;
            Permute4<0, 1, 3, 2> xywz;
            Permute4<1, 1, 3, 2> yywz;
            Permute4<2, 1, 3, 2> zywz;
            Permute4<3, 1, 3, 2> wywz;
            Permute4<0, 2, 3, 2> xzwz;
            Permute4<1, 2, 3, 2> yzwz;
            Permute4<2, 2, 3, 2> zzwz;
            Permute4<3, 2, 3, 2> wzwz;
            Permute4<0, 3, 3, 2> xwwz;
            Permute4<1, 3, 3, 2> ywwz;
            Permute4<2, 3, 3, 2> zwwz;
            Permute4<3, 3, 3, 2> wwwz;
            Permute4<0, 0, 0, 3> xxxw;
            Permute4<1, 0, 0, 3> yxxw;
            Permute4<2, 0, 0, 3> zxxw;
            Permute4<3, 0, 0, 3> wxxw;
            Permute4<0, 1, 0, 3> xyxw;
            Permute4<1, 1, 0, 3> yyxw;
            Permute4<2, 1, 0, 3> zyxw;
            Permute4<3, 1, 0, 3> wyxw;
            Permute4<0, 2, 0, 3> xzxw;
            Permute4<1, 2, 0, 3> yzxw;
            Permute4<2, 2, 0, 3> zzxw;
            Permute4<3, 2, 0, 3> wzxw;
            Permute4<0, 3, 0, 3> xwxw;
            Permute4<1, 3, 0, 3> ywxw;
            Permute4<2, 3, 0, 3> zwxw;
            Permute4<3, 3, 0, 3> wwxw;
            Permute4<0, 0, 1, 3> xxyw;
            Permute4<1, 0, 1, 3> yxyw;
            Permute4<2, 0, 1, 3> zxyw;
            Permute4<3, 0, 1, 3> wxyw;
            Permute4<0, 1, 1, 3> xyyw;
            Permute4<1, 1, 1, 3> yyyw;
            Permute4<2, 1, 1, 3> zyyw;
            Permute4<3, 1, 1, 3> wyyw;
            Permute4<0, 2, 1, 3> xzyw;
            Permute4<1, 2, 1, 3> yzyw;
            Permute4<2, 2, 1, 3> zzyw;
            Permute4<3, 2, 1, 3> wzyw;
            Permute4<0, 3, 1, 3> xwyw;
            Permute4<1, 3, 1, 3> ywyw;
            Permute4<2, 3, 1, 3> zwyw;
            Permute4<3, 3, 1, 3> wwyw;
            Permute4<0, 0, 2, 3> xxzw;
            Permute4<1, 0, 2, 3> yxzw;
            Permute4<2, 0, 2, 3> zxzw;
            Permute4<3, 0, 2, 3> wxzw;
            Permute4<0, 1, 2, 3> xyzw;
            Permute4<1, 1, 2, 3> yyzw;
            Permute4<2, 1, 2, 3> zyzw;
            Permute4<3, 1, 2, 3> wyzw;
            Permute4<0, 2, 2, 3> xzzw;
            Permute4<1, 2, 2, 3> yzzw;
            Permute4<2, 2, 2, 3> zzzw;
            Permute4<3, 2, 2, 3> wzzw;
            Permute4<0, 3, 2, 3> xwzw;
            Permute4<1, 3, 2, 3> ywzw;
            Permute4<2, 3, 2, 3> zwzw;
            Permute4<3, 3, 2, 3> wwzw;
            Permute4<0, 0, 3, 3> xxww;
            Permute4<1, 0, 3, 3> yxww;
            Permute4<2, 0, 3, 3> zxww;
            Permute4<3, 0, 3, 3> wxww;
            Permute4<0, 1, 3, 3> xyww;
            Permute4<1, 1, 3, 3> yyww;
            Permute4<2, 1, 3, 3> zyww;
            Permute4<3, 1, 3, 3> wyww;
            Permute4<0, 2, 3, 3> xzww;
            Permute4<1, 2, 3, 3> yzww;
            Permute4<2, 2, 3, 3> zzww;
            Permute4<3, 2, 3, 3> wzww;
            Permute4<0, 3, 3, 3> xwww;
            Permute4<1, 3, 3, 3> ywww;
            Permute4<2, 3, 3, 3> zwww;
            Permute4<3, 3, 3, 3> wwww;
        };

        explicit Vector()
        {
        }

        explicit Vector(double s)
        : m(simd::float64x4_set1(s))
        {
        }

        explicit Vector(int s)
        : m(simd::float64x4_set1(double(s)))
        {
        }

        explicit Vector(double s0, double s1, double s2, double s3)
        : m(simd::float64x4_set4(s0, s1, s2, s3))
        {
        }

        explicit Vector(const Vector<double, 2>& v, double s0, double s1)
        : m(simd::float64x4_set4(v.x, v.y, s0, s1))
        {
        }

        explicit Vector(double s0, double s1, const Vector<double, 2>& v)
        : m(simd::float64x4_set4(s0, s1, v.x, v.y))
        {
        }

        explicit Vector(double s0, const Vector<double, 2>& v, double s1)
        : m(simd::float64x4_set4(s0, v.x, v.y, s1))
        {
        }

        explicit Vector(const Vector<double, 2>& v0, const Vector<double, 2>& v1)
        : m(simd::float64x4_set4(v0.x, v0.y, v1.x, v1.y))
        {
        }

        explicit Vector(const Vector<double, 3>& v, double s)
        : m(simd::float64x4_set4(v.x, v.y, v.z, s))
        {
        }

        explicit Vector(double s, const Vector<double, 3>& v)
        : m(simd::float64x4_set4(s, v.x, v.y, v.z))
        {
        }

        Vector(simd::float64x4 v)
        : m(v)
        {
        }

        template <int X, int Y, int Z, int W>
        Vector(const Permute4<X, Y, Z, W>& p)
        {
            m = p;
        }

        template <int X, int Y, int Z, int W>
        Vector& operator = (const Permute4<X, Y, Z, W>& p)
        {
            m = p;
            return *this;
        }

        Vector& operator = (simd::float64x4 v)
        {
            m = v;
            return *this;
        }

        Vector& operator = (double s)
        {
            m = simd::float64x4_set1(s);
            return *this;
        }

        operator simd::float64x4 () const
        {
            return m;
        }

        operator simd::float64x4 ()
        {
            return m;
        }
    };

    // ------------------------------------------------------------------
    // operators
    // ------------------------------------------------------------------

    static inline const double4& operator + (const double4& v)
    {
        return v;
    }

    static inline double4 operator - (const double4& v)
    {
        return simd::float64x4_neg(v);
    }

    static inline double4& operator += (double4& a, const double4& b)
    {
        a = simd::float64x4_add(a, b);
        return a;
    }

    static inline double4& operator -= (double4& a, const double4& b)
    {
        a = simd::float64x4_sub(a, b);
        return a;
    }

    static inline double4& operator *= (double4& a, const double4& b)
    {
        a = simd::float64x4_mul(a, b);
        return a;
    }

    static inline double4& operator *= (double4& a, double b)
    {
        a = simd::float64x4_mul(a, b);
        return a;
    }

    static inline double4& operator /= (double4& a, const double4& b)
    {
        a = simd::float64x4_div(a, b);
        return a;
    }

    static inline double4& operator /= (double4& a, double b)
    {
        a = simd::float64x4_div(a, b);
        return a;
    }

    static inline double4 operator + (const double4& a, const double4& b)
    {
        return simd::float64x4_add(a, b);
    }

    template <int X, int Y, int Z, int W, int A, int B, int C, int D>
    static inline double4 operator + (const double4::Permute4<X,Y,Z,W>& a, const double4::Permute4<A,B,C,D>& b)
    {
        return simd::float64x4_add(a, b);
    }
    
    static inline double4 operator - (const double4& a, const double4& b)
    {
        return simd::float64x4_sub(a, b);
    }

    template <int X, int Y, int Z, int W, int A, int B, int C, int D>
    static inline double4 operator - (const double4::Permute4<X,Y,Z,W>& a, const double4::Permute4<A,B,C,D>& b)
    {
        return simd::float64x4_sub(a, b);
    }

    static inline double4 operator * (const double4& a, const double4& b)
    {
        return simd::float64x4_mul(a, b);
    }

    static inline double4 operator * (const double4& a, double b)
    {
        return simd::float64x4_mul(a, b);
    }

    static inline double4 operator * (double a, const double4& b)
    {
        return simd::float64x4_mul(a, b);
    }

    template <int X, int Y, int Z, int W, int A, int B, int C, int D>
    static inline double4 operator * (const double4::Permute4<X,Y,Z,W>& a, const double4::Permute4<A,B,C,D>& b)
    {
        return simd::float64x4_mul(a, b);
    }
    
    static inline double4 operator / (const double4& a, const double4& b)
    {
        return simd::float64x4_div(a, b);
    }

    static inline double4 operator / (const double4& a, double b)
    {
        return simd::float64x4_div(a, b);
    }

    template <int X, int Y, int Z, int W, int A, int B, int C, int D>
    static inline double4 operator / (const double4::Permute4<X,Y,Z,W>& a, const double4::Permute4<A,B,C,D>& b)
    {
        return simd::float64x4_div(a, b);
    }

    // ------------------------------------------------------------------
    // functions
    // ------------------------------------------------------------------

#define MAKE_VECTOR_FUNCTION1(Name, SimdName) \
    static inline double4 Name(const double4& a) { \
        return SimdName(a); \
    }

#define MAKE_VECTOR_FUNCTION2(Name, SimdName) \
    static inline double4 Name(const double4& a, const double4& b) { \
        return SimdName(a, b); \
    }

    MAKE_VECTOR_FUNCTION1(abs, simd::float64x4_abs)
    MAKE_VECTOR_FUNCTION1(square, simd::float64x4_square)
    MAKE_VECTOR_FUNCTION1(length, simd::float64x4_length)
    MAKE_VECTOR_FUNCTION1(normalize, simd::float64x4_normalize)
    MAKE_VECTOR_FUNCTION1(round, simd::float64x4_round)
    MAKE_VECTOR_FUNCTION1(floor, simd::float64x4_floor)
    MAKE_VECTOR_FUNCTION1(ceil, simd::float64x4_ceil)
    MAKE_VECTOR_FUNCTION1(fract, simd::float64x4_fract)
    MAKE_VECTOR_FUNCTION1(sin, simd::float64x4_sin)
    MAKE_VECTOR_FUNCTION1(cos, simd::float64x4_cos)
    MAKE_VECTOR_FUNCTION1(tan, simd::float64x4_tan)
    MAKE_VECTOR_FUNCTION1(asin, simd::float64x4_asin)
    MAKE_VECTOR_FUNCTION1(acos, simd::float64x4_acos)
    MAKE_VECTOR_FUNCTION1(atan, simd::float64x4_atan)
    MAKE_VECTOR_FUNCTION1(exp, simd::float64x4_exp)
    MAKE_VECTOR_FUNCTION1(log, simd::float64x4_log)
    MAKE_VECTOR_FUNCTION1(exp2, simd::float64x4_exp2)
    MAKE_VECTOR_FUNCTION1(log2, simd::float64x4_log2)
    MAKE_VECTOR_FUNCTION1(sign, simd::float64x4_sign)
    MAKE_VECTOR_FUNCTION1(radians, simd::float64x4_radians)
    MAKE_VECTOR_FUNCTION1(degrees, simd::float64x4_degrees)
    MAKE_VECTOR_FUNCTION1(sqrt, simd::float64x4_sqrt)
    MAKE_VECTOR_FUNCTION1(rsqrt, simd::float64x4_rsqrt)

    MAKE_VECTOR_FUNCTION2(min, simd::float64x4_min)
    MAKE_VECTOR_FUNCTION2(max, simd::float64x4_max)
    MAKE_VECTOR_FUNCTION2(dot, simd::float64x4_dot4)
    //MAKE_VECTOR_FUNCTION2(cross, simd::float64x4_cross3)
    MAKE_VECTOR_FUNCTION2(mod, simd::float64x4_mod)
    MAKE_VECTOR_FUNCTION2(pow, simd::float64x4_pow)
    MAKE_VECTOR_FUNCTION2(atan2, simd::float64x4_atan2)

#undef MAKE_VECTOR_FUNCTION1
#undef MAKE_VECTOR_FUNCTION2
    
    static inline double4 clamp(const double4& a, const double4& amin, const double4& amax)
    {
        return simd::float64x4_clamp(a, amin, amax);
    }

    static inline double4 madd(const double4& a, const double4& b, const double4& c)
    {
        return simd::float64x4_madd(a, b, c);
    }

    static inline double4 msub(const double4& a, const double4& b, const double4& c)
    {
        return simd::float64x4_msub(a, b, c);
    }

    static inline double4 lerp(const double4& a, const double4& b, double factor)
    {
        return a + (b - a) * factor;
    }

    static inline double4 lerp(const double4& a, const double4& b, const double4& factor)
    {
        return a + (b - a) * factor;
    }

    static inline double4 hmin(const double4& v)
    {
        const double4 temp = min(v, v.zwxy);
        return min(temp, temp.yxwz);
    }

    static inline double4 hmax(const double4& v)
    {
        const double4 temp = max(v, v.zwxy);
        return max(temp, temp.yxwz);
    }

    // ------------------------------------------------------------------
	// compare / select
    // ------------------------------------------------------------------

    static inline simd::float64x4 operator > (const double4& a, const double4& b)
    {
        return simd::float64x4_compare_gt(a, b);
    }

    static inline simd::float64x4 operator >= (const double4& a, const double4& b)
    {
        return simd::float64x4_compare_ge(a, b);
    }

    static inline simd::float64x4 operator < (const double4& a, const double4& b)
    {
        return simd::float64x4_compare_lt(a, b);
    }

    static inline simd::float64x4 operator <= (const double4& a, const double4& b)
    {
        return simd::float64x4_compare_le(a, b);
    }

    static inline simd::float64x4 operator == (const double4& a, const double4& b)
    {
        return simd::float64x4_compare_eq(a, b);
    }

    static inline simd::float64x4 operator != (const double4& a, const double4& b)
    {
        return simd::float64x4_compare_neq(a, b);
    }

    static inline simd::float64x4 select(simd::float64x4 mask, const double4& a, const double4& b)
    {
        return simd::float64x4_select(mask, a, b);
    }

} // namespace mango

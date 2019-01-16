/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "simd.hpp"

namespace mango {
namespace simd {

    // -----------------------------------------------------------------
    // float64x2
    // -----------------------------------------------------------------

    template <uint32 x, uint32 y>
    static inline float64x2 shuffle(float64x2 v)
    {
        static_assert(x < 2 && y < 2, "Index out of range.");
        return _mm_shuffle_pd(v, v, y * 2 + x);
    }

    template <uint32 x, uint32 y>
    static inline float64x2 shuffle(float64x2 a, float64x2 b)
    {
        static_assert(x < 2 && y < 2, "Index out of range.");
        return _mm_shuffle_pd(a, b, y * 2 + x);
    }

    // set component

    template <int Index>
    static inline float64x2 set_component(float64x2 a, double s);

    template <>
    inline float64x2 set_component<0>(float64x2 a, double x)
    {
        return _mm_move_sd(a, _mm_set1_pd(x));
    }

    template <>
    inline float64x2 set_component<1>(float64x2 a, double y)
    {
        return _mm_move_sd(_mm_set1_pd(y), a);
    }

    // get component

    template <int Index>
    static inline double get_component(float64x2 a);

    template <>
    inline double get_component<0>(float64x2 a)
    {
        return _mm_cvtsd_f64(a);
    }

    template <>
    inline double get_component<1>(float64x2 a)
    {
        const __m128d yy = _mm_unpackhi_pd(a, a);
        return _mm_cvtsd_f64(yy);
    }

    static inline float64x2 float64x2_zero()
    {
        return _mm_setzero_pd();
    }

    static inline float64x2 float64x2_set1(double s)
    {
        return _mm_set1_pd(s);
    }

    static inline float64x2 float64x2_set2(double x, double y)
    {
        return _mm_setr_pd(x, y);
    }

    static inline float64x2 float64x2_uload(const double* source)
    {
        return _mm_loadu_pd(source);
    }

    static inline void float64x2_ustore(double* dest, float64x2 a)
    {
        _mm_storeu_pd(dest, a);
    }

    static inline float64x2 unpackhi(float64x2 a, float64x2 b)
    {
        return _mm_unpackhi_pd(a, b);
    }

    static inline float64x2 unpacklo(float64x2 a, float64x2 b)
    {
        return _mm_unpacklo_pd(a, b);
    }

    // bitwise

    static inline float64x2 bitwise_nand(float64x2 a, float64x2 b)
    {
        return _mm_andnot_pd(a, b);
    }

    static inline float64x2 bitwise_and(float64x2 a, float64x2 b)
    {
        return _mm_and_pd(a, b);
    }

    static inline float64x2 bitwise_or(float64x2 a, float64x2 b)
    {
        return _mm_or_pd(a, b);
    }

    static inline float64x2 bitwise_xor(float64x2 a, float64x2 b)
    {
        return _mm_xor_pd(a, b);
    }

    static inline float64x2 bitwise_not(float64x2 a)
    {
        return _mm_xor_pd(a, _mm_cmpeq_pd(a, a));
    }

    static inline float64x2 min(float64x2 a, float64x2 b)
    {
        return _mm_min_pd(a, b);
    }

    static inline float64x2 max(float64x2 a, float64x2 b)
    {
        return _mm_max_pd(a, b);
    }

    static inline float64x2 abs(float64x2 a)
    {
        return _mm_max_pd(a, _mm_sub_pd(_mm_setzero_pd(), a));
    }

    static inline float64x2 neg(float64x2 a)
    {
        return _mm_sub_pd(_mm_setzero_pd(), a);
    }

    static inline float64x2 sign(float64x2 a)
    {
        __m128d sign_mask = _mm_set1_pd(-0.0);
        __m128d value_mask = _mm_cmpneq_pd(a, _mm_setzero_pd());
        __m128d sign_bits = _mm_and_pd(a, sign_mask);
        __m128d value_bits = _mm_and_pd(_mm_set1_pd(1.0), value_mask);
        return _mm_or_pd(value_bits, sign_bits);
    }
    
    static inline float64x2 add(float64x2 a, float64x2 b)
    {
        return _mm_add_pd(a, b);
    }

    static inline float64x2 sub(float64x2 a, float64x2 b)
    {
        return _mm_sub_pd(a, b);
    }

    static inline float64x2 mul(float64x2 a, float64x2 b)
    {
        return _mm_mul_pd(a, b);
    }

    static inline float64x2 div(float64x2 a, float64x2 b)
    {
        return _mm_div_pd(a, b);
    }

    static inline float64x2 div(float64x2 a, double b)
    {
        return _mm_div_pd(a, _mm_set1_pd(b));
    }

#if defined(MANGO_ENABLE_FMA3)

    static inline float64x2 madd(float64x2 a, float64x2 b, float64x2 c)
    {
        return _mm_fmadd_pd(b, c, a);
    }

    static inline float64x2 msub(float64x2 a, float64x2 b, float64x2 c)
    {
        return _mm_fnmadd_pd(b, c, a);
    }

#else

    static inline float64x2 madd(float64x2 a, float64x2 b, float64x2 c)
    {
        return _mm_add_pd(a, _mm_mul_pd(b, c));
    }

    static inline float64x2 msub(float64x2 a, float64x2 b, float64x2 c)
    {
        return _mm_sub_pd(a, _mm_mul_pd(b, c));
    }

#endif

    static inline float64x2 fast_rcp(float64x2 a)
    {
        return _mm_rcp14_pd(a);
    }

    static inline float64x2 fast_rsqrt(float64x2 a)
    {
        return _mm_div_pd(_mm_set1_pd(1.0), _mm_sqrt_pd(a));
    }

    static inline float64x2 fast_sqrt(float64x2 a)
    {
        return _mm_sqrt_pd(a);
    }

    static inline float64x2 rcp(float64x2 a)
    {
        return _mm_div_pd(_mm_set1_pd(1.0), a);
    }

    static inline float64x2 rsqrt(float64x2 a)
    {
        return _mm_div_pd(_mm_set1_pd(1.0), _mm_sqrt_pd(a));
    }

    static inline float64x2 sqrt(float64x2 a)
    {
        return _mm_sqrt_pd(a);
    }

    static inline double dot2(float64x2 a, float64x2 b)
    {
        const __m128d xy = _mm_mul_pd(a, b);
        const __m128d yx = _mm_shuffle_pd(xy, xy, 0x01);
        float64x2 s = _mm_add_pd(xy, yx);
        return get_component<0>(s);
    }

    // compare

    static inline mask64x2 compare_neq(float64x2 a, float64x2 b)
    {
        return _mm_cmp_pd_mask(a, b, _CMP_NEQ_UQ);
    }

    static inline mask64x2 compare_eq(float64x2 a, float64x2 b)
    {
        return _mm_cmp_pd_mask(a, b, _CMP_EQ_OQ);
    }

    static inline mask64x2 compare_lt(float64x2 a, float64x2 b)
    {
        return _mm_cmp_pd_mask(a, b, _CMP_LT_OS);
    }

    static inline mask64x2 compare_le(float64x2 a, float64x2 b)
    {
        return _mm_cmp_pd_mask(a, b, _CMP_LE_OS);
    }

    static inline mask64x2 compare_gt(float64x2 a, float64x2 b)
    {
        return _mm_cmp_pd_mask(b, a, _CMP_LT_OS);
    }

    static inline mask64x2 compare_ge(float64x2 a, float64x2 b)
    {
        return _mm_cmp_pd_mask(b, a, _CMP_LE_OS);
    }

    static inline float64x2 select(mask64x2 mask, float64x2 a, float64x2 b)
    {
        return _mm_mask_blend_pd(mask, b, a);
    }

    // rounding

    static inline float64x2 round(float64x2 s)
    {
        return _mm_round_pd(s, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    }

    static inline float64x2 trunc(float64x2 s)
    {
        return _mm_round_pd(s, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
    }

    static inline float64x2 floor(float64x2 s)
    {
        return _mm_round_pd(s, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
    }

    static inline float64x2 ceil(float64x2 s)
    {
        return _mm_round_pd(s, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
    }

    static inline float64x2 fract(float64x2 s)
    {
        return sub(s, floor(s));
    }

} // namespace simd
} // namespace mango

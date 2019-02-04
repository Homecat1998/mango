/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2019 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "simd.hpp"

namespace mango {
namespace simd {

    // -----------------------------------------------------------------
    // float32x16
    // -----------------------------------------------------------------

    static inline float32x16 float32x16_zero()
    {
        return _mm512_setzero_ps();
    }

    static inline float32x16 float32x16_set1(float s)
    {
        return _mm512_set1_ps(s);
    }

    static inline float32x16 float32x16_set16(float s0, float s1, float s2, float s3, float s4, float s5,
        float s6, float s7, float s8, float s9, float s10, float s11, float s12, float s13, float s14, float s15)
    {
        return _mm512_setr_ps(s0, s1, s2, s3, s4, s5, s6, s7,
            s8, s9, s10, s11, s12, s13, s14, s15);
    }

    static inline float32x16 float32x16_uload(const float* source)
    {
        return _mm512_loadu_ps(source);
    }

    static inline void float32x16_ustore(float* dest, float32x16 a)
    {
        _mm512_storeu_ps(dest, a);
    }

    static inline float32x16 unpackhi(float32x16 a, float32x16 b)
    {
        return _mm512_unpackhi_ps(a, b);
    }

    static inline float32x16 unpacklo(float32x16 a, float32x16 b)
    {
        return _mm512_unpacklo_ps(a, b);
    }

    // bitwise

    static inline float32x16 bitwise_nand(float32x16 a, float32x16 b)
    {
        return _mm512_andnot_ps(a, b);
    }

    static inline float32x16 bitwise_and(float32x16 a, float32x16 b)
    {
         return _mm512_and_ps(a, b);
    }

    static inline float32x16 bitwise_or(float32x16 a, float32x16 b)
    {
         return _mm512_or_ps(a, b);
    }

    static inline float32x16 bitwise_xor(float32x16 a, float32x16 b)
    {
         return _mm512_xor_ps(a, b);
    }

    static inline float32x16 bitwise_not(float32x16 a)
    {
        return _mm512_xor_ps(a, _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)));
    }

    static inline float32x16 min(float32x16 a, float32x16 b)
    {
        return _mm512_min_ps(a, b);
    }

    static inline float32x16 max(float32x16 a, float32x16 b)
    {
        return _mm512_max_ps(a, b);
    }

    static inline float32x16 abs(float32x16 a)
    {
        return _mm512_abs_ps(a);
    }

    static inline float32x16 neg(float32x16 a)
    {
        return _mm512_sub_ps(_mm512_setzero_ps(), a);
    }

    static inline float32x16 sign(float32x16 a)
    {
        __m512 zero = _mm512_setzero_ps();
        __m512 negative = _mm512_mask_blend_ps(_mm512_cmp_ps_mask(a, zero, _CMP_LT_OS), zero, _mm512_set1_ps(-1.0f));
        __m512 positive = _mm512_mask_blend_ps(_mm512_cmp_ps_mask(zero, a, _CMP_LT_OS), zero, _mm512_set1_ps( 1.0f));
        return _mm512_or_ps(negative, positive);
    }

    static inline float32x16 add(float32x16 a, float32x16 b)
    {
        return _mm512_add_ps(a, b);
    }

    static inline float32x16 sub(float32x16 a, float32x16 b)
    {
        return _mm512_sub_ps(a, b);
    }

    static inline float32x16 mul(float32x16 a, float32x16 b)
    {
        return _mm512_mul_ps(a, b);
    }

    static inline float32x16 div(float32x16 a, float32x16 b)
    {
        return _mm512_div_ps(a, b);
    }

    static inline float32x16 div(float32x16 a, float b)
    {
        return _mm512_div_ps(a, _mm512_set1_ps(b));
    }

#if defined(MANGO_ENABLE_FMA3)

    static inline float32x16 madd(float32x16 a, float32x16 b, float32x16 c)
    {
        return _mm512_fmadd_ps(b, c, a);
    }

    static inline float32x16 msub(float32x16 a, float32x16 b, float32x16 c)
    {
        return _mm512_fnmadd_ps(b, c, a);
    }

#else

    static inline float32x16 madd(float32x16 a, float32x16 b, float32x16 c)
    {
        return _mm512_add_ps(a, _mm512_mul_ps(b, c));
    }

    static inline float32x16 msub(float32x16 a, float32x16 b, float32x16 c)
    {
        return _mm512_sub_ps(a, _mm512_mul_ps(b, c));
    }

#endif

    static inline float32x16 fast_rcp(float32x16 a)
    {
        return _mm512_rcp14_ps(a);
    }

    static inline float32x16 fast_rsqrt(float32x16 a)
    {
        return _mm512_rsqrt14_ps(a);
    }

    static inline float32x16 fast_sqrt(float32x16 a)
    {
        return _mm512_sqrt_ps(a);
    }

    static inline float32x16 rcp(float32x16 a)
    {
        return _mm512_rcp28_ps(a);
    }

    static inline float32x16 rsqrt(float32x16 a)
    {
        return _mm512_rsqrt28_ps(a);
    }

    static inline float32x16 sqrt(float32x16 a)
    {
        return _mm512_sqrt_ps(a);
    }

    // compare

    static inline mask32x16 compare_neq(float32x16 a, float32x16 b)
    {
        return _mm512_cmp_ps_mask(a, b, _CMP_NEQ_UQ);
    }

    static inline mask32x16 compare_eq(float32x16 a, float32x16 b)
    {
        return _mm512_cmp_ps_mask(a, b, _CMP_EQ_OQ);
    }

    static inline mask32x16 compare_lt(float32x16 a, float32x16 b)
    {
        return _mm512_cmp_ps_mask(a, b, _CMP_LT_OS);
    }

    static inline mask32x16 compare_le(float32x16 a, float32x16 b)
    {
        return _mm512_cmp_ps_mask(a, b, _CMP_LE_OS);
    }

    static inline mask32x16 compare_gt(float32x16 a, float32x16 b)
    {
        return _mm512_cmp_ps_mask(b, a, _CMP_LT_OS);
    }

    static inline mask32x16 compare_ge(float32x16 a, float32x16 b)
    {
        return _mm512_cmp_ps_mask(b, a, _CMP_LE_OS);
    }

    static inline float32x16 select(mask32x16 mask, float32x16 a, float32x16 b)
    {
        return _mm512_mask_blend_ps(mask, b, a);
    }

    // rounding

    static inline float32x16 round(float32x16 s)
    {
        return _mm512_add_round_ps(s, _mm512_setzero_ps(), _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    }

    static inline float32x16 trunc(float32x16 s)
    {
        return _mm512_add_round_ps(s, _mm512_setzero_ps(), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
    }

    static inline float32x16 floor(float32x16 s)
    {
        return _mm512_add_round_ps(s, _mm512_setzero_ps(), _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
    }

    static inline float32x16 ceil(float32x16 s)
    {
        return _mm512_add_round_ps(s, _mm512_setzero_ps(), _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
    }

    static inline float32x16 fract(float32x16 s)
    {
        return _mm512_sub_ps(s, floor(s));
    }

} // namespace simd
} // namespace mango

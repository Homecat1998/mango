/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "simd.hpp"

namespace mango {
namespace simd {

    // -----------------------------------------------------------------
    // helpers
    // -----------------------------------------------------------------

#define simd128_shuffle_epi32(a, b, mask) \
    _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(a), _mm_castsi128_ps(b), mask))

#define simd128_shuffle_epi64(a, b, mask) \
    _mm_castpd_si128(_mm_shuffle_pd(_mm_castsi128_pd(a), _mm_castsi128_pd(b), mask))

#if defined(MANGO_ENABLE_SSE4_1)

    static inline __m128i simd128_shuffle_x0z0(__m128i a)
    {
        return _mm_blend_epi16(a, _mm_xor_si128(a, a), 0xcc);
    }

    static inline __m128i simd128_shuffle_4x4(__m128i a, __m128i b, __m128i c, __m128i d)
    {
        a = _mm_blend_epi16(a, b, 0x0c);
        c = _mm_blend_epi16(c, d, 0xc0);
        a = _mm_blend_epi16(a, c, 0xf0);
        return a;
    }

#else

    static inline __m128i simd128_shuffle_x0z0(__m128i a)
    {
        return _mm_and_si128(a, _mm_setr_epi32(0xffffffff, 0, 0xffffffff, 0));
    }

    static inline __m128i simd128_shuffle_4x4(__m128i a, __m128i b, __m128i c, __m128i d)
    {
        const __m128i v0 = simd128_shuffle_epi32(a, b, _MM_SHUFFLE(1, 1, 0, 0));
        const __m128i v1 = simd128_shuffle_epi32(c, d, _MM_SHUFFLE(3, 3, 2, 2));
        return simd128_shuffle_epi32(v0, v1, _MM_SHUFFLE(2, 0, 2, 0));
    }

#endif

    static inline __m128i simd128_mullo_epi32(__m128i a, __m128i b)
    {
        __m128i temp0 = _mm_mul_epu32(a, b);
        __m128i temp1 = _mm_mul_epu32(_mm_srli_si128(a, 4), _mm_srli_si128(b, 4));
        temp0 = _mm_shuffle_epi32(temp0, _MM_SHUFFLE(0, 0, 2, 0));
        temp1 = _mm_shuffle_epi32(temp1, _MM_SHUFFLE(0, 0, 2, 0));
        return _mm_unpacklo_epi32(temp0, temp1);
    }

    static inline __m128i simd128_packus_epi32(__m128i a, __m128i b)
    {
        a = _mm_slli_epi32(a, 16);
        a = _mm_srai_epi32(a, 16);
        b = _mm_slli_epi32(b, 16);
        b = _mm_srai_epi32(b, 16);
        return _mm_packs_epi32(a, b);
    }

    static inline __m128i _mm_not_si128(__m128i a)
    {
        return _mm_xor_si128(a, _mm_cmpeq_epi8(a, a));
    }

    static inline __m128i _mm_select_si128(__m128i mask, __m128i a, __m128i b)
    {
        return _mm_or_si128(_mm_and_si128(mask, a), _mm_andnot_si128(mask, b));
    }

#if defined(MANGO_CPU_64BIT)

    static inline __m128i simd128_cvtsi64_si128(s64 a)
    {
        return _mm_cvtsi64_si128(a);
    }

    static inline s64 simd128_cvtsi128_si64(__m128i a)
    {
        return _mm_cvtsi128_si64(a);
    }

#else

    static inline __m128i simd128_cvtsi64_si128(int64 a)
    {
        return _mm_set_epi64x(0, a);
    }

    static inline int64 simd128_cvtsi128_si64(__m128i a)
    {
        uint64 value = _mm_cvtsi128_si32(a);
        value |= uint64(_mm_cvtsi128_si32(simd128_shuffle_epi32(a, a, 0xee))) << 32;
        return value;
    }

#endif

    // -----------------------------------------------------------------
    // uint8x16
    // -----------------------------------------------------------------

#if defined(MANGO_ENABLE_SSE4_1)

    template <unsigned int Index>
    static inline uint8x16 set_component(uint8x16 a, u8 s)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm_insert_epi8(a, s, Index);
    }

    template <unsigned int Index>
    static inline u8 get_component(uint8x16 a)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm_extract_epi8(a, Index);
    }

#else

    template <unsigned int Index>
    static inline uint8x16 set_component(uint8x16 a, u8 s)
    {
        static_assert(Index < 16, "Index out of range.");
        uint32 temp = _mm_extract_epi16(a, Index / 2);
        if (Index & 1)
            temp = (temp & 0x00ff) | uint32(s) << 8;
        else
            temp = (temp & 0xff00) | uint32(s);
        return _mm_insert_epi16(a, temp, Index / 2);
    }

    template <unsigned int Index>
    static inline u8 get_component(uint8x16 a)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm_extract_epi16(a, Index / 2) >> ((Index & 1) * 8);
    }

#endif

    static inline uint8x16 uint8x16_zero()
    {
        return _mm_setzero_si128();
    }

    static inline uint8x16 uint8x16_set1(u8 s)
    {
        return _mm_set1_epi8(s);
    }

    static inline uint8x16 uint8x16_set16(
        u8 s0, u8 s1, u8 s2, u8 s3, u8 s4, u8 s5, u8 s6, u8 s7,
        u8 s8, u8 s9, u8 s10, u8 s11, u8 s12, u8 s13, u8 s14, u8 s15)
    {
        return _mm_setr_epi8(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15);
    }

    static inline uint8x16 uint8x16_load_low(const u8* source)
    {
        return _mm_loadl_epi64(reinterpret_cast<__m128i const *>(source));
    }

    static inline void uint8x16_store_low(u8* dest, uint8x16 a)
    {
        _mm_storel_epi64(reinterpret_cast<__m128i *>(dest), a);
    }

    static inline uint8x16 unpacklo(uint8x16 a, uint8x16 b)
    {
        return _mm_unpacklo_epi8(a, b);
    }

    static inline uint8x16 unpackhi(uint8x16 a, uint8x16 b)
    {
        return _mm_unpackhi_epi8(a, b);
    }

    static inline uint8x16 add(uint8x16 a, uint8x16 b)
    {
        return _mm_add_epi8(a, b);
    }

    static inline uint8x16 sub(uint8x16 a, uint8x16 b)
    {
        return _mm_sub_epi8(a, b);
    }

    // saturated

    static inline uint8x16 adds(uint8x16 a, uint8x16 b)
    {
        return _mm_adds_epu8(a, b);
    }

    static inline uint8x16 subs(uint8x16 a, uint8x16 b)
    {
        return _mm_subs_epu8(a, b);
    }

    // bitwise

    static inline uint8x16 bitwise_nand(uint8x16 a, uint8x16 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline uint8x16 bitwise_and(uint8x16 a, uint8x16 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline uint8x16 bitwise_or(uint8x16 a, uint8x16 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline uint8x16 bitwise_xor(uint8x16 a, uint8x16 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline uint8x16 bitwise_not(uint8x16 a)
    {
        return _mm_not_si128(a);
    }

    // compare

#if defined(MANGO_ENABLE_XOP)

    static inline umask8x16 compare_eq(uint8x16 a, uint8x16 b)
    {
        return _mm_comeq_epu8(a, b);
    }

    static inline umask8x16 compare_gt(uint8x16 a, uint8x16 b)
    {
        return _mm_comgt_epu8(a, b);
    }

    static inline umask8x16 compare_neq(uint8x16 a, uint8x16 b)
    {
        return _mm_comneq_epu8(a, b);
    }

    static inline umask8x16 compare_lt(uint8x16 a, uint8x16 b)
    {
        return _mm_comlt_epu8(a, b);
    }

    static inline umask8x16 compare_le(uint8x16 a, uint8x16 b)
    {
        return _mm_comle_epu8(a, b);
    }

    static inline umask8x16 compare_ge(uint8x16 a, uint8x16 b)
    {
        return _mm_comge_epu8(a, b);
    }

#else

    static inline mask8x16 compare_eq(uint8x16 a, uint8x16 b)
    {
        return _mm_cmpeq_epi8(a, b);
    }

    static inline mask8x16 compare_gt(uint8x16 a, uint8x16 b)
    {
        const __m128i sign = _mm_set1_epi32(0x80808080);
        return _mm_cmpgt_epi8(_mm_xor_si128(a, sign), _mm_xor_si128(b, sign));
    }

    static inline mask8x16 compare_neq(uint8x16 a, uint8x16 b)
    {
        return _mm_not_si128(compare_eq(b, a));
    }

    static inline mask8x16 compare_lt(uint8x16 a, uint8x16 b)
    {
        return compare_gt(b, a);
    }

    static inline mask8x16 compare_le(uint8x16 a, uint8x16 b)
    {
        return _mm_not_si128(compare_gt(a, b));
    }

    static inline mask8x16 compare_ge(uint8x16 a, uint8x16 b)
    {
        return _mm_not_si128(compare_gt(b, a));
    }

#endif

    static inline uint8x16 select(mask8x16 mask, uint8x16 a, uint8x16 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    static inline uint8x16 min(uint8x16 a, uint8x16 b)
    {
        return _mm_min_epu8(a, b);
    }

    static inline uint8x16 max(uint8x16 a, uint8x16 b)
    {
        return _mm_max_epu8(a, b);
    }

    // -----------------------------------------------------------------
    // uint16x8
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline uint16x8 set_component(uint16x8 a, u16 s)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm_insert_epi16(a, s, Index);
    }

    template <unsigned int Index>
    static inline u16 get_component(uint16x8 a)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm_extract_epi16(a, Index);
    }

    static inline uint16x8 uint16x8_zero()
    {
        return _mm_setzero_si128();
    }

    static inline uint16x8 uint16x8_set1(u16 s)
    {
        return _mm_set1_epi16(s);
    }

    static inline uint16x8 uint16x8_set8(u16 s0, u16 s1, u16 s2, u16 s3, u16 s4, u16 s5, u16 s6, u16 s7)
    {
        return _mm_setr_epi16(s0, s1, s2, s3, s4, s5, s6, s7);
    }

    static inline uint16x8 uint16x8_load_low(const u16* source)
    {
        return _mm_loadl_epi64(reinterpret_cast<__m128i const *>(source));
    }

    static inline void uint16x8_store_low(u16* dest, uint16x8 a)
    {
        _mm_storel_epi64(reinterpret_cast<__m128i *>(dest), a);
    }

    static inline uint16x8 unpacklo(uint16x8 a, uint16x8 b)
    {
        return _mm_unpacklo_epi16(a, b);
    }

    static inline uint16x8 unpackhi(uint16x8 a, uint16x8 b)
    {
        return _mm_unpackhi_epi16(a, b);
    }

    static inline uint16x8 add(uint16x8 a, uint16x8 b)
    {
        return _mm_add_epi16(a, b);
    }

    static inline uint16x8 sub(uint16x8 a, uint16x8 b)
    {
        return _mm_sub_epi16(a, b);
    }

    static inline uint16x8 mullo(uint16x8 a, uint16x8 b)
    {
        return _mm_mullo_epi16(a, b);
    }

    // saturated

    static inline uint16x8 adds(uint16x8 a, uint16x8 b)
    {
        return _mm_adds_epu16(a, b);
    }

    static inline uint16x8 subs(uint16x8 a, uint16x8 b)
    {
        return _mm_subs_epu16(a, b);
    }

    // bitwise

    static inline uint16x8 bitwise_nand(uint16x8 a, uint16x8 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline uint16x8 bitwise_and(uint16x8 a, uint16x8 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline uint16x8 bitwise_or(uint16x8 a, uint16x8 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline uint16x8 bitwise_xor(uint16x8 a, uint16x8 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline uint16x8 bitwise_not(uint16x8 a)
    {
        return _mm_not_si128(a);
    }

    // compare

#if defined(MANGO_ENABLE_XOP)

    static inline mask16x8 compare_neq(uint16x8 a, uint16x8 b)
    {
        return _mm_comneq_epu16(a, b);
    }

    static inline mask16x8 compare_lt(uint16x8 a, uint16x8 b)
    {
        return _mm_comlt_epu16(a, b);
    }

    static inline mask16x8 compare_le(uint16x8 a, uint16x8 b)
    {
        return _mm_comle_epu16(a, b);
    }

    static inline mask16x8 compare_ge(uint16x8 a, uint16x8 b)
    {
        return _mm_comge_epu16(a, b);
    }

    static inline mask16x8 compare_eq(uint16x8 a, uint16x8 b)
    {
        return _mm_comeq_epu16(a, b);
    }

    static inline mask16x8 compare_gt(uint16x8 a, uint16x8 b)
    {
        return _mm_comgt_epu16(a, b);
    }

#else

    static inline mask16x8 compare_eq(uint16x8 a, uint16x8 b)
    {
        return _mm_cmpeq_epi16(a, b);
    }

    static inline mask16x8 compare_gt(uint16x8 a, uint16x8 b)
    {
        const __m128i sign = _mm_set1_epi32(0x80008000);
        return _mm_cmpgt_epi16(_mm_xor_si128(a, sign), _mm_xor_si128(b, sign));
    }

    static inline mask16x8 compare_neq(uint16x8 a, uint16x8 b)
    {
        return _mm_not_si128(compare_eq(b, a));
    }

    static inline mask16x8 compare_lt(uint16x8 a, uint16x8 b)
    {
        return compare_gt(b, a);
    }

    static inline mask16x8 compare_le(uint16x8 a, uint16x8 b)
    {
        return _mm_not_si128(compare_gt(a, b));
    }

    static inline mask16x8 compare_ge(uint16x8 a, uint16x8 b)
    {
        return _mm_not_si128(compare_gt(b, a));
    }

#endif

    static inline uint16x8 select(mask16x8 mask, uint16x8 a, uint16x8 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline uint16x8 slli(uint16x8 a)
    {
        return _mm_slli_epi16(a, Count);
    }

    template <int Count>
    static inline uint16x8 srli(uint16x8 a)
    {
        return _mm_srli_epi16(a, Count);
    }

    template <int Count>
    static inline uint16x8 srai(uint16x8 a)
    {
        return _mm_srai_epi16(a, Count);
    }

    // shift by scalar

    static inline uint16x8 sll(uint16x8 a, int count)
    {
        return _mm_sll_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline uint16x8 srl(uint16x8 a, int count)
    {
        return _mm_srl_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline uint16x8 sra(uint16x8 a, int count)
    {
        return _mm_sra_epi16(a, _mm_cvtsi32_si128(count));
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline uint16x8 min(uint16x8 a, uint16x8 b)
    {
        return _mm_min_epu16(a, b);
    }

    static inline uint16x8 max(uint16x8 a, uint16x8 b)
    {
        return _mm_max_epu16(a, b);
    }

#else

    static inline uint16x8 min(uint16x8 a, uint16x8 b)
    {
        return _mm_select_si128(compare_gt(a, b), b, a);
    }

    static inline uint16x8 max(uint16x8 a, uint16x8 b)
    {
        return _mm_select_si128(compare_gt(a, b), a, b);
    }

#endif
    
    // -----------------------------------------------------------------
    // uint32x4
    // -----------------------------------------------------------------

    // shuffle

    template <u32 x, u32 y, u32 z, u32 w>
    static inline uint32x4 shuffle(uint32x4 v)
    {
        static_assert(x < 4 && y < 4 && z < 4 && w < 4, "Index out of range.");
        return _mm_shuffle_epi32(v, _MM_SHUFFLE(w, z, y, x));
    }

    template <>
    inline uint32x4 shuffle<0, 1, 2, 3>(uint32x4 v)
    {
        // .xyzw
        return v;
    }

    // indexed access

#if defined(MANGO_ENABLE_SSE4_1)

    template <unsigned int Index>
    static inline uint32x4 set_component(uint32x4 a, u32 s)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm_insert_epi32(a, s, Index);
    }

    template <unsigned int Index>
    static inline u32 get_component(uint32x4 a)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm_extract_epi32(a, Index);
    }

#else

    template <int Index>
    static inline uint32x4 set_component(uint32x4 a, u32 s);

    template <>
    inline uint32x4 set_component<0>(uint32x4 a, u32 x)
    {
        const __m128i b = _mm_unpacklo_epi32(_mm_set1_epi32(x), a);
        return simd128_shuffle_epi32(b, a, _MM_SHUFFLE(3, 2, 3, 0));
    }

    template <>
    inline uint32x4 set_component<1>(uint32x4 a, u32 y)
    {
        const __m128i b = _mm_unpacklo_epi32(_mm_set1_epi32(y), a);
        return simd128_shuffle_epi32(b, a, _MM_SHUFFLE(3, 2, 0, 1));
    }

    template <>
    inline uint32x4 set_component<2>(uint32x4 a, u32 z)
    {
        const __m128i b = _mm_unpackhi_epi32(_mm_set1_epi32(z), a);
        return simd128_shuffle_epi32(a, b, _MM_SHUFFLE(3, 0, 1, 0));
    }

    template <>
    inline uint32x4 set_component<3>(uint32x4 a, u32 w)
    {
        const __m128i b = _mm_unpackhi_epi32(_mm_set1_epi32(w), a);
        return simd128_shuffle_epi32(a, b, _MM_SHUFFLE(0, 1, 1, 0));
    }

    template <int Index>
    static inline u32 get_component(uint32x4 a);

    template <>
    inline u32 get_component<0>(uint32x4 a)
    {
        return _mm_cvtsi128_si32(a);
    }

    template <>
    inline u32 get_component<1>(uint32x4 a)
    {
        return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, 0x55));
    }

    template <>
    inline u32 get_component<2>(uint32x4 a)
    {
        return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, 0xaa));
    }

    template <>
    inline u32 get_component<3>(uint32x4 a)
    {
        return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, 0xff));
    }

#endif // defined(MANGO_ENABLE_SSE4_1)

    static inline uint32x4 uint32x4_zero()
    {
        return _mm_setzero_si128();
    }

    static inline uint32x4 uint32x4_set1(u32 s)
    {
        return _mm_set1_epi32(s);
    }

    static inline uint32x4 uint32x4_set4(u32 x, u32 y, u32 z, u32 w)
    {
        return _mm_setr_epi32(x, y, z, w);
    }

    static inline uint32x4 uint32x4_uload(const u32* source)
    {
        return _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
    }

    static inline void uint32x4_ustore(u32* dest, uint32x4 a)
    {
        _mm_storeu_si128(reinterpret_cast<__m128i*>(dest), a);
    }

    static inline uint32x4 uint32x4_load_low(const u32* source)
    {
        return _mm_loadl_epi64(reinterpret_cast<__m128i const *>(source));
    }

    static inline void uint32x4_store_low(u32* dest, uint32x4 a)
    {
        _mm_storel_epi64(reinterpret_cast<__m128i *>(dest), a);
    }

    static inline uint32x4 unpacklo(uint32x4 a, uint32x4 b)
    {
        return _mm_unpacklo_epi32(a, b);
    }

    static inline uint32x4 unpackhi(uint32x4 a, uint32x4 b)
    {
        return _mm_unpackhi_epi32(a, b);
    }

    static inline uint32x4 add(uint32x4 a, uint32x4 b)
    {
        return _mm_add_epi32(a, b);
    }

    static inline uint32x4 sub(uint32x4 a, uint32x4 b)
    {
        return _mm_sub_epi32(a, b);
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline uint32x4 mullo(uint32x4 a, uint32x4 b)
    {
        return _mm_mullo_epi32(a, b);
    }

#else

    static inline uint32x4 mullo(uint32x4 a, uint32x4 b)
    {
        return simd128_mullo_epi32(a, b);
    }

#endif

    // saturated

    static inline uint32x4 adds(uint32x4 a, uint32x4 b)
    {
  	    const __m128i temp = _mm_add_epi32(a, b);
  	    return _mm_or_si128(temp, _mm_cmplt_epi32(temp, a));
    }

    static inline uint32x4 subs(uint32x4 a, uint32x4 b)
    {
  	    const __m128i temp = _mm_sub_epi32(a, b);
  	    return _mm_and_si128(temp, _mm_cmpgt_epi32(a, temp));
    }

    // bitwise

    static inline uint32x4 bitwise_nand(uint32x4 a, uint32x4 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline uint32x4 bitwise_and(uint32x4 a, uint32x4 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline uint32x4 bitwise_or(uint32x4 a, uint32x4 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline uint32x4 bitwise_xor(uint32x4 a, uint32x4 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline uint32x4 bitwise_not(uint32x4 a)
    {
        return _mm_not_si128(a);
    }

    // compare

#if defined(MANGO_ENABLE_XOP)

    static inline mask32x4 compare_eq(uint32x4 a, uint32x4 b)
    {
        return _mm_comeq_epu32(a, b);
    }

    static inline mask32x4 compare_gt(uint32x4 a, uint32x4 b)
    {
        return _mm_comgt_epu32(a, b);
    }

    static inline mask32x4 compare_neq(uint32x4 a, uint32x4 b)
    {
        return _mm_comneq_epu32(a, b);
    }

    static inline mask32x4 compare_lt(uint32x4 a, uint32x4 b)
    {
        return _mm_comlt_epu32(a, b);
    }

    static inline mask32x4 compare_le(uint32x4 a, uint32x4 b)
    {
        return _mm_comle_epu32(a, b);
    }

    static inline mask32x4 compare_ge(uint32x4 a, uint32x4 b)
    {
        return _mm_comge_epu32(a, b);
    }

#else

    static inline mask32x4 compare_eq(uint32x4 a, uint32x4 b)
    {
        return _mm_cmpeq_epi32(a, b);
    }

    static inline mask32x4 compare_gt(uint32x4 a, uint32x4 b)
    {
        const __m128i sign = _mm_set1_epi32(0x80000000);
        return _mm_cmpgt_epi32(_mm_xor_si128(a, sign), _mm_xor_si128(b, sign));
    }

    static inline mask32x4 compare_neq(uint32x4 a, uint32x4 b)
    {
        return _mm_not_si128(compare_eq(b, a));
    }

    static inline mask32x4 compare_lt(uint32x4 a, uint32x4 b)
    {
        return compare_gt(b, a);
    }

    static inline mask32x4 compare_le(uint32x4 a, uint32x4 b)
    {
        return _mm_not_si128(compare_gt(a, b));
    }

    static inline mask32x4 compare_ge(uint32x4 a, uint32x4 b)
    {
        return _mm_not_si128(compare_gt(b, a));
    }

#endif

    static inline uint32x4 select(mask32x4 mask, uint32x4 a, uint32x4 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline uint32x4 slli(uint32x4 a)
    {
        return _mm_slli_epi32(a, Count);
    }

    template <int Count>
    static inline uint32x4 srli(uint32x4 a)
    {
        return _mm_srli_epi32(a, Count);
    }

    template <int Count>
    static inline uint32x4 srai(uint32x4 a)
    {
        return _mm_srai_epi32(a, Count);
    }

    // shift by scalar

    static inline uint32x4 sll(uint32x4 a, int count)
    {
        return _mm_sll_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline uint32x4 srl(uint32x4 a, int count)
    {
        return _mm_srl_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline uint32x4 sra(uint32x4 a, int count)
    {
        return _mm_sra_epi32(a, _mm_cvtsi32_si128(count));
    }

    // shift by vector

#if defined(MANGO_ENABLE_AVX2)
    
    static inline uint32x4 sll(uint32x4 a, uint32x4 count)
    {
        return _mm_sllv_epi32(a, count);
    }

    static inline uint32x4 srl(uint32x4 a, uint32x4 count)
    {
        return _mm_srlv_epi32(a, count);
    }

    static inline uint32x4 sra(uint32x4 a, uint32x4 count)
    {
        return _mm_srav_epi32(a, count);
    }

#else

    static inline uint32x4 sll(uint32x4 a, uint32x4 count)
    {
        __m128i count0 = simd128_shuffle_x0z0(count);
        __m128i count1 = _mm_srli_epi64(count, 32);
        __m128i count2 = _mm_srli_si128(count0, 8);
        __m128i count3 = _mm_srli_si128(count, 12);
        __m128i x = _mm_sll_epi32(a, count0);
        __m128i y = _mm_sll_epi32(a, count1);
        __m128i z = _mm_sll_epi32(a, count2);
        __m128i w = _mm_sll_epi32(a, count3);
        return simd128_shuffle_4x4(x, y, z, w);
    }

    static inline uint32x4 srl(uint32x4 a, uint32x4 count)
    {
        __m128i count0 = simd128_shuffle_x0z0(count);
        __m128i count1 = _mm_srli_epi64(count, 32);
        __m128i count2 = _mm_srli_si128(count0, 8);
        __m128i count3 = _mm_srli_si128(count, 12);
        __m128i x = _mm_srl_epi32(a, count0);
        __m128i y = _mm_srl_epi32(a, count1);
        __m128i z = _mm_srl_epi32(a, count2);
        __m128i w = _mm_srl_epi32(a, count3);
        return simd128_shuffle_4x4(x, y, z, w);
    }

    static inline uint32x4 sra(uint32x4 a, uint32x4 count)
    {
        __m128i count0 = simd128_shuffle_x0z0(count);
        __m128i count1 = _mm_srli_epi64(count, 32);
        __m128i count2 = _mm_srli_si128(count0, 8);
        __m128i count3 = _mm_srli_si128(count, 12);
        __m128i x = _mm_sra_epi32(a, count0);
        __m128i y = _mm_sra_epi32(a, count1);
        __m128i z = _mm_sra_epi32(a, count2);
        __m128i w = _mm_sra_epi32(a, count3);
        return simd128_shuffle_4x4(x, y, z, w);
    }

#endif

#if defined(MANGO_ENABLE_SSE4_1)

    static inline uint32x4 min(uint32x4 a, uint32x4 b)
    {
        return _mm_min_epu32(a, b);
    }

    static inline uint32x4 max(uint32x4 a, uint32x4 b)
    {
        return _mm_max_epu32(a, b);
    }

#else

    static inline uint32x4 min(uint32x4 a, uint32x4 b)
    {
        return _mm_select_si128(compare_gt(a, b), b, a);
    }

    static inline uint32x4 max(uint32x4 a, uint32x4 b)
    {
        return _mm_select_si128(compare_gt(a, b), a, b);
    }

#endif // defined(MANGO_ENABLE_SSE4_1)

    // -----------------------------------------------------------------
    // uint64x2
    // -----------------------------------------------------------------

#if defined(MANGO_ENABLE_SSE4_1)

    template <unsigned int Index>
    static inline uint64x2 set_component(uint64x2 a, u64 s)
    {
        static_assert(Index < 2, "Index out of range.");
        return _mm_insert_epi64(a, s, Index);
    }

    template <unsigned int Index>
    static inline u64 get_component(uint64x2 a)
    {
        static_assert(Index < 2, "Index out of range.");
        return _mm_extract_epi64(a, Index);
    }

#else

    template <unsigned int Index>
    static inline uint64x2 set_component(uint64x2 a, u64 s)
    {
        static_assert(Index < 2, "Index out of range.");
        const __m128i temp = simd128_cvtsi64_si128(s);
        return Index ? simd128_shuffle_epi64(a, temp, 0x00)
                     : simd128_shuffle_epi64(temp, a, 0x02);
    }

    template <unsigned int Index>
    static inline u64 get_component(uint64x2 a)
    {
        static_assert(Index < 2, "Index out of range.");
        const __m128i temp = _mm_shuffle_epi32(a, 0x44 + Index * 0xaa);
        return simd128_cvtsi128_si64(temp);
    }

#endif

    static inline uint64x2 uint64x2_zero()
    {
        return _mm_setzero_si128();
    }

    static inline uint64x2 uint64x2_set1(u64 s)
    {
        return _mm_set1_epi64x(s);
    }

    static inline uint64x2 uint64x2_set2(u64 x, u64 y)
    {
        return _mm_set_epi64x(y, x);
    }

    static inline uint64x2 unpacklo(uint64x2 a, uint64x2 b)
    {
        return _mm_unpacklo_epi64(a, b);
    }

    static inline uint64x2 unpackhi(uint64x2 a, uint64x2 b)
    {
        return _mm_unpackhi_epi64(a, b);
    }

    static inline uint64x2 add(uint64x2 a, uint64x2 b)
    {
        return _mm_add_epi64(a, b);
    }

    static inline uint64x2 sub(uint64x2 a, uint64x2 b)
    {
        return _mm_sub_epi64(a, b);
    }

    static inline uint64x2 bitwise_nand(uint64x2 a, uint64x2 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline uint64x2 bitwise_and(uint64x2 a, uint64x2 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline uint64x2 bitwise_or(uint64x2 a, uint64x2 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline uint64x2 bitwise_xor(uint64x2 a, uint64x2 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline uint64x2 bitwise_not(uint64x2 a)
    {
        return _mm_not_si128(a);
    }

    static inline uint64x2 select(mask64x2 mask, uint64x2 a, uint64x2 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline uint64x2 slli(uint64x2 a)
    {
        return _mm_slli_epi64(a, Count);
    }

    template <int Count>
    static inline uint64x2 srli(uint64x2 a)
    {
        return _mm_srli_epi64(a, Count);
    }

    // shift by scalar

    static inline uint64x2 sll(uint64x2 a, int count)
    {
        return _mm_sll_epi64(a, _mm_cvtsi32_si128(count));
    }

    static inline uint64x2 srl(uint64x2 a, int count)
    {
        return _mm_srl_epi64(a, _mm_cvtsi32_si128(count));
    }

    // -----------------------------------------------------------------
    // int8x16
    // -----------------------------------------------------------------

#if defined(MANGO_ENABLE_SSE4_1)

    template <unsigned int Index>
    static inline int8x16 set_component(int8x16 a, s8 s)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm_insert_epi8(a, s, Index);
    }

    template <unsigned int Index>
    static inline s8 get_component(int8x16 a)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm_extract_epi8(a, Index);
    }

#else

    template <unsigned int Index>
    static inline int8x16 set_component(int8x16 a, s8 s)
    {
        static_assert(Index < 16, "Index out of range.");
        u32 temp = _mm_extract_epi16(a, Index / 2);
        if (Index & 1)
            temp = (temp & 0x00ff) | uint32(s) << 8;
        else
            temp = (temp & 0xff00) | uint32(s);
        return _mm_insert_epi16(a, temp, Index / 2);
    }

    template <unsigned int Index>
    static inline s8 get_component(int8x16 a)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm_extract_epi16(a, Index / 2) >> ((Index & 1) * 8);
    }

#endif

    static inline int8x16 int8x16_zero()
    {
        return _mm_setzero_si128();
    }

    static inline int8x16 int8x16_set1(s8 s)
    {
        return _mm_set1_epi8(s);
    }

    static inline int8x16 int8x16_set16(
        s8 v0, s8 v1, s8 v2, s8 v3, s8 v4, s8 v5, s8 v6, s8 v7,
        s8 v8, s8 v9, s8 v10, s8 v11, s8 v12, s8 v13, s8 v14, s8 v15)
    {
        return _mm_setr_epi8(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
    }

    static inline int8x16 int8x16_load_low(const s8* source)
    {
        return _mm_loadl_epi64(reinterpret_cast<__m128i const *>(source));
    }

    static inline void int8x16_store_low(s8* dest, int8x16 a)
    {
        _mm_storel_epi64(reinterpret_cast<__m128i *>(dest), a);
    }

    static inline int8x16 unpacklo(int8x16 a, int8x16 b)
    {
        return _mm_unpacklo_epi8(a, b);
    }

    static inline int8x16 unpackhi(int8x16 a, int8x16 b)
    {
        return _mm_unpackhi_epi8(a, b);
    }

    static inline int8x16 add(int8x16 a, int8x16 b)
    {
        return _mm_add_epi8(a, b);
    }

    static inline int8x16 sub(int8x16 a, int8x16 b)
    {
        return _mm_sub_epi8(a, b);
    }

    // saturated

    static inline int8x16 adds(int8x16 a, int8x16 b)
    {
        return _mm_adds_epi8(a, b);
    }

    static inline int8x16 subs(int8x16 a, int8x16 b)
    {
        return _mm_subs_epi8(a, b);
    }

    static inline int8x16 abs(int8x16 a)
    {
#if defined(MANGO_ENABLE_SSSE3)
        return _mm_abs_epi8(a);
#else
        const __m128i negative = _mm_cmplt_epi16(a, _mm_setzero_si128());
        return _mm_sub_epi16(_mm_xor_si128(a, negative), negative);
#endif
    }

    static inline int8x16 neg(int8x16 a)
    {
        return _mm_sub_epi8(_mm_setzero_si128(), a);
    }

    // bitwise

    static inline int8x16 bitwise_nand(int8x16 a, int8x16 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline int8x16 bitwise_and(int8x16 a, int8x16 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline int8x16 bitwise_or(int8x16 a, int8x16 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline int8x16 bitwise_xor(int8x16 a, int8x16 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline int8x16 bitwise_not(int8x16 a)
    {
        return _mm_not_si128(a);
    }

    // compare

#if defined(MANGO_ENABLE_XOP)

    static inline mask8x16 compare_eq(int8x16 a, int8x16 b)
    {
        return _mm_comeq_epi8(a, b);
    }

    static inline mask8x16 compare_gt(int8x16 a, int8x16 b)
    {
        return _mm_comgt_epi8(a, b);
    }

    static inline mask8x16 compare_neq(int8x16 a, int8x16 b)
    {
        return _mm_comneq_epi8(a, b);
    }

    static inline mask8x16 compare_lt(int8x16 a, int8x16 b)
    {
        return _mm_comlt_epi8(a, b);
    }

    static inline mask8x16 compare_le(int8x16 a, int8x16 b)
    {
        return _mm_comle_epi8(a, b);
    }

    static inline mask8x16 compare_ge(int8x16 a, int8x16 b)
    {
        return _mm_comge_epi8(a, b);
    }

#else

    static inline mask8x16 compare_eq(int8x16 a, int8x16 b)
    {
        return _mm_cmpeq_epi8(a, b);
    }

    static inline mask8x16 compare_gt(int8x16 a, int8x16 b)
    {
        return _mm_cmpgt_epi8(a, b);
    }

    static inline mask8x16 compare_neq(int8x16 a, int8x16 b)
    {
        return _mm_not_si128(compare_eq(b, a));
    }

    static inline mask8x16 compare_lt(int8x16 a, int8x16 b)
    {
        return compare_gt(b, a);
    }

    static inline mask8x16 compare_le(int8x16 a, int8x16 b)
    {
        return _mm_not_si128(compare_gt(a, b));
    }

    static inline mask8x16 compare_ge(int8x16 a, int8x16 b)
    {
        return _mm_not_si128(compare_gt(b, a));
    }

#endif

    static inline int8x16 select(mask8x16 mask, int8x16 a, int8x16 b)
    {
        return _mm_select_si128(mask, a, b);
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline int8x16 min(int8x16 a, int8x16 b)
    {
        return _mm_min_epi8(a, b);
    }

    static inline int8x16 max(int8x16 a, int8x16 b)
    {
        return _mm_max_epi8(a, b);
    }

#else

    static inline int8x16 min(int8x16 a, int8x16 b)
    {
        return _mm_select_si128(_mm_cmpgt_epi8(a, b), b, a);
    }

    static inline int8x16 max(int8x16 a, int8x16 b)
    {
        return _mm_select_si128(_mm_cmpgt_epi8(a, b), a, b);
    }

#endif

    // -----------------------------------------------------------------
    // int16x8
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline int16x8 set_component(int16x8 a, s16 s)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm_insert_epi16(a, s, Index);
    }

    template <unsigned int Index>
    static inline s16 get_component(int16x8 a)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm_extract_epi16(a, Index);
    }

    static inline int16x8 int16x8_zero()
    {
        return _mm_setzero_si128();
    }

    static inline int16x8 int16x8_set1(s16 s)
    {
        return _mm_set1_epi16(s);
    }

    static inline int16x8 int16x8_set8(s16 v0, s16 v1, s16 v2, s16 v3, s16 v4, s16 v5, s16 v6, s16 v7)
    {
        return _mm_setr_epi16(v0, v1, v2, v3, v4, v5, v6, v7);
    }

    static inline int16x8 int16x8_load_low(const s16* source)
    {
        return _mm_loadl_epi64(reinterpret_cast<__m128i const *>(source));
    }

    static inline void int16x8_store_low(s16* dest, int16x8 a)
    {
        _mm_storel_epi64(reinterpret_cast<__m128i *>(dest), a);
    }

    static inline int16x8 unpacklo(int16x8 a, int16x8 b)
    {
        return _mm_unpacklo_epi16(a, b);
    }

    static inline int16x8 unpackhi(int16x8 a, int16x8 b)
    {
        return _mm_unpackhi_epi16(a, b);
    }

    static inline int16x8 add(int16x8 a, int16x8 b)
    {
        return _mm_add_epi16(a, b);
    }

    static inline int16x8 sub(int16x8 a, int16x8 b)
    {
        return _mm_sub_epi16(a, b);
    }

    static inline int16x8 mullo(int16x8 a, int16x8 b)
    {
        return _mm_mullo_epi16(a, b);
    }

    // saturated

    static inline int16x8 adds(int16x8 a, int16x8 b)
    {
        return _mm_adds_epi16(a, b);
    }

    static inline int16x8 subs(int16x8 a, int16x8 b)
    {
        return _mm_subs_epi16(a, b);
    }

    static inline int16x8 abs(int16x8 a)
    {
#if defined(MANGO_ENABLE_SSSE3)
        return _mm_abs_epi16(a);
#else
        __m128i mask = _mm_srai_epi16(a, 15);
        return _mm_sub_epi16(_mm_xor_si128(a, mask), mask);
#endif
    }

    static inline int16x8 neg(int16x8 a)
    {
        return _mm_sub_epi16(_mm_setzero_si128(), a);
    }

    // bitwise

    static inline int16x8 bitwise_nand(int16x8 a, int16x8 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline int16x8 bitwise_and(int16x8 a, int16x8 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline int16x8 bitwise_or(int16x8 a, int16x8 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline int16x8 bitwise_xor(int16x8 a, int16x8 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline int16x8 bitwise_not(int16x8 a)
    {
        return _mm_not_si128(a);
    }

    // compare

#if defined(MANGO_ENABLE_XOP)

    static inline mask16x8 compare_eq(int16x8 a, int16x8 b)
    {
        return _mm_comeq_epi16(a, b);
    }

    static inline mask16x8 compare_gt(int16x8 a, int16x8 b)
    {
        return _mm_comgt_epi16(a, b);
    }

    static inline mask16x8 compare_neq(int16x8 a, int16x8 b)
    {
        return _mm_comneq_epi16(a, b);
    }

    static inline mask16x8 compare_lt(int16x8 a, int16x8 b)
    {
        return _mm_comlt_epi16(a, b);
    }

    static inline mask16x8 compare_le(int16x8 a, int16x8 b)
    {
        return _mm_comle_epi16(a, b);
    }

    static inline mask16x8 compare_ge(int16x8 a, int16x8 b)
    {
        return _mm_comge_epi16(a, b);
    }

#else

    static inline mask16x8 compare_eq(int16x8 a, int16x8 b)
    {
        return _mm_cmpeq_epi16(a, b);
    }

    static inline mask16x8 compare_gt(int16x8 a, int16x8 b)
    {
        return _mm_cmpgt_epi16(a, b);
    }

    static inline mask16x8 compare_neq(int16x8 a, int16x8 b)
    {
        return _mm_not_si128(compare_eq(b, a));
    }

    static inline mask16x8 compare_lt(int16x8 a, int16x8 b)
    {
        return compare_gt(b, a);
    }

    static inline mask16x8 compare_le(int16x8 a, int16x8 b)
    {
        return _mm_not_si128(compare_gt(a, b));
    }

    static inline mask16x8 compare_ge(int16x8 a, int16x8 b)
    {
        return _mm_not_si128(compare_gt(b, a));
    }

#endif

    static inline int16x8 select(mask16x8 mask, int16x8 a, int16x8 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline int16x8 slli(int16x8 a)
    {
        return _mm_slli_epi16(a, Count);
    }

    template <int Count>
    static inline int16x8 srli(int16x8 a)
    {
        return _mm_srli_epi16(a, Count);
    }

    template <int Count>
    static inline int16x8 srai(int16x8 a)
    {
        return _mm_srai_epi16(a, Count);
    }

    // shift by scalar

    static inline int16x8 sll(int16x8 a, int count)
    {
        return _mm_sll_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline int16x8 srl(int16x8 a, int count)
    {
        return _mm_srl_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline int16x8 sra(int16x8 a, int count)
    {
        return _mm_sra_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline int16x8 min(int16x8 a, int16x8 b)
    {
        return _mm_min_epi16(a, b);
    }

    static inline int16x8 max(int16x8 a, int16x8 b)
    {
        return _mm_max_epi16(a, b);
    }

    // -----------------------------------------------------------------
    // int32x4
    // -----------------------------------------------------------------

    // shuffle

    template <u32 x, u32 y, u32 z, u32 w>
    static inline int32x4 shuffle(int32x4 v)
    {
        static_assert(x < 4 && y < 4 && z < 4 && w < 4, "Index out of range.");
        return _mm_shuffle_epi32(v, _MM_SHUFFLE(w, z, y, x));
    }

    template <>
    inline int32x4 shuffle<0, 1, 2, 3>(int32x4 v)
    {
        // .xyzw
        return v;
    }

    // indexed access

#if defined(MANGO_ENABLE_SSE4_1)

    template <unsigned int Index>
    static inline int32x4 set_component(int32x4 a, s32 s)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm_insert_epi32(a, s, Index);
    }

    template <unsigned int Index>
    static inline s32 get_component(int32x4 a)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm_extract_epi32(a, Index);
    }

#else

    template <int Index>
    static inline int32x4 set_component(int32x4 a, s32 s);

    template <>
    inline int32x4 set_component<0>(int32x4 a, s32 x)
    {
        const __m128i b = _mm_unpacklo_epi32(_mm_set1_epi32(x), a);
        return simd128_shuffle_epi32(b, a, _MM_SHUFFLE(3, 2, 3, 0));
    }

    template <>
    inline int32x4 set_component<1>(int32x4 a, s32 y)
    {
        const __m128i b = _mm_unpacklo_epi32(_mm_set1_epi32(y), a);
        return simd128_shuffle_epi32(b, a, _MM_SHUFFLE(3, 2, 0, 1));
    }

    template <>
    inline int32x4 set_component<2>(int32x4 a, s32 z)
    {
        const __m128i b = _mm_unpackhi_epi32(_mm_set1_epi32(z), a);
        return simd128_shuffle_epi32(a, b, _MM_SHUFFLE(3, 0, 1, 0));
    }

    template <>
    inline int32x4 set_component<3>(int32x4 a, s32 w)
    {
        const __m128i b = _mm_unpackhi_epi32(_mm_set1_epi32(w), a);
        return simd128_shuffle_epi32(a, b, _MM_SHUFFLE(0, 1, 1, 0));
    }

    template <int Index>
    static inline s32 get_component(int32x4 a);

    template <>
    inline s32 get_component<0>(int32x4 a)
    {
        return _mm_cvtsi128_si32(a);
    }

    template <>
    inline s32 get_component<1>(int32x4 a)
    {
        return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, 0x55));
    }

    template <>
    inline s32 get_component<2>(int32x4 a)
    {
        return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, 0xaa));
    }

    template <>
    inline s32 get_component<3>(int32x4 a)
    {
        return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, 0xff));
    }

#endif // defined(MANGO_ENABLE_SSE4_1)

    static inline int32x4 int32x4_zero()
    {
        return _mm_setzero_si128();
    }

    static inline int32x4 int32x4_set1(int s)
    {
        return _mm_set1_epi32(s);
    }

    static inline int32x4 int32x4_set4(int x, int y, int z, int w)
    {
        return _mm_setr_epi32(x, y, z, w);
    }

    static inline int32x4 int32x4_uload(const int* source)
    {
        return _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
    }

    static inline void int32x4_ustore(int* dest, int32x4 a)
    {
        _mm_storeu_si128(reinterpret_cast<__m128i*>(dest), a);
    }

    static inline int32x4 int32x4_load_low(const s32* source)
    {
        return _mm_loadl_epi64(reinterpret_cast<__m128i const *>(source));
    }

    static inline void int32x4_store_low(s32* dest, int32x4 a)
    {
        _mm_storel_epi64(reinterpret_cast<__m128i *>(dest), a);
    }

    static inline int32x4 unpacklo(int32x4 a, int32x4 b)
    {
        return _mm_unpacklo_epi32(a, b);
    }

    static inline int32x4 unpackhi(int32x4 a, int32x4 b)
    {
        return _mm_unpackhi_epi32(a, b);
    }

    static inline int32x4 abs(int32x4 a)
    {
#if defined(MANGO_ENABLE_SSSE3)
        return _mm_abs_epi32(a);
#else
        __m128i mask = _mm_srai_epi32(a, 31);
        return _mm_sub_epi32(_mm_xor_si128(a, mask), mask);
#endif
    }

    static inline int32x4 neg(int32x4 a)
    {
        return _mm_sub_epi32(_mm_setzero_si128(), a);
    }

    static inline int32x4 add(int32x4 a, int32x4 b)
    {
        return _mm_add_epi32(a, b);
    }

    static inline int32x4 sub(int32x4 a, int32x4 b)
    {
        return _mm_sub_epi32(a, b);
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline int32x4 mullo(int32x4 a, int32x4 b)
    {
        return _mm_mullo_epi32(a, b);
    }

#else

    static inline int32x4 mullo(int32x4 a, int32x4 b)
    {
        return simd128_mullo_epi32(a, b);
    }

#endif

    // saturated

    static inline int32x4 adds(int32x4 a, int32x4 b)
    {
        const __m128i v = _mm_add_epi32(a, b);
        a = _mm_srai_epi32(a, 31);
        __m128i temp = _mm_xor_si128(b, v);
        temp = _mm_xor_si128(temp, _mm_cmpeq_epi32(temp, temp));
        temp = _mm_or_si128(temp, _mm_xor_si128(a, b));
        return _mm_select_si128(_mm_cmpgt_epi32(_mm_setzero_si128(), temp), v, a);
    }

    static inline int32x4 subs(int32x4 a, int32x4 b)
    {
        const __m128i v = _mm_sub_epi32(a, b);
        a = _mm_srai_epi32(a, 31);
        __m128i temp = _mm_and_si128(_mm_xor_si128(a, b), _mm_xor_si128(a, v));
        return _mm_select_si128(_mm_cmpgt_epi32(_mm_setzero_si128(), temp), a, v);
    }

    // bitwise

    static inline int32x4 bitwise_nand(int32x4 a, int32x4 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline int32x4 bitwise_and(int32x4 a, int32x4 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline int32x4 bitwise_or(int32x4 a, int32x4 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline int32x4 bitwise_xor(int32x4 a, int32x4 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline int32x4 bitwise_not(int32x4 a)
    {
        return _mm_not_si128(a);
    }

    // compare

#if defined(MANGO_ENABLE_XOP)

    static inline mask32x4 compare_eq(int32x4 a, int32x4 b)
    {
        return _mm_comeq_epi32(a, b);
    }

    static inline mask32x4 compare_gt(int32x4 a, int32x4 b)
    {
        return _mm_comgt_epi32(a, b);
    }

    static inline mask32x4 compare_neq(int32x4 a, int32x4 b)
    {
        return _mm_comneq_epi32(a, b);
    }

    static inline mask32x4 compare_lt(int32x4 a, int32x4 b)
    {
        return _mm_comlt_epi32(a, b);
    }

    static inline mask32x4 compare_le(int32x4 a, int32x4 b)
    {
        return _mm_comle_epi32(a, b);
    }

    static inline mask32x4 compare_ge(int32x4 a, int32x4 b)
    {
        return _mm_comge_epi32(a, b);
    }

#else

    static inline mask32x4 compare_eq(int32x4 a, int32x4 b)
    {
        return _mm_cmpeq_epi32(a, b);
    }

    static inline mask32x4 compare_gt(int32x4 a, int32x4 b)
    {
        return _mm_cmpgt_epi32(a, b);
    }

    static inline mask32x4 compare_neq(int32x4 a, int32x4 b)
    {
        return _mm_not_si128(compare_eq(b, a));
    }

    static inline mask32x4 compare_lt(int32x4 a, int32x4 b)
    {
        return compare_gt(b, a);
    }

    static inline mask32x4 compare_le(int32x4 a, int32x4 b)
    {
        return _mm_not_si128(compare_gt(a, b));
    }

    static inline mask32x4 compare_ge(int32x4 a, int32x4 b)
    {
        return _mm_not_si128(compare_gt(b, a));
    }

#endif

    static inline int32x4 select(mask32x4 mask, int32x4 a, int32x4 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline int32x4 slli(int32x4 a)
    {
        return _mm_slli_epi32(a, Count);
    }

    template <int Count>
    static inline int32x4 srli(int32x4 a)
    {
        return _mm_srli_epi32(a, Count);
    }

    template <int Count>
    static inline int32x4 srai(int32x4 a)
    {
        return _mm_srai_epi32(a, Count);
    }

    // shift by scalar

    static inline int32x4 sll(int32x4 a, int count)
    {
        return _mm_sll_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline int32x4 srl(int32x4 a, int count)
    {
        return _mm_srl_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline int32x4 sra(int32x4 a, int count)
    {
        return _mm_sra_epi32(a, _mm_cvtsi32_si128(count));
    }

    // shift by vector

#if defined(MANGO_ENABLE_AVX2)

    static inline int32x4 sll(int32x4 a, uint32x4 count)
    {
        return _mm_sllv_epi32(a, count);
    }

    static inline int32x4 srl(int32x4 a, uint32x4 count)
    {
        return _mm_srlv_epi32(a, count);
    }

    static inline int32x4 sra(int32x4 a, uint32x4 count)
    {
        return _mm_srav_epi32(a, count);
    }

#else

    static inline int32x4 sll(int32x4 a, uint32x4 count)
    {
        __m128i count0 = simd128_shuffle_x0z0(count);
        __m128i count1 = _mm_srli_epi64(count, 32);
        __m128i count2 = _mm_srli_si128(count0, 8);
        __m128i count3 = _mm_srli_si128(count, 12);
        __m128i x = _mm_sll_epi32(a, count0);
        __m128i y = _mm_sll_epi32(a, count1);
        __m128i z = _mm_sll_epi32(a, count2);
        __m128i w = _mm_sll_epi32(a, count3);
        return simd128_shuffle_4x4(x, y, z, w);
    }

    static inline int32x4 srl(int32x4 a, uint32x4 count)
    {
        __m128i count0 = simd128_shuffle_x0z0(count);
        __m128i count1 = _mm_srli_epi64(count, 32);
        __m128i count2 = _mm_srli_si128(count0, 8);
        __m128i count3 = _mm_srli_si128(count, 12);
        __m128i x = _mm_srl_epi32(a, count0);
        __m128i y = _mm_srl_epi32(a, count1);
        __m128i z = _mm_srl_epi32(a, count2);
        __m128i w = _mm_srl_epi32(a, count3);
        return simd128_shuffle_4x4(x, y, z, w);
    }

    static inline int32x4 sra(int32x4 a, uint32x4 count)
    {
        __m128i count0 = simd128_shuffle_x0z0(count);
        __m128i count1 = _mm_srli_epi64(count, 32);
        __m128i count2 = _mm_srli_si128(count0, 8);
        __m128i count3 = _mm_srli_si128(count, 12);
        __m128i x = _mm_sra_epi32(a, count0);
        __m128i y = _mm_sra_epi32(a, count1);
        __m128i z = _mm_sra_epi32(a, count2);
        __m128i w = _mm_sra_epi32(a, count3);
        return simd128_shuffle_4x4(x, y, z, w);
    }

#endif

    static inline u32 pack(int32x4 s)
    {
        __m128i s16 = _mm_packs_epi32(s, s);
        __m128i s8 = _mm_packus_epi16(s16, s16);
        return _mm_cvtsi128_si32(s8);
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline int32x4 min(int32x4 a, int32x4 b)
    {
        return _mm_min_epi32(a, b);
    }

    static inline int32x4 max(int32x4 a, int32x4 b)
    {
        return _mm_max_epi32(a, b);
    }

    static inline int32x4 unpack(u32 s)
    {
        const __m128i i = _mm_cvtsi32_si128(s);
        return _mm_cvtepu8_epi32(i);
    }

#else

    static inline int32x4 min(int32x4 a, int32x4 b)
    {
        const __m128i mask = _mm_cmpgt_epi32(a, b);
        return _mm_select_si128(mask, b, a);
    }

    static inline int32x4 max(int32x4 a, int32x4 b)
    {
        const __m128i mask = _mm_cmpgt_epi32(a, b);
        return _mm_select_si128(mask, a, b);
    }

    static inline int32x4 unpack(u32 s)
    {
        const __m128i zero = _mm_setzero_si128();
        const __m128i i = _mm_cvtsi32_si128(s);
        return _mm_unpacklo_epi16(_mm_unpacklo_epi8(i, zero), zero);
    }

#endif // defined(MANGO_ENABLE_SSE4_1)

    // -----------------------------------------------------------------
    // int64x2
    // -----------------------------------------------------------------

#if defined(MANGO_ENABLE_SSE4_1)

    template <unsigned int Index>
    static inline int64x2 set_component(int64x2 a, s64 s)
    {
        static_assert(Index < 2, "Index out of range.");
        return _mm_insert_epi64(a, s, Index);
    }

    template <unsigned int Index>
    static inline s64 get_component(int64x2 a)
    {
        static_assert(Index < 2, "Index out of range.");
        return _mm_extract_epi64(a, Index);
    }

#else

    template <unsigned int Index>
    static inline int64x2 set_component(int64x2 a, s64 s)
    {
        static_assert(Index < 2, "Index out of range.");
        const __m128i temp = simd128_cvtsi64_si128(s);
        return Index ? simd128_shuffle_epi64(a, temp, 0x00)
                     : simd128_shuffle_epi64(temp, a, 0x02);
    }

    template <unsigned int Index>
    static inline s64 get_component(int64x2 a)
    {
        static_assert(Index < 2, "Index out of range.");
        const __m128i temp = _mm_shuffle_epi32(a, 0x44 + Index * 0xaa);
        return simd128_cvtsi128_si64(temp);
    }

#endif

    static inline int64x2 int64x2_zero()
    {
        return _mm_setzero_si128();
    }

    static inline int64x2 int64x2_set1(s64 s)
    {
        return _mm_set1_epi64x(s);
    }

    static inline int64x2 int64x2_set2(s64 x, s64 y)
    {
        return _mm_set_epi64x(y, x);
    }

    static inline int64x2 unpacklo(int64x2 a, int64x2 b)
    {
        return _mm_unpacklo_epi64(a, b);
    }

    static inline int64x2 unpackhi(int64x2 a, int64x2 b)
    {
        return _mm_unpackhi_epi64(a, b);
    }

    static inline int64x2 add(int64x2 a, int64x2 b)
    {
        return _mm_add_epi64(a, b);
    }

    static inline int64x2 sub(int64x2 a, int64x2 b)
    {
        return _mm_sub_epi64(a, b);
    }

    static inline int64x2 bitwise_nand(int64x2 a, int64x2 b)
    {
        return _mm_andnot_si128(a, b);
    }

    static inline int64x2 bitwise_and(int64x2 a, int64x2 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline int64x2 bitwise_or(int64x2 a, int64x2 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline int64x2 bitwise_xor(int64x2 a, int64x2 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline int64x2 bitwise_not(int64x2 a)
    {
        return _mm_not_si128(a);
    }

    static inline int64x2 select(mask64x2 mask, int64x2 a, int64x2 b)
    {
        return _mm_select_si128(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline int64x2 slli(int64x2 a)
    {
        return _mm_slli_epi64(a, Count);
    }

    template <int Count>
    static inline int64x2 srli(int64x2 a)
    {
        return _mm_srli_epi64(a, Count);
    }

    // shift by scalar

    static inline int64x2 sll(int64x2 a, int count)
    {
        return _mm_sll_epi64(a, _mm_cvtsi32_si128(count));
    }

    static inline int64x2 srl(int64x2 a, int count)
    {
        return _mm_srl_epi64(a, _mm_cvtsi32_si128(count));
    }

    // -----------------------------------------------------------------
    // mask8x16
    // -----------------------------------------------------------------

    static inline mask8x16 operator & (mask8x16 a, mask8x16 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline mask8x16 operator | (mask8x16 a, mask8x16 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline mask8x16 operator ^ (mask8x16 a, mask8x16 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline u32 get_mask(mask8x16 a)
    {
        return _mm_movemask_epi8(a);
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline bool none_of(mask8x16 a)
    {
        return _mm_testz_si128(a, a) != 0;
    }

    static inline bool any_of(mask8x16 a)
    {
        return _mm_testz_si128(a, a) == 0;
    }

    static inline bool all_of(mask8x16 a)
    {
        return _mm_testc_si128(a, _mm_cmpeq_epi8(a, a));
    }

#else

    static inline bool none_of(mask8x16 a)
    {
        return _mm_movemask_epi8(a) == 0;
    }

    static inline bool any_of(mask8x16 a)
    {
        return _mm_movemask_epi8(a) != 0;
    }

    static inline bool all_of(mask8x16 a)
    {
        return _mm_movemask_epi8(a) == 0xffff;
    }

#endif

    // -----------------------------------------------------------------
    // mask16x8
    // -----------------------------------------------------------------

    static inline mask16x8 operator & (mask16x8 a, mask16x8 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline mask16x8 operator | (mask16x8 a, mask16x8 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline mask16x8 operator ^ (mask16x8 a, mask16x8 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline u32 get_mask(mask16x8 a)
    {
        __m128i temp = _mm_packus_epi16(a, _mm_setzero_si128());
        return _mm_movemask_epi8(temp);
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline bool none_of(mask16x8 a)
    {
        return _mm_testz_si128(a, a) != 0;
    }

    static inline bool any_of(mask16x8 a)
    {
        return _mm_testz_si128(a, a) == 0;
    }

    static inline bool all_of(mask16x8 a)
    {
        return _mm_testc_si128(a, _mm_cmpeq_epi16(a, a));
    }

#else

    static inline bool none_of(mask16x8 a)
    {
        return _mm_movemask_epi8(a) == 0;
    }

    static inline bool any_of(mask16x8 a)
    {
        return _mm_movemask_epi8(a) != 0;
    }

    static inline bool all_of(mask16x8 a)
    {
        return _mm_movemask_epi8(a) == 0xffff;
    }

#endif

    // -----------------------------------------------------------------
    // mask32x4
    // -----------------------------------------------------------------

    static inline mask32x4 operator & (mask32x4 a, mask32x4 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline mask32x4 operator | (mask32x4 a, mask32x4 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline mask32x4 operator ^ (mask32x4 a, mask32x4 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline u32 get_mask(mask32x4 a)
    {
        return _mm_movemask_ps(_mm_castsi128_ps(a));
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline bool none_of(mask32x4 a)
    {
        return _mm_testz_si128(a, a) != 0;
    }

    static inline bool any_of(mask32x4 a)
    {
        return _mm_testz_si128(a, a) == 0;
    }

    static inline bool all_of(mask32x4 a)
    {
        return _mm_testc_si128(a, _mm_cmpeq_epi32(a, a));
    }

#else

    static inline bool none_of(mask32x4 a)
    {
        return _mm_movemask_ps(_mm_castsi128_ps(a)) == 0;
    }

    static inline bool any_of(mask32x4 a)
    {
        return _mm_movemask_ps(_mm_castsi128_ps(a)) != 0;
    }

    static inline bool all_of(mask32x4 a)
    {
        return _mm_movemask_ps(_mm_castsi128_ps(a)) == 0xf;
    }

#endif

    // -----------------------------------------------------------------
    // mask64x2
    // -----------------------------------------------------------------

    static inline mask64x2 operator & (mask64x2 a, mask64x2 b)
    {
        return _mm_and_si128(a, b);
    }

    static inline mask64x2 operator | (mask64x2 a, mask64x2 b)
    {
        return _mm_or_si128(a, b);
    }

    static inline mask64x2 operator ^ (mask64x2 a, mask64x2 b)
    {
        return _mm_xor_si128(a, b);
    }

    static inline u32 get_mask(mask64x2 a)
    {
        return _mm_movemask_pd(_mm_castsi128_pd(a));
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline bool none_of(mask64x2 a)
    {
        return _mm_testz_si128(a, a) != 0;
    }

    static inline bool any_of(mask64x2 a)
    {
        return _mm_testz_si128(a, a) == 0;
    }

    static inline bool all_of(mask64x2 a)
    {
        return _mm_testc_si128(a, _mm_cmpeq_epi64(a, a));
    }

#else

    static inline bool none_of(mask64x2 a)
    {
        return _mm_movemask_pd(_mm_castsi128_pd(a)) == 0;
    }

    static inline bool any_of(mask64x2 a)
    {
        return _mm_movemask_pd(_mm_castsi128_pd(a)) != 0;
    }

    static inline bool all_of(mask64x2 a)
    {
        return _mm_movemask_pd(_mm_castsi128_pd(a)) == 0x3;
    }

#endif

#undef simd128_shuffle_epi32
#undef simd128_shuffle_epi64

} // namespace simd
} // namespace mango

/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "simd.hpp"

namespace mango {
namespace simd {

    // -----------------------------------------------------------------
    // helpers
    // -----------------------------------------------------------------

    static inline __m256i _mm256_not_si256(__m256i a)
    {
        return _mm256_xor_si256(a, _mm256_cmpeq_epi8(a, a));
    }

    static inline __m256i _mm256_select_si256(__m256i mask, __m256i a, __m256i b)
    {
        return _mm256_or_si256(_mm256_and_si256(mask, a), _mm256_andnot_si256(mask, b));
    }

    // -----------------------------------------------------------------
    // uint8x32
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline uint8x32 set_component(uint8x32 a, u8 b)
    {
        static_assert(Index < 32, "Index out of range.");
        return _mm256_insert_epi8(a, b, Index);
    }

    template <unsigned int Index>
    static inline u8 get_component(uint8x32 a)
    {
        static_assert(Index < 32, "Index out of range.");
        return _mm256_extract_epi8(a, Index);
    }

    static inline uint8x32 uint8x32_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline uint8x32 uint8x32_set1(u8 s)
    {
        return _mm256_set1_epi8(s);
    }

    static inline uint8x32 unpacklo(uint8x32 a, uint8x32 b)
    {
        return _mm256_unpacklo_epi8(a, b);
    }

    static inline uint8x32 unpackhi(uint8x32 a, uint8x32 b)
    {
        return _mm256_unpackhi_epi8(a, b);
    }

    static inline uint8x32 add(uint8x32 a, uint8x32 b)
    {
        return _mm256_add_epi8(a, b);
    }

    static inline uint8x32 sub(uint8x32 a, uint8x32 b)
    {
        return _mm256_sub_epi8(a, b);
    }

    // saturated

    static inline uint8x32 adds(uint8x32 a, uint8x32 b)
    {
        return _mm256_adds_epu8(a, b);
    }

    static inline uint8x32 subs(uint8x32 a, uint8x32 b)
    {
        return _mm256_subs_epu8(a, b);
    }

    // bitwise

    static inline uint8x32 bitwise_nand(uint8x32 a, uint8x32 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline uint8x32 bitwise_and(uint8x32 a, uint8x32 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline uint8x32 bitwise_or(uint8x32 a, uint8x32 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline uint8x32 bitwise_xor(uint8x32 a, uint8x32 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline uint8x32 bitwise_not(uint8x32 a)
    {
        return _mm256_not_si256(a);
    }

    // compare

    static inline mask8x32 compare_eq(uint8x32 a, uint8x32 b)
    {
        return _mm256_cmpeq_epi8(a, b);
    }

    static inline mask8x32 compare_gt(uint8x32 a, uint8x32 b)
    {
        const __m256i sign = _mm256_set1_epi32(0x80808080);
        return _mm256_cmpgt_epi8(_mm256_xor_si256(a, sign), _mm256_xor_si256(b, sign));
    }

    static inline uint8x32 select(mask8x32 mask, uint8x32 a, uint8x32 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    static inline uint8x32 min(uint8x32 a, uint8x32 b)
    {
        return _mm256_min_epu8(a, b);
    }

    static inline uint8x32 max(uint8x32 a, uint8x32 b)
    {
        return _mm256_max_epu8(a, b);
    }

    // -----------------------------------------------------------------
    // uint16x16
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline uint16x16 set_component(uint16x16 a, u16 b)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm256_insert_epi16(a, b, Index);
    }

    template <unsigned int Index>
    static inline u16 get_component(uint16x16 a)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm256_extract_epi16(a, Index);
    }

    static inline uint16x16 uint16x16_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline uint16x16 uint16x16_set1(u16 s)
    {
        return _mm256_set1_epi16(s);
    }

    static inline uint16x16 unpacklo(uint16x16 a, uint16x16 b)
    {
        return _mm256_unpacklo_epi16(a, b);
    }

    static inline uint16x16 unpackhi(uint16x16 a, uint16x16 b)
    {
        return _mm256_unpackhi_epi16(a, b);
    }

    static inline uint16x16 add(uint16x16 a, uint16x16 b)
    {
        return _mm256_add_epi16(a, b);
    }

    static inline uint16x16 sub(uint16x16 a, uint16x16 b)
    {
        return _mm256_sub_epi16(a, b);
    }

    static inline uint16x16 mullo(uint16x16 a, uint16x16 b)
    {
        return _mm256_mullo_epi16(a, b);
    }

    // saturated

    static inline uint16x16 adds(uint16x16 a, uint16x16 b)
    {
        return _mm256_adds_epu16(a, b);
    }

    static inline uint16x16 subs(uint16x16 a, uint16x16 b)
    {
        return _mm256_subs_epu16(a, b);
    }

    // bitwise

    static inline uint16x16 bitwise_nand(uint16x16 a, uint16x16 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline uint16x16 bitwise_and(uint16x16 a, uint16x16 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline uint16x16 bitwise_or(uint16x16 a, uint16x16 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline uint16x16 bitwise_xor(uint16x16 a, uint16x16 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline uint16x16 bitwise_not(uint16x16 a)
    {
        return _mm256_not_si256(a);
    }

    // compare

    static inline mask16x16 compare_eq(uint16x16 a, uint16x16 b)
    {
        return _mm256_cmpeq_epi16(a, b);
    }

    static inline mask16x16 compare_gt(uint16x16 a, uint16x16 b)
    {
        const __m256i sign = _mm256_set1_epi32(0x80008000);
        return _mm256_cmpgt_epi16(_mm256_xor_si256(a, sign), _mm256_xor_si256(b, sign));
    }

    static inline uint16x16 select(mask16x16 mask, uint16x16 a, uint16x16 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline uint16x16 slli(uint16x16 a)
    {
        return _mm256_slli_epi16(a, Count);
    }

    template <int Count>
    static inline uint16x16 srli(uint16x16 a)
    {
        return _mm256_srli_epi16(a, Count);
    }

    template <int Count>
    static inline uint16x16 srai(uint16x16 a)
    {
        return _mm256_srai_epi16(a, Count);
    }

    // shift by scalar

    static inline uint16x16 sll(uint16x16 a, int count)
    {
        return _mm256_sll_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline uint16x16 srl(uint16x16 a, int count)
    {
        return _mm256_srl_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline uint16x16 sra(uint16x16 a, int count)
    {
        return _mm256_sra_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline uint16x16 min(uint16x16 a, uint16x16 b)
    {
        return _mm256_min_epu16(a, b);
    }

    static inline uint16x16 max(uint16x16 a, uint16x16 b)
    {
        return _mm256_max_epu16(a, b);
    }

    // -----------------------------------------------------------------
    // uint32x8
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline uint32x8 set_component(uint32x8 a, u32 b)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm256_insert_epi32(a, b, Index);
    }

    template <unsigned int Index>
    static inline u32 get_component(uint32x8 a)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm256_extract_epi32(a, Index);
    }

    static inline uint32x8 uint32x8_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline uint32x8 uint32x8_set1(u32 s)
    {
        return _mm256_set1_epi32(s);
    }

    static inline uint32x8 uint32x8_set8(u32 s0, u32 s1, u32 s2, u32 s3, u32 s4, u32 s5, u32 s6, u32 s7)
    {
        return _mm256_setr_epi32(s0, s1, s2, s3, s4, s5, s6, s7);
    }

    static inline uint32x8 uint32x8_uload(const u32* source)
    {
        return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(source));
    }

    static inline void uint32x8_ustore(u32* dest, uint32x8 a)
    {
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(dest), a);
    }

    static inline uint32x8 unpacklo(uint32x8 a, uint32x8 b)
    {
        return _mm256_unpacklo_epi32(a, b);
    }

    static inline uint32x8 unpackhi(uint32x8 a, uint32x8 b)
    {
        return _mm256_unpackhi_epi32(a, b);
    }

    static inline uint32x8 add(uint32x8 a, uint32x8 b)
    {
        return _mm256_add_epi32(a, b);
    }

    static inline uint32x8 sub(uint32x8 a, uint32x8 b)
    {
        return _mm256_sub_epi32(a, b);
    }

    static inline uint32x8 mullo(uint32x8 a, uint32x8 b)
    {
        return _mm256_mullo_epi32(a, b);
    }

    // saturated

    static inline uint32x8 adds(uint32x8 a, uint32x8 b)
    {
  	    const __m256i temp = _mm256_add_epi32(a, b);
  	    return _mm256_or_si256(temp, _mm256_cmpgt_epi32(a, temp));
    }

    static inline uint32x8 subs(uint32x8 a, uint32x8 b)
    {
  	    const __m256i temp = _mm256_sub_epi32(a, b);
  	    return _mm256_and_si256(temp, _mm256_cmpgt_epi32(a, temp));
    }

    // bitwise

    static inline uint32x8 bitwise_nand(uint32x8 a, uint32x8 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline uint32x8 bitwise_and(uint32x8 a, uint32x8 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline uint32x8 bitwise_or(uint32x8 a, uint32x8 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline uint32x8 bitwise_xor(uint32x8 a, uint32x8 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline uint32x8 bitwise_not(uint32x8 a)
    {
        return _mm256_not_si256(a);
    }

    // compare

    static inline mask32x8 compare_eq(uint32x8 a, uint32x8 b)
    {
        return _mm256_cmpeq_epi32(a, b);
    }

    static inline mask32x8 compare_gt(uint32x8 a, uint32x8 b)
    {
        const __m256i sign = _mm256_set1_epi32(0x80000000);
        return _mm256_cmpgt_epi32(_mm256_xor_si256(a, sign), _mm256_xor_si256(b, sign));
    }

    static inline uint32x8 select(mask32x8 mask, uint32x8 a, uint32x8 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline uint32x8 slli(uint32x8 a)
    {
        return _mm256_slli_epi32(a, Count);
    }

    template <int Count>
    static inline uint32x8 srli(uint32x8 a)
    {
        return _mm256_srli_epi32(a, Count);
    }

    template <int Count>
    static inline uint32x8 srai(uint32x8 a)
    {
        return _mm256_srai_epi32(a, Count);
    }

    // shift by scalar

    static inline uint32x8 sll(uint32x8 a, int count)
    {
        return _mm256_sll_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline uint32x8 srl(uint32x8 a, int count)
    {
        return _mm256_srl_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline uint32x8 sra(uint32x8 a, int count)
    {
        return _mm256_sra_epi32(a, _mm_cvtsi32_si128(count));
    }

    // shift by vector

    static inline uint32x8 sll(uint32x8 a, uint32x8 count)
    {
        return _mm256_sllv_epi32(a, count);
    }

    static inline uint32x8 srl(uint32x8 a, uint32x8 count)
    {
        return _mm256_srlv_epi32(a, count);
    }

    static inline uint32x8 sra(uint32x8 a, uint32x8 count)
    {
        return _mm256_srav_epi32(a, count);
    }

    static inline uint32x8 min(uint32x8 a, uint32x8 b)
    {
        return _mm256_min_epu32(a, b);
    }

    static inline uint32x8 max(uint32x8 a, uint32x8 b)
    {
        return _mm256_max_epu32(a, b);
    }

    // -----------------------------------------------------------------
    // uint64x4
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline uint64x4 set_component(uint64x4 a, u64 b)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm256_insert_epi64(a, b, Index);
    }

    template <unsigned int Index>
    static inline u64 get_component(uint64x4 a)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm256_extract_epi64(a, Index);
    }

    static inline uint64x4 uint64x4_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline uint64x4 uint64x4_set1(u64 s)
    {
        return _mm256_set1_epi64x(s);
    }

    static inline uint64x4 uint64x4_set4(u64 x, u64 y, u64 z, u64 w)
    {
        return _mm256_setr_epi64x(x, y, z, w);
    }

    static inline uint64x4 unpacklo(uint64x4 a, uint64x4 b)
    {
        return _mm256_unpacklo_epi64(a, b);
    }

    static inline uint64x4 unpackhi(uint64x4 a, uint64x4 b)
    {
        return _mm256_unpackhi_epi64(a, b);
    }

    static inline uint64x4 add(uint64x4 a, uint64x4 b)
    {
        return _mm256_add_epi64(a, b);
    }

    static inline uint64x4 sub(uint64x4 a, uint64x4 b)
    {
        return _mm256_sub_epi64(a, b);
    }

    static inline uint64x4 bitwise_nand(uint64x4 a, uint64x4 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline uint64x4 bitwise_and(uint64x4 a, uint64x4 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline uint64x4 bitwise_or(uint64x4 a, uint64x4 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline uint64x4 bitwise_xor(uint64x4 a, uint64x4 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline uint64x4 bitwise_not(uint64x4 a)
    {
        return _mm256_not_si256(a);
    }

    static inline uint64x4 select(mask64x4 mask, uint64x4 a, uint64x4 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline uint64x4 slli(uint64x4 a)
    {
        return _mm256_slli_epi64(a, Count);
    }

    template <int Count>
    static inline uint64x4 srli(uint64x4 a)
    {
        return _mm256_srli_epi64(a, Count);
    }

    // shift by scalar

    static inline uint64x4 sll(uint64x4 a, int count)
    {
        return _mm256_sll_epi64(a, _mm_cvtsi32_si128(count));
    }

    static inline uint64x4 srl(uint64x4 a, int count)
    {
        return _mm256_srl_epi64(a, _mm_cvtsi32_si128(count));
    }

    // -----------------------------------------------------------------
    // int8x32
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline int8x32 set_component(int8x32 a, s8 b)
    {
        static_assert(Index < 32, "Index out of range.");
        return _mm256_insert_epi8(a, b, Index);
    }

    template <unsigned int Index>
    static inline s8 get_component(int8x32 a)
    {
        static_assert(Index < 32, "Index out of range.");
        return _mm256_extract_epi8(a, Index);
    }

    static inline int8x32 int8x32_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline int8x32 int8x32_set1(s8 s)
    {
        return _mm256_set1_epi8(s);
    }

    static inline int8x32 unpacklo(int8x32 a, int8x32 b)
    {
        return _mm256_unpacklo_epi8(a, b);
    }

    static inline int8x32 unpackhi(int8x32 a, int8x32 b)
    {
        return _mm256_unpackhi_epi8(a, b);
    }

    static inline int8x32 add(int8x32 a, int8x32 b)
    {
        return _mm256_add_epi8(a, b);
    }

    static inline int8x32 sub(int8x32 a, int8x32 b)
    {
        return _mm256_sub_epi8(a, b);
    }

    // saturated

    static inline int8x32 adds(int8x32 a, int8x32 b)
    {
        return _mm256_adds_epi8(a, b);
    }

    static inline int8x32 subs(int8x32 a, int8x32 b)
    {
        return _mm256_subs_epi8(a, b);
    }

    static inline int8x32 abs(int8x32 a)
    {
        return _mm256_abs_epi8(a);
    }

    static inline int8x32 neg(int8x32 a)
    {
        return _mm256_sub_epi8(_mm256_setzero_si256(), a);
    }

    // bitwise

    static inline int8x32 bitwise_nand(int8x32 a, int8x32 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline int8x32 bitwise_and(int8x32 a, int8x32 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline int8x32 bitwise_or(int8x32 a, int8x32 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline int8x32 bitwise_xor(int8x32 a, int8x32 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline int8x32 bitwise_not(int8x32 a)
    {
        return _mm256_not_si256(a);
    }

    // compare

    static inline mask8x32 compare_eq(int8x32 a, int8x32 b)
    {
        return _mm256_cmpeq_epi8(a, b);
    }

    static inline mask8x32 compare_gt(int8x32 a, int8x32 b)
    {
        return _mm256_cmpgt_epi8(a, b);
    }

    static inline int8x32 select(mask8x32 mask, int8x32 a, int8x32 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    static inline int8x32 min(int8x32 a, int8x32 b)
    {
        return _mm256_min_epi8(a, b);
    }

    static inline int8x32 max(int8x32 a, int8x32 b)
    {
        return _mm256_max_epi8(a, b);
    }

    // -----------------------------------------------------------------
    // int16x16
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline int16x16 set_component(int16x16 a, s16 b)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm256_insert_epi16(a, b, Index);
    }

    template <unsigned int Index>
    static inline s16 get_component(int16x16 a)
    {
        static_assert(Index < 16, "Index out of range.");
        return _mm256_extract_epi16(a, Index);
    }

    static inline int16x16 int16x16_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline int16x16 int16x16_set1(s16 s)
    {
        return _mm256_set1_epi16(s);
    }

    static inline int16x16 unpacklo(int16x16 a, int16x16 b)
    {
        return _mm256_unpacklo_epi16(a, b);
    }

    static inline int16x16 unpackhi(int16x16 a, int16x16 b)
    {
        return _mm256_unpackhi_epi16(a, b);
    }

    static inline int16x16 add(int16x16 a, int16x16 b)
    {
        return _mm256_add_epi16(a, b);
    }

    static inline int16x16 sub(int16x16 a, int16x16 b)
    {
        return _mm256_sub_epi16(a, b);
    }

    static inline int16x16 mullo(int16x16 a, int16x16 b)
    {
        return _mm256_mullo_epi16(a, b);
    }

    // saturated

    static inline int16x16 adds(int16x16 a, int16x16 b)
    {
        return _mm256_adds_epi16(a, b);
    }

    static inline int16x16 subs(int16x16 a, int16x16 b)
    {
        return _mm256_subs_epi16(a, b);
    }

    static inline int16x16 abs(int16x16 a)
    {
        return _mm256_abs_epi16(a);
    }

    static inline int16x16 neg(int16x16 a)
    {
        return _mm256_sub_epi16(_mm256_setzero_si256(), a);
    }

    // bitwise

    static inline int16x16 bitwise_nand(int16x16 a, int16x16 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline int16x16 bitwise_and(int16x16 a, int16x16 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline int16x16 bitwise_or(int16x16 a, int16x16 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline int16x16 bitwise_xor(int16x16 a, int16x16 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline int16x16 bitwise_not(int16x16 a)
    {
        return _mm256_not_si256(a);
    }

    // compare

    static inline mask16x16 compare_eq(int16x16 a, int16x16 b)
    {
        return _mm256_cmpeq_epi16(a, b);
    }

    static inline mask16x16 compare_gt(int16x16 a, int16x16 b)
    {
        return _mm256_cmpgt_epi16(a, b);
    }

    static inline int16x16 select(mask16x16 mask, int16x16 a, int16x16 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline int16x16 slli(int16x16 a)
    {
        return _mm256_slli_epi16(a, Count);
    }

    template <int Count>
    static inline int16x16 srli(int16x16 a)
    {
        return _mm256_srli_epi16(a, Count);
    }

    template <int Count>
    static inline int16x16 srai(int16x16 a)
    {
        return _mm256_srai_epi16(a, Count);
    }

    // shift by scalar

    static inline int16x16 sll(int16x16 a, int count)
    {
        return _mm256_sll_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline int16x16 srl(int16x16 a, int count)
    {
        return _mm256_srl_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline int16x16 sra(int16x16 a, int count)
    {
        return _mm256_sra_epi16(a, _mm_cvtsi32_si128(count));
    }

    static inline int16x16 min(int16x16 a, int16x16 b)
    {
        return _mm256_min_epi16(a, b);
    }

    static inline int16x16 max(int16x16 a, int16x16 b)
    {
        return _mm256_max_epi16(a, b);
    }

    // -----------------------------------------------------------------
    // int32x8
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline int32x8 set_component(int32x8 a, s32 b)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm256_insert_epi32(a, b, Index);
    }

    template <unsigned int Index>
    static inline s32 get_component(int32x8 a)
    {
        static_assert(Index < 8, "Index out of range.");
        return _mm256_extract_epi32(a, Index);
    }

    static inline int32x8 int32x8_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline int32x8 int32x8_set1(s32 s)
    {
        return _mm256_set1_epi32(s);
    }

    static inline int32x8 int32x8_set8(s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s32 s6, s32 s7)
    {
        return _mm256_setr_epi32(s0, s1, s2, s3, s4, s5, s6, s7);
    }

    static inline int32x8 int32x8_uload(const s32* source)
    {
        return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(source));
    }

    static inline void int32x8_ustore(s32* dest, int32x8 a)
    {
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(dest), a);
    }

    static inline int32x8 unpacklo(int32x8 a, int32x8 b)
    {
        return _mm256_unpacklo_epi32(a, b);
    }

    static inline int32x8 unpackhi(int32x8 a, int32x8 b)
    {
        return _mm256_unpackhi_epi32(a, b);
    }

    static inline int32x8 abs(int32x8 a)
    {
        return _mm256_abs_epi32(a);
    }

    static inline int32x8 neg(int32x8 a)
    {
        return _mm256_sub_epi32(_mm256_setzero_si256(), a);
    }

    static inline int32x8 add(int32x8 a, int32x8 b)
    {
        return _mm256_add_epi32(a, b);
    }

    static inline int32x8 sub(int32x8 a, int32x8 b)
    {
        return _mm256_sub_epi32(a, b);
    }

    static inline int32x8 mullo(int32x8 a, int32x8 b)
    {
        return _mm256_mullo_epi32(a, b);
    }

    // saturated

    static inline int32x8 adds(int32x8 a, int32x8 b)
    {
        const __m256i v = _mm256_add_epi32(a, b);
        a = _mm256_srai_epi32(a, 31);
        __m256i temp = _mm256_xor_si256(b, v);
        temp = _mm256_xor_si256(temp, _mm256_cmpeq_epi32(temp, temp));
        temp = _mm256_or_si256(temp, _mm256_xor_si256(a, b));
        return _mm256_select_si256(_mm256_cmpgt_epi32(_mm256_setzero_si256(), temp), v, a);
    }

    static inline int32x8 subs(int32x8 a, int32x8 b)
    {
        const __m256i v = _mm256_sub_epi32(a, b);
        a = _mm256_srai_epi32(a, 31);
        __m256i temp = _mm256_and_si256(_mm256_xor_si256(a, b), _mm256_xor_si256(a, v));
        return _mm256_select_si256(_mm256_cmpgt_epi32(_mm256_setzero_si256(), temp), a, v);
    }

    // bitwise

    static inline int32x8 bitwise_nand(int32x8 a, int32x8 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline int32x8 bitwise_and(int32x8 a, int32x8 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline int32x8 bitwise_or(int32x8 a, int32x8 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline int32x8 bitwise_xor(int32x8 a, int32x8 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline int32x8 bitwise_not(int32x8 a)
    {
        return _mm256_not_si256(a);
    }

    // compare

    static inline mask32x8 compare_eq(int32x8 a, int32x8 b)
    {
        return _mm256_cmpeq_epi32(a, b);
    }

    static inline mask32x8 compare_gt(int32x8 a, int32x8 b)
    {
        return _mm256_cmpgt_epi32(a, b);
    }

    static inline int32x8 select(mask32x8 mask, int32x8 a, int32x8 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline int32x8 slli(int32x8 a)
    {
        return _mm256_slli_epi32(a, Count);
    }

    template <int Count>
    static inline int32x8 srli(int32x8 a)
    {
        return _mm256_srli_epi32(a, Count);
    }

    template <int Count>
    static inline int32x8 srai(int32x8 a)
    {
        return _mm256_srai_epi32(a, Count);
    }

    // shift by scalar

    static inline int32x8 sll(int32x8 a, int count)
    {
        return _mm256_sll_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline int32x8 srl(int32x8 a, int count)
    {
        return _mm256_srl_epi32(a, _mm_cvtsi32_si128(count));
    }

    static inline int32x8 sra(int32x8 a, int count)
    {
        return _mm256_sra_epi32(a, _mm_cvtsi32_si128(count));
    }

    // shift by vector

    static inline int32x8 sll(int32x8 a, uint32x8 count)
    {
        return _mm256_sllv_epi32(a, count);
    }

    static inline int32x8 srl(int32x8 a, uint32x8 count)
    {
        return _mm256_srlv_epi32(a, count);
    }

    static inline int32x8 sra(int32x8 a, uint32x8 count)
    {
        return _mm256_srav_epi32(a, count);
    }

    static inline int32x8 min(int32x8 a, int32x8 b)
    {
        return _mm256_min_epi32(a, b);
    }

    static inline int32x8 max(int32x8 a, int32x8 b)
    {
        return _mm256_max_epi32(a, b);
    }

    // -----------------------------------------------------------------
    // int64x4
    // -----------------------------------------------------------------

    template <unsigned int Index>
    static inline int64x4 set_component(int64x4 a, s64 b)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm256_insert_epi64(a, b, Index);
    }

    template <unsigned int Index>
    static inline s64 get_component(int64x4 a)
    {
        static_assert(Index < 4, "Index out of range.");
        return _mm256_extract_epi64(a, Index);
    }

    static inline int64x4 int64x4_zero()
    {
        return _mm256_setzero_si256();
    }

    static inline int64x4 int64x4_set1(s64 s)
    {
        return _mm256_set1_epi64x(s);
    }

    static inline int64x4 int64x4_set4(s64 x, s64 y, s64 z, s64 w)
    {
        return _mm256_setr_epi64x(x, y, z, w);
    }

    static inline int64x4 unpacklo(int64x4 a, int64x4 b)
    {
        return _mm256_unpacklo_epi64(a, b);
    }

    static inline int64x4 unpackhi(int64x4 a, int64x4 b)
    {
        return _mm256_unpackhi_epi64(a, b);
    }

    static inline int64x4 add(int64x4 a, int64x4 b)
    {
        return _mm256_add_epi64(a, b);
    }

    static inline int64x4 sub(int64x4 a, int64x4 b)
    {
        return _mm256_sub_epi64(a, b);
    }

    static inline int64x4 bitwise_nand(int64x4 a, int64x4 b)
    {
        return _mm256_andnot_si256(a, b);
    }

    static inline int64x4 bitwise_and(int64x4 a, int64x4 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline int64x4 bitwise_or(int64x4 a, int64x4 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline int64x4 bitwise_xor(int64x4 a, int64x4 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline int64x4 bitwise_not(int64x4 a)
    {
        return _mm256_not_si256(a);
    }

    static inline int64x4 select(mask64x4 mask, int64x4 a, int64x4 b)
    {
        return _mm256_select_si256(mask, a, b);
    }

    // shift by constant

    template <int Count>
    static inline int64x4 slli(int64x4 a)
    {
        return _mm256_slli_epi64(a, Count);
    }

    template <int Count>
    static inline int64x4 srli(int64x4 a)
    {
        return _mm256_srli_epi64(a, Count);
    }

    // shift by scalar

    static inline int64x4 sll(int64x4 a, int count)
    {
        return _mm256_sll_epi64(a, _mm_cvtsi32_si128(count));
    }

    static inline int64x4 srl(int64x4 a, int count)
    {
        return _mm256_srl_epi64(a, _mm_cvtsi32_si128(count));
    }

    // -----------------------------------------------------------------
    // mask8x32
    // -----------------------------------------------------------------

    static inline mask8x32 operator & (mask8x32 a, mask8x32 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline mask8x32 operator | (mask8x32 a, mask8x32 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline mask8x32 operator ^ (mask8x32 a, mask8x32 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline u32 get_mask(mask8x32 a)
    {
        return _mm256_movemask_epi8(a);
    }

    static inline bool none_of(mask8x32 a)
    {
        return _mm256_testz_si256(a, a) != 0;
    }

    static inline bool any_of(mask8x32 a)
    {
        return _mm256_testz_si256(a, a) == 0;
    }

    static inline bool all_of(mask8x32 a)
    {
        return _mm256_testc_si256(a, _mm256_cmpeq_epi8(a, a));
    }

    // -----------------------------------------------------------------
    // mask16x16
    // -----------------------------------------------------------------

    static inline mask16x16 operator & (mask16x16 a, mask16x16 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline mask16x16 operator | (mask16x16 a, mask16x16 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline mask16x16 operator ^ (mask16x16 a, mask16x16 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline u32 get_mask(mask16x16 a)
    {
        __m256i temp = _mm256_packus_epi16(a, _mm256_setzero_si256());
        return _mm256_movemask_epi8(temp);
    }

    static inline bool none_of(mask16x16 a)
    {
        return _mm256_testz_si256(a, a) != 0;
    }

    static inline bool any_of(mask16x16 a)
    {
        return _mm256_testz_si256(a, a) == 0;
    }

    static inline bool all_of(mask16x16 a)
    {
        return _mm256_testc_si256(a, _mm256_cmpeq_epi16(a, a));
    }

    // -----------------------------------------------------------------
    // mask32x8
    // -----------------------------------------------------------------

    static inline mask32x8 operator & (mask32x8 a, mask32x8 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline mask32x8 operator | (mask32x8 a, mask32x8 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline mask32x8 operator ^ (mask32x8 a, mask32x8 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline u32 get_mask(mask32x8 a)
    {
        return _mm256_movemask_ps(_mm256_castsi256_ps(a));
    }

    static inline bool none_of(mask32x8 a)
    {
        return _mm256_testz_si256(a, a) != 0;
    }

    static inline bool any_of(mask32x8 a)
    {
        return _mm256_testz_si256(a, a) == 0;
    }

    static inline bool all_of(mask32x8 a)
    {
        return _mm256_testc_si256(a, _mm256_cmpeq_epi32(a, a));
    }

    // -----------------------------------------------------------------
    // mask64x4
    // -----------------------------------------------------------------

    static inline mask64x4 operator & (mask64x4 a, mask64x4 b)
    {
        return _mm256_and_si256(a, b);
    }

    static inline mask64x4 operator | (mask64x4 a, mask64x4 b)
    {
        return _mm256_or_si256(a, b);
    }

    static inline mask64x4 operator ^ (mask64x4 a, mask64x4 b)
    {
        return _mm256_xor_si256(a, b);
    }

    static inline u32 get_mask(mask64x4 a)
    {
        return _mm256_movemask_pd(_mm256_castsi256_pd(a));
        
    }

    static inline bool none_of(mask64x4 a)
    {
        return _mm256_testz_si256(a, a) != 0;
    }

    static inline bool any_of(mask64x4 a)
    {
        return _mm256_testz_si256(a, a) == 0;
    }

    static inline bool all_of(mask64x4 a)
    {
        return _mm256_testc_si256(a, _mm256_cmpeq_epi64(a, a));
    }

} // namespace simd
} // namespace mango

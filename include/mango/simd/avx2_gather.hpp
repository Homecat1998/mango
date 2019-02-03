/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "simd.hpp"

namespace mango {
namespace simd {

    // 128 bit gather

    static inline float32x4 gather4(const float* address, int32x4 offset)
    {
        return _mm_i32gather_ps(reinterpret_cast<const float*>(address), offset, 4);
    }

    static inline float64x2 gather2(const double* address, int32x4 offset)
    {
        return _mm_i32gather_pd(reinterpret_cast<const double*>(address), offset, 8);
    }

    static inline uint32x4 gather4(const u32* address, int32x4 offset)
    {
        return _mm_i32gather_epi32(reinterpret_cast<const int*>(address), offset, 4);
    }

    static inline int32x4 gather4(const s32* address, int32x4 offset)
    {
        return _mm_i32gather_epi32(reinterpret_cast<const int*>(address), offset, 4);
    }

    static inline uint64x2 gather2(const u64* address, int32x4 offset)
    {
        return _mm_i32gather_epi64(reinterpret_cast<const long long*>(address), offset, 8);
    }

    static inline int64x2 gather2(const s64* address, int32x4 offset)
    {
        return _mm_i32gather_epi64(reinterpret_cast<const long long*>(address), offset, 8);
    }

    // 256 bit gather

    static inline float32x8 gather8(const float* address, int32x8 offset)
    {
        return _mm256_i32gather_ps(reinterpret_cast<const float*>(address), offset, 4);
    }

    static inline float64x4 gather4(const double* address, int32x4 offset)
    {
        return _mm256_i32gather_pd(reinterpret_cast<const double*>(address), offset, 8);
    }

    static inline uint32x8 gather8(const u32* address, int32x8 offset)
    {
        return _mm256_i32gather_epi32(reinterpret_cast<const int*>(address), offset, 4);
    }

    static inline int32x8 gather8(const s32* address, int32x8 offset)
    {
        return _mm256_i32gather_epi32(reinterpret_cast<const int*>(address), offset, 4);
    }

    static inline uint64x4 gather4(const u64* address, int32x4 offset)
    {
        return _mm256_i32gather_epi64(reinterpret_cast<const long long*>(address), offset, 8);
    }

    static inline int64x4 gather4(const s64* address, int32x4 offset)
    {
        return _mm256_i32gather_epi64(reinterpret_cast<const long long*>(address), offset, 8);
    }

    // 512 bit gather

    static inline float32x16 gather16(const float* address, int32x16 offset)
    {
        float32x16 result;
        result.lo = gather8(address, offset.lo);
        result.hi = gather8(address, offset.hi);
        return result;
    }

    static inline float64x8 gather8(const double* address, int32x8 offset)
    {
        float64x8 result;
        result.lo = gather4(address, get_low(offset));
        result.hi = gather4(address, get_high(offset));
        return result;
    }

    static inline uint32x16 gather16(const u32* address, int32x16 offset)
    {
        uint32x16 result;
        result.lo = gather8(address, offset.lo);
        result.hi = gather8(address, offset.hi);
        return result;
    }

    static inline int32x16 gather16(const s32* address, int32x16 offset)
    {
        int32x16 result;
        result.lo = gather8(address, offset.lo);
        result.hi = gather8(address, offset.hi);
        return result;
    }

    static inline uint64x8 gather8(const u64* address, int32x8 offset)
    {
        uint64x8 result;
        result.lo = gather4(address, get_low(offset));
        result.hi = gather4(address, get_high(offset));
        return result;
    }

    static inline int64x8 gather8(const s64* address, int32x8 offset)
    {
        int64x8 result;
        result.lo = gather4(address, get_low(offset));
        result.hi = gather4(address, get_high(offset));
        return result;
    }

    // 128 bit masked gather

    static inline float32x4 gather4(const float* address, int32x4 offset, float32x4 value, mask32x4 mask)
    {
        return _mm_mask_i32gather_ps(value, reinterpret_cast<const float*>(address), offset, _mm_castsi128_ps(mask), 4);
    }

    static inline float64x2 gather2(const double* address, int32x4 offset, float64x2 value, mask64x2 mask)
    {
        return _mm_mask_i32gather_pd(value, reinterpret_cast<const double*>(address), offset, _mm_castsi128_pd(mask), 8);
    }

    static inline uint32x4 gather4(const u32* address, int32x4 offset, uint32x4 value, mask32x4 mask)
    {
        return _mm_mask_i32gather_epi32(value, reinterpret_cast<const int*>(address), offset, mask, 4);
    }

    static inline int32x4 gather4(const s32* address, int32x4 offset, int32x4 value, mask32x4 mask)
    {
        return _mm_mask_i32gather_epi32(value, reinterpret_cast<const int*>(address), offset, mask, 4);
    }

    static inline uint64x2 gather2(const u64* address, int32x4 offset, uint64x2 value, mask64x2 mask)
    {
        return _mm_mask_i32gather_epi64(value, reinterpret_cast<const long long*>(address), offset, mask, 8);
    }

    static inline int64x2 gather2(const s64* address, int32x4 offset, int64x2 value, mask64x2 mask)
    {
        return _mm_mask_i32gather_epi64(value, reinterpret_cast<const long long*>(address), offset, mask, 8);
    }

    // 256 bit masked gather

    static inline float32x8 gather8(const float* address, int32x8 offset, float32x8 value, mask32x8 mask)
    {
        return _mm256_mask_i32gather_ps(value, reinterpret_cast<const float*>(address), offset, _mm256_castsi256_ps(mask), 4);
    }

    static inline float64x4 gather4(const double* address, int32x4 offset, float64x4 value, mask64x4 mask)
    {
        return _mm256_mask_i32gather_pd(value, reinterpret_cast<const double*>(address), offset, _mm256_castsi256_pd(mask), 8);
    }

    static inline uint32x8 gather8(const u32* address, int32x8 offset, uint32x8 value, mask32x8 mask)
    {
        return _mm256_mask_i32gather_epi32(value, reinterpret_cast<const int*>(address), offset, mask, 4);
    }

    static inline int32x8 gather8(const s32* address, int32x8 offset, int32x8 value, mask32x8 mask)
    {
        return _mm256_mask_i32gather_epi32(value, reinterpret_cast<const int*>(address), offset, mask, 4);
    }

    static inline uint64x4 gather4(const u64* address, int32x4 offset, uint64x4 value, mask64x4 mask)
    {
        return _mm256_mask_i32gather_epi64(value, reinterpret_cast<const long long*>(address), offset, mask, 8);
    }

    static inline int64x4 gather4(const s64* address, int32x4 offset, int64x4 value, mask64x4 mask)
    {
        return _mm256_mask_i32gather_epi64(value, reinterpret_cast<const long long*>(address), offset, mask, 8);
    }

    // 512 bit masked gather

    static inline float32x16 gather16(const float* address, int32x16 offset, float32x16 value, mask32x16 mask)
    {
        return select(mask, gather16(address, offset), value);
    }

    static inline float64x8 gather8(const double* address, int32x8 offset, float64x8 value, mask64x8 mask)
    {
        return select(mask, gather8(address, offset), value);
    }

    static inline uint32x16 gather16(const u32* address, int32x16 offset, uint32x16 value, mask32x16 mask)
    {
        return select(mask, gather16(address, offset), value);
    }

    static inline int32x16 gather16(const s32* address, int32x16 offset, int32x16 value, mask32x16 mask)
    {
        return select(mask, gather16(address, offset), value);
    }

    static inline uint64x8 gather8(const u64* address, int32x8 offset, uint64x8 value, mask64x8 mask)
    {
        return select(mask, gather8(address, offset), value);
    }

    static inline int64x8 gather8(const s64* address, int32x8 offset, int64x8 value, mask64x8 mask)
    {
        return select(mask, gather8(address, offset), value);
    }

} // namespace simd
} // namespace mango

/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include <cmath>
#include <algorithm>
#include "configure.hpp"
#include "half.hpp"

namespace mango
{

    // ----------------------------------------------------------------------------
    // byteswap
    // ----------------------------------------------------------------------------

#if defined(MANGO_COMPILER_MICROSOFT)

    static inline uint16 byteswap(uint16 v)
    {
        return _byteswap_ushort(v);
    }

    static inline uint32 byteswap(uint32 v)
    {
        return _byteswap_ulong(v);
    }

    static inline uint64 byteswap(uint64 v)
    {
        return _byteswap_uint64(v);
    }

#elif defined(MANGO_COMPILER_GCC) || defined(MANGO_COMPILER_CLANG)

    // GCC / CLANG intrinsics

    static inline uint16 byteswap(uint16 v)
    {
        return __builtin_bswap32(v << 16);
    }

    static inline uint32 byteswap(uint32 v)
    {
        return __builtin_bswap32(v);
    }

    static inline uint64 byteswap(uint64 v)
    {
        return __builtin_bswap64(v);
    }

#else

    // Generic implementation

    // These idioms are often recognized by compilers and result in bswap instruction being generated
    // but cannot be guaranteed so compiler intrinsics above are preferred when available.

    static inline uint16 byteswap(uint16 v)
    {
        return static_cast<uint16>((v << 8) | (v >> 8));
    }

    static inline uint32 byteswap(uint32 v)
    {
        return (v >> 24) | ((v >> 8) & 0x0000ff00) | ((v << 8) & 0x00ff0000) | (v << 24);
    }

    static inline uint64 byteswap(uint64 v)
    {
        // We could unroll the computation to be done with 64 bits but this approach results in
        // simpler and more efficient code (has been measured on gcc 5.4 on x86-64 and ARMv7)
        uint32 low = v & 0xffffffff;
        uint32 high = v >> 32;
        low = byteswap(low);
        high = byteswap(high);
        return (uint64(low) << 32) | high;
    }

#endif

    static inline Half byteswap(Half v)
    {
        v.u = byteswap(v.u);
        return v;
    }

    static inline Float byteswap(Float v)
    {
        v.u = byteswap(v.u);
        return v;
    }

    static inline Double byteswap(Double v)
    {
        v.u = byteswap(v.u);
        return v;
    }

    // ----------------------------------------------------------------------------
    // uint24
    // ----------------------------------------------------------------------------

    struct uint24
    {
        uint8 data[3];

        uint24()
        {
        }

        uint24(uint32 v)
        {
            *this = v;
        }

        operator uint32 () const
        {
            uint32 v = (data[2] << 16) | (data[1] << 8) | data[0];
            return v;
        }

        uint24& operator = (uint32 v)
        {
            data[0] = uint8(v);
            data[1] = uint8(v >> 8);
            data[2] = uint8(v >> 16);
            return *this;
        }
    };

    // ----------------------------------------------------------------------------
    // misc
    // ----------------------------------------------------------------------------

    static inline float ntsc_luminance(float red, float green, float blue)
    {
        return red * 0.299f + green * 0.587f + blue * 0.114f;
    }

    template <typename T>
    static inline T clamp(T value, T min, T max)
    {
        return std::min(max, std::max(min, value));
    }

    static inline constexpr uint32 byteclamp(int32 v)
    {
        // clamp value to [0, 255] range
        return v & 0xffffff00 ? uint32(((~v) >> 31) & 0xff) : uint32(v);
    }

    static inline int modulo(int value, int range)
    {
        const int remainder = value % range;
        return remainder < 0 ? remainder + range : remainder;
    }

    static inline int round_to_next(int v, int multiple)
    {
        return std::max(1, (v + (multiple - 1)) / multiple);
    }

    static inline constexpr float snap(float value, float gridsize)
    {
        return gridsize ? std::floor(0.5f + value / gridsize) * gridsize : value;
    }

    // ----------------------------------------------------------------------------
    // 32 bits
    // ----------------------------------------------------------------------------

    static inline uint32 u32_expand_msb(uint32 value)
    {
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        return value;
    }

#ifdef MANGO_ENABLE_BMI

    static inline uint32 u32_clear_lsb(uint32 value)
    {
        return _blsr_u32(value);
    }

    static inline uint32 u32_expand_lsb(uint32 value)
    {
		// NOTE: 0 expands to 0xffffffff
        return _blsmsk_u32(value);
    }

    static inline uint32 u32_lsb(uint32 value)
    {
        return _blsi_u32(value);
    }

#else

    static inline uint32 u32_clear_lsb(uint32 value)
    {
        // value:     xxxxx100000
        // value - 1: xxxxx011111
        // Subtracting one from the value borrows from the first set bit
        // that is encountered. The bitwise-and will yield 0 ONLY if the
        // the other bits in the value (marked with x) are not set.
        // The expression will evaluate to zero ONLY when a single bit is set,
        // which means the value is a power of two.
        return value & (value - 1);
    }

    static inline uint32 u32_expand_lsb(uint32 value)
    {
		// NOTE: 0 expands to 0xffffffff
        return value ^ (value - 1);
    }

    static inline uint32 u32_lsb(uint32 value)
    {
        return value & (0 - value);
    }

#endif

    static inline uint32 u32_expand_high_lsb(uint32 value)
    {
        return value | (0 - value);
    }

    static inline int u32_index_of_bit(uint32 bit)
    {
        static const uint8 table[] =
        {
            0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
            31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
        };
        return table[(bit * 0x077cb531) >> 27];
    }

    static inline int u32_index_of_expanded_bit(uint32 mask)
    {
        static const uint8 table[] =
        {
			0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
			8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
        };
        return table[(mask * 0x07c4acdd) >> 27];
    }

#ifdef MANGO_ENABLE_BMI

    static inline int u32_tzcnt(uint32 value)
    {
		// NOTE: value 0 is undefined
        return _tzcnt_u32(value);
    }

    static inline int u32_index_of_lsb(uint32 value)
    {
		// NOTE: value 0 is undefined
        return _tzcnt_u32(value);
    }

#else

    static inline int u32_tzcnt(uint32 value)
    {
		// NOTE: value 0 is undefined
        const uint32 lsb = u32_lsb(value);
        return u32_index_of_bit(lsb);
    }

    static inline int u32_index_of_lsb(uint32 value)
    {
		// NOTE: value 0 is undefined
        const uint32 lsb = u32_lsb(value);
        return u32_index_of_bit(lsb);
    }

#endif

#ifdef MANGO_ENABLE_LZCNT

    static inline int u32_lzcnt(uint32 value)
    {
		// NOTE: value 0 is undefined
        return _lzcnt_u32(value);
    }

    static inline int u32_index_of_msb(uint32 value)
    {
		// NOTE: value 0 is undefined
        return 31 - _lzcnt_u32(value);
    }

    static inline uint32 u32_msb(uint32 value)
    {
		// NOTE: value 0 is undefined
        return 1u << u32_index_of_msb(value);
    }

    static inline int u32_log2(uint32 value)
    {
		// NOTE: value 0 is undefined
        return u32_index_of_msb(value);
    }

#else

    static inline int u32_lzcnt(uint32 value)
    {
		// NOTE: value 0 is undefined
        const uint32 msb = u32_expand_msb(value);
        return 31 - u32_index_of_expanded_bit(msb);
    }

    static inline int u32_index_of_msb(uint32 value)
    {
		// NOTE: value 0 is undefined
        int base = 0;
        uint32 temp;
        temp = value & 0xffff0000; if (temp) { base |= 16; value = temp; }
        temp = value & 0xff00ff00; if (temp) { base |= 8;  value = temp; }
        temp = value & 0xf0f0f0f0; if (temp) { base |= 4;  value = temp; }
        temp = value & 0xcccccccc; if (temp) { base |= 2;  value = temp; }
        temp = value & 0xaaaaaaaa; if (temp) { base |= 1; }
        return base;
    }

    static inline uint32 u32_msb(uint32 value)
    {
		// NOTE: value 0 is undefined
        const uint32 mask = u32_expand_msb(value);
        return (mask + 1) >> 1;
    }

    static inline int u32_log2(uint32 value)
    {
		// NOTE: value 0 is undefined
        const uint32 mask = u32_expand_msb(value);
        return u32_index_of_expanded_bit(mask);
    }

#endif

    static inline uint32 u32_reverse_bits(uint32 value)
    {
        value = ((value >> 1) & 0x55555555) | ((value << 1) & 0xaaaaaaaa);
        value = ((value >> 2) & 0x33333333) | ((value << 2) & 0xcccccccc);
        value = ((value >> 4) & 0x0f0f0f0f) | ((value << 4) & 0xf0f0f0f0);
        value = ((value >> 8) & 0x00ff00ff) | ((value << 8) & 0xff00ff00);
        value = (value >> 16) | (value << 16);
        return value;
    }

#if defined(MANGO_ENABLE_POPCNT)

    static inline int u32_count_bits(uint32 value)
    {
		return _mm_popcnt_u32(value);
    }

#else

    static inline int u32_count_bits(uint32 value)
    {
        value -= (value >> 1) & 0x55555555;
        value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
        value = (value + (value >> 4)) & 0x0f0f0f0f;
        return int((value * 0x01010101) >> 24);
    }

#endif

#ifdef MANGO_ENABLE_BMI

    static inline uint32 u32_extract_bits(uint32 value, int offset, int size)
    {
        return _bextr_u32(value, offset, size);
    }

#else

    static inline uint32 u32_extract_bits(uint32 value, int offset, int size)
    {
        return (value >> offset) & ((1 << size) - 1);
    }

#endif

#ifdef MANGO_ENABLE_BMI2

    static inline uint32 u32_deinterleave_bits(uint32 value)
    {
        return _pext_u32(value, 0x55555555);
    }

    static inline uint32 u32_interleave_bits(uint32 value)
    {
        return _pdep_u32(value, 0x55555555);
    }

    static inline uint32 u32_interleave_bits(uint32 x, uint32 y)
    {
        return _pdep_u32(x, 0x55555555) | _pdep_u32(y, 0xaaaaaaaa);
    }

#else

    static inline uint32 u32_deinterleave_bits(uint32 value)
    {
        value &= 0x55555555;
        value = (value ^ (value >> 1 )) & 0x33333333;
        value = (value ^ (value >> 2 )) & 0x0f0f0f0f;
        value = (value ^ (value >> 4 )) & 0x00ff00ff;
        value = (value ^ (value >> 8 )) & 0x0000ffff;
        return value;
    }

    static inline uint32 u32_interleave_bits(uint32 value)
    {
        value = (value | (value << 8)) & 0x00ff00ff;
        value = (value | (value << 4)) & 0x0f0f0f0f;
        value = (value | (value << 2)) & 0x33333333;
        value = (value | (value << 1)) & 0x55555555;
        return value;
    }

    static inline uint32 u32_interleave_bits(uint32 x, uint32 y)
    {
        return u32_interleave_bits(x) | (u32_interleave_bits(y) << 1);
    }

#endif

    static inline uint32 u32_select(uint32 mask, uint32 a, uint32 b)
    {
        // bitwise mask ? a : b
        return (mask & (a ^ b)) ^ b;
    }

    static inline bool u32_has_zero_byte(uint32 value)
    {
	    return ((value - 0x01010101) & ~value & 0x80808080) != 0;
    }

    static inline bool u32_is_power_of_two(uint32 value)
    {
        return u32_clear_lsb(value) == 0;
    }

    static inline uint32 u32_floor_power_of_two(uint32 value)
    {
        return u32_msb(value);
    }

    static inline uint32 u32_ceil_power_of_two(uint32 value)
    {
        const uint32 mask = u32_expand_msb(value - 1);
        return mask + 1;
    }

    // ----------------------------------------------------------------------------
    // 64 bits
    // ----------------------------------------------------------------------------

    static inline uint64 u64_expand_msb(uint64 value)
    {
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        value |= value >> 32;
        return value;
    }

#ifdef MANGO_ENABLE_BMI

    static inline uint64 u64_clear_lsb(uint64 value)
    {
        return _blsr_u64(value);
    }

    static inline uint64 u64_expand_lsb(uint64 value)
    {
		// NOTE: 0 expands to 0xffffffffffffffff
        return _blsmsk_u64(value);
    }

    static inline uint64 u64_lsb(uint64 value)
    {
        return _blsi_u64(value);
    }

#else

    static inline uint64 u64_clear_lsb(uint64 value)
    {
        return value & (value - 1);
    }

    static inline uint64 u64_expand_lsb(uint64 value)
    {
		// NOTE: 0 expands to 0xffffffffffffffff
        return value ^ (value - 1);
    }

    static inline uint64 u64_lsb(uint64 value)
    {
        return value & (0 - value);
    }

#endif

    static inline uint64 u64_expand_high_lsb(uint64 value)
    {
        return value | (0 - value);
    }

    static inline int u64_index_of_bit(uint64 bit)
    {
        static const uint8 table[] =
        {
            0,  1,  2, 53,  3,  7, 54, 27,
            4, 38, 41,  8, 34, 55, 48, 28,
            62,  5, 39, 46, 44, 42, 22,  9,
            24, 35, 59, 56, 49, 18, 29, 11,
            63, 52,  6, 26, 37, 40, 33, 47,
            61, 45, 43, 21, 23, 58, 17, 10,
            51, 25, 36, 32, 60, 20, 57, 16,
            50, 31, 19, 15, 30, 14, 13, 12,
        };
        return table[(bit * 0x022fdd63cc95386du) >> 58];
    }

    static inline int u64_index_of_expanded_bit(uint64 mask)
    {
        static const uint8 table[] =
        {
            0, 47, 1, 56, 48, 27, 2, 60,
            57, 49, 41, 37, 28, 16, 3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11, 4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30, 9, 24,
            13, 18, 8, 12, 7, 6, 5, 63
        };
        return table[(mask * 0x03f79d71b4cb0a89u) >> 58];
    }

#ifdef MANGO_ENABLE_BMI

    static inline int u64_tzcnt(uint64 value)
    {
		// NOTE: value 0 is undefined
        return _tzcnt_u64(value);
    }

    static inline int u64_index_of_lsb(uint64 value)
    {
		// NOTE: value 0 is undefined
        return _tzcnt_u64(value);
    }

#else

    static inline int u64_tzcnt(uint64 value)
    {
		// NOTE: value 0 is undefined
        const uint64 lsb = u64_lsb(value);
        return u64_index_of_bit(lsb);
    }

    static inline int u64_index_of_lsb(uint64 value)
    {
		// NOTE: value 0 is undefined
        const uint64 lsb = u64_lsb(value);
        return u64_index_of_bit(lsb);
    }

#endif

#ifdef MANGO_ENABLE_LZCNT

    static inline int u64_lzcnt(uint64 value)
    {
		// NOTE: value 0 is undefined
        return _lzcnt_u64(value);
    }

    static inline int u64_index_of_msb(uint64 value)
    {
		// NOTE: value 0 is undefined
        return 63 - _lzcnt_u64(value);
    }

    static inline uint64 u64_msb(uint64 value)
    {
		// NOTE: value 0 is undefined
        return 1ull << u64_index_of_msb(value);
    }

    static inline int u64_log2(uint64 value)
    {
		// NOTE: value 0 is undefined
        return u64_index_of_msb(value);
    }

#else

    static inline int u64_lzcnt(uint64 value)
    {
		// NOTE: value 0 is undefined
        const uint64 msb = u64_expand_msb(value);
        return 63 - u64_index_of_expanded_bit(msb);
    }

    static inline int u64_index_of_msb(uint64 value)
    {
		// NOTE: value 0 is undefined
        const uint64 msb = u64_expand_msb(value);
        return u64_index_of_expanded_bit(msb);
    }

    static inline uint64 u64_msb(uint64 value)
    {
		// NOTE: value 0 is undefined
        const uint64 mask = u64_expand_msb(value);
        return (mask + 1) >> 1;
    }

    static inline int u64_log2(uint64 value)
    {
		// NOTE: value 0 is undefined
        const uint64 mask = u64_expand_msb(value);
        return u64_index_of_expanded_bit(mask);
    }

#endif

    static inline uint64 u64_reverse_bits(uint64 value)
    {
#if defined(MANGO_CPU_64BIT)
        value = ((value >>  1) & 0x5555555555555555) | ((value <<  1) & 0xaaaaaaaaaaaaaaaa);
        value = ((value >>  2) & 0x3333333333333333) | ((value <<  2) & 0xcccccccccccccccc);
        value = ((value >>  4) & 0x0f0f0f0f0f0f0f0f) | ((value <<  4) & 0xf0f0f0f0f0f0f0f0);
        value = ((value >>  8) & 0x00ff00ff00ff00ff) | ((value <<  8) & 0xff00ff00ff00ff00);
        value = ((value >> 16) & 0x0000ffff0000ffff) | ((value << 16) & 0xffff0000ffff0000);
        value = ( value >> 32)                       | ( value << 32);
        return value;
#else
        uint32 low = value & 0xffffffff;
        uint32 high = value >> 32;
        low = u32_reverse_bits(low);
        high = u32_reverse_bits(high);
        return (static_cast<uint64>(low) << 32) | high;
#endif
    }

#if defined(MANGO_ENABLE_POPCNT)

    static inline int u64_count_bits(uint64 value)
    {
    #if defined(MANGO_CPU_64BIT)
        return static_cast<int>(_mm_popcnt_u64(value));
    #else
        // popcnt_u64 is invalid instruction in 32 bit legacy mode
        uint32 low = value & 0xffffffff;
        uint32 high = value >> 32;
        return _mm_popcnt_u32(low) + _mm_popcnt_u32(high);
    #endif
    }

#else

    static inline int u64_count_bits(uint64 value)
    {
        const uint64 c = 0x3333333333333333u;
        value -= (value >> 1) & 0x5555555555555555u;
        value = (value & c) + ((value >> 2) & c);
        value = (value + (value >> 4)) & 0x0f0f0f0f0f0f0f0fu;
        return int((value * 0x0101010101010101u) >> 56);
    }

#endif

#ifdef MANGO_ENABLE_BMI

    static inline uint64 u64_extract_bits(uint64 value, int offset, int size)
    {
        return _bextr_u64(value, offset, size);
    }

#else

    static inline uint64 u64_extract_bits(uint64 value, int offset, int size)
    {
        return (value >> offset) & ((1 << size) - 1);
    }

#endif

#ifdef MANGO_ENABLE_BMI2

    static inline uint32 u64_deinterleave_bits(uint64 value)
    {
        return uint32(_pext_u64(value, 0x5555555555555555));
    }

    static inline uint64 u64_interleave_bits(uint64 value)
    {
        return _pdep_u64(value, 0x5555555555555555);
    }

    static inline uint64 u64_interleave_bits(uint64 x, uint64 y)
    {
        return _pdep_u64(x, 0x5555555555555555) | _pdep_u64(y, 0xaaaaaaaaaaaaaaaa);
    }

#else

    static inline uint32 u64_deinterleave_bits(uint64 value)
    {
        value &= 0x5555555555555555;
        value = (value ^ (value >> 1 )) & 0x3333333333333333;
        value = (value ^ (value >> 2 )) & 0x0f0f0f0f0f0f0f0f;
        value = (value ^ (value >> 4 )) & 0x00ff00ff00ff00ff;
        value = (value ^ (value >> 8 )) & 0x0000ffff0000ffff;
        value = (value ^ (value >> 16)) & 0x00000000ffffffff;
        return uint32(value);
    }

    static inline uint64 u64_interleave_bits(uint64 value)
    {
        value = (value | (value << 16)) & 0x0000ffff0000ffff;
        value = (value | (value <<  8)) & 0x00ff00ff00ff00ff;
        value = (value | (value <<  4)) & 0x0f0f0f0f0f0f0f0f;
        value = (value | (value <<  2)) & 0x3333333333333333;
        value = (value | (value <<  1)) & 0x5555555555555555;
        return value;
    }

    static inline uint64 u64_interleave_bits(uint64 x, uint64 y)
    {
        return u64_interleave_bits(x) | (u64_interleave_bits(y) << 1);
    }

#endif

    static inline uint64 u64_select(uint64 mask, uint64 a, uint64 b)
    {
        // bitwise mask ? a : b
        return (mask & (a ^ b)) ^ b;
    }

    static inline bool u64_has_zero_byte(uint64 value)
    {
	    return (~value & (value - 0x0101010101010101) & 0x8080808080808080) != 0;
    }

    static inline bool u64_is_power_of_two(uint64 value)
    {
        return u64_clear_lsb(value) == 0;
    }

    static inline uint64 u64_floor_power_of_two(uint64 value)
    {
        return u64_msb(value);
    }

    static inline uint64 u64_ceil_power_of_two(uint64 value)
    {
        const uint64 mask = u64_expand_msb(value - 1);
        return mask + 1;
    }

} // namespace mango

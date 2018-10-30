/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
/*
    Based on Half/Float conversion code by Fabian "ryg" Giesen.
*/
#pragma once

#include "configure.hpp"

namespace mango
{

    union Double
    {
        enum
        {
            SIGN = 1,
            EXPONENT = 11,
            MANTISSA = 52,
            BIAS = 1023
        };

        uint64 u;
        double f;
        struct
        {
            uint64 mantissa : MANTISSA;
            uint64 exponent : EXPONENT;
            uint64 sign : SIGN;
        };

        Double()
        {
        }

        explicit Double(uint64 sign, uint64 exponent, uint64 mantissa)
        : mantissa(mantissa), exponent(exponent), sign(sign)
        {
        }

        explicit Double(uint64 bits)
        : u(bits)
        {
        }

        Double(double s)
        : f(s)
        {
        }

        ~Double()
        {
        }

        Double& operator = (double s)
        {
            f = s;
            return *this;
        }

        operator double () const
        {
            return f;
        }
    };

    union Float
    {
        enum
        {
            SIGN = 1,
            EXPONENT = 8,
            MANTISSA = 23,
            BIAS = 127
        };

        uint32 u;
        float f;
        struct
        {
            uint32 mantissa : MANTISSA;
            uint32 exponent : EXPONENT;
            uint32 sign : SIGN;
        };

        Float()
        {
        }

        explicit Float(uint32 sign, uint32 exponent, uint32 mantissa)
        : mantissa(mantissa), exponent(exponent), sign(sign)
        {
        }

        explicit Float(uint32 bits)
        : u(bits)
        {
        }

        Float(float s)
        : f(s)
        {
        }

        ~Float()
        {
        }

        Float& operator = (float s)
        {
            f = s;
            return *this;
        }

        operator float () const
        {
            return f;
        }
    };

    template <int SIGN, int EXPONENT, int MANTISSA>
    uint32 packFloat(const Float& value)
    {
        const Float infty(0, (1 << EXPONENT) - 1, 0);
        const Float magic(0, (1 << (EXPONENT - 1)) - 1, 0);

        uint32 result = 0;

        Float temp(value);
        temp.sign = 0;

        if (temp.exponent == (1 << Float::EXPONENT) - 1)
        {
            // Inf / NaN
            result = ((1 << EXPONENT) - 1) << MANTISSA;
            result |= temp.mantissa ? temp.mantissa >> (Float::MANTISSA - MANTISSA) : 0; // Nan -> qNaN, Inf -> Inf
        }
        else
        {
            // (De)Normalized number or zero
            temp.u &= ~((1 << (Float::MANTISSA - MANTISSA - 1)) - 1);
            temp.f *= magic.f;
            temp.u += (1 << (Float::MANTISSA - MANTISSA - 1)); // Rounding bias

            if (temp.u > infty.u)
            {
                // Clamp to signed Infinity
                temp.u = infty.u;
            }

            result = temp.u >> (Float::MANTISSA - MANTISSA);
        }

        result |= ((value.sign & SIGN) << (EXPONENT + MANTISSA));

        return result;
    }

    template <uint32 SIGN, uint32 EXPONENT, uint32 MANTISSA>
    Float unpackFloat(uint32 sign, uint32 exponent, uint32 mantissa)
    {
        const int bias = (1 << (EXPONENT - 1)) - 1;
        const Float magic(0, Float::BIAS - 1, 0);

        Float result;

        if (!exponent)
        {
            // Zero / Denormal
            result.u = magic.u + mantissa;
            result.f -= magic.f;
        }
        else
        {
            result.mantissa = mantissa << (Float::MANTISSA - MANTISSA);

            if (exponent == (1 << EXPONENT) - 1)
            {
                // Inf / NaN
                result.exponent = (1 << Float::EXPONENT) - 1;
            }
            else
            {
                result.exponent = Float::BIAS - bias + exponent;
            }
        }

        result.sign = sign & SIGN;

        return result;
    }

    union Half
    {
        enum
        {
            SIGN = 1,
            EXPONENT = 5,
            MANTISSA = 10,
            BIAS = 15
        };

        uint16 u;
        struct
        {
            uint16 mantissa : MANTISSA;
            uint16 exponent : EXPONENT;
            uint16 sign : SIGN;
        };

        Half()
        {
        }

        explicit Half(uint16 sign, uint16 exponent, uint16 mantissa)
        : mantissa(mantissa), exponent(exponent), sign(sign)
        {
        }

        explicit Half(uint16 bits)
        : u(bits)
        {
        }

        Half(float s)
        {
            *this = s;
        }

        ~Half()
        {
        }

        Half& operator = (float s)
        {
            u = uint16(packFloat<SIGN, EXPONENT, MANTISSA>(s));
            return *this;
        }

        operator float () const
        {
            Float result = unpackFloat<SIGN, EXPONENT, MANTISSA>(sign, exponent, mantissa);
            return result;
        }
    };

    // conversions

    static inline Half f32_to_f16(float f)
    {
        return Half(f);
    }

    static inline float f16_to_f32(Half h)
    {
        return float(h);
    }

    static inline double u32_to_f64(uint32 i)
    {
        const double bias = (1ll << 52) * 1.5;
        Double x(uint64(0x4338000000000000UL | i));
        return x.f - bias;
    }

    static inline uint32 f64_to_u32(double d)
    {
        const double bias = (1ll << 52) * 1.5;
        Double x = d + bias;
        return uint32(x.u);
    }

    // floating-point types

    using float16 = Half;
    using float32 = float;
    using float64 = double;

} // namespace mango

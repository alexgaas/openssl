#pragma once

#include <string>
#include <sstream>

#include "holders/bn.h"

namespace OpenSsl {
    class BigInteger {
        BigInteger() = default;

        explicit BigInteger(BIGNUM* impl) noexcept
            : Impl_(impl)
        {
        }

        static int Compare(const BigInteger& a, const BigInteger& b) noexcept;

    public:
        BigInteger(BigInteger&& other) noexcept = default;
        BigInteger& operator=(BigInteger&& other) noexcept = default;

        ~BigInteger() noexcept = default;

        static BigInteger FromULong(uint64_t value);
        static BigInteger FromRegion(const void* ptr, size_t len);

        const BIGNUM* Impl() const noexcept {
            return static_cast<const BIGNUM*>(Impl_);
        }

        BIGNUM* Impl() noexcept {
            return static_cast<BIGNUM*>(Impl_);
        }

        void Swap(BigInteger& other) noexcept {
            Impl_.Swap(other.Impl_);
        }

        friend bool operator==(const BigInteger& a, const BigInteger& b) noexcept {
            return Compare(a, b) == 0;
        }

        friend bool operator!=(const BigInteger& a, const BigInteger& b) noexcept {
            return !(a == b);
        }

        size_t NumBytes() const noexcept;
        size_t ToRegion(void* to) const noexcept;

        std::string ToDecimalString() const;

    private:
        Bignum Impl_;
    };
}

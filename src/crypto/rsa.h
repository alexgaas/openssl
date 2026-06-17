#pragma once
#include "holders/rsa.h"

namespace OpenSsl {
    class BigInteger;

    namespace Rsa {
        class PublicKey {
        public:
            PublicKey(PublicKey&& other) noexcept = default;
            PublicKey& operator=(PublicKey&& other) noexcept = default;

            PublicKey(const BigInteger& e, const BigInteger& n);
            ~PublicKey() noexcept = default;

            size_t OutputLength() const noexcept;

            BigInteger EncryptNoPad(const BigInteger& src) const;
            size_t EncryptNoPad(void* dst, const void* src, size_t size) const;

            void Swap(PublicKey& other) noexcept {
                Key_.Swap(other.Key_);
            }

        private:
            RsaKey Key_;
        };
    };
}

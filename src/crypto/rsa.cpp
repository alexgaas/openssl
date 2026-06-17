#include "rsa.h"
#include <cstddef>
#include <stdexcept>

#include "big_integer/big_integer.h"
#include "util/buffer.h"

#include <openssl/rsa.h>

#include "holders/bn.h"

using namespace OpenSsl;
using namespace OpenSsl::Rsa;

PublicKey::PublicKey(const BigInteger& e, const BigInteger& n)
{
    Bignum n_copy(BN_dup(n.Impl()));
    Bignum e_copy(BN_dup(e.Impl()));

    if (!n_copy || !e_copy) {
        throw std::runtime_error("BN_dup failed");
    }

    if (RSA_set0_key(static_cast<RSA*>(Key_), n_copy.Get(), e_copy.Get(), nullptr) != 1) {
        throw std::runtime_error("RSA_set0_key failed");
    }

    // Ownership successfully transferred to Key_
    n_copy.Release();
    e_copy.Release();
}

size_t PublicKey::OutputLength() const noexcept {
    return RSA_size(static_cast<const RSA*>(Key_));
}

size_t PublicKey::EncryptNoPad(void* dst, const void* src, size_t size) const {
    int len = RSA_public_encrypt(static_cast<int>(size), 
                                 static_cast<const uint8_t *>(src), 
                                 static_cast<uint8_t *>(dst), 
                                 static_cast<RSA*>(Key_), 
                                 RSA_NO_PADDING);

    if (len < 0) {
        throw std::runtime_error("RSA_public_encrypt failed");
    }

    return static_cast<size_t>(len);
}

BigInteger PublicKey::EncryptNoPad(const BigInteger& src) const {
    const auto len = OutputLength();
    Buffer src_buf(len);
    Buffer dst_buf(len);

    // RSA_NO_PADDING expects the input to be the same size as the RSA key
    // We need to pad the input with zeros if it's smaller
    size_t src_bytes = src.NumBytes();
    if (src_bytes > len) {
        throw std::runtime_error("Input too large for RSA key");
    }

    src.ToRegion(static_cast<uint8_t*>(src_buf.Data()) + (len - src_bytes));
    
    size_t encrypted_bytes = EncryptNoPad(dst_buf.Data(), src_buf.Data(), len);
    return BigInteger::FromRegion(dst_buf.Data(), encrypted_bytes);
}

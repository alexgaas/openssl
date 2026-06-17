#include "big_integer.h"
#include <string>

#include <openssl/bn.h>

using namespace OpenSsl;

BigInteger BigInteger::FromULong(uint64_t value) {
    BigInteger result;
    BN_set_word(result.Impl(), value);
    return result;
}

BigInteger BigInteger::FromRegion(const void* ptr, size_t len) {
    auto result = BN_bin2bn(static_cast<const uint8_t*>(ptr), static_cast<int>(len), nullptr);
    return BigInteger(result);
}

int BigInteger::Compare(const BigInteger& a, const BigInteger& b) noexcept {
    return BN_cmp(a.Impl(), b.Impl());
}

size_t BigInteger::NumBytes() const noexcept {
    return BN_num_bytes(Impl());
}

size_t BigInteger::ToRegion(void* to) const noexcept {
    return BN_bn2bin(Impl(), static_cast<unsigned char *>(to));
}

std::string BigInteger::ToDecimalString() const {
    auto res = BN_bn2dec(Impl());
    if (!res) {
        return {};
    }
    std::string result(res);
    OPENSSL_free(res);
    return result;
}

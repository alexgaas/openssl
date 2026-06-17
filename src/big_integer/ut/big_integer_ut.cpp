#include "big_integer/big_integer.h"
#include <gtest/gtest.h>

using namespace OpenSsl;

TEST(BigInteger, FromULong) {
    auto bi = BigInteger::FromULong(12345);
    EXPECT_EQ(bi.ToDecimalString(), "12345");
}

TEST(BigInteger, FromRegion) {
    uint8_t data[] = { 0x01, 0x02, 0x03 };
    auto bi = BigInteger::FromRegion(data, sizeof(data));
    // 0x010203 = 66051
    EXPECT_EQ(bi.ToDecimalString(), "66051");
}

TEST(BigInteger, Move) {
    auto bi1 = BigInteger::FromULong(12345);
    auto bi2 = std::move(bi1);
    EXPECT_EQ(bi2.ToDecimalString(), "12345");
    // bi1's Bignum holder now contains nullptr
    EXPECT_EQ(bi1.Impl(), nullptr);
}

TEST(BigInteger, Swap) {
    auto bi1 = BigInteger::FromULong(123);
    auto bi2 = BigInteger::FromULong(456);
    bi1.Swap(bi2);
    EXPECT_EQ(bi1.ToDecimalString(), "456");
    EXPECT_EQ(bi2.ToDecimalString(), "123");
}

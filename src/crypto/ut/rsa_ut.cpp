#include "crypto/rsa.h"
#include "big_integer/big_integer.h"
#include <gtest/gtest.h>
#include <openssl/bn.h>

#include "holders/bn.h"

using namespace OpenSsl;
using namespace OpenSsl::Rsa;

TEST(Rsa, EncryptDecryptNoPad) {
    // RSA parameters: p=61, q=53, n=3233, e=17
    auto e = BigInteger::FromULong(17);
    auto n = BigInteger::FromULong(3233);
    
    PublicKey pk(e, n);
    
    // Message m = 65
    auto m = BigInteger::FromULong(65);
    
    // Encrypt
    auto c = pk.EncryptNoPad(m);
    
    // Expected result: c = m^e mod n
    // 65^17 mod 3233 = 2790
    
    // Use Bignum and BnCtx holders to verify the expected value
    Bignum res;
    BnCtx ctx;
    
    Bignum bn_m(BN_new());
    Bignum bn_e(BN_new());
    Bignum bn_n(BN_new());
    
    BN_set_word(bn_m.Get(), 65);
    BN_set_word(bn_e.Get(), 17);
    BN_set_word(bn_n.Get(), 3233);
    
    BN_mod_exp(res.Get(), bn_m.Get(), bn_e.Get(), bn_n.Get(), ctx.Get());
    
    char* expected_str = BN_bn2dec(res.Get());
    EXPECT_EQ(c.ToDecimalString(), std::string(expected_str));
    
    OPENSSL_free(expected_str);
}

TEST(Rsa, PublicKeyCreation) {
    auto e = BigInteger::FromULong(65537);
    auto n = BigInteger::FromULong(3233);
    
    EXPECT_NO_THROW({
        PublicKey pk(e, n);
        EXPECT_GT(pk.OutputLength(), 0);
    });
}

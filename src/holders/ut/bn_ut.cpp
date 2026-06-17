#include "holders/bn.h"
#include <gtest/gtest.h>

TEST(Bn, Ctx) {
    OpenSsl::BnCtx ctx;
    EXPECT_TRUE(ctx);
}

TEST(Bn, Bignum) {
    OpenSsl::Bignum num;
    EXPECT_TRUE(num);
}

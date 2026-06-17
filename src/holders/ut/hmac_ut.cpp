#include "holders/hmac.h"
#include <gtest/gtest.h>

TEST(Hmac, Ctx) {
    OpenSsl::HmacCtx ctx;
    EXPECT_TRUE(ctx);
}
#include <gtest/gtest.h>

#include "util/base64.h"

TEST(Base64, DecodeString) {
    const std::string bs = "UHVibGljIGtleQ==";

    const auto out = OpenSsl::base64_decode(bs, false);

    EXPECT_EQ(out, "Public key");
};

TEST(Base64, DecodeUrl) {
    const std::string bs = "aHR0cHM6Ly9nb29nbGUuY29t";

    const auto out = OpenSsl::base64_decode(bs, true);

    EXPECT_EQ(out, "https://google.com");
};
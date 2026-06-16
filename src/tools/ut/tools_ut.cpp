#include <gtest/gtest.h>

#include "tools/tools.h"

TEST(Init, CreateEvpKey) {
    OpenSsl::Initialize();

    const auto s = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuuE5vs7J4exsVhWzWRbQ2y1niuQn5ey/"
                   "ufhlQraIx+6iAbl2r2YhfLBPIvmk5NIeOHp2S2hplG2f4ROrtj4iQBFhXzj7H0QxnZvFJAtiV+GU"
                   "bI+iTBNdFYl2Joxp3ztbCxF4jf471INRUuk+/AuMXi2R0h3KPBvknelb9cE49n3Oa2L8J4IOVeL8"
                   "XrqaJ2YImaDrYvUNI0qPUtPrT/L2St0Yf8adyP5QIsGGXCWM0SfAJFF4Bvi5FIKrZg4MciRFSOA/"
                   "r5t4uPw+UVQgAVYVI6JXPcEyIPvm8Dd72oBXvdkS4GCx04r+PmQg2m/0PO3gcRKDAKV8s0CM9IM+"
                   "maYmawIDAQAB";
    const OpenSsl::TBase64String base64_string(s);

    const auto key = OpenSsl::CreateEvpKey(base64_string);
    EXPECT_TRUE(key.has_value());

    OpenSsl::Uninitialize();
}

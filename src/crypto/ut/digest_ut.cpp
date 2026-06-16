#include <gtest/gtest.h>
#include "crypto/sha1_digest.h"
#include <tools/tools.h>

TEST(Sha1Digest, Verify) {
    OpenSsl::Initialize();

    const auto s = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEArzMiN2OJ9RHVzi2yp+5UA9t1iDRd1r+p"
                   "z8XSKNjIZeE6fVNrzRLRgifpHmjS9MKEMPCI0xpfndkj4jWiS+AcA4E5skN0Vs4zglRSofA6vGaP"
                   "lnj6a/d0ZnFm3EgWYfb2RW9t+ge3JLBUr2ci8GdTffYRjZQjG2zm/ZnbJGlRF5C2MW6OPPF8rYyc"
                   "VZY7ryTvzPWFicSiHOQCXCWVBysN/3+JqDncojxi+sh0frYEEI2kFAKgBeu7YbmRKzOml1tcL1UT"
                   "b9fTq6bfrdQmCd2JmdlmPM8PCJoLdjL4iKvtmo4ID72tTQHfx1rwstBZsD+UyaH5/HtUzRNQMPqw"
                   "aRzaUwIDAQAB";
    const OpenSsl::TBase64String base64_string(s);

    const auto key = OpenSsl::CreateEvpKey(base64_string);
    ASSERT_TRUE(key.has_value());

    OpenSsl::TSha1Digest sha1Digest(key);
    ASSERT_TRUE(sha1Digest.IsInitilized());

    const OpenSsl::TBinaryString message{"test message"};
    EXPECT_TRUE(sha1Digest.Update(message));

    const auto sig = "KyUZmRABhBqOry/Af2bV+EgmvRI08xZiTeoqr5K5yN9X3gg289/ZCkzD+D6mBZV7NeEi7COS8nkh"
                     "A9JpezuooS57YcgsDET+KJHhXg+Gw6offEO7u7dVT6LwwhbfP6bNHOFciy5xtR/bde90L2Z5sWlt"
                     "u55mcNJBEHvrj/saFNvu7kHPCrhG4gwvipaidbR2pYp7SMtBnX9LFN4vJsQfYntxhxjnpi3u4rxv"
                     "VJfiV1HT+HIFenYlhvqD/Z4VtlCKQ1IldXAgy44RQTWHRVMdVGLNiVNGRRapbEzrhnFZGsK4mQ8G"
                     "/BHxoOg+FcEmYhJGkH4VQ2SV/XtcA/DeG/6qOg==";
    const OpenSsl::TBase64String signature(sig);

    EXPECT_TRUE(sha1Digest.Verify(signature));

    OpenSsl::Uninitialize();
}

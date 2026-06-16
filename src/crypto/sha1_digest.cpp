#include <crypto/sha1_digest.h>

#include <openssl/evp.h>
#include <util/base64.h>

namespace OpenSsl
{
    TSha1Digest::TSha1Digest(const std::optional<Poco::Crypto::EVPPKey>& publicKey)
        : TDigest("SHA1")
        , Initialized(false)
        , PublicKey(publicKey) {
        if (PublicKey) {
            Initialized = EVP_DigestVerifyInit(GetContext(), nullptr, GetDigest(), nullptr, PublicKey->operator EVP_PKEY*()) == 1;
        }
    }

    bool TSha1Digest::IsInitilized() const {
        return Initialized;
    }

    bool TSha1Digest::Update(const TBinaryString& data) const {
        return IsInitilized()
            ? EVP_DigestVerifyUpdate(GetContext(), data.Value.c_str(), data.Value.size()) == 1
            : false;
    }

    bool TSha1Digest::Verify(const TBase64String& signature) const {
        return Verify(TBinaryString{base64_decode(signature.Value)});
    }

    bool TSha1Digest::Verify(const TBinaryString& signature) const {
        const auto signaturePointer = reinterpret_cast<const unsigned char*>(signature.Value.c_str());
        return IsInitilized()
            ? EVP_DigestVerifyFinal(GetContext(), signaturePointer, signature.Value.size()) == 1
            : false;
    }

}

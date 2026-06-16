#pragma once

#include <crypto/digest.h>
#include <util/types.h>

#include <optional>
#include <Poco/Crypto/EVPPKey.h>

namespace OpenSsl
{

    class TSha1Digest: public TDigest
    {
    public:
        TSha1Digest(const std::optional<Poco::Crypto::EVPPKey>& publicKey);

        bool IsInitilized() const;

        bool Update(const TBinaryString& data) const;

        bool Verify(const TBase64String& signature) const;
        bool Verify(const TBinaryString& signature) const;

    private:
        bool Initialized;
        std::optional<Poco::Crypto::EVPPKey> PublicKey;
    };

}

#pragma once

#include <util/types.h>

#include <optional>
#include <Poco/Crypto/EVPPKey.h>

namespace OpenSsl
{
    void Initialize();
    void Uninitialize();

    std::optional<Poco::Crypto::EVPPKey> CreateEvpKey(const TBase64String& publicKey);
}

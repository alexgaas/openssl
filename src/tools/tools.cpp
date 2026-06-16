#include <tools/tools.h>

#include <Poco/Crypto/OpenSSLInitializer.h>
#include <sstream>

namespace OpenSsl
{

    void Initialize()
    {
        Poco::Crypto::OpenSSLInitializer::initialize();
    }

    void Uninitialize()
    {
        Poco::Crypto::OpenSSLInitializer::uninitialize();
    }

    std::optional<Poco::Crypto::EVPPKey> CreateEvpKey(const TBase64String& publicKey)
    {
        try
        {
            std::stringstream stream;
            stream << "-----BEGIN PUBLIC KEY-----\n";
            for (size_t i = 0; i < publicKey.Value.length(); i += 64)
            {
                stream << publicKey.Value.substr(i, 64) << "\n";
            }
            stream << "-----END PUBLIC KEY-----\n";

            return Poco::Crypto::EVPPKey(&stream, nullptr);
        }
        catch (...)
        {
            return std::nullopt;
        }
    }

} // namespace NOpenSsl

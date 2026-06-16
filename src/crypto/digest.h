#pragma once

#include <openssl/ossl_typ.h>
#include <string>

namespace OpenSsl
{

    class TDigest
    {
    public:
        TDigest(const std::string& name);

        EVP_MD_CTX* GetContext() const;
        const EVP_MD* GetDigest() const;

    private:
        class TContext{
        public:
            TContext();
            ~TContext();

            EVP_MD_CTX* Get() const;

        private:
            EVP_MD_CTX* Context;
        };

        TContext Context;
        const EVP_MD* Digest;
    };

}

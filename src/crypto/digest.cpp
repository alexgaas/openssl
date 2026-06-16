#include <crypto/digest.h>

#include <openssl/evp.h>
#include <stdexcept>

namespace OpenSsl
{
    TDigest::TContext::TContext(): Context(EVP_MD_CTX_create()) {}

    TDigest::TContext::~TContext(){
        EVP_MD_CTX_destroy(Context);
    }

    EVP_MD_CTX* TDigest::TContext::Get() const {
        return Context;
    }

    TDigest::TDigest(const std::string& name) {
        Digest = EVP_get_digestbyname(name.c_str());
        if (!Digest)
            throw std::runtime_error("Digest not found: " + name);

        EVP_DigestInit_ex(Context.Get(), Digest, nullptr);
    }

    EVP_MD_CTX* TDigest::GetContext() const {
        return Context.Get();
    }

    const EVP_MD* TDigest::GetDigest() const {
        return Digest;
    }

}

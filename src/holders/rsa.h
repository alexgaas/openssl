#pragma once

#include "holder.h"
#include <openssl/rsa.h>

namespace OpenSsl {
    class RsaKey : public Holder<RSA, RSA_new, RSA_free> {
    public:
        using Holder::Holder;
    };
}

#pragma once

#include "holder.h"

#include <openssl/bn.h>

namespace OpenSsl {
    class Bignum : public Holder<BIGNUM, BN_new, BN_clear_free> {
    public:
        using Holder::Holder;
    };

    class BnCtx : public Holder<BN_CTX, BN_CTX_new, BN_CTX_free> {
    public:
        using Holder::Holder;
    };
}
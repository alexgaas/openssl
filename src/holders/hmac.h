#pragma once

#include "holder.h"

#include <openssl/hmac.h>

namespace OpenSsl {
    class HmacCtx : public Holder<HMAC_CTX, HMAC_CTX_new, HMAC_CTX_free> {
    public:
        using Holder::Holder;
    };
}
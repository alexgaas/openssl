#pragma once

#include <string>

namespace OpenSsl
{
    std::string base64_decode(const std::string & str, bool isWeb = false);

    void url_base64_to_base64(std::string & url_base64);
}

#pragma once

#include <string>

namespace OpenSsl
{
    struct TBinaryString
    {
        explicit TBinaryString(const std::string& value);

        std::string Value;
    };

    struct TBase64String
    {
        explicit TBase64String(const std::string& value);

        std::string Value;
    };
}

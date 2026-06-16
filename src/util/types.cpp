#include <util/types.h>

namespace OpenSsl
{
    TBinaryString::TBinaryString(const std::string& value): Value(value){}
    TBase64String::TBase64String(const std::string& value): Value(value){}
}

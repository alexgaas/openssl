#include <util/base64.h>
#include <algorithm>
#include <Poco/Base64Decoder.h>
#include <Poco/StreamCopier.h>
#include <sstream>

namespace OpenSsl
{
    std::string base64_decode(const std::string& _s, bool _isWeb)
    {
        std::string s = _s;
        if (_isWeb)
            url_base64_to_base64(s);

        std::istringstream input(s);
        std::ostringstream res;

        {
            Poco::Base64Decoder decoder(input);
            Poco::StreamCopier::copyStream(decoder, res);
        }

        return res.str();
    }

    void url_base64_to_base64(std::string& url_base64)
    {
        std::replace(url_base64.begin(), url_base64.end(), '-', '+');
        std::replace(url_base64.begin(), url_base64.end(), '_', '/');

        switch (url_base64.size() % 4)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            url_base64.push_back('=');
            url_base64.push_back('=');
            break;
        case 3:
            url_base64.push_back('=');
            break;
        }
    }
}

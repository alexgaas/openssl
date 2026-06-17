# openssl cpp

C++ **OpenSSL** thin wrapper I use for all my cryptography experiments and **identity** servers / frameworks.

**v1 version**:
- basic initialization / uninitialization of OpenSSL
- POCO Crypto constructs (_EVPPKey_ as example) exposed for crypto-based operations
- SHA1 / digest as example to call constructs
- basic unit tests

**v2 version**:
- introduces Holder class to effectively initialize OpenSSL constructs
- RSA added as example of using holder class
- additional unit tests added for RSA  

### Prerequisites

- CMake 3.10+
- [OpenSSL](https://www.openssl.org/)
- [Poco Project](https://pocoproject.org/) (Foundation, Util, Crypto)

### Building

```bash
mkdir build
cd build
cmake ..
make
```

### Testing

The project uses **GoogleTest**. Tests are automatically discovered and can be run after building:

```bash
./build/openssl_tests
```

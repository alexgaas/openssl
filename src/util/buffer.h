#pragma once

#include <vector>

namespace OpenSsl {
    class Buffer {
    public:
        explicit Buffer(const size_t size = 0) : Data_(size) {}

        void* Data() { return Data_.data(); }
        const void* Data() const { return Data_.data(); }

        size_t Size() const { return Data_.size(); }
        void Resize(const size_t size) { Data_.resize(size); }

    private:
        std::vector<char> Data_;
    };
}
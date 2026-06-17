#pragma once
#include <new>
#include <utility>

namespace OpenSsl {
    template <typename TType, auto Create, auto Destroy, class... Args>
    class Holder {
    public:
        explicit Holder(Args... args) {
            Ptr = Create(args...);
            if (!Ptr) {
                throw std::bad_alloc();
            }
        }

        explicit Holder(TType* ptr) noexcept: Ptr(ptr){}

        Holder(const Holder&) = delete;
        Holder& operator=(const Holder&) = delete;

        Holder(Holder&& other) noexcept: Ptr(other.Ptr) {
            other.Ptr = nullptr;
        }

        Holder& operator=(Holder&& other) noexcept {
            if (this != &other) {
                if (Ptr) {
                    Destroy(Ptr);
                }
                Ptr = other.Ptr;
                other.Ptr = nullptr;
            }
            return *this;
        }

        ~Holder() noexcept {
            if (Ptr) {
                Destroy(Ptr);
            }
        }

        explicit operator TType* () const noexcept {
            return Ptr;
        }

        explicit operator bool() const noexcept {
            return Ptr != nullptr;
        }

        TType* Get() const noexcept {
            return Ptr;
        }

        TType* Release() noexcept {
            TType* ret = Ptr;
            Ptr = nullptr;
            return ret;
        }

        void Swap(Holder& other) noexcept {
            std::swap(Ptr, other.Ptr);
        }

    private:
        TType* Ptr;
    };
}

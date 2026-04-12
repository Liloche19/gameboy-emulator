#pragma once

#include "Data/MemTypes.hpp"
#include <cstdint>
#include <variant>

namespace gmb
{
    template<typename MemType>
    struct TByte {
        // byte linked to the memory
        std::uint8_t& byte_;

        // cast
        operator std::uint8_t() {
            return MemType::read(byte_);
        }

        // = operator overload
        TByte& operator=(std::uint8_t val) {
            MemType::write(byte_, val);
            return *this;
        }
        TByte& operator=(TByte& val) {
            MemType::write(byte_, val);
            return *this;
        }

        // arithmetic operations
        std::uint8_t operator+(std::uint8_t val) {
            return byte_ + val;
        }
        std::uint8_t operator-(std::uint8_t val) {
            return byte_ - val;
        }
        std::uint8_t operator*(std::uint8_t val) {
            return byte_ * val;
        }
        std::uint8_t operator/(std::uint8_t val) {
            return byte_ / val;
        }

        TByte& operator+=(std::uint8_t val) {
            MemType::write(byte_, byte_ + val);
            return *this;
        }
        TByte& operator-=(std::uint8_t val) {
            MemType::write(byte_, byte_ - val);
            return *this;
        }
        TByte& operator*=(std::uint8_t val) {
            MemType::write(byte_, byte_ * val);
            return *this;
        }
        TByte& operator/=(std::uint8_t val) {
            MemType::write(byte_, byte_ / val);
            return *this;
        }

        // increment / decrement overload
        std::uint8_t operator++(int) {
            std::uint8_t old_byte = byte_;
            MemType::write(byte_, byte_ + 1);
            return old_byte;
        }
        std::uint8_t operator--(int) {
            std::uint8_t old_byte = byte_;
            MemType::write(byte_, byte_ - 1);
            return old_byte;
        }

        // binary operation overload
        std::uint8_t operator&(std::uint8_t val) {
            return byte_ & val;
        }
        std::uint8_t operator|(std::uint8_t val) {
            return byte_ | val;
        }
        std::uint8_t operator^(std::uint8_t val) {
            return byte_ ^ val;
        }
        std::uint8_t operator~() {
            return ~byte_;
        }

        TByte& operator&=(std::uint8_t val) {
            MemType::write(byte_, byte_ & val);
            return *this;
        }
        TByte& operator|=(std::uint8_t val) {
            MemType::write(byte_, byte_ | val);
            return *this;
        }
        TByte& operator^=(std::uint8_t val) {
            MemType::write(byte_, byte_ ^ val);
            return *this;
        }
    };

    using AnyMemByte =std::variant<TByte<RegisterType>, TByte<RAMType>>;

    struct MemByte {
        AnyMemByte data;

        // cast
        operator std::uint8_t() {
            return std::visit([](auto& byte) -> std::uint8_t {return static_cast<std::uint8_t>(byte);}, data);
        }

        // = operator overload
        MemByte& operator=(std::uint8_t val) {
            std::visit([val](auto& byte) { byte = val; }, data);
            return *this;
        }
        MemByte& operator=(MemByte& val) {
            std::uint8_t v = static_cast<std::uint8_t>(val);
            *this = v;
            return *this;
        }

        // arithmetic operations
        std::uint8_t operator+(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t {return byte + val;}, data);
        }
        std::uint8_t operator-(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t {return byte - val;}, data);
        }
        std::uint8_t operator*(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t {return byte * val;}, data);
        }
        std::uint8_t operator/(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t {return byte / val;}, data);
        }

        MemByte& operator+=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte += val;}, data);
            return *this;
        }
        MemByte& operator-=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte -= val;}, data);
            return *this;
        }
        MemByte& operator*=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte *= val;}, data);
            return *this;
        }
        MemByte& operator/=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte /= val;}, data);
            return *this;
        }

        // increment / decrement overload
        std::uint8_t operator++(int) {
            return std::visit([](auto& byte) -> std::uint8_t { return byte++; }, data);
        }
        std::uint8_t operator--(int) {
            return std::visit([](auto& byte) -> std::uint8_t { return byte--; }, data);
        }

        // binary operation overload
        std::uint8_t operator&(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t { return byte & val; }, data);
        }
        std::uint8_t operator|(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t { return byte | val; }, data);
        }
        std::uint8_t operator^(std::uint8_t val) {
            return std::visit([val](auto& byte) -> std::uint8_t { return byte ^ val; }, data);
        }
        std::uint8_t operator~() {
            return std::visit([](auto& byte) -> std::uint8_t { return ~byte; }, data);
        }

        MemByte& operator&=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte &= val;}, data);
            return *this;
        }
        MemByte& operator|=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte |= val;}, data);
            return *this;
        }
        MemByte& operator^=(std::uint8_t val) {
            std::visit([val](auto& byte) {byte ^= val;}, data);
            return *this;
        }
    };
}

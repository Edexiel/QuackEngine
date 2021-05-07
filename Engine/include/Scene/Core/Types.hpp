//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_TYPES_HPP
#define QUACKENGINE_TYPES_HPP

#include <cstdint>
#include <bitset>

const std::uint32_t COMPONENTS_NUMBER = 6;
const size_t START_SIZE = 10000;
typedef uint_fast32_t Entity;
using ComponentType = std::uint_fast8_t;
using Signature = std::bitset<COMPONENTS_NUMBER>;


//class Entity
//{
//private:
//    std::uint_fast32_t val;
//public:
//    explicit Entity(uint_fast32_t val) : val(val)
//    {}
//    explicit operator uint_fast32_t() const noexcept
//    {
//        return val;
//    }
//};


#endif //QUACKENGINE_TYPES_HPP

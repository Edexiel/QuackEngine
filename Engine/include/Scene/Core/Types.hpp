//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_TYPES_HPP
#define QUACKENGINE_TYPES_HPP

#include <cstdint>
#include <bitset>

typedef std::uint_fast32_t EntityId;
typedef std::uint_fast8_t ComponentType;
const std::uint32_t COMPONENTS_NUMBER = 3;
typedef std::bitset<COMPONENTS_NUMBER> Signature;

#endif //QUACKENGINE_TYPES_HPP

//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_TYPES_HPP
#define QUACKENGINE_TYPES_HPP

#include <cstdint>
#include <bitset>

const std::uint32_t COMPONENTS_NUMBER = 10;
const size_t START_SIZE = 1000;
typedef std::uint_fast32_t EntityId;
typedef std::uint_fast8_t ComponentType;
typedef std::bitset<COMPONENTS_NUMBER> Signature;



#endif //QUACKENGINE_TYPES_HPP

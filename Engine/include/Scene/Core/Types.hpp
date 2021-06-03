
#ifndef QUACKENGINE_TYPES_HPP
#define QUACKENGINE_TYPES_HPP

#include <cstdint>
#include <bitset>
#include <cereal/types/string.hpp>


const std::uint_fast8_t COMPONENTS_NUMBER = 12;
const size_t START_SIZE = 10000;
typedef std::uint_fast32_t Entity;
using ComponentType = std::uint_fast8_t;
using Signature = std::bitset<COMPONENTS_NUMBER>;


//class Entity
//{
//private:
//    uint val;
//public:
//    Entity():val()
//    {}
//
//    explicit Entity(const uint & val) : val(val)
//    {}
//
//    explicit Entity(uint && value) noexcept(std::is_nothrow_move_constructible<uint>::value)
//    : val(value)
//    {
//    }
//
//    friend void swap(Entity& a, Entity& b) noexcept
//    {
//        using std::swap;
//        swap(a.val, b.val);
//    }
//
//    explicit operator const uint&() const noexcept
//    {
//        return val;
//    }
//    explicit operator uint&() noexcept
//    {
//        return val;
//    }
//
//    bool operator==(const Entity &rhs) const
//    {
//        return val == rhs.val;
//    }
//
//    bool operator!=(const Entity &rhs) const
//    {
//        return !(rhs == *this);
//    }
//
//    bool operator<(const Entity &rhs) const
//    {
//        return val < rhs.val;
//    }
//
//    bool operator>(const Entity &rhs) const
//    {
//        return rhs < *this;
//    }
//
//    bool operator<=(const Entity &rhs) const
//    {
//        return !(rhs < *this);
//    }
//
//    bool operator>=(const Entity &rhs) const
//    {
//        return !(*this < rhs);
//    }
//
//    uint operator++(int)
//    {
//        return val++;
//    }
//
//};
//
//namespace std
//{
//    template<>
//    struct hash<Entity>
//    {
//        std::size_t operator()(Entity const& e) const noexcept
//        {
//            return std::hash<uint>{}(e.operator const unsigned int &());
//        }
//    };
//}


#endif //QUACKENGINE_TYPES_HPP

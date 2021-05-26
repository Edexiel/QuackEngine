//
// https://stackoverflow.com/a/4541470
//

#ifndef QUACKENGINE_TYPE_HPP
#define QUACKENGINE_TYPE_HPP

#include <string>

std::string demangle(const char* name);

template <class T>
std::string type(const T& t) {

    return demangle(typeid(t).name());
}
#endif //QUACKENGINE_TYPE_HPP

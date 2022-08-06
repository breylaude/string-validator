//
// Created by Kyle Gendreau on 7/12/21.
//

#ifndef STRINGVALIDATOR_STRINGVALIDATOR_CPP
#define STRINGVALIDATOR_STRINGVALIDATOR_CPP

#include "../include/StringValidator.h"

template<typename C, typename S>
StringValidator<C, S>::StringValidator() : charValidator(), substringValidator() {}

template<typename C, typename S>
StringValidator<C, S>::StringValidator(const StringValidator &rhs) : charValidator(rhs.charValidator), substringValidator(rhs.substringValidator) {}

template<typename C, typename S>
StringValidator<C, S>::StringValidator(const StringValidator &&rhs) : charValidator(rhs.charValidator), substringValidator(rhs.substringValidator) {}

template<typename C, typename S>
StringValidator<C,S> &StringValidator<C, S>::operator=(const StringValidator &rhs) {
    if (this != &rhs) {
        StringValidator ph(rhs);
        std::swap(*this,ph);
    }
    return *this;
}

template<typename C, typename S>
StringValidator<C,S> &StringValidator<C, S>::operator=(const StringValidator &&rhs) {
    return *this = rhs;
}

template<typename C, typename S>
std::string StringValidator<C, S>::operator()(std::string str) {
    for (uint32_t i(0); i < str.size(); ++i) {
        charValidator(str.at(i));
    }
    substringValidator(str);
    return str;
}

template<typename C, typename S>
C &StringValidator<C, S>::getCharValidator() {
    return charValidator;
}

template<typename C, typename S>
S &StringValidator<C, S>::getSubstringValidator() {
    return substringValidator;
}


#endif // STRINGVALIDATOR_STRINGVALIDATOR_CPP
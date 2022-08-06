//
// Created by Kyle Gendreau on 7/11/21.
//

#ifndef STRINGVALIDATOR_STRINGVALIDATOR_H
#define STRINGVALIDATOR_STRINGVALIDATOR_H

#include <unordered_map>
#include <list>
#include <string>

/**
 * @class CharValidator
 * @brief Default parameter for charValidator member, manages the validation and/or replacement of
 * character within string to be valid.
 *
 * Holds a container that maps any potential character to a valid character.  Client must insert all pairs themselves.
 *
 * Functor call void operator()(char) validates any given character independently.
 */
struct CharValidator {

    // operator that checks validity and makes any edits necessary
    void operator()(char32_t& c) {
        auto it(map.find(c));
        if (it != map.end()) {
            c = it->second;
        }
        else
            throw std::logic_error("no matching mapped character\n");
    }

    // map holds keys of readable chars, and values that it should equal
    std::unordered_map<char32_t, char32_t> map;

};

/**
 * @class SubstrValidator
 * @brief Default parameter for substringValidator member, manages the replacement of any specified susbtrings with a
 * specified replacement.
 *
 * Holds a list of pairs of, first: strings to look for, and second: strings to replace targets with, all in the order
 * the client wants.
 *
 * Functor void operator()(string) iteratively searches through the string for targets to replace, if any replacement
 * occurs, loops through entire list again after going through it fully
 */
struct SubstrValidator {

    // operator looks for ALL substrings to replace in order
    void operator()(std::string& s) {
        bool altered(false);
        int32_t index(-1);
        for (auto it(list.begin()); it != list.end(); ++it) {
            index = s.find(it->first);
            if (index != -1) {
                altered = true;
                s.replace(index,it->first.size(),it->second);
            }
        }
        if (altered)
            operator()(s); // if altered, make recursive call to do it all again
    }

    // ordered list of all substrings to search for and replace
    std::list<std::pair<std::string,std::string>> list;

};


/**
 * @class StringValidator
 * @brief this class takes in a string and returns a validated copy of it, validation is defined by template parameter
 * classes C and S, where C class validates all characters and S validates substrings of the string
 *
 * First, character validation for all strings occurs, and then substring validation occurs.  It is assumed that
 * replacements account for valid characters itself.
 *
 * @tparam C - the class of charValidator member variable, validates all characters in string
 * @tparam S - the class of substringValidator member variable, searches for substrings to replace within the string
 */
template <typename C = CharValidator, typename S = SubstrValidator>
class StringValidator {
public:

    // default ctor
    explicit StringValidator();

    // copy ctor
    explicit StringValidator(const StringValidator& rhs);
    explicit StringValidator(const StringValidator&& rhs);

    // dtor
    ~StringValidator() = default;

    // assignment operator
    StringValidator& operator=(const StringValidator& rhs);
    StringValidator& operator=(const StringValidator&& rhs);

//////////////////////////////////////////////////////
//// FUNCTOR

    /**
     * operator() - first calls charValidator on all characters, then calls substringValidator on string
     * @param str - copy parameter string being validated
     * @return validated string
     */
    std::string operator()(std::string str);

//////////////////////////////////////////////////////
//// ACCESSORS

    /**
     * @return charValidator
     */
    C& getCharValidator();

    /**
     * @return substringValidator
     */
    S& getSubstringValidator();

private:

    C charValidator;

    S substringValidator;

};

#include "../src/StringValidator.cpp"

#endif //STRINGVALIDATOR_STRINGVALIDATOR_H

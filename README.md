# String Validator 

## Table of Contents
1. [Objective](#objective)
2. [Outline](#outline)
    1. [General](#general)
    2. [Object Details](#object-details)
        1. [CharValidator](#charvalidator)
        2. [SubstrValidator](#substrvalidator)
        3. [StringValidator](#stringvalidator)
    
## Objective
Create a modular string validator that can validate characters and can handle any substrings

## Outline
### General
StringValidator is a class template that takes in two template parameters, one that acts as a functor to take in 
characters and validate them, another to handle any substrings.

### Object Details
#### CharValidator
CharValidator is the default template parameter for StringValidator's C class.  This specific class will check if a
character is a key value in its std::map member variable, and then assign it to the value type mapped at the key.  If 
the character is not present in the map, then an error will throw.  Therefore, ALL POTENTIAL INPUT CHARACTERS must be 
accounted for.

##### Member Variables:
variable | description
----------|-----------
std::unordered_map<char32_t, char32_t> map; | hashes all readable characters to valid characters

##### Member Functions:
signature | description
----------|-----------
void operator()(char32_t& c); | finds reference parameter in map and assigns to paired value, else throws error


#### SubstrValidator
SubstrValidator is the default template parameter for StringValidator's S class.  This specific class will check if 
the string contains any listed substrings IN ORDER, and if present will replace them with a specified substitute.  After
a replacement occurs, the operation will continue on through the entire list and then start over from the beginning.  If
no replacements occur, then the operation's finished.

##### Member Variables:
variable | description
----------|-----------
std::list<std::pair\<std::string,std::string>> list; | client ordered list, first: target to search for, second: replacement for target

##### Member Functions:
signature | description
----------|-----------
void operator()(std::string& s); | replaces any specified substrings with specified replacements


#### StringValidator
StringValidator<typename C, typename S> : this class takes in a string parameter by copy, validates its characters and 
then any substrings it may have, and then returns a validated string.  It's assumed that any substring replacements 
account for valid characters itself, and will not be checked.

##### Member Variables:
variable | description
----------|-----------
C charValidator; | A functor that handles character validation
S substringValidator; | A functor that handles validating any substrings within the string

##### Member Functions:
signature | description
----------|-----------
explicit StringValidator(); | default constructor
explicit StringValidator(...); takes const StringValidator& rhs OR const StringValidator&& rhs as parameters | copy constructor
~StringValidator() = default; | destructor
StringValidator& operator=(...); takes const StringValidator& rhs OR const StringValidator&& rhs as parameters | assignement operator
std::string operator()(std::string str); | takes a parameter by value and validates it as defined by charValidator and substringValidator (in that order)
C& getCharValidator(); | returns the charValidator member variable
S& getSubstringValidator(); | returns the substringValidator member variable

##### Template Parameter Requirements
###### C
The C class must have a member function thats signature is: **void operator()(char32_t& c)**.
The objective of this function is to validate the character either by assuring its valid or by replacing it.

###### S
The S class must have a member function thats signature is: **void operator()(std::string& s)**.
The objective of this function is to search for any target substrings and replace it with whatever the client wants.
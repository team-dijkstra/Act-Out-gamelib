
/**
 * \file namecomparators.h
 * 
 * contains implementations of comparators based on a 'name' member function
 * of the supplied types.
 *
 */

#ifndef NAME_COMPARATORS_H
#define NAME_COMPARATORS_H

//#include <functional>

/**
 * Less than operator to compare objects by name.
 *
 * \tparam T the type of the objects to compare. T must supply a 'name()' 
 *    method that takes no arguments and returns a std::string.
 *
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 *
 * \return true if \begincode lhs.name() < rhs.name() \endcode. false otherwise.
 */
template<typename T>
bool operator< (const T & lhs, const T & rhs) {
   return lhs.name() < rhs.name();
}

/**
 * Equality operator to compare objects by name.
 *
 * \tparam T the type of the objects to compare. T must supply a 'name()'
 *    method that takes no arguments and returns a std::string.
 *
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 *
 * \return true if \begincode lhs.name() == rhs.name() \endcode. false
 *    otherwise.
 */
template<typename T>
bool operator== (const T & lhs, const T & rhs) {
   return lhs.name() == rhs.name();
}

/**
 * Less than or equal comparison operator. Implemented in terms of 
 * operator< and operator==.
 * 
 * \see operator<
 * \see operator==
 */
template<typename T>
bool operator<= (const T & lhs, const T & rhs) {
   return lhs < rhs || lhs == rhs;
}
/**
 * Greater than comparison operator. Implemented in terms of 
 * operator< and operator==.
 * 
 * \see operator<
 * \see operator==
 */
template<typename T>
bool operator> (const T & lhs, const T rhs) {
   return !(lhs <= rhs);
}

/**
 * Greater than or equal comparison operator. Implemented in terms of 
 * operator< and operator==.
 * 
 * \see operator<
 * \see operator==
 */
template<typename T>
bool operator>= (const T & lhs, const T & rhs) {
   return lhs == rhs || lhs > rhs;
}

#endif /* NAME_COMPARATORS_H */

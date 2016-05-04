/*
 * File:    iteratorex.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 28, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "iterator_ex.h"
#include <exception>

using namespace std;

iterator_ex::iterator_ex() : m_message("") { /* Empty constructor */ }

iterator_ex::iterator_ex(char* msg) : m_message(msg) { /* Empty constructor */ }

const char* iterator_ex::what() const throw () {
    return m_message;
}

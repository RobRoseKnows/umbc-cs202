/*
 * File:    iteratorex.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 28, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef ITERATOREX_H_
#define ITERATOREX_H_

#include <exception>

using namespace std;

class iterator_ex: public exception {
public:
    iterator_ex();

    iterator_ex(char* msg);

    const char* what() const throw();
private:
    const char *m_message;
};

#endif /* ITERATOREX_H_ */

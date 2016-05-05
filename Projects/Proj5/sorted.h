/*
 * File:    sorted.h
 * Author:  Robert Rose
 * Section: 3
 * Created: May 2, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef SORTED_H_
#define SORTED_H_

using namespace std;

class sorted {
public:

    // Size of storage array.  Maximum number of objects that can be
    // stored in an array.
    static const int MAX_SIZE = 15;

    // Forward declare iterator classe(s)
    class const_iterator;
    class rand_iterator;

    //Default constructor
    sorted();

    // Non-default constructor copies data from array to sorted
    sorted(int* data, int len);

    // Copy constructor
    sorted(const sorted& srtd);

    // Destructor
    ~sorted();

    // Overloaded assignment operator
    sorted operator=(const sorted& srtd);

    // Return the capacity of the storage array
    int capacity() const;

    // Return number of items stored
    int size() const;

    // Return the address of the storage array;
    // for use in grading programs
    int* getStorageArray() const;

    // Insert an item in sorted; return iterator to inserted item
    const_iterator insert(int data);

    // Remove an item from sorted; return iterator to next item
    // after the erased item
    const_iterator erase(const_iterator itr);

    // Get element at indx position
    const int& at(int indx);

    // Returns an iterator pointing to the first item in the array.
    const_iterator begin();

    // Returns an iterator pointing to the first item in the array.
    // This is the constant version so I can use it in copy constructor.
    const_iterator beginConst() const;

    // Returns an iterator poiting to the end of the array, one
    // past the last item.
    const_iterator end();

    // Returns an iterator poiting to the end of the array, one
    // past the last item.
    // This is the constant version so I can use it in copy constructor.
    const_iterator endConst() const;

    // Starting iterator value for rand_iterator.  Should use constant
    // value or time(NULL) as seed value for srand().
    rand_iterator rndbegin();

    // Starting iterator value for rand_iterator with seed for
    // srand() specified.  Given a sorted<T> object x, repeated
    // use of rndbegin( unsigned seed ) with the same seed value
    // must produce the same permutation of the elements of x.
    rand_iterator rndbegin(unsigned seed);

    // Ending iterator value for rand_iterator
    rand_iterator rndend();

    class const_iterator {
    public:

        // Allows sorted to access const_iterator's private variables.
        friend class sorted;

        // Default constructor
        const_iterator();

        // Non-default constructor sets m_current to given address
        const_iterator(int* addr);

        // Pre-increment const_iterator
        const_iterator operator++();

        // Post-increment const_iterator
        const_iterator operator++(int);

        // operator!= needed for loop control, e.g. itr != x.end()
        bool operator!=(const const_iterator& itr);

        // Unary dereference operator
        const int& operator*();

    private:
        int* m_current;  // pointer to current entry in array
    };

    class rand_iterator {
    public:
        rand_iterator();

        // Non-default constructor; pointer to sorted<T> object passed
        // as a parameter, which allows the rand_iterator to access
        // variables of the associated sorted<T>> container
        rand_iterator( sorted* srtdPtr );

        // Non-default constructor; pointer to sorted<T> passed as in
        // previous constructor, but also passes seed for random number
        // generator
        rand_iterator( sorted* srtdPtr, unsigned seed );

        // Copy constructor
        rand_iterator( const rand_iterator& itr );

        // Destructor
        ~rand_iterator();

        // pre-increment
        rand_iterator operator++();

        // post-increment
        rand_iterator operator++(int);

        // operator!= needed for loop control, e.g. itr != x.end()
        bool operator!=(const rand_iterator& itr);

        // Unary dereference operator
        const int& operator*();

        // Overloaded assignment operator
        rand_iterator operator=(const rand_iterator& itr);
    private:
        int* m_current;
        int m_version_created;  // stores the version of the array that this iterator was created on.
        int m_rand[MAX_SIZE];   // storing the randomized indexes.
        int m_seed; // The seed for the random number. Don't really need to store this but w/e.
        sorted* m_sorted;

        void randomize(int seed);
    };

private:
    int m_size;              // number of items in my_array
    int m_version;           // Version of the array.

    int m_data[MAX_SIZE];    // storage array

    int bubble_sort(int indexToTrack);
};

#endif /* SORTED_H_ */

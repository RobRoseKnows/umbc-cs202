/*
 *  File:    sorted.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: May 2, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "sorted.h"
#include "iterator_ex.h"

#include<stdlib.h>
#include<stdexcept>
#include<iostream>
#include<cmath>

using namespace std;

/*
 * Default constructor for sorted. Copied from the my_array class.
 */
sorted::sorted() {
    m_size = 0;
    m_version = 0;
    m_resized_count = 0;
    m_data = new int[capacity()];
}

/*
 * Constructor that takes data and the length of the array.
 */
sorted::sorted(int* data, int len) {
    m_resized_count = 0;

    // Resize the array
    while(len > capacity())
        m_resized_count++;

    m_data = new int[capacity()];

    for (int i = 0; i < len; i++)
        m_data[i] = data[i];

    // Track nothing
    bubble_sort(-1);

    m_size = len;
    m_version = 0;
}

sorted::sorted(const sorted& srtd) {
    m_resized_count = 0;

    // Resize the array by making the capacity exponent bigger.
    while(srtd.m_size > capacity())
        m_resized_count++;

    m_size = srtd.m_size;
    // It doesn't really have to copy the other one's version, but I thought it was a good idea.
    m_version = srtd.m_version;
    m_resized_count = srtd.m_resized_count;

    m_data = new int[capacity()];

    // I wasn't able to use begin() and end() for this because they aren't const so I
    // made a const version of them. I could have used the overloaded ='s operator but
    // I figured that it would just be redundant and could introduce another point of
    // failure since I used the same method in the equality operator.
    for(int i = 0; i < srtd.m_size; i++) {
        m_data[i] = srtd.m_data[i];
    }
}

sorted::~sorted() {
//    for(int i = 0; i < capacity(); i++) {
//        delete m_data[i];
//    }
    delete [] m_data;
}

sorted sorted::operator=(const sorted& srtd) {

//    if(m_resized_count != srtd.m_resized_count
//    m_resized_count = srtd.m_resized_count;
//    m_size = srtd.m_size;
//
//    for(int i = 0; i < srtd.m_size; i++) {
//        m_data[i] = srtd.m_data[i];
//    }

    // I decided not to use this because that data is irrelevant and it shouldn't
    // cause anything to go wrong but I wanted to include it in the code anyway so
    // the grader could see it.
    //while(toArrItr++ != endConst()) {
    //toArrItr = NULL;
    //toArrItr++;
    //}

    m_version++;

    return sorted(srtd);
}

// Returns the MAX_SIZE of the array.
int sorted::capacity() const {
    return SIZE_UNIT * pow(2, m_resized_count);
}

// Returns the current size of the array.
int sorted::size() const {
    return m_size;
}

// Returns the storage array for debugging and testing purposes.
int* sorted::getStorageArray() const {
    return m_data;
}

// Returns the value at an index.
const int& sorted::at(int indx) {
    return m_data[indx];
}

/*
 * Inserts a new item into the array in sorted order.
 * Takes:   data to insert into the array
 * Returns: a const_iterator pointing to the item in the array.
 */
sorted::const_iterator sorted::insert(int data) {
    // Make sure we aren't going out of range.
    if (m_size + 1 > capacity()) {
        m_resized_count++;
        int *resize = new int[capacity()];

        for(int i = 0; i < m_size; i++)
            resize[i] = m_data[i];

        delete [] m_data;

        m_data = resize;
    }

    // Add data to end and then save the index so we can track it.
    m_data[m_size] = data;
    int indexToTrack = m_size;
    m_size++;

    // Increments the version that we're currently on so that rand_iterator
    // can throw an exception if necessary.
    m_version++;

    // Sort the array and track the number we just added.
    // Although indexToTrack should be changed in-place, I find assigning
    // variables to be more self-documenting.
    indexToTrack = bubble_sort(indexToTrack);

    return const_iterator(&m_data[indexToTrack]);

}

/* This sorts the array using bubble sort. Since the array should usually
 * be mostly sorted, bubble sort is actually rather efficient.
 * Takes:   the index of a value to track. Usually the one we recently added.
 * Returns: the index that the tracked value ended up at. Technically it
 *          will change indexToTrack inplace, but I prefer to return values
 *          because it makes it more clear what code does.
 */
int sorted::bubble_sort(int indexToTrack) {
    bool done = false;
    int on = 0;
    int tmp;

    // Sort until we know it's gone.
    while (not done) {
        // Assume it's sorted
        done = true;
        on++;
        for (int i = 0; i < m_size - on; i++) {
            if (m_data[i] > m_data[i + 1]) {
                // Do the sorting shuffle
                tmp = m_data[i];
                m_data[i] = m_data[i + 1];
                m_data[i + 1] = tmp;

                // See if the index we were tracking switched with anything
                if (i == indexToTrack)
                    indexToTrack = i + 1;
                else if (i + 1 == indexToTrack)
                    indexToTrack = i;

                // If we're in here, it means the array isn't sorted.
                done = false;
            }
        }
    }

    return indexToTrack;
}

// Remove an item from sorted; return iterator to next item
// after the erased item
sorted::const_iterator sorted::erase(sorted::const_iterator itr) {

    int* end = &m_data[capacity()];    // one past the end of data
    int* ptr = itr.m_current;        // element to erase

    // to erase element at ptr, shift elements from ptr+1 to
    // the end of the array down one position
    while (ptr + 1 != end) {
        *ptr = *(ptr + 1);
        ptr++;
    }

    m_size--;

    // Since we're creating a new array to hold the shortened array, we need to be
    // able to return the new current pointer.
    int* newItrLocation = itr.m_current;

    // If the array is small enough, size it down.
    if (m_size <= SIZE_UNIT * pow(2, m_resized_count - 1)) {
        m_resized_count--;
        int *resize = new int[capacity()];

        for(int i = 0; i < m_size - 1; i++) {
            resize[i] = m_data[i];

            // If we're on the one we are on the original one we removed (now the one
            // next to it and what we want to return) then we want to store its new
            // location.
            if(&m_data[i] == itr.m_current)
                newItrLocation = &resize[i];
        }

        delete [] m_data;

        m_data = resize;
    }

    // Increments the version that we're currently on so that rand_iterator
    // can throw an exception if necessary.
    m_version++;

    return const_iterator(newItrLocation);
}

// Returns an iterator pointing to the first item in the array.
sorted::const_iterator sorted::begin() {
    return const_iterator(&m_data[0]);
}

// Returns an iterator poiting to the end of the array, one
// past the last item.
sorted::const_iterator sorted::end() {
    return const_iterator(&m_data[m_size]);
}

sorted::rand_iterator sorted::rndbegin() {
    // The seed will be 12345
    return rand_iterator(this);
}

sorted::rand_iterator sorted::rndbegin(unsigned seed) {
    return rand_iterator(this, seed);
}

sorted::rand_iterator sorted::rndend() {
    rand_iterator ptr = rand_iterator(this);

    for(int i = 0; i <= m_size; i++)
        ptr++;

    return ptr;
}

/*****************************************************************************
 ************************ const_iterator BEGINS HERE  ************************
 *****************************************************************************/

sorted::const_iterator::const_iterator() :
        m_current(NULL) { /* Empty constructor */
}

sorted::const_iterator::const_iterator(int* addr) :
        m_current(addr) { /* Empty constructor */
}

// Pre-increment const_iterator
sorted::const_iterator sorted::const_iterator::operator++() {
    ++m_current;
    return *this;
}

// Post-increment const_iterator
sorted::const_iterator sorted::const_iterator::operator++(int) {
    const_iterator result(*this);
    ++(*this);
    return result;
}

// operator!= needed for loop control, e.g. itr != x.end()
bool sorted::const_iterator::operator!=(const const_iterator& itr) {
    return m_current != itr.m_current;
}

// Unary dereference operator
const int& sorted::const_iterator::operator*() {
    return *m_current;
}

void sorted::const_iterator::setCurrent(int data) {

}



/*****************************************************************************
 ************************* rand_iterator BEGINS HERE  ************************
 *****************************************************************************/

sorted::rand_iterator::rand_iterator() {
    /* Empty constructor */
}

/*
 *
 */
sorted::rand_iterator::rand_iterator(sorted* srtdPtr) {
    m_version_created = srtdPtr->m_version;
    // Set a constant seed
    m_seed = 12345;
    m_sorted = srtdPtr;
    m_rand = new int[m_sorted->capacity()];

    randomize(m_seed);

    m_current = &m_sorted->m_data[m_rand[0]];
}

// Non-default constructor; pointer to sorted<T> passed as in
// previous constructor, but also passes seed for random number
// generator
sorted::rand_iterator::rand_iterator(sorted* srtdPtr, unsigned seed) {
    m_version_created = srtdPtr->m_version;
    m_seed = seed;
    m_sorted = srtdPtr;
    m_rand = new int[m_sorted->capacity()];

    randomize(seed);

    m_current = &m_sorted->m_data[m_rand[0]];
}

// Copy constructor
sorted::rand_iterator::rand_iterator(const rand_iterator& itr) {
    m_version_created = itr.m_version_created;
    m_seed = itr.m_seed;
    m_sorted = itr.m_sorted;
    m_rand = new int[m_sorted->capacity()];

    for(int i = 0; i < itr.m_sorted->m_size; i++)
        m_rand[i] = itr.m_rand[i];

    m_current = &m_sorted->m_data[m_rand[0]];
}

/*
 * Randomly fills up m_rand using a given seed and the code from Proj4
 * Takes:   An integer seed.
 */
void sorted::rand_iterator::randomize(int seed) {
    // Fill the rand array with the indexes.
    for (int i = 0; i < m_sorted->m_size; i++) {
        m_rand[i] = i;
    }

    // Set the seed.
    srand(seed);

    // Shuffle the indexes.
    for (int i = 0; i < m_sorted->m_size; i++) {
        int temp;
        int j = rand() % m_sorted->m_size;
        temp = m_rand[i];
        m_rand[i] = m_rand[j];
        m_rand[j] = temp;
    }
}

// Destructor
sorted::rand_iterator::~rand_iterator() {
    delete [] m_rand;
}

// pre-increment
sorted::rand_iterator sorted::rand_iterator::operator++() {
    if (m_sorted->m_version != m_version_created)
        throw iterator_ex(
                "sorted::rand_iterator::operator++() underlying array has changed");

    ++m_current;
    return *this;
}

// post-increment
sorted::rand_iterator sorted::rand_iterator::operator++(int) {
    if (m_sorted->m_version != m_version_created)
        throw iterator_ex(
                "sorted::rand_iterator::operator++(int) underlying array has changed");

    rand_iterator result(m_sorted, m_seed);
    ++(*this);
    return result;
}

/*
 * The not comparison operator to compare two rand_iterators by their
 * m_current values.
 * Takes:   a rand_iterator to compare
 * Returns: a boolean indicating whether or not two rand_iterators are
 *          != each other.
 */
bool sorted::rand_iterator::operator!=(const rand_iterator& itr) {
//    // Check this one for sorted changes.
//    if (m_sorted->m_version != m_version_created)
//        throw iterator_ex(
//                "sorted::rand_iterator::operator!=(rand_iterator&) first array has changed");
//    // Check the other one for sorted changes.
//    if (itr.m_sorted->m_version != itr.m_version_created)
//        throw iterator_ex(
//                "sorted::rand_iterator::operator!=(rand_iterator&) second array has changed");

    // I did this assuming that the comparison function is only comparing the
    // m_current values and not the whole things. That is how it is used in
    // other parts of the code.
    return m_current != itr.m_current;
}

/*
 * The dereference operator for rand_iterator that returns a the current object
 * Returns: the current object
 */
const int& sorted::rand_iterator::operator*() {
    if (m_sorted->m_version != m_version_created)
        throw iterator_ex(
                "sorted::rand_iterator::operator*() underlying array has changed");

    return *m_current;
}

// Overloaded assignment operator
sorted::rand_iterator sorted::rand_iterator::operator=(
        const rand_iterator& itr) {
//    if (m_sorted->m_version != m_version_created)
//        throw iterator_ex(
//                "sorted::rand_iterator::operator++() calling underlying array has changed");
//    if (itr.m_sorted->m_version != itr.m_version_created)
//        throw iterator_ex(
//                "sorted::rand_iterator::operator=(rand_iterator&) set to underlying array has changed");
//
//    m_version_created = itr.m_version_created;
//    m_seed = itr.m_seed;
//    m_sorted = itr.m_sorted;
//
//    // Copy them one by one instead of rerandomizing
//    for(int i = 0; i < itr.m_sorted->m_size; i++)
//        m_rand[i] = itr.m_rand[i];
//
//    m_current = itr.m_current;

    return rand_iterator(itr);
}

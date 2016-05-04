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
#include<stdexcept>
#include<iostream>

using namespace std;

sorted::sorted() {
    m_size = 0;
}

sorted::sorted(int* data, int len) {
    if (len > MAX_SIZE)
        throw range_error("sorted(int* data, int len) len exceeds MAX_SIZE");

    for (int i = 0; i < len; i++)
        m_data[i] = data[i];

    // Track nothing
    bubble_sort(-1);

    m_size = len;
}

sorted::sorted(const sorted& srtd) {

}

sorted::~sorted() {

}

// Returns the MAX_SIZE of the array.
int sorted::capacity() const {
    return MAX_SIZE;
}

// Returns the current size of the array.
int sorted::size() const {
    return m_size;
}

// Returns the storage array for debugging and testing purposes.
int* sorted::getStorageArray() {
    return m_data;
}

// Returns the value at an index.
const int& sorted::at(int indx) {
    return m_data[indx];
}

// Insert an item in sorted; return iterator to inserted item
sorted::const_iterator sorted::insert(int data) {
    // Make sure we aren't going out of range.
    if(m_size + 1 > MAX_SIZE)
        throw range_error("insert(int data) new length exceeds MAX_SIZE");

    m_data[m_size] = data;
    cout << "Added " << m_data[m_size] << endl;
    int indexToTrack = m_size;
    m_size++;

    // Sort the array and track the number we just added.
    // Although indexToTrack should be changed in-place, I find assigning
    // variables to be more self-documenting.
    indexToTrack = bubble_sort(indexToTrack);

//    cout << "Print m_data:";
//    for(int i = 0; i < m_size; i++)
//        cout << " " << m_data[i];
//    cout << endl;

    return const_iterator(&m_data[indexToTrack]);

// TODO: Remove this if bubble sort alone works fine.
//    int index = 0;
//
//    // Go through the array until we reach a point that is greater
//    while(index < m_size && m_data[index + 1] < data) {
//        index++;
//    }
//
//    int* stop = &m_data[index];
//    int* onPtr = &m_data[m_size];
//
//    while (onPtr != stop) {
//        // Set the current one equal to the next
//        *onPtr = *(onPtr - 1);
//        onPtr--;
//    }


}

// This sorts the array using bubble sort. Since the array should usually
// be mostly sorted, bubble sort is actually rather efficient.
// Takes: the index of a value to track. Usually the one we recently added.
// Returns: the index that the tracked value ended up at. Technically it
//          will change indexToTrack inplace, but I prefer to return values
//          because it makes it more clear what code does.
int sorted::bubble_sort(int indexToTrack) {
    bool done = false;
    int on = 0;
    int tmp;

    while (not done) {
        // Assume it's sorted
        done = true;
        on++;
        for (int i = 0; i < m_size - on; i++) {
            if (m_data[i] > m_data[i + 1]) {
                tmp = m_data[i];
                m_data[i] = m_data[i + 1];
                m_data[i + 1] = tmp;

                // See if the index we were tracking switched with anything
                if(i == indexToTrack)
                    indexToTrack = i+1;
                else if(i + 1 == indexToTrack)
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
    int* end = &m_data[MAX_SIZE];    // one past the end of data
    int* ptr = itr.m_current;        // element to erase

    // to erase element at ptr, shift elements from ptr+1 to
    // the end of the array down one position
    while (ptr + 1 != end) {
        *ptr = *(ptr + 1);
        ptr++;
    }

    m_size--;

    return itr;
}

// Starting iterator value for const_iterator
sorted::const_iterator sorted::begin() {
    return const_iterator(&m_data[0]);
}

// Ending iterator value for const_iterator; typically,
// one element beyond the last valid element in the array.
sorted::const_iterator sorted::end() {
    return const_iterator(&m_data[m_size]);
}

/* const_iterator */

sorted::const_iterator::const_iterator() :
        m_current(NULL) { /* Empty constructor */ }

sorted::const_iterator::const_iterator(int* addr) :
        m_current(addr) { /* Empty constructor */ }

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

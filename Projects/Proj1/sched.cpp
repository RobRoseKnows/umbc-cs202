#include "include/sched.h"

#include <iostream>
#include <iomanip>
#include <string>
#include "include/sched.h"


using namespace std;

// FUNCTION PROTOTYPES -- DO NOT CHANGE!

// sort() - sorts an array of floats returning sorted indices
// On return, indx[] is an array of indices such that data[indx[0]], 
// data[indx[1]], ..., data[indx[len-1]] is data[] in ascending order.
//
// Parameters
//    data[] - float array of data to be ordered
//    indx[] - int array, same length as data[], to hold indices
//    len - int specifying the length of data[] and indx[]

void sort(float data[], int indx[], int len);

// sched() - schedules events given start and end times, and indx[] from sort
// Returns number of events scheduled; on return, scheduled[] contains 
// indices of scheduled events (e.g. startTime[scheduled[0]] is the start
// time of the first schedled event).
//
// Parameters
//    startTime[] - float array of event start times
//    endTime[] - float array of event end times
//    indx[] - array of indices that orders the end times
//    scheduled[] - int array to hold indices of scheduled events
//    len - int specifying the length of the arrays
// Returns
//    int value specifying number of events scheduled

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len);

// printEvent() - prints an event to the console
// Converts float start and end times to hh:mm format and prints times
// along with description.  E.g. Study Session from 12.5 to 13.25 should
// print as "12:30 - 13:15 Study Session"
//
// Parameters
//    startTime - float event start time
//    endTime - float event end time
//    description - string event description

void printEvent(float startTime, float endTime, string description);

// MAIN PROGRAM - DO NOT CHANGE!

int main() {

  int indx[NUM_EVENTS];
  int scheduledEvents[NUM_EVENTS];
  int numSched = 0;

  // Sort by event ending times
  sort(endTime, indx, NUM_EVENTS);
  
  // Call greedy scheduling algorithm
  numSched = sched(startTime, endTime, indx, scheduledEvents, NUM_EVENTS);

  // Display scheduled events
  for (int i = 0; i < numSched; i++)
    printEvent(startTime[scheduledEvents[i]], endTime[scheduledEvents[i]],
	       description[scheduledEvents[i]]);

  return 0;
}

// Selection sort
void sort(float data[], int indx[], int len) {

  // startAt counts how many times we've gone gone through and exchanged.
  for(int startAt = 0; startAt < len; startAt++) {
    float min = data[indx[startAt]];
    int mindex = startAt; // Pun intended

    for(int i = startAt; i < len; i++) {
      if(data[indx[i]] < min) {
	min = data[indx[i]];
	mindex = i; // Save where we are traversing the indx array.
      }
    }
    
    // Exchange values.
    int tmpIndex = indx[startAt]; // Temp save the index we're looking at
    indx[startAt] = indx[mindex];
    indx[mindex] = tmpIndex;
  } 
}

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len) {
  int numEvents = 0; // numEvents can also act as an index to the next scheduled space.

  //scheduled[0] = indx[0];
  numEvents++;

  for(int i = 1; i < len; i++) {
    if(startTime[indx[i]] >= endTime[scheduled[numEvents-1]]) {
      scheduled[numEvents] = indx[i];
      numEvents++;
    }
  }

  return numEvents;
}

void printEvent(float startTime, float endTime, string description) {
  string output = "";
  
  int startInt = (int) (startTime);
  int startMinutes = (startTime - startInt) * 60;
  
  if(startInt < 10) {
    output += "0";
  }
  output += startInt + ":";

  if(startMinutes < 10) {
    output += "0";
  }
  output += startMinutes + " - ";

  int endInt = (int) (endTime);
  int endMinutes = (endTime - endInt) * 60;

  if(endInt < 10) {
    output += "0";
  }
  output += endInt + ":";

  if(endMinutes < 10) {
    output += "0";
  }
  output += endMinutes + " ";

  output += description;
  cout << output << endl;
}

// Testing method. Remove on complete.
void printArray(float data[], int indx[], int len) {
  for(int i = 0; i < len; i++) {
    cout << data[indx[i]] << endl;
  }
}

// Testing main method. Remove on complete.
/*
int main() {
  float data[] = {10.0, 1.0, 2.0, 4.0, 7.0, 3.0, 6.0, 9.0, 0.0, 5.0, 8.0};
  int indx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  sort(data, indx, 11);
  printArray(data, indx, 11);

  return 0;
  }*/

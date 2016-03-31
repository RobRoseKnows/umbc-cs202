//
// File: Train.h
// Author: Robert Rose
// Date: 3/30/16
// Section: 03
// E-mail: robrose2@umbc.edu


#ifndef TRAIN_H
#define TRAIN_H

#include "TrainCar.h"
#include "Time.h"

class Train {
 public:

  // Constructors; see implementations in Train.cpp
  Train();
  Train( int num, Time dep, string dest );

  // Destructor needed to destroy linked list
  ~Train();

  // Add a car to the train.
  //
  // A train must have at least one locomotive and one coach car.
  // All other car types are optional.  See the TrainCar class for
  // definitions of the car types.
  //
  // addCar() must place cars in correct order within the linked list:
  // 
  //    1. Locomotive(s) - 1st non-dummy node(s)
  //    2. Business Class
  //    3. Coach
  //    4. Sleeping Cars
  //
  //    Snack Car 
  //       a. If the train has both Business Class and Coach, the Snack Car
  //          must be placed between coach and business.
  //       b. If the train has no Business Class, then the Snack Car must
  //          be placed in the middle of the Coach cars; if there is an 
  //          odd number of Coach cars, it should be placed closer to the
  //          locomotive.
  //
  //    Dining Car
  //       a. A train has a Dining Car if and only if it has one or more
  //          sleeping cars.  The Dining Car should be placed between the
  //          coach cars and the sleeping cars.
  //
  void addCar( TrainCar::cType car );

  // Remove a car from the train
  // 
  // removeCar() must keep the cars in the correct order / position
  // within the train.  Return true if successful; false if there is
  // no car of the specified type in the train.
  bool removeCar( TrainCar::cType car );

  // Return the train number
  int getNumber() const;

  // Set the train number
  void setNumber( int num );

  // Get the departure time
  Time getDepartureTime() const;

  // Set the departure time
  void setDepartureTime( const Time& t );

  // Get the train's destination
  string getDestination() const;

  // Set the train's destination
  void setDestination( string dest );

  // Check that the train is valid; must have at least one
  // locomotive and one CoachClass car, and the first non-dummy node
  // must be a Locomotive.  
  // addCar() and removeCar() should ensure that all cars are in the
  // correct position.
  bool isValid();

  // Overloaded insertion operator prints a character graphics
  // representation of the train
  friend ostream& operator<<(ostream &outStream, const Train& t);

 private:
  
  int m_number;               // train number
  Time m_departs;             // departure time
  string m_destination;       // destination
  TrainCar *m_head;           // head of linked list

  // These variables are optional, but will make programming addCar()
  // and removeCar() easier.  

  int m_numCoachClass;        // number of CoachClass cars
  int m_numBusinessClass;     // number of BusinessClass cars
  int m_numSleepingCar;       // number of SleepingCar cars
  bool m_hasSnackCar;         // true if has SnackCar

  //
  // MAY ADD PRIVATE HELPER FUNCTIONS HERE
  //

  // Returns the TrainCar pointer for the last car in the train
  TrainCar* getFinalCar();
  // Returns a pointer to the final car of a given type in a train.
  // Returns NULL if no car of that type is present.
  TrainCar* getFinalCarOfType(TrainCar::cType type);

  // Returns a pointer to the Nth car of a given type in the train.
  // Returns NULL if no car of that type or number is present.
  // Count starts at 1.
  TrainCar* getNthCarOfType(TrainCar::cType type, int n);

  // Returns a pointer to the car before the first instance of a
  // given type.
  // Count starts at 1.
  // Returns NULL if no such car exists.
  TrainCar* getFirstCarBeforeType(TrainCar::cType type);

};

#endif  
  

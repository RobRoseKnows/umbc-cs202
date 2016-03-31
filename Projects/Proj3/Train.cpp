//
// File: Train.cpp
// Author: Robert Rose
// Date: 3/28/16
// Section: 03
// E-mail: robrose2@umbc.edu
//

#include <iostream>
using namespace std;

#include "Train.h"
#include "TrainCar.h"

// Default constructor.  Initialize variables and create dummy node.
Train::Train() : m_number(0), m_departs( Time() ), m_destination ( "" ),
		 m_numCoachClass(0), m_numBusinessClass(0),
		 m_numSleepingCar(0), m_hasSnackCar(false){
  m_head = new TrainCar(); // dummy node
}

// Non-default constructor.  Initialize variables and create dummy node.
Train::Train( int num, Time dep, string dest) 
  : m_number(num), m_departs(dep), m_destination(dest),
    m_numCoachClass(0), m_numBusinessClass(0),
    m_numSleepingCar(0), m_hasSnackCar(false){
  m_head = new TrainCar(); // dummy node
}

Train::~Train(){
	TrainCar* nodeOn = m_head;
	while(nodeOn != NULL) {
		TrainCar* next = nodeOn->m_next;
		delete nodeOn;
		nodeOn = next;
	}
	m_head = NULL;

}

//
// IMPLEMENT THE REMAINDER OF THE CLASS AND THE OVERLOADED
// INSERTION OPERATOR
//

void Train::addCar(TrainCar::cType car) {

	switch(car) {
	case TrainCar::Locomotive: {
		TrainCar* lastCarOfType = getFinalCarOfType(TrainCar::Locomotive);

		if(lastCarOfType == NULL) {
			m_head = new TrainCar(TrainCar::Locomotive);
		} else {
			TrainCar* newCar = new TrainCar(TrainCar::Locomotive);

			// I use this snippet throughout the program for consistencies sake.
			newCar->m_next = lastCarOfType->m_next;
			lastCarOfType->m_next = newCar;
		}
		break;
	}
	case TrainCar::BusinessClass: {
		if(m_numBusinessClass == 0) {
			// If this is the first BusinessClass car, add it directly behind the Locomotive.
			TrainCar* lastLocomotive = getFinalCarOfType(TrainCar::Locomotive);
			TrainCar* newCar = new TrainCar(TrainCar::BusinessClass);

			newCar->m_next = lastLocomotive->m_next;
			lastLocomotive->m_next = newCar;
		} else {
			// If there are already BusinessClass cars.
			TrainCar* lastBC = getFinalCarOfType(TrainCar::BusinessClass);
			TrainCar* newCar = new TrainCar(TrainCar::BusinessClass);

			newCar->m_next = lastBC->m_next;
			lastBC->m_next = newCar;
		}
		m_numBusinessClass++;

		// Put the SnackCar in correct place if there is one.
		if(m_hasSnackCar) {
			removeCar(TrainCar::SnackCar);
			addCar(TrainCar::SnackCar);
		}
		break;
	}
	case TrainCar::SnackCar: {
		if(!m_hasSnackCar) {
			if(m_numBusinessClass > 0){
				// If there are both business class and coach
				TrainCar* lastBC = getFinalCarOfType(TrainCar::BusinessClass);
				TrainCar* newCar = new TrainCar(TrainCar::SnackCar);

				newCar->m_next = lastBC->m_next;
				lastBC->m_next = newCar;
			} else {
				// Place car if there are only coach cars.
				int carNum = m_numCoachClass / 2;
				TrainCar* prevCar = getNthCarOfType(TrainCar::CoachClass, carNum);
				TrainCar* newCar = new TrainCar(TrainCar::SnackCar);

				// Catches the case that there is only one coach car.
				if(prevCar == NULL) {
					prevCar = getFinalCarOfType(TrainCar::Locomotive);
				}

				newCar->m_next = prevCar->m_next;
				prevCar->m_next = newCar;
			}
		}

		m_hasSnackCar = true;
		break;
	}
	case TrainCar::CoachClass: {
		TrainCar* prevCar = getFinalCarOfType(TrainCar::CoachClass);

		// Because we can have Invalid trains without CoachCars, this will add the car
		// behind the locomotive.
		if(prevCar == NULL) {
			prevCar = getFinalCarOfType(TrainCar::Locomotive);
		}

		// If there is no locomotive as well, the previous will remain NULL. Then we
		// just add the car to the beggining of the train.
		if(prevCar == NULL) {
			prevCar = m_head;
		}

		TrainCar* newCar = new TrainCar(TrainCar::CoachClass);

		newCar->m_next = prevCar->m_next;
		prevCar->m_next = newCar;

		m_numCoachClass++;

		// If there's a SnackCar, it will need rebalancing.
		if(m_hasSnackCar) {
			removeCar(TrainCar::SnackCar);
			addCar(TrainCar::SnackCar);
		}

		break;
	}
	case TrainCar::DiningCar: {
		// Check to make sure there is not a dining car already, if there is, do nothing.
		TrainCar* existingDiningCar = getFinalCarOfType(TrainCar::DiningCar);
		if(existingDiningCar == NULL) {
			// TODO: Find out if adding a DiningCar separately should always add another SleepingCar or only when there is none.
			if(m_numSleepingCar <= 0) {
				addCar(TrainCar::SleepingCar);
			}

			TrainCar* prevCar = getFirstCarBeforeType(TrainCar::SleepingCar);
			TrainCar* newCar = new TrainCar(TrainCar::DiningCar);

			newCar->m_next = prevCar->m_next;
			prevCar->m_next = newCar;
		}

		break;
	}

	case TrainCar::SleepingCar: {
		// Adds the sleeping car to the end of the train no matter what.
		// This is simpler than adding it in front of the other sleeping cars.
		TrainCar* prevCar = getFinalCar();
		TrainCar* newCar = new TrainCar(TrainCar::SleepingCar);

		// Even though prevCar->m_next will always be NULL, I used the same snippet I
		// used for all the other cars to remain consistent.
		newCar->m_next = prevCar->m_next;
		prevCar->m_next = newCar;

		// It's crucial that the counter is incremented BEFORE adding the dining car.
		// Otherwise we'd get stuck in an infinite loop.
		m_numSleepingCar++;
		// DiningCar case self-checks to make sure it isn't adding more than one DiningCar.
		// I decided not to check again here because the cost of calling a function isn't
		// going to make a sizeable difference in the performance of the program.
		addCar(TrainCar::DiningCar);
		break;
	}
	default: {
		cout << "Error in Train::addCar : user tried to add a TrainCar::cType that is not valid." << endl;
	}
	}

}

bool Train::removeCar(TrainCar::cType car) {
	switch(car) {
	case TrainCar::Locomotive: {
		TrainCar* firstLocomotive = getNthCarOfType(TrainCar::Locomotive, 1);
		if(firstLocomotive != NULL){
			// TODO: If you can't make a train invalid check to make sure that the first is not the final.
			m_head->m_next = firstLocomotive->m_next;
			delete firstLocomotive;
			return true;
		}
		break;
	}

	case TrainCar::BusinessClass: {
		if(m_numBusinessClass > 0) {
			TrainCar* prevCar = getFirstCarBeforeType(TrainCar::BusinessClass);
			TrainCar* businessCar = prevCar->m_next;

			prevCar->m_next = businessCar->m_next;
			delete businessCar;

			m_numBusinessClass--;

			// Rebalance snack car if there is one and the last BussinessClass car was removed.
			if(m_numBusinessClass <= 0) {
				if(m_hasSnackCar) {
					if(m_numCoachClass > 0) {
						removeCar(TrainCar::SnackCar);
						addCar(TrainCar::SnackCar);
					} else {
						removeCar(TrainCar::SnackCar);
					}
				}
			}
			return true;
		}
		break;
	}

	case TrainCar::SnackCar: {
		// Check to make sure there is a snack car
		if(m_hasSnackCar) {
			m_hasSnackCar = false;

			TrainCar* prevCar = getFirstCarBeforeType(TrainCar::SnackCar);
			TrainCar* snackCar = prevCar->m_next;

			prevCar->m_next = snackCar->m_next;
			delete snackCar;
			return true;
		}
		break;
	}

	case TrainCar::CoachClass: {
		if (m_numCoachClass > 0) {
			TrainCar* prevCar = getFirstCarBeforeType(TrainCar::CoachClass);
			TrainCar* coachCar = prevCar->m_next;

			prevCar->m_next = coachCar->m_next;
			delete coachCar;

			m_numCoachClass--;

			// If the train has a SnackCar, rebalance it because it could've gotten out of place.
			if(m_hasSnackCar) {
				removeCar(TrainCar::SnackCar);
				addCar(TrainCar::SnackCar);
			}
			return true;
		}
		break;
	}

	/***
	 * I set up SleepingCar and DiningCar in a way so that each case only directly removes
	 * train cars of its same type. I had to add a bunch of things to make sure they didn't
	 * get caught in a loop because they each they might need to be removed at the same time.
	 */
	case TrainCar::DiningCar: {
		TrainCar* prevCar = getFirstCarBeforeType(TrainCar::DiningCar);
		// Check to see if there is actually a DiningCar
		if(prevCar != NULL) {
			TrainCar* diningCar = prevCar->m_next;

			prevCar->m_next = diningCar->m_next;
			delete diningCar;

			// Go through and get rid of all the sleeping cars.
			while(m_numSleepingCar > 0) {
				removeCar(TrainCar::SleepingCar);
			}
			return true;
		}
		break;
	}

	case TrainCar::SleepingCar: {
		// Make sure there actually is a sleeping car to remove.
		if(m_numSleepingCar > 0) {
			TrainCar* prevCar = getFirstCarBeforeType(TrainCar::SleepingCar);
			TrainCar* sleepingCar = prevCar->m_next;

			// Deletion operation
			prevCar->m_next = sleepingCar->m_next;
			delete sleepingCar;

			m_numSleepingCar--;


			// If there is a dining car and there are no more SleepingCarsd, remove DiningCar.
			// The conditional is essential for preventing infinite loops.

			TrainCar* isThereADiningCar = getFinalCarOfType(TrainCar::DiningCar);
			if(m_numSleepingCar == 0 && isThereADiningCar != NULL) {
				removeCar(TrainCar::DiningCar);
			}
			return true;
		}
		break;
	}

	default: {
		cout << "Error in Train::removeCar : user tried to remove a TrainCar::cType that is not valid." << endl;
		return false;
	}
	}
	return false;
}


int Train::getNumber() const {
	return m_number;
}

void Train::setNumber(int num) {
	m_number = num;
}

Time::Time Train::getDepartureTime() const {
	return m_departs;
}

void Train::setDepartureTime(const Time &t) {
	m_departs = t;
}

string Train::getDestination() const {
	return m_destination;
}

void Train::setDestination(string dest) {
	m_destination = dest;
}

bool Train::isValid() {
	bool locomotiveAtFront = m_head->getType() == TrainCar::Locomotive;
	bool coachCarExists = (getFinalCarOfType(TrainCar::CoachClass) != NULL);

	if(!locomotiveAtFront) {
		cout << "Error in Train::isValid() : Train #" << m_number << " does not have a Locomotive in the front." << endl;
	}

	if(!coachCarExists) {
		cout << "Error in Train::isValid() : Train #" << m_number << " does not have any coaches." << endl;
	}

	return coachCarExists && locomotiveAtFront;
}

/// Helper function to find the final car in a train.
TrainCar* Train::getFinalCar() {
	TrainCar* nodeOn = m_head;
	while(nodeOn->m_next != NULL) {
		nodeOn = nodeOn->m_next;
	}
	return nodeOn;
}

// Returns a pointer to the final car of a given type in a train.
// Returns NULL if there is no car of given type.
TrainCar* Train::getFinalCarOfType(TrainCar::cType type){
	TrainCar* nodeOn = m_head;
	TrainCar* lastOfType = NULL;
	while(nodeOn->m_next != NULL) {
		if(nodeOn->getType() == type) {
			lastOfType = nodeOn;
		}
		nodeOn = nodeOn->m_next;
	}
	return lastOfType;
}

// Returns a pointer to the Nth car of a given type in the train.
// Returns NULL if no car of that type or number appears in the train.
// Count starts at 1.
TrainCar* Train::getNthCarOfType(TrainCar::cType type, int n) {
	TrainCar* nodeOn = m_head;
	TrainCar* nthCar = NULL;
	// The number of cars of a given type found.
	int foundSoFar = 0;
	while(nodeOn->m_next != NULL && nthCar == NULL) {
		if(nodeOn->getType() == type) {
			foundSoFar++;
		}

		if(foundSoFar == n) {
			nthCar = nodeOn;
		}

		nodeOn = nodeOn->m_next;
	}
	return nthCar;
}

// Returns a pointer to the car before the first instance of a given type.
// Useful for removal of SnackCar and adding of DiningCar
// Returns NULL if no such car exists.
TrainCar* Train::getFirstCarBeforeType(TrainCar::cType type) {
	TrainCar* nodeOn = m_head;
	TrainCar* carFound = NULL;

	while(nodeOn->m_next != NULL && carFound == NULL) {
		if(nodeOn->m_next->getType() == type) {
			carFound = nodeOn;
		}

		nodeOn = nodeOn->m_next;
	}

	return carFound;
}

ostream &operator<<(ostream &output, const Train &train) {
	TrainCar* nodeOn = train.m_head;
	while(nodeOn->m_next != NULL) {
		output << *nodeOn << " ";
		nodeOn = nodeOn->m_next;
	}
	output << *nodeOn << endl;
	return output;
}

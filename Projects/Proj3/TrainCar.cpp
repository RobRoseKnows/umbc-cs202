//
// File: TrainCar.cpp
// Author: Robert Rose
// Date: 3/28/16
// Section: 03
// E-mail: robrose2@umbc.edu
// 
// CMSC 202 Project file
//
// COMPLETE THE IMPLEMENTATION AS INSTRUCTED
//

#include <iostream>
using namespace std;

#include "TrainCar.h"

TrainCar::TrainCar() :
		m_next( NULL), m_type(NoType) { /* empty constructor body */
}

TrainCar::TrainCar(TrainCar::cType car) :
		m_next( NULL), m_type(car) { /* empty constructor body */
}

void TrainCar::setType(TrainCar::cType car) {
	m_type = car;
}

TrainCar::cType TrainCar::getType() const {
	return m_type;
}

ostream& operator<<(ostream &outStream, const TrainCar& car) {
	//Switch statement for all the different cases.
	switch (car.getType()) {
	case TrainCar::Locomotive:
		outStream << "// Locomotive ]]";
		break;
	case TrainCar::CoachClass:
		outStream << "[ oo Coach oo ]";
		break;
	case TrainCar::BusinessClass:
		outStream << "[  Business  ]";
		break;
	case TrainCar::DiningCar:
		outStream << "[ -  Dining - |";
		break;
	case TrainCar::SnackCar:
		outStream << "[ -- Snack -- ]";
		break;
	case TrainCar::SleepingCar:
		outStream << "[ o Sleeper o ]";
		break;
	case TrainCar::NoType:
		outStream << "[ NO TYPE ]";
		break;
	default:
		outStream << "[ INVALID ]";
	}

	return outStream;

}

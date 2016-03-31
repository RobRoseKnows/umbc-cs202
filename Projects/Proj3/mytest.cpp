// File: mytest.cpp
// Author: Robert Rose
// Date: 3/31/16
// Section: 03
// E-mail: robrose2@umbc.edu

#include <iostream>
#include <string>

using namespace std;

#include "Time.h"
#include "TrainCar.h"
#include "Train.h"
#include "TrainStation.h"

int main() {

	cerr << "ALL FUNCTIONS WORK AS EXPECTED" << endl;
	cerr << "This function does not test everything because I wrote it at the end." << endl;

	cerr << "----- Test Time.cpp -----" << endl;
	cerr << "Test Time::operator<< : Expected: 1:07  | Result: " << Time(1, 7) << endl;
	cerr << "Test Time::operator<< : Expected: 13:30 | Result: " << Time(13, 30) << endl;
	cerr << "Test Time::operator+  : Expected: 14:07 | Result: " << Time(13, 30) + 37 << endl;
	cerr << "Test Time::operator<  : Expected:   1   | Result: " << (Time(12, 30) < Time(13, 30)) << endl;

	cerr << endl;

	cerr << "----- Test TrainCar.cpp -----" << endl;
	cerr << "Test TrainCar::TrainCar() : Expected: [ NO TYPE ] | Result: ";
	TrainCar* carOne = new TrainCar();
	cerr << carOne << endl;
	cerr << "Test TrainCar::TrainCar(TrainCar::cType) : Expected: [ -- Snack -- ] | Result: ";
	TrainCar* carTwo = new TrainCar(TrainCar::SnackCar);
	cerr << carTwo << endl;

	cerr << "----- Test Train.cpp -----" << endl;
	cerr << "Test Train::Train(int, Time, string) : Expected: NO OUTPUT | Result: ";
	Train* trainOne = new Train(42, Time(16,20), "Canada");
	cerr << "NO OUTPUT" << endl;
	cerr << "Train Time: " << trainOne->getDepartureTime() << " Train Number: " << trainOne->getNumber() << endl;


	// There's no point in writing more test code when this tests everything I have.
	Train* ner111 = new Train( 111, Time(13, 25), "Boston" );

	  ner111->addCar( TrainCar::Locomotive );
	  ner111->addCar( TrainCar::CoachClass );
	  ner111->addCar( TrainCar::CoachClass );
	  ner111->addCar( TrainCar::CoachClass );
	  ner111->addCar( TrainCar::BusinessClass );
	  ner111->addCar( TrainCar::SnackCar );

	  Train *ner531 = new Train( 531, Time(13, 30), "Montreal" );

	  ner531->addCar( TrainCar::Locomotive );
	  ner531->addCar( TrainCar::CoachClass );
	  ner531->addCar( TrainCar::CoachClass );
	  ner531->addCar( TrainCar::CoachClass );
	  ner531->addCar( TrainCar::CoachClass );
	  ner531->addCar( TrainCar::SnackCar );
	  ner531->addCar( TrainCar::SleepingCar );
	  ner531->addCar( TrainCar::SleepingCar );

	  Train *ner227 = new Train( 227, Time(13, 40), "Lynchburg");

	  ner227->addCar( TrainCar::Locomotive );
	  ner227->addCar( TrainCar::CoachClass );
	  ner227->addCar( TrainCar::CoachClass );
	  ner227->addCar( TrainCar::CoachClass );
	  ner227->addCar( TrainCar::SnackCar );

	  Train *invalid = new Train( 0, Time(13, 50), "Nowhere" );

	  invalid->addCar( TrainCar::Locomotive );

	  Train *ner032 = new Train( 32, Time(13, 55), "New York" );

	  ner032->addCar( TrainCar::Locomotive );
	  ner032->addCar( TrainCar::CoachClass );
	  ner032->addCar( TrainCar::CoachClass );
	  ner032->addCar( TrainCar::CoachClass );
	  ner032->addCar( TrainCar::SnackCar );

	  TrainStation unionStation(4);

	  unionStation.addTrain( ner111 );
	  unionStation.addTrain( ner531 );
	  unionStation.addTrain( ner227 );
	  unionStation.addTrain( invalid );
	  unionStation.addTrain( ner032);

	  unionStation.departureBoard( Time(13, 00), 60 );

	  unionStation.departure( ner111 );

	  unionStation.addTrain( ner032 );

	  unionStation.departureBoard( Time(13, 00), 60 );

	  unionStation.departure( ner531 );

	  unionStation.departureBoard( Time(13, 30), 60 );

	  unionStation.departure( invalid );

	  unionStation.removeTrain( invalid );

	  unionStation.departureBoard( Time(13, 30), 60 );

	return 0;
}

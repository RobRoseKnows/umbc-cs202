#include <iostream>
#include <string>

using namespace std;

#include "Time.h"

int main() {

	cout << Time(1, 7) << endl;
	cout << Time(12, 30) << endl;
	cout << Time(12, 30) + 37 << endl;
	cout << (Time(12, 30) < Time(13, 30)) << endl;

	return 0;
}

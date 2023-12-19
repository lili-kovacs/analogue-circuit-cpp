#define _USE_MATH_DEFINES
#include "circuit.h"
#include "component.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "interface.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>

int main()
{
	std::string starter = welcome(); // user decides what type of circuit to build
	circuit C{ starter }; // construct circuit
	C.set_frequency(); // user sets initial circuit frequency

	// menu is opened, namespace determinded by type of circuit
	if (starter == "s" || starter == "p") {
		using namespace simple;
		menu(C);
	}
	if (starter == "c") {
		using namespace compound;
		menu(C);
	}
	return 0;
}
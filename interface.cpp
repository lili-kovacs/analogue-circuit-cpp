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
#include <tuple>

std::string string_input(std::vector<std::string> acceptable_values)
{
	std::string input;
	bool valid = false;
	std::getline(std::cin, input);
	for (auto& it : acceptable_values) {
		if (input == it) {
			valid = true;
			break;
		}
	}
	while (!valid) {
		std::cout << "Please enter a valid choice: ";
		std::getline(std::cin, input);
		for (auto& it : acceptable_values) {
			if (input == it) {
				valid = true;
				break;
			}
		}
	}
	return input;
}

double number_input() {
	std::string temp;
	std::getline(std::cin, temp);
	std::stringstream temp_ss(temp);
	bool valid = false;
	double number;
	if (temp_ss >> number && !temp_ss.fail() && temp_ss.eof()) {
		if (std::stod(temp) > 0) {
			valid = true;
			number = std::stod(temp);
		}
	}
	while (!valid) {
		std::cout << "Please enter a valid number (positive double): ";
		std::getline(std::cin, temp);
		std::stringstream temp_ss(temp);
		if (temp_ss >> number && !temp_ss.fail() && temp_ss.eof()) {
			if (std::stod(temp) > 0) {
				valid = true;
				number = std::stod(temp);
			}
		}
	}
	return number;
}

std::string welcome()
{
	std::cout << "Let's create an analogue circuit! \n";
	std::cout << "Choose if you would like the components to be series or in parallel or if you want a more compound circuit. \n";
	std::cout << "For series or parallel, you will be able to switch between the two cases, display the circuit and change its frequency at any point. \n";
	std::cout << "For a more compound one, you will be able to choose how you want to connect new components to the existing circuit. \n" << std::endl;
	std::cout << "Type s, p or c to choose: " << std::endl;
	return string_input(circuit_choices);
}

// specify menu options for each namespace and link them to their corresponding functions from the circuit class
void simple::menu(circuit c) 
{
	std::cout << "~~~ AC CIRCUIT ~~~ \n";
	std::cout << " 1. Add component \n";
	std::cout << " 2. Display circuit information \n";
	std::cout << " 3. Display circuit \n";
	std::cout << " 4. Display component information \n";
	std::cout << " 5. Change frequency \n";
	std::cout << " 6. Change circuit type \n";
	std::cout << " 7. Quit \n";
	int choice;
	do
	{
		std::cout << "Enter a number to choose what to do (1-7): ";
		choice = std::stoi(string_input(menu_choices));
		switch (choice)
		{
		case 1: c = add_component(c); break;
		case 2: c.circuit_info(); break;
		case 3: c.display_circuit(); break;
		case 4: c.component_info(); break;
		case 5: c.set_frequency(); break;
		case 6: c.change_type(); break;
		case 7: exit(1); break;
		}
	} while (true);
}

void compound::menu(circuit c)
{
	std::complex<double> Z; // a complex value is declared to keep track of the impedance of the circuit as new components are added
	std::tuple<circuit, std::complex<double>> circuit_data(c, Z); // tuple of circuit and its impedance
	std::cout << "~~~ AC CIRCUIT ~~~ \n";
	std::cout << " 1. Add component \n";
	std::cout << " 2. Display circuit information \n";
	std::cout << " 3. Display component information \n";
	std::cout << " 4. Quit \n";
	int choice;
	do
	{
		std::cout << "Enter a number to choose what to do (1-4): ";
		choice = std::stoi(string_input(menu_choices));
		switch (choice)
		{
		case 1: circuit_data = add_component(circuit_data); break;
		case 2: std::get<0>(circuit_data).compound_circuit_info(std::get<1>(circuit_data)); break;
		case 3: std::get<0>(circuit_data).component_info(); break;
		case 4: exit(1); break;
		}
	} while (true);
}

// define add_component() function for both namespaces: user input validation and then add_component template (from circuit class) is used
circuit simple::add_component(circuit c)
{
	std::string newcomp;
	double val;
	std::cout << "Please specify what type of component you'd like to add. Type 'resistor' or 'R' for a resistor, 'capacitor' or 'C' for a capacitor or 'inductor or 'I' for an inductor. ";
	newcomp = string_input(component_choices);
	if (newcomp == "R" || newcomp == "resistor" || newcomp == "r" || newcomp == "Resistor") {
		std::cout << "Enter the resistance (in Ohms): ";
		val = number_input();
		c.add_component<resistor>(val);
	}
	if (newcomp == "C" || newcomp == "capacitor" || newcomp == "c" || newcomp == "Capacitor") {
		std::cout << "Enter the capacitance (in Farads): ";
		val = number_input();
		c.add_component<capacitor>(val);
	}
	if (newcomp == "I" || newcomp == "inductor" || newcomp == "i" || newcomp == "Inductor") {
		std::cout << "Enter the inductance (in Henrys): ";
		val = number_input();
		c.add_component<inductor>(val);
	}
	return c;
}

std::tuple<circuit, std::complex<double>> compound::add_component(std::tuple<circuit, std::complex<double>> tuple)
{
	circuit c_temp = std::get<0>(tuple);
	std::complex<double> z_temp = std::get<1>(tuple);
	std::string newcomp;
	std::string how;
	double val;
	if (c_temp.get_components().size() == 0) { // for the first element, the user does not need to decide how to add it - it would not make sense
		how = "s";
	}
	else {
		std::cout << "How would you like to add the component to the existing circuit? Type 's' for series or 'p' for parallel.";
		how = string_input(component_connection_choices);
	}
	std::cout << "Please specify what type of component you'd like to add. Type 'resistor' or 'R' for a resistor, 'capacitor' or 'C' for a capacitor or 'inductor or 'I' for an inductor. ";
	newcomp = string_input(component_choices);
	if (newcomp == "R" || newcomp == "resistor" || newcomp == "r" || newcomp == "Resistor") {
		std::cout << "Enter the resistance (in Ohms): ";
		val = number_input();
		c_temp.add_component<resistor>(val);
	}
	if (newcomp == "C" || newcomp == "capacitor" || newcomp == "c" || newcomp == "Capacitor") {
		std::cout << "Enter the capacitance (in Farads): ";
		val = number_input();
		c_temp.add_component<capacitor>(val);
	}
	if (newcomp == "I" || newcomp == "inductor" || newcomp == "i" || newcomp == "Inductor") {
		std::cout << "Enter the inductance (in Henrys): ";
		val = number_input();
		c_temp.add_component<inductor>(val);
	}
	// simple namespace function also includes updating the impedance value of the circuit when adding a new component
	if (how == "s" || how == "series") {
		z_temp += c_temp.get_components().back()->get_component_impedance();
	}
	if (how == "p" || how == "parallel") {
		z_temp = pow(z_temp, -1) + pow(c_temp.get_components().back()->get_component_impedance(), -1);
		z_temp = pow(z_temp, -1);
	}
	return std::tuple<circuit, std::complex<double>>{c_temp, z_temp};
}
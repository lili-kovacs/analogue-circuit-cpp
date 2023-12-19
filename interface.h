#ifndef INTERFACE_H
#define INTERFACE_H
#include "circuit.h"
#include <vector>
#include <string>

// define acceptable values for user inputs
const std::vector<std::string> circuit_choices = { "s", "p", "c" };
const std::vector<std::string> component_choices = { "R", "resistor", "r", "Resistor", "C", "capacitor", "c", "Capacitor", "I", "inductor", "i", "Inductor"};
const std::vector<std::string> component_connection_choices = { "s", "series", "p", "parallel" };

std::string string_input(std::vector<std::string> acceptable_values);
double number_input();
std::string welcome();

namespace simple
{
	void menu(circuit c);
	circuit add_component(circuit c);
	const std::vector<std::string> menu_choices = { "1", "2", "3", "4", "5", "6", "7"}; // acceptable values for menu choices are defines
																						// separately for each namespace
}
namespace compound
{
	void menu(circuit c);
	std::tuple<circuit, std::complex<double>> add_component(std::tuple<circuit, std::complex<double>> pair);
	const std::vector<std::string> menu_choices = { "1", "2", "3", "4" };
}

#endif
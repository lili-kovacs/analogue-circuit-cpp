#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "component.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>

class circuit
{
protected:
	static double frequency; // static so can easily be used for component calculations
							// (user does not need to specify which circuit's frequency to consider when adding components)
	char structure; // s or p for series or parallel or c for compound
	std::vector<std::shared_ptr<component>> components;
	std::complex<double> impedance;

public:
	circuit() : structure{ }, impedance { } {}
	circuit(std::string type) : structure{ 0 }, impedance{0,0} {
		if (type == "s") {
			structure = 's';
		}
		if (type == "p") {
			structure = 'p';
		}
		if (type == "c") {
			structure = 'c';
		}
	}
	~circuit() {}

	void set_frequency(); // allows user to change frequency of the circuit. also updates the frequencies of the existing components

	static double get_frequency()
	{
		return frequency;
	}

	void print_frequency() const;
	int change_type(); // switches between s and p (not an option for compound namespace)
	
	template <class ctype> void add_component(double value) // template function to add a component
	{
		components.push_back(std::make_shared<ctype>(value));
		std::cout << "Component added!" << std::endl;
	}

	std::complex<double> get_impedance() const;
	double get_magnitude() const;
	double get_phase() const;
	std::vector<std::shared_ptr<component>> get_components() const;
	void circuit_info() const;
	void compound_circuit_info(std::complex<double> z);
	void component_info() const;
	int display_circuit() const;
};

#endif
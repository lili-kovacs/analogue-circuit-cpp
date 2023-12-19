#ifndef RESISTOR_H
#define RESISTOR_H

#include "circuit.h"
#include "component.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>

class resistor : public component
{
private:
	double resistance, component_frequency;
	std::string name, symbol;
public:
	resistor() : resistance{}, component_frequency{}, name{}, symbol{} {}
	resistor(double R) : resistance{ R }, component_frequency{ circuit::get_frequency() }, name{"resistor"}, symbol{"[R]"} {}
	// some members can be defined without user input eg. name and symbol: these are only used for output
	~resistor() {}

	void set_component_frequency(double freq) override;
	double get_component_frequency() const override;
	std::complex<double> get_component_impedance() const override;
	double get_component_magnitude() const override;
	double get_component_phase() const override;
	std::string get_component_type() const override;
	std::string get_component_symbol() const override;
};

#endif
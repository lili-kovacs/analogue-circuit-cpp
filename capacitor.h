#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "circuit.h"
#include "component.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>

class capacitor : public component
{
private:
	double capacitance, component_frequency;
	std::string name, symbol;
public:
	capacitor() : capacitance{}, component_frequency{ }, name{}, symbol{} {}
	capacitor(double C) : capacitance{ C }, component_frequency{ circuit::get_frequency() }, name{"capacitor"}, symbol{"|C|"} {}
	~capacitor() {}

	void set_component_frequency(double freq) override;
	double get_component_frequency() const override;
	std::complex<double> get_component_impedance() const override;
	double get_component_magnitude() const override;
	double get_component_phase() const override;
	std::string get_component_type() const override;
	std::string get_component_symbol() const override;
};

#endif
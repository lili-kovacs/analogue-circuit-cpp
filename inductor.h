#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "circuit.h"
#include "component.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>

class inductor : public component
{
private:
	double inductance, component_frequency;
	std::string name, symbol;
public:
	inductor() : inductance{ }, component_frequency{}, name {}, symbol{} {}
	inductor(double L) : inductance{ L }, component_frequency{ circuit::get_frequency() }, name{"inductor"}, symbol{"{L}"} {}
	~inductor() {}

	void set_component_frequency(double freq) override;
	double get_component_frequency() const override;
	std::complex<double> get_component_impedance() const override;
	double get_component_magnitude() const override;
	double get_component_phase() const override;
	std::string get_component_type() const override;
	std::string get_component_symbol() const override;
};

#endif
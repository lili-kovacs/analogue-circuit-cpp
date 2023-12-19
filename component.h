#ifndef COMPONENT_H
#define COMPONENT_H

#include "circuit.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>

class component // abstract base class for components: declare set_frequency() and all get functions
{
public:
	virtual ~component() {}
	virtual void set_component_frequency(double freq) = 0;
	virtual double get_component_frequency() const = 0;
	virtual std::complex<double> get_component_impedance() const = 0;
	virtual double get_component_magnitude() const = 0;
	virtual double get_component_phase() const = 0;
	virtual std::string get_component_type() const = 0;
	virtual std::string get_component_symbol() const = 0;
};

#endif
#include "circuit.h"
#include "component.h"
#include "resistor.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>

void resistor::set_component_frequency(double freq)
{
	component_frequency = freq;
}

double resistor::get_component_frequency() const
{
	return component_frequency;
}

std::complex<double> resistor::get_component_impedance() const
{
	return std::complex<double>{resistance,0};
}

double resistor::get_component_magnitude() const
{
	return resistance;
}

double resistor::get_component_phase() const // the phases of individual components do not depend on any parameters, they are always the same
{
	return 0;
}

std::string resistor::get_component_type() const
{
	return name;
}

std::string resistor::get_component_symbol() const
{
	return symbol;
}
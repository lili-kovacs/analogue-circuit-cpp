#define _USE_MATH_DEFINES
#include "circuit.h"
#include "component.h"
#include "capacitor.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>

void capacitor::set_component_frequency(double freq)
{
	component_frequency = freq;
}

double capacitor::get_component_frequency() const
{
	return component_frequency;
}

std::complex<double> capacitor::get_component_impedance() const
{
	std::complex<double> z{ 0,-1/(capacitance * component_frequency * 2 * M_PI) };
	return z;
}

double capacitor::get_component_magnitude() const
{
	return std::abs(capacitor::get_component_impedance().imag()); // since this component's impedance does not have a real part
}

double capacitor::get_component_phase() const
{
	return M_PI/2;
}

std::string capacitor::get_component_type() const
{
	return name;
}

std::string capacitor::get_component_symbol() const
{
	return symbol;
}
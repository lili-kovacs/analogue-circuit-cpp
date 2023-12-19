#define _USE_MATH_DEFINES
#include "circuit.h"
#include "component.h"
#include "inductor.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>

void inductor::set_component_frequency(double freq)
{
	component_frequency = freq;
}

double inductor::get_component_frequency() const
{
	return component_frequency;
}

std::complex<double> inductor::get_component_impedance() const
{
	std::complex<double> z{ 0,inductance*component_frequency*2*M_PI };
	return z;
}

double inductor::get_component_magnitude() const
{
	return inductor::get_component_impedance().imag();
}

double inductor::get_component_phase() const
{
	return -M_PI/2;
}

std::string inductor::get_component_type() const
{
	return name;
}

std::string inductor::get_component_symbol() const
{
	return symbol;
}
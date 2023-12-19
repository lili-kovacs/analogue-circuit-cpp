#include "circuit.h"
#include "component.h"
#include "interface.h"
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>

void circuit::set_frequency()
{
	std::cout << "Enter the frequency of the circuit (in Hz): ";
	frequency = number_input();
	for (int i = 0; i < components.size(); i++) {
		components[i]->set_component_frequency(frequency);
	}
}

void circuit::print_frequency() const
{
	std::cout << "The frequency of the circuit is " << frequency << " Hz." << std::endl;
}

int circuit::change_type()
{
	if (structure == 's') {
		structure = 'p';
		std::cout << "Components are now in parallel." << std::endl;
		return 0;
	}
	if (structure == 'p') {
		structure = 's';
		std::cout << "Components are now in series." << std::endl;
		return 0;
	}
	else {
		return 0;
	}
}

std::complex<double> circuit::get_impedance() const
{
	if (structure == 's') {
		std::complex<double> z;
		for (int i = 0; i < components.size(); i++) {
			z += components[i]->get_component_impedance();
		}
		return z;
	}
	if (structure == 'p') {
		std::complex<double> z_rec;
		for (int i = 0; i < components.size(); i++) {
			z_rec += pow(components[i]->get_component_impedance(), -1); // sum of reciprocals
		}
		return pow(z_rec, -1);
	}
	else {
		void();
	}
}

double circuit::get_magnitude() const
{
	return std::sqrt(std::pow(get_impedance().real(), 2) + std::pow(get_impedance().imag(), 2));
}

double circuit::get_phase() const
{
	double fraction = get_impedance().imag() / get_impedance().real();
	return std::atan(fraction);
}

std::vector<std::shared_ptr<component>> circuit::get_components() const
{
	return components;
}

void circuit::circuit_info() const
{
	std::cout << std::endl << "Circuit information: " << std::endl << "Circuit type: ";
	if (structure == 's') {
		std::cout << "series." << std::endl;
	}
	if (structure == 'p') {
		std::cout << "parallel." << std::endl;
	}
	circuit::print_frequency();
	std::cout << "Impedance of circuit Z(real, imaginary) = " << circuit::get_impedance() << " Ohms" << std::endl;
	std::cout << "Magnitude of impedance = " << circuit::get_magnitude() << " Ohms" << std::endl;
	std::cout << "Phase angle of impedance = " << circuit::get_phase() << " radians" << std::endl;
	std::cout << "Number of components: " << components.size() << std::endl << std::endl;
}

void circuit::compound_circuit_info(std::complex<double> z)
{
	std::cout << std::endl << "Circuit information: " << std::endl << "Circuit type: ";
	std::cout << "compound." << std::endl;
	circuit::print_frequency();
	std::cout << "Impedance of circuit Z(real, imaginary) = " << z << " Ohms" << std::endl;
	std::cout << "Magnitude of impedance = " << std::sqrt(std::pow(z.real(), 2) + std::pow(z.imag(), 2)) << " Ohms" << std::endl;
	std::cout << "Phase angle of impedance = " << std::atan(z.imag()/z.real()) << " radians" << std::endl;
	std::cout << "Number of components: " << components.size() << std::endl << std::endl;
}

void circuit::component_info() const
{
	std::cout << std::endl << "Component information: " << std::endl;
	for (int i = 0; i < components.size(); i++) {
		std::cout << "component: " << components[i]->get_component_type() << std::endl;
		std::cout << "\timpedance (real, imaginary): " << components[i]->get_component_impedance() << " Ohms" << std::endl;
		std::cout << "\tmagnitude of impedance: " << components[i]->get_component_magnitude() << " Ohms" << std::endl;
		std::cout << "\tphase: " << components[i]->get_component_phase() << " radians" << std::endl;
	}
	std::cout << std::endl;
}

int circuit::display_circuit() const
{
	if (components.size() == 0) {
		std::cout << "There are no components to display yet!" << std::endl;
		return 0;
	}
	std::cout << "Printing your circuit ... " << std::endl;
	if (structure == 's') {
		for (int i = 0; i < components.size(); i++) {
			std::cout << "---" << components[i]->get_component_symbol() << "---";
		}
		std::cout << std::endl;
		std::cout << "|";
		for (int i = 0; i < components.size(); i++) {
			std::cout << "         ";
		}
		std::cout << "|" << std::endl;
		std::cout << "|";
		for (int i = 0; i < components.size(); i++) {
			std::cout << "         ";
		}
		std::cout << "|" << std::endl;
		for (int i = 0; i < components.size(); i++) {
			if ((components.size()%2==0 && i == (components.size() / 2)) || (components.size() % 2 != 0 && i == (components.size() / 2) +1)) {
				std::cout << "(~)";
			}
			std::cout << "--------";
		}
		std::cout << std::endl;
	}
	if (structure == 'p') {
		for (int i = 0; i < components.size(); i++) {
			std::cout << "---" << components[i]->get_component_symbol() << "---" << std::endl;
			std::cout << "|        |" << std::endl;
			if (i == components.size() - 1) {
				std::cout << "---(~)---" << std::endl;
			}
			else {
				std::cout << "---------" << std::endl;
			}
		}
	}
	else {
		return 0;
	}
}

double circuit::frequency{}; // define static data member
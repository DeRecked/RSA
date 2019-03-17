// Standard libraries
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>

// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

int main() {
	try { 
		bool prime = false;		// Flag for prime success
		
		// File stream objects
		std::ofstream p_q("p_q.txt");
		std::ofstream e_n("e_n.txt"); 
		std::ofstream d_n("d_n.txt");

		// Big Unsigned object declaration and/or initialization
		BigUnsigned n;
		BigUnsigned p = 1, q = 1;

		// Big Integer object declaration and/or initialization
		BigInteger a, phi;
		BigInteger e = 65537, d = 0, r = 0, s = 0, g = 0;
	
		// Seed rand with system clock
		srand(time(NULL));

		std::cout << "\nGenerating prime p" << std::endl;		

		while (!prime) {							// Generate a random number p and test if it is prime
			p = 1, a = 3;							// Re-assign values of p and a for restart of loop
		
			for (int i = 0; i < 277; i++)			// Generate random off number that's at least 278 digits 
				p = p*10 + (rand() % 10);	
			p = p*10 + 7;							// Guarantee that p will be odd

			if (modexp(a, p-1, p) == 1) {			// First fermat test case
				a = 7;
				if (modexp(a, p-1, p) == 1)			// Second fermat test case
					prime = true;
			}
		}

		std::cout << "Generating prime q" << std::endl;
		prime = false;								// Reset prime flag
	
		while (!prime) {							// Generate a random number p and test if it is prime
			q = 1, a = 3;							// Re-assign values of p and a for restart of loop
		
			for (int i = 0; i < 277; i++)			// Generate random off number that's at least 278 digits 
				q = q*10 + (rand() % 10);	
			q = q*10 + 7;							// Guarantee that p will be odd

			if (modexp(a, q-1, q) == 1) {			// First fermat test case
				a = 7;
				if (modexp(a, q-1, q) == 1)			// Second fermat test case
					prime = true;
			}
		}
		
		std::cout << "Calculating n and phi" << std::endl;	
		
		// Calcualte n and phi
		n = p*q;
		phi = (p-1)*(q-1);
		std::cout << "Finding e and d" << std::endl;
		
		while (g != 1) {
			extendedEuclidean(phi, e, g, r, s);
			if (g == 1) break;
			e += 2;
		}

		// If s is negative, d = s + phi
		if (s < 0)
			d = s + phi;
		else d = s;		// Otherwise, d = s, where: phi*r + e*s = 1
		
		std::cout << "Writing values to output files" << std::endl;
		p_q << p << std::endl << q;		// Write p and q (p_q.txt)
		e_n << e << std::endl << n;		// Write public key (e_n.txt)
		d_n << d << std::endl << n;		// Write private key (d_n.txt)
	
		// Close file steams
		p_q.close();
		e_n.close();
		d_n.close();
	}
	catch(char const* err) {
		std::cout << "The library threw an exception:\n"
		<< err << std::endl;
	}

	return 0;
}

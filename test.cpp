#include <iostream>

int main() {
    int num = 11;          
    int bit_position = 0; 
    // int mask = (1 << bit_position); 
    // int result = num | mask;
	int mask = (num & (1 << bit_position));
    std::cout << "Résultat : " << mask << std::endl; 
    return 0;
}


/*
Enlever droit
	int num = 11;          
    int bit_position = 0; 
    int mask = ~(1 << bit_position); 
	int result = num & mask;
Mettre droit
	int num = 11;          
    int bit_position = 0; 
    int mask = (1 << bit_position); 
	int result = num | mask;
Determiner position
	    int num = 11;          
    int bit_position = 0; 
	int mask = (num & (1 << bit_position));
*/
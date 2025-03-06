#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string input = "hello";  // Example input
    std::istringstream iss(input);

    while (iss)
	{
        std::string wordParam;
    	std::getline(iss, wordParam, ',');
   		std::cout << "Extracted: " << wordParam << std::endl;
    }

    return 0;
}


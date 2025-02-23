#include <iostream>

int main() {
	std::string s = "test";
	s.erase(3);
	 s.erase(0,2);
	std::cout << s << "\n"; 
}

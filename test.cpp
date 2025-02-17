#include <iostream>
// #include <cstring>   // memset
// #include <unistd.h>  // close
#include <cstdarg>

void test (std::string tests...);

int main()
{
	test("Hello", "world", "this", "is", "a", "test", nullptr);
}

void test (std::string tests...)
{
	std::va_list args;
	va_start(args, tests);
	while (true)
	{
        const char* p = va_arg(args, const char*);
        if (!p)
			return;
		printf("%s | ", p);
    //    std::cout << p << std::endl;
    }
}
# mttoptcpp
C++ version of "mttopt"

# Example
```cpp
#include "mttlib/mttopt/mttopt.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	mttopt_optv optv = { mttopt_opt('f', IGNORE_COPIES | MUST_HAVE_ARG), mttopt_opt('t', IGNORE_COPIES | MUST_HAVE_ARG), mttopt_opt('u', HAS_NO_ARG) };
	char **av = argv + mttopt_extr_optv(argc, argv, optv), **avc = argv + argc;

	if (optv[0].found) std::cout << optv[0].shrt << ' ' << optv[0].arg << std::endl;
	if (optv[1].found) std::cout << optv[1].shrt << ' ' << optv[1].arg << std::endl;
	if (optv[2].found) std::cout << optv[2].shrt << std::endl;

	while (av < avc)
	{
		std::cout << *av << std::endl;
		av++;
	}

	return 0;
}
```

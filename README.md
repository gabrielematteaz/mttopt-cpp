# mttoptcpp
C++ version of "mttopt"

# Example
```cpp
#include "mttlib/mttopt/mttopt.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	mttopt_optv_t optv = { mttopt_opt_t('f', OPT_FLAGS_MUST_HAVE_ARG), mttopt_opt_t('t', OPT_FLAGS_CAN_HAVE_ARG), mttopt_opt_t('u', OPT_FLAGS_HAS_NO_ARG) };
	char **av = argv + mttopt_extr_optv(argc, argv, optv), **avc = argv + argc;

	if (optv[0].found) std::cout << '\'' << optv[0].shrt << "' '" << optv[0].arg << '\'' << std::endl;

	if (optv[1].found)
	{
		std::cout << '\'' << optv[1].shrt << '\'';

		if (optv[1].arg != nullptr) std::cout << " '" << optv[1].arg << '\'' << std::endl;
		else std::cout << std::endl;
	}

	if (optv[2].found) std::cout << '\'' << optv[2].shrt << '\'' << std::endl;

	while (av < avc)
	{
		std::cout << *av << std::endl;
		av++;
	}

	return 0;
}
```

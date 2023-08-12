#ifndef MTTOPT_HPP
#define MTTOPT_HPP

#include <vector>

enum mttopt_opt_flags : char
{
	OVERWRITE_ON_COPY = 0,
	IGNORE_COPIES = 1,
	EXIT_ON_COPY = 2,
	HAS_NO_ARG = 0,
	CAN_HAVE_ARG = 4,
	MUST_HAVE_ARG = 8,
};

struct mttopt_opt
{
	char *arg = nullptr;
	char shrt = 0;
	char flags = OVERWRITE_ON_COPY | HAS_NO_ARG;
	bool found = false;

	mttopt_opt();
	mttopt_opt(char shrt, char flags);
};

using mttopt_optv = std::vector<mttopt_opt>;

std::size_t mttopt_extr_optv(int argc, char *argv[], mttopt_optv &optv);

#endif
#ifndef MTTOPT_HPP
#define MTTOPT_HPP

#include <vector>

#define OPT_FS_OVERWRITE_ON_COPY 0
#define OPT_FS_IGNORE_COPIES 1
#define OPT_FS_EXIT_ON_COPY 2
#define OPT_FS_HAS_NO_ARG 0
#define OPT_FS_CAN_HAVE_ARG 4
#define OPT_FS_MUST_HAVE_ARG 12

struct mttopt_opt_t
{
	char shrt;
	int fs;
	bool found;
	const char *arg;

	inline mttopt_opt_t() noexcept
		: shrt(0), fs(OPT_FS_HAS_NO_ARG), found(false), arg(nullptr)
	{

	}

	inline mttopt_opt_t(char shrt, int fs) noexcept
		: shrt(shrt), fs(fs), found(false), arg(nullptr)
	{

	}
};

struct mttopt_wopt_t
{
	wchar_t shrt;
	int fs;
	bool found;
	const wchar_t *arg;

	inline mttopt_wopt_t() noexcept
		: shrt(0), fs(OPT_FS_HAS_NO_ARG), found(false), arg(nullptr)
	{

	}

	inline mttopt_wopt_t(wchar_t shrt, int fs) noexcept
		: shrt(shrt), fs(fs), found(false), arg(nullptr)
	{

	}
};

using mttopt_optv_t = std::vector < mttopt_opt_t >;
using mttopt_woptv_t = std::vector < mttopt_wopt_t >;

int mttopt_extr_optv(int argc, char *argv[], mttopt_optv_t &optv) noexcept;

int mttopt_extr_woptv(int wargc, wchar_t *wargv[], mttopt_woptv_t &woptv) noexcept;

#endif
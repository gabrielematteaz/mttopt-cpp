#include "mttopt.hpp"

mttopt_opt_t::mttopt_opt_t()
	: shrt(0), flags(0), found(false), arg(nullptr)
{

}

mttopt_opt_t::mttopt_opt_t(uint8_t shrt, uint8_t flags)
	: shrt(shrt), flags(flags), found(false), arg(nullptr)
{

}

int mttopt_extr_optv(int argc, char *argv[], mttopt_optv_t &optv)
{
	char **av, **avc, *arg, *a;
	struct mttopt_opt_t *ov, *ovc;
	uint8_t ac, flags;

	if (argv == nullptr) return 0;

	av = argv + 1;
	avc = argv + argc;
	ovc = optv.data() + optv.size();
	
	while (av < avc)
	{
		arg = *av;

		if (*arg == '-')
		{
			a = arg + 1;

			if (*a == '-')
			{
				av++;

				break;
			}

			ac = *a;

			while (ac)
			{
				ov = optv.data();

				while (ov < ovc)
				{
					if (ac == ov->shrt)
					{
						flags = ov->flags;

						if (ov->found)
						{
							if (flags & OPT_FLAGS_IGNORE_COPIES)
							{
								if (flags & OPT_FLAGS_CAN_HAVE_ARG)
								{
									if (flags & OPT_FLAGS_MUST_HAVE_ARG)
									{
										a++;

										if (*a == 0) av++;
									}

									goto next;
								}

								break;
							}
							else if (flags & OPT_FLAGS_EXIT_ON_COPY)
							{
								av++;

								if (flags & OPT_FLAGS_MUST_HAVE_ARG)
								{
									a++;

									if (*a == 0) av++;
								}

								goto exit;
							}
						}

						ov->found = 1;

						if (flags & OPT_FLAGS_CAN_HAVE_ARG)
						{
							a++;

							if ((flags & OPT_FLAGS_MUST_HAVE_ARG) == 12)
							{
								if (*a) ov->arg = a;
								else
								{
									av++;
									ov->arg = *av;
								}
							}
							else ov->arg = *a ? a : nullptr;

							goto next;
						}

						ov->arg = nullptr;

						break;
					}

					ov++;
				}

				a++;
				ac = *a;
			}
		}
		else break;

	next:
		av++;
	}

exit:
	return av - argv;
}
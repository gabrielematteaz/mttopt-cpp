#include "mttopt.hpp"

mttopt_opt::mttopt_opt()
{

}

mttopt_opt::mttopt_opt(char shrt, char flags)
	: shrt(shrt), flags(flags)
{

}

std::size_t mttopt_extr_optv(int argc, char *argv[], mttopt_optv &optv)
{
	char **av, **avc, *arg, *a, ac;
	mttopt_opt *ov, *ovc;

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
						if (ov->found)
						{
							if (ov->flags & IGNORE_COPIES)
							{
								if (ov->flags & MUST_HAVE_ARG)
								{
									a++;
									ac = *a;

									if (ac == 0) av++;

									goto next;
								}
								else if (ov->flags & CAN_HAVE_ARG) goto next;

								break;
							}
							else if (ov->flags & EXIT_ON_COPY)
							{
								av++;

								if (ov->flags & MUST_HAVE_ARG)
								{
									a++;
									ac = *a;

									if (ac == 0) av++;
								}

								goto exit;
							}
						}

						ov->found = true;

						if (ov->flags & CAN_HAVE_ARG)
						{
							a++;
							ac = *a;
							ov->arg = ac ? a : nullptr;

							goto next;
						}
						else if (ov->flags & MUST_HAVE_ARG)
						{
							a++;
							ac = *a;

							if (ac) ov->arg = a;
							else
							{
								av++;
								ov->arg = *av;
							}
							
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
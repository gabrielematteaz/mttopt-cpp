#include "mttopt.hpp"

int mttopt_extr_optv(int argc, char *argv[], mttopt_optv_t &optv) noexcept
{
	if (argv == nullptr) return 0;

	char **av = argv + 1, **avc = argv + argc;
	mttopt_opt_t *ovc = optv.data() + optv.size();
	
	while (av < avc)
	{
		char *arg = *av;

		if (*arg == '-')
		{
			char *a = arg + 1;

			if (*a == '-')
			{
				av++;

				break;
			}

			char ac = *a;

			while (ac)
			{
				mttopt_opt_t *ov = optv.data();

				while (ov < ovc)
				{
					if (ac == ov->shrt)
					{
						int fs = ov->fs;

						if (ov->found)
						{
							if (fs & OPT_FS_IGNORE_COPIES)
							{
								if (fs & OPT_FS_CAN_HAVE_ARG)
								{
									if (fs & OPT_FS_MUST_HAVE_ARG)
									{
										a++;

										if (*a == 0) av++;
									}

									goto next;
								}

								break;
							}
							else if (fs & OPT_FS_EXIT_ON_COPY)
							{
								av++;

								if (fs & OPT_FS_MUST_HAVE_ARG)
								{
									a++;

									if (*a == 0) av++;
								}

								goto exit;
							}
						}

						ov->found = 1;

						if (fs & OPT_FS_CAN_HAVE_ARG)
						{
							a++;

							if ((fs & OPT_FS_MUST_HAVE_ARG) == 12)
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

int mttopt_extr_woptv(int wargc, wchar_t *wargv[], mttopt_woptv_t &woptv) noexcept
{
	if (wargv == nullptr) return 0;

	wchar_t **wav = wargv + 1, **wavc = wargv + wargc;
	mttopt_wopt_t *wovc = woptv.data() + woptv.size();
	
	while (wav < wavc)
	{
		wchar_t *warg = *wav;

		if (*warg == '-')
		{
			wchar_t *wa = warg + 1;

			if (*wa == '-')
			{
				wav++;

				break;
			}

			wchar_t wac = *wa;

			while (wac)
			{
				mttopt_wopt_t *wov = woptv.data();

				while (wov < wovc)
				{
					if (wac == wov->shrt)
					{
						int fs = wov->fs;

						if (wov->found)
						{
							if (fs & OPT_FS_IGNORE_COPIES)
							{
								if (fs & OPT_FS_CAN_HAVE_ARG)
								{
									if (fs & OPT_FS_MUST_HAVE_ARG)
									{
										wa++;

										if (*wa == 0) wav++;
									}

									goto next;
								}

								break;
							}
							else if (fs & OPT_FS_EXIT_ON_COPY)
							{
								wav++;

								if (fs & OPT_FS_MUST_HAVE_ARG)
								{
									wa++;

									if (*wa == 0) wav++;
								}

								goto exit;
							}
						}

						wov->found = 1;

						if (fs & OPT_FS_CAN_HAVE_ARG)
						{
							wa++;

							if ((fs & OPT_FS_MUST_HAVE_ARG) == 12)
							{
								if (*wa) wov->arg = wa;
								else
								{
									wav++;
									wov->arg = *wav;
								}
							}
							else wov->arg = *wa ? wa : nullptr;

							goto next;
						}

						wov->arg = nullptr;

						break;
					}

					wov++;
				}

				wa++;
				wac = *wa;
			}
		}
		else break;

	next:
		wav++;
	}

exit:
	return wav - wargv;
}
#include "scop.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	Window* window = new Window(av[1], 800, 800);

	if (!window->getWindow())
	{
		delete window;
		return (1);
	}

	delete window;
	return (0);
}

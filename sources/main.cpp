#include "scop.hpp"

int	main(int ac, char **av)
{
	GLFWwindow*	window;

	if (!glfwInit())
		return (1);
	window = glfwCreateWindow(960, 640, "scop", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (1);
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	(void) ac;
	(void) av;
	return (0);
}

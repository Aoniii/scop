#include "scop.h"

int	main(int ac, char **av)
{
	if (!glfwInit())
		return (1);

	GLFWwindow* window = glfwCreateWindow(960, 640, "scop", NULL, NULL);
	if (!window)
	{
        glfwTerminate();
        return (1);
    }
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	glfwTerminate();
	(void) ac;
	(void) av;
	return (0);
}

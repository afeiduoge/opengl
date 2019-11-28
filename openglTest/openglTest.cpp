#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>


void key_Callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
	}
}

int main1()
{
	if (GL_FALSE == glfwInit())
	{
		std::cout << "Init GLFW False!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* glfwWindow = glfwCreateWindow(800, 600, "Learn OpenGL",nullptr, nullptr);
	if (glfwWindow == nullptr)
	{
		std::cout << "Create GLFW window False!" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(glfwWindow);
	glfwSetKeyCallback(glfwWindow, key_Callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init False!" << std::endl;
		return -1;
	}

	int iWndWidth, iWndHeight;
	glfwGetFramebufferSize(glfwWindow, &iWndWidth, &iWndHeight);
	glViewport(0, 0, iWndWidth, iWndHeight);

	while (!glfwWindowShouldClose(glfwWindow))
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(glfwWindow);
	}
	glfwTerminate();
	return 0;
}

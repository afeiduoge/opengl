#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


//define window size
const GLuint iWidth = 800, iHeight = 600;

//shader
const GLchar* vertexShaderSource = "#version 330 core \n"
"layout (location=0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x,position.y,position.z,1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(iWidth, iHeight, "Triangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;

	glewInit();

	int windowWidth, windowHeight;
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	//shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint bSuccess;
	GLchar strErrorLogs[256];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetShaderInfoLog(vertexShader, 256, NULL, strErrorLogs);
		std::cout << "Vertex Error Info  :" << strErrorLogs << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 256, NULL, strErrorLogs);
		std::cout << "Fragment Error Info  :" << strErrorLogs << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &bSuccess);
	if (!bSuccess) {
		glGetProgramInfoLog(shaderProgram, 256, NULL, strErrorLogs);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << strErrorLogs << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
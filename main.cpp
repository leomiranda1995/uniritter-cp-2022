#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit(); // habilitar a GLFW

	GLFWwindow* minhaJanela = glfwCreateWindow(800, 600, "Leonardo da Silva Miranda", NULL, NULL);

	if (!minhaJanela)
	{
		std::cout << "Falha ao criar a janela utilizando GLFW.";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(minhaJanela); // Escifico a janela atual da aplicação

	gladLoadGL(); // Habilita o uso da OpenGL
	glViewport(0, 0, 800, 600); // Área da janela que será utilizada

	glClearColor(0.0f, 0.5f, 0.5f, 0.0f); // Cor em RGBA
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(minhaJanela); // Atualiza para o próximo frame

	
	// Vertices do triângulo que vai ser desenhado
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0,
		 0.5f, -0.5f, 0.0,
		 0.0f,  0.5f, 0.0f
	};	
	
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const GLchar* fragmentShaderSource = "#version 330\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(0.2f, 0.1f, 0.7f, 1.0f);\n"
		"}\n\0";

	// Criei os shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // alocando um vertex shader (vertices dos triangulos)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);// cor dos fragmentos / pixels na tela

	// Adicionei os códigos
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	// Compilei
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Criar um programa para combinar os shaders compilados que irão rodar na GPU
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);	
	glAttachShader(shaderProgram, fragmentShader);

	// Linkar em um único elemento
	glad_glLinkProgram(shaderProgram);

	// Objetos que já foram linkados podem ser desalocads
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Criando o buffer com o array de vertices
	GLuint VBO; // Vertex buffer object - guarda os vertices
	glGenBuffers(1, &VBO); // buffer para guardar 1 array de vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (GLvoid*)0); // Especificar cada atributo que está indo no buffer
	glEnableVertexAttribArray(0);

	// Retornar para o início do buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(minhaJanela)) // Loop da Aplicação
	{
		glClearColor(0.0f, 0.5f, 0.5f, 0.0f); // Cor em RGBA
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Atualiza para o próximo frame

		glfwSwapBuffers(minhaJanela); // Atualiza para o próximo frame
		glfwPollEvents();
	}

	// DELETAR OS BUFFERS
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(minhaJanela);
	glfwTerminate(); // Encerra o uso da GLFW
	return 0;
}
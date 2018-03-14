// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"


#include <iostream>

#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"

using namespace std;

GLfloat red, green, blue;

GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;

Modelo *figura;
Modelo *cuadrado;

Shader *shader;
//Declaración de ventana
GLFWwindow *window;

void actualizar() { 
	int estadoDerecha = 
		glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		/*cuadrado->transformaciones =
			translate(cuadrado->transformaciones,
			vec3(0.001f, 0.0f, 0.0f));*/
		/*cuadrado->transformaciones =
			scale(cuadrado->transformaciones,
				vec3(1.001f, 1.001f, 1.001f));*/
		cuadrado->transformaciones =
			rotate(cuadrado->transformaciones,
				0.05f, vec3(0.0f, 0.0f, 1.0f));
	}
}

void dibujar() {
	figura->dibujar(GL_POLYGON);
	cuadrado->dibujar(GL_POLYGON);
}

void inicializarFigura() {
	figura = new Modelo();
	Vertice v1 =
	{ vec4(-1.0f,0.5f,0.0f,1.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	Vertice v2 =
	{ vec4(0.0f,-0.5f,0.0f,1.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	Vertice v3 =
	{ vec4(1.0f,0.5f,0.0f,1.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	figura->vertices.push_back(v1);
	figura->vertices.push_back(v2);
	figura->vertices.push_back(v3);
}

void inicializarCuadrado() {
	cuadrado = new Modelo();
	Vertice v1 =
	{ vec4(-0.3f,-0.3f,0.0f,1.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	Vertice v2 =
	{ vec4(-0.3f,0.3f,0.0f,1.0f), vec4(0.0f,1.0f,1.0f,1.0f) };
	Vertice v3 =
	{ vec4(0.3f,0.3f,0.0f,1.0f), vec4(1.0f,1.0f,0.0f,1.0f) };
	Vertice v4 =
	{ vec4(0.3f,-0.3f,0.0f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f) };
	cuadrado->vertices.push_back(v1);
	cuadrado->vertices.push_back(v2);
	cuadrado->vertices.push_back(v3);
	cuadrado->vertices.push_back(v4);
}

int main()
{
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit()) {
		//Si no se inició bien, terminar la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verficar si se creó bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializó bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;


	red = green = blue = 0.75f;

	inicializarFigura();
	inicializarCuadrado();

	//Crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";
	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID =
		glGetAttribLocation(shader->getID(), "posicion");
	colorID =
		glGetAttribLocation(shader->getID(), "color");
	transformacionesID =
		glGetUniformLocation(shader->getID(), "transformaciones");

	//Desenlazar shader
	shader->desenlazarShader();

	figura->shader = shader;
	figura->inicializarVertexArray(posicionID, colorID, transformacionesID);

	cuadrado->shader = shader;
	cuadrado->inicializarVertexArray(posicionID, colorID, transformacionesID);

	
	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}


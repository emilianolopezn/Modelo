#include "stdafx.h"
#include "Modelo.h"

Modelo::Modelo() {
	transformaciones = mat4(1.0f);
}

void Modelo::inicializarVertexArray(GLuint posicionID, 
	GLuint colorID, GLuint transformacionesID) {

	this->transformacionesID = transformacionesID;
	
	//Crear un vertex array
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Crear vertex buffer
	glGenBuffers(1, &bufferID);
	//De aqui en adelante se trabja con este buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Llenar el buffer
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertice) * vertices.size(),
		vertices.data(), GL_STATIC_DRAW);

	//Habilitar el atributo solo en el vertex array en uso
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	
	//Especificar a OpenGL como usar la memoria con ese atributo
	glVertexAttribPointer(posicionID, 4, GL_FLOAT,
		GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertice), (void*) sizeof(vec4));

	//Soltarlos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Modelo::dibujar(GLenum modoDibujo) {
	shader->enlazarShader();
	glBindVertexArray(vertexArrayID);

	glUniformMatrix4fv(transformacionesID, 1,
		GL_FALSE, &transformaciones[0][0]);

	glDrawArrays(modoDibujo, 0, vertices.size());
	glBindVertexArray(0);
	shader->desenlazarShader();
}
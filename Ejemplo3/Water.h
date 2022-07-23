#ifndef _wata
#define _wata
#include "Geometrias.h"
#include "Imagenes.h"
//#include "ShaderDemo.h"

class Water : public Primitivos
{

private:
	float anchof;
	float proff;
	float deltax, deltaz;
	unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;
	OpenGLClass* sale;
	//ShaderDemo *gpuDemo;

public:

	Maya wata;
	int verx, verz;
	//el nombre numerico de la textura en cuestion, por lo pronto una
	unsigned int planoTextura;

	Water(HWND hWnd, OpenGLClass* OpenGL, const wchar_t* alturas, const wchar_t* textura, const wchar_t* normales, float ancho, float prof, int numtext, int numtext2)
	{
		anchof = ancho;
		proff = prof;
		//en caso del puntero de la imagen sea nulo se brica esta opcion
		wata = Plano(2, 2, ancho, prof);
		deltax = anchof / 2;
		deltaz = proff / 2;
		verx = 2;
		verz = 2;
		//disponemos la textura del gdi.

		sale = OpenGL;
		// Allocate an OpenGL vertex array object.
		OpenGL->glGenVertexArrays(1, &m_vertexArrayId);

		// Bind the vertex array object to store all the buffers and vertex attributes we create here.
		OpenGL->glBindVertexArray(m_vertexArrayId);

		// Generate an ID for the vertex buffer.
		OpenGL->glGenBuffers(1, &m_vertexBufferId);

		// Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
		OpenGL->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		OpenGL->glBufferData(GL_ARRAY_BUFFER, cantVert * sizeof(Vertices), wata.maya, GL_STATIC_DRAW);

		// Enable the three vertex array attributes.
		OpenGL->glEnableVertexAttribArray(0);  // Vertex position.
		OpenGL->glEnableVertexAttribArray(1);  // Normals.
		OpenGL->glEnableVertexAttribArray(2);  // Texture coordinates.
		OpenGL->glEnableVertexAttribArray(3);  // Tangent.
		OpenGL->glEnableVertexAttribArray(4);  // BiNormals.

		// Specify the location and format of the position portion of the vertex buffer.
		OpenGL->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		OpenGL->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertices), 0);

		// Specify the location and format of the normal vector portion of the vertex buffer.
		OpenGL->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		OpenGL->glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertices), (unsigned char*)NULL + (3 * sizeof(float)));

		// Specify the location and format of the texture coordinate portion of the vertex buffer.
		OpenGL->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		OpenGL->glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertices), (unsigned char*)NULL + (6 * sizeof(float)));

		// Specify the location and format of the texture coordinate portion of the vertex buffer.
		OpenGL->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		OpenGL->glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertices), (unsigned char*)NULL + (8 * sizeof(float)));

		// Specify the location and format of the texture coordinate portion of the vertex buffer.
		OpenGL->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		OpenGL->glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertices), (unsigned char*)NULL + (11 * sizeof(float)));

		// Generate an ID for the index buffer.
		OpenGL->glGenBuffers(1, &m_indexBufferId);

		// Bind the index buffer and load the index data into it.
		OpenGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
		OpenGL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, cantIndices * sizeof(unsigned int),
			wata.indices, GL_STATIC_DRAW);



		delete[] wata.indices;
		wata.indices = 0;

		CargarTextura(OpenGL, normales, numtext2);
		CargarTextura(OpenGL, textura, numtext);

		//gpuDemo = new ShaderDemo("basic.vert", "basic.frag");
		//gpuDemo->ligador(gpuDemo->vertShader, gpuDemo->fragShader);
	}

	~Water()
	{
		//nos aseguramos de disponer de los recursos previamente reservados
		delete wata.maya;
		delete wata.indices;
		glDeleteTextures(1, &planoTextura);
	}

	void CargarTextura(OpenGLClass* OpenGL, const wchar_t* textura, int numtext) {
		Carga(textura);
		// Set the unique texture unit in which to store the data.
		OpenGL->glActiveTexture(GL_TEXTURE0 + numtext);

		// Generate an ID for the texture.
		glGenTextures(1, &planoTextura);

		// Bind the texture as a 2D texture.
		glBindTexture(GL_TEXTURE_2D, planoTextura);

		// Load the image data into the texture unit.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Ancho(), Alto(), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set the texture filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Generate mipmaps for the texture.
		OpenGL->glGenerateMipmap(GL_TEXTURE_2D);
		Descarga();
	}

	void Draw(OpenGLClass* OpenGL)
	{
		// Bind the vertex array object that stored all the information about the vertex and index buffers.
		OpenGL->glBindVertexArray(m_vertexArrayId);

		// Render the vertex buffer using the index buffer.
		glDrawElements(GL_TRIANGLES, cantIndices, GL_UNSIGNED_INT, 0);
		//glDisable(GL_DEPTH_TEST);
	}

	int getLargo() {
		return Alto();
	}
};

#endif 
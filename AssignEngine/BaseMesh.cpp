#include "BaseMesh.h"
#include "Glew/include/glew.h"

#include "Devil/include/IL/il.h"
#include "Devil/include/IL/ilu.h"
#include "Devil/include/IL/ilut.h"

#pragma comment(lib, "Devil/libx86/DevIL.lib")
#pragma comment(lib, "Devil/libx86/ILU.lib")
#pragma comment(lib, "Devil/libx86/ILUT.lib")

BaseMesh::BaseMesh(bool wires): wireframe(wires)
{
}

BaseMesh::~BaseMesh()
{
}

void BaseMesh::GenerateNewBuffer()
{
	//Vertex Buffer
	glGenBuffers(1, (GLuint*)&(mesh.id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.num_vertex * 3, mesh.vertex, GL_STATIC_DRAW);

	//Index Buffer
	glGenBuffers(1, (GLuint*)&(mesh.id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.num_index, mesh.index, GL_STATIC_DRAW);

	//Textures

	glGenBuffers(1, (GLuint*)&(mesh.textureID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.textureID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.num_vertex * 2, mesh.texCoords, GL_STATIC_DRAW);
}


void BaseMesh::AssignTexture(uint texID)
{
}

void BaseMesh::Draw()
{
	if (mesh.num_vertex > 0 && mesh.num_index > 0) {
		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (mesh.texCoords != nullptr) {
			//Texture
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindTexture(GL_TEXTURE_2D, mesh.imageID);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.textureID);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_index);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawElements(GL_TRIANGLES, mesh.num_index, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_NORMAL_ARRAY, 0);
		glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}

void BaseMesh::Clear()
{
	//Free Buffers
	glDeleteBuffers(1, &mesh.id_index);
	glDeleteBuffers(1, &mesh.id_vertex);
	glDeleteBuffers(1, &mesh.textureID);

}

void BaseMesh::ClearTextures()
{
}

void BaseMesh::AssignCheckersImage()
{
}

bool BaseMesh::SetWireframe(bool wires)
{
	wireframe = wires;
	return wireframe;
}

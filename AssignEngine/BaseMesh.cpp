#include "BaseMesh.h"
#include "Glew/include/glew.h"

BaseMesh::BaseMesh()
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
	glGenBuffers(1, (GLuint*) &(mesh.id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.num_index, mesh.index, GL_STATIC_DRAW);
}

void BaseMesh::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_index);

	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, mesh.num_index, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
}

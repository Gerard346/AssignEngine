#include "Application.h"
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

	//Normals

	glGenBuffers(1, (GLuint*)&(mesh.id_normals));
	glBindBuffer(GL_NORMAL_ARRAY, mesh.id_normals);
	glBufferData(GL_NORMAL_ARRAY, sizeof(float) * mesh.num_vertex * 3, mesh.normals, GL_STATIC_DRAW);
	
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

		glBindBuffer(GL_NORMAL_ARRAY, mesh.id_normals);
		glNormalPointer(GL_FLOAT, 0, NULL);

		if (mesh.texCoords != nullptr) {
			if (App->renderer3D->show_textures) {
				//Texture
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindTexture(GL_TEXTURE_2D, mesh.imageID);

				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.textureID);
				glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			}
		}

		glBindBuffer(GL_NORMAL_ARRAY, mesh.id_normals);
		glNormalPointer(GL_FLOAT, 0, NULL);

		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_index);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawElements(GL_TRIANGLES, mesh.num_index, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (mesh.normals != nullptr) {
			if (mesh.see_face_normals) {
				DrawNormalsFace();
			}
			if (mesh.see_vertex_normals) {
				DrawNormalsVertex();
			}
		}

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

void BaseMesh::SeeNormalsVertex()
{
	mesh.see_vertex_normals = !mesh.see_vertex_normals;
}

void BaseMesh::DrawNormalsVertex()
{
	glBegin(GL_LINES);

	for (uint i = 0; i < mesh.num_vertex; i++) {
		glLineWidth(0.2f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(mesh.vertex[i], mesh.vertex[i + 1], mesh.vertex[i + 2]);
		glVertex3f(mesh.vertex[i] + mesh.normals[i], mesh.vertex[i + 1] + mesh.normals[i + 1], mesh.vertex[i + 2] + mesh.vertex[i + 2]);
	}

	glEnd();
}

void BaseMesh::SeeNormalsFace()
{
	mesh.see_face_normals = !mesh.see_face_normals;
}

void BaseMesh::DrawNormalsFace()
{
	glBegin(GL_LINES);

	for (uint i = 0; i < mesh.num_vertex; i++) {
		glLineWidth(0.2f);
		glColor3f(1.0f, 1.0f, 1.0f);
		float vx = (mesh.vertex[i] + mesh.vertex[i + 3] + mesh.vertex[i + 6]) / 3;

		float vy = (mesh.vertex[i + 1] + mesh.vertex[i + 4] + mesh.vertex[i + 7]) / 3;
		float vz = (mesh.vertex[i + 2] + mesh.vertex[i + 5] + mesh.vertex[i + 8]) / 3;

		float nx = (mesh.normals[i] + mesh.normals[i + 3] + mesh.normals[i + 6]) / 3;
		float ny = (mesh.normals[i + 1] + mesh.normals[i + 4] + mesh.normals[i + 7]) / 3;
		float nz = (mesh.normals[i + 2] + mesh.normals[i + 5] + mesh.normals[i + 8]) / 3;

		glVertex3f(vx, vy, vz);
		glVertex3f(vx + mesh.normals[i], vy + mesh.normals[i + 1], vz + mesh.normals[i + 2]);
	}

	glEnd();
}

#pragma once
#include "Globals.h"
#include <string>
#include "MathGeoLib/include/MathGeoLib.h"
#include "Glew/include/glew.h"

struct DataMesh {
	~DataMesh() {
		delete[] index;
		delete[] vertex;
		delete[] texCoords;
	}

	uint id_index = 0; //Index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; //Unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint textureID = 0;
	uint imageID = 0;
	float* texCoords = nullptr;
	char* texPath = nullptr;

	uint id_normals = 0;
	float* normals = nullptr;
	bool see_vertex_normals = false;
	bool see_face_normals = false;
};



class BaseMesh {
public:
	BaseMesh(bool wires);
	virtual ~BaseMesh();

	 virtual void GenerateNewBuffer();

	 void AssignTexture(uint);
	 void AssignCheckersImage();

	 bool SetWireframe(bool w);

	 void SeeNormalsVertex();
	 void DrawNormalsVertex();

	 void SeeNormalsFace();
	 void DrawNormalsFace();

	 void Draw();
	 void Clear();
	 void ClearTextures();

public:
	DataMesh mesh;
	bool wireframe = false;
	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

};
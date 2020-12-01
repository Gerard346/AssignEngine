#pragma once
#include "Globals.h"
#include <string>
#include "MathGeoLib/include/MathGeoLib.h"

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
};



class BaseMesh {
public:
	BaseMesh(bool wires);
	virtual ~BaseMesh();

	 virtual void GenerateNewBuffer();
	 void AssignTexture(uint);
	 void AssignCheckersImage();
	 bool SetWireframe(bool w);

	 void Draw();
	 void Clear();
	 void ClearTextures();

public:
	DataMesh mesh;
	bool wireframe = false;

};
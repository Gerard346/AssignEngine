#pragma once
#include "Globals.h"

struct DataMesh {
	~DataMesh() {
		delete[] index;
		delete[] vertex;
	}

	uint id_index = 0; //Index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; //Unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class BaseMesh {
public:
	BaseMesh();
	virtual ~BaseMesh();

	 void GenerateNewBuffer();
	 void Draw();
	 void Clear();

public:
	DataMesh mesh;
};
#include<stdio.h>
#include<stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

struct Color
{
	int R, G, B, A;
};

struct UV
{
	float x, y;
};

struct VectorData
{
	VectorData()
	{
		for (int i = 0; i < 4; i++)
		{
			Matrix[i] = new float[4];
		}
	}
public:
	float** Matrix = new float*[4];
	
};

struct Texture
{
	Texture(int width,int lenght)
	{
		Matrix = new Color*[width];
		for (int i = 0; i < lenght; i++)
		{
			Matrix[i] = new Color[width];
		}
	}
public:
	Color** Matrix;
};

struct MeshData
{
	MeshData(int VectorNumber)
	{
		Matrix->resize(VectorNumber);
		UVS->resize(VectorNumber);
	}
	vector<VectorData>* Matrix = new vector<VectorData>;
	vector<UV>* UVS = new vector<UV>;
	Texture* texture = new Texture(1080, 1920);
};

void Render(MeshData* meshData) {
	for (int i = 0; i < meshData->Matrix->size(); i++)
	{
		for (int a = 0; a < 4; a++)
		{
			meshData->Matrix->at(i).Matrix[0][a] *= meshData->Matrix->at(i).Matrix[0][3];
		}
		while (meshData->Matrix->at(i).Matrix[0][3] < 1)
		{
			for (int a = 0; a < 4; a++)
			{
				meshData->Matrix->at(i).Matrix[0][a] /= meshData->Matrix->at(i).Matrix[0][3];
			}
		}
	}
}

int main() {
	MeshData* meshData = new MeshData(20000);
	clock_t tStarted = clock();
	while (true)
	{
		clock_t tStart = clock();
		Render(meshData);
		printf("Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
		if ((double)(clock() - tStart) > 10)
		{
			break;
		}
	}
	
	return 0;
}

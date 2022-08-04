#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;


int main() {
	clock_t tStart = clock();
	const int N = 45000;
	__int8** firstMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		firstMatrix[i] = new __int8[N];

	__int8** secondMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		secondMatrix[i] = new __int8[N];

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			firstMatrix[y][x] = 5;
			secondMatrix[y][x] = 6;
		}
	}
	printf("Random number in matrix Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	tStart = clock();

	__int8** ReverseSecondMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		ReverseSecondMatrix[i] = new __int8[N];
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			ReverseSecondMatrix[x][y] = secondMatrix[y][x];
		}
	}
	for (int i = 0; i < N; ++i)
		delete(secondMatrix[i]);
	delete(secondMatrix);

	printf("Matrix Reverse Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	tStart = clock();

	__int8** MultiMatrixMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		MultiMatrixMatrix[i] = new __int8[N];

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			MultiMatrixMatrix[x][y] = firstMatrix[y][x] * ReverseSecondMatrix[y][x];
		}
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}

/*int main() {
	clock_t tStart = clock();
	const int N = 45000;
	__int8** firstMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		firstMatrix[i] = new __int8[N];

	__int8** secondMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		secondMatrix[i] = new __int8[N];

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			firstMatrix[y][x] = 5;
			secondMatrix[y][x] = 6;
		}
	}
	printf("Random number in matrix Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	tStart = clock();

	__int8** MultiMatrixMatrix = new __int8* [N];
	for (int i = 0; i < N; ++i)
		MultiMatrixMatrix[i] = new __int8[N];

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			MultiMatrixMatrix[x][y] = firstMatrix[y][x] * secondMatrix[x][y];
		}
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}*/
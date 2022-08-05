#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <thread>

using namespace std;

void RandomGenMatrix(int** firstMatrix, int** secondMatrix, int N, int ThreadID,int threadNumber) {
	for (int y = N * ThreadID; y <(ThreadID+1) * N / threadNumber; y++)
	{
		for (int x = N * ThreadID; x < (ThreadID + 1) * N / threadNumber; x++)
		{
			firstMatrix[y][x] = rand();
			secondMatrix[y][x] = rand();
		}
	}
}

void ReverseMajorMatrix(int** ReverseSecondMatrix, int** secondMatrix, int N, int ThreadID, int threadNumber) {
	for (int y = N * ThreadID; y < (ThreadID + 1) * N / threadNumber; y++)
	{
		for (int x = N * ThreadID; x < (ThreadID + 1) * N / threadNumber; x++)
		{
			ReverseSecondMatrix[x][y] = secondMatrix[y][x];
		}
	}
}

void MultiMatrix(int** MultiMatrixMatrix, int** firstMatrix, int** secondMatrix,  int N, int ThreadID, int threadNumber) {
	for (int y = N * ThreadID; y < (ThreadID + 1) * N / threadNumber; y++)
	{
		for (int x = N * ThreadID; x < (ThreadID + 1) * N / threadNumber; x++)
		{
			MultiMatrixMatrix[y][x] = 0;
			for (int k = 0; k < N; k++)
			{
				MultiMatrixMatrix[y][x] = MultiMatrixMatrix[y][x] + firstMatrix[x][k] * secondMatrix[x][k];
			}
		}
	}
}

int main() {
	clock_t tStart = clock();
	const int N = 2500;
	int** firstMatrix = new int*[N];
	for (int i = 0; i < N; ++i)
		firstMatrix[i] = new int[N];

	int** secondMatrix = new int* [N];
	for (int i = 0; i < N; ++i)
		secondMatrix[i] = new int[N];

	RandomGenMatrix(firstMatrix, secondMatrix, N, 0, 4);
	thread* t1 = new thread(RandomGenMatrix, firstMatrix, secondMatrix, N, 1, 4);
	thread* t2 = new thread(RandomGenMatrix, firstMatrix, secondMatrix, N, 2, 4);
	thread* t3 = new thread(RandomGenMatrix, firstMatrix, secondMatrix, N, 3, 4);

	t1->join();
	t2->join();
	t3->join();

	delete(t1);
	delete(t2);
	delete(t3);
	printf("Random number in matrix Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	tStart = clock();

	int** ReverseSecondMatrix = new int* [N];
	for (int i = 0; i < N; ++i)
		ReverseSecondMatrix[i] = new int[N];
	
	ReverseMajorMatrix(ReverseSecondMatrix, secondMatrix, N, 0, 4);
	t1 = new thread(ReverseMajorMatrix, ReverseSecondMatrix, secondMatrix, N, 1, 4);
	t2 = new thread(ReverseMajorMatrix, ReverseSecondMatrix, secondMatrix, N, 2, 4);
	t3 = new thread(ReverseMajorMatrix, ReverseSecondMatrix, secondMatrix, N, 3, 4);

	t1->join();
	t2->join();
	t3->join();

	delete(t1);
	delete(t2);
	delete(t3);

	for (int i = 0; i < N; ++i)
		delete(secondMatrix[i]);
	delete(secondMatrix);

	printf("Matrix Reverse Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	tStart = clock();

	int** MultiMatrixMatrix = new int* [N];
	for (int i = 0; i < N; ++i)
		MultiMatrixMatrix[i] = new int[N];

	MultiMatrix(MultiMatrixMatrix, firstMatrix, ReverseSecondMatrix, N, 0, 4);
	t1 = new thread(MultiMatrix, MultiMatrixMatrix, firstMatrix, ReverseSecondMatrix, N, 1, 4);
	t2 = new thread(MultiMatrix, MultiMatrixMatrix, firstMatrix, ReverseSecondMatrix, N, 2, 4);
	t3 = new thread(MultiMatrix, MultiMatrixMatrix, firstMatrix, ReverseSecondMatrix, N, 3, 4);

	t1->join();
	t2->join();
	t3->join();

	delete(t1);
	delete(t2);
	delete(t3);
	
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}

/*int main() {
	clock_t tStart = clock();
	const int N = 2500;
	int** firstMatrix = new int*[N];
	for (int i = 0; i < N; ++i)
		firstMatrix[i] = new int[N];
	int** secondMatrix = new int*[N];
	for (int i = 0; i < N; ++i)
		secondMatrix[i] = new int[N];
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
	int** MultiMatrixMatrix = new int* [N];
	for (int i = 0; i < N; ++i)
		MultiMatrixMatrix[i] = new int[N];
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			MultiMatrixMatrix[y][x] = 0;
			for (int k = 0; k < N; k++)
			{
				MultiMatrixMatrix[y][x] = MultiMatrixMatrix[y][x] + firstMatrix[x][k] * secondMatrix[k][x];
			}
		}
	}
	cout << MultiMatrixMatrix[20][10];

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}*/

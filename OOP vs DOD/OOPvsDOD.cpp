#include<stdio.h>
#include<stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

class Apartment
{
public:
    float light;
    char* ApartOwnerName = new char[40];

    float apartNumber;
    Apartment(float light , float apartNumber)
    {
        this->light = light;
        this->apartNumber = apartNumber;
    }
    Apartment()
    {
        light = 0;
        apartNumber = -1;
    }
};

class Structure
{
public:
    char* StructureName = new char[30];
    char* StructureColor = new char[30];
    Apartment* Apartments = new Apartment[5];

};

struct ApartLightData
{
    ApartLightData(int N)
    {
        //we split memory for cache line
        lightData->resize(N);
    }
    vector<float>* lightData = new vector<float>;
};

int main() {
    vector<Structure*>* Structures = new vector<Structure*>();
    int N = 50000;
    Structures->resize(N/5);

    //OOP
    clock_t tStart = clock();
    for (int i = 0; i < N/5; i++)
    {
        Structure* structure = new Structure();

        Apartment* Apart1 = new Apartment();
        Apartment* Apart2 = new Apartment();
        Apartment* Apart3 = new Apartment();
        Apartment* Apart4 = new Apartment();
        Apartment* Apart5 = new Apartment();

        structure->Apartments[0] = *Apart1;
        structure->Apartments[1] = *Apart2;
        structure->Apartments[2] = *Apart3;
        structure->Apartments[3] = *Apart4;
        structure->Apartments[4] = *Apart5;

        Structures->at(i) = structure;
    }

    printf("structure creater Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    tStart = clock();

    for (int i = 0; i < N; i++)
    {
        for (auto item : *Structures)
        {
            for (int i = 0; i < 5; i++)
            {
                item->Apartments[i].light = 5;
            }
        }
    }
    printf("Set Light OOP Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    //DOD
    tStart = clock();
    ApartLightData* apartLightData = new ApartLightData(N);
    for (int i = 0; i < N; i++)
    {
        apartLightData->lightData->at(i) = 5;
    }
    printf("Set Light DOD Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}

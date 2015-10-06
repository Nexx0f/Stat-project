#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include <time.h>
using namespace std;

//extern "C++" void qsort( void *ptr, std::size_t count, std::size_t size,
//            int (*comp)(const void *, const void *) );

int table_mode = 0;
int graph_mode = 1;

class Vector
{
public:
    int size;
    int* vector;
    
    Vector (int newSize)
    {
        size = newSize;
        vector = (int*)malloc (sizeof(int)*newSize);
        
        for (int i = 0; i < size; i++)
            vector[i] = -1;
    }
    
    void Generate (double chance)
    {
        
        for (int y = 0; y < size; y++)
            {
                
                
                if (rand() <= RAND_MAX*chance) vector[y] = 1;
                    else                       vector[y] = 0;
            }
    }
    
    void PrintVector ()
    {
        for (int y = 0; y < size; y++)
        {
            printf ("%d\n", vector[y]);
        }
    }
};

class Table 
{
public:
    int heavyKolumnsCount;
    int vectorSize;
    double chance;
    Vector* vectData;
    
    int* dependence;
    
public:
    Table (const int new_size, const int vectorNewSize)
    {
        srand(time(NULL)*10);
        
        heavyKolumnsCount = new_size;
        vectorSize        = vectorNewSize;
        chance = -1;
        
        vectData   = (Vector*)malloc (sizeof(Vector)*heavyKolumnsCount    );
        dependence = (int*)   malloc (sizeof(int)*   (heavyKolumnsCount+1));
        
        for (int i = 0; i < heavyKolumnsCount; i++)
            vectData[i] = Vector (vectorSize);
        for (int i = 0; i <= heavyKolumnsCount; i++)
            dependence[i] = 0;
    }
    
    void Generate (double newChance)
    {
        chance = newChance;
        for (int i = 0; i < heavyKolumnsCount; i++)
            vectData[i].Generate (chance);
    }
    
    void CollectDependence ()
    {
        for (int string = 0; string < vectorSize; string++)
        {
            int quantity = 0;
            for (int i = 0; i < heavyKolumnsCount; i++)
                quantity += vectData[i].vector[string];
            
            dependence[quantity]++;     
        }
    }
    
    void PrintTable ()
    {
        for (int y = 0; y < vectorSize; y++)
        {
            for (int x = 0; x < heavyKolumnsCount; x++)
                printf ("%d ", vectData[x].vector[y]);
                printf ("\n");
        }
        printf ("\n");         
    }
    
    void PrintDependence ()
    {
        printf ("|\n"
                    "|\n"
                    "|\n");
        for (int i = 0; i <= heavyKolumnsCount; i++)
        {
            for (int t = 0; t < dependence[i]; t++)
                printf ("#");
            printf ("\n");
        }
        printf ("|\n"
                    "|\n"
                    "|\n");
    }
    ~Table ();
};

int main(int argc, char **argv) 
{
    Table* t;
    printf ("\n");
    t = new Table (5, 10);
    t -> PrintTable();
    printf ("Generating\n");
    t -> Generate (0.5);
    t -> PrintTable();
    printf ("Collecting Dependence...\n\n");
    t -> CollectDependence();
    printf ("PrintingDependence...\n\n");
    t -> PrintDependence();
    
    return 0;
}

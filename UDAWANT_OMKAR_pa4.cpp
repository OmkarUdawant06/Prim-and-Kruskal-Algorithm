#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <iomanip> 
#include <string.h>
using namespace std;

#define vertices 15

string choice, ch;
int prim[15] = {0};
int set[15] = {0};
int height[15] = {0};
int edge[100][3];
int T[15][3];
int n, **mat_A;
void creatematrix();
int search(int x);
void op_union(int repx, int repy);
void op_insert(int *array, int n);
void prim_algo(int **graph, int n);
void kruskal_algo(int **mat_A, int n);

void creatematrix()
{
    srand(time(0));                         //initialize rand before use
    n = rand() % (10-5+1)+5;                //(generator() % (max - min + 1)) + min
    mat_A = new int *[n+1];
        
    cout<<endl<<"Randomly selected "<<n<<" vertices "<<endl;
        
    for (int i = 0; i<n; i++) 
    {
        mat_A[i] = new int[n+1];
    }
    for (int i = 0; i<n; i++) 
    {
        mat_A[i][i] = 0;
    }
    for (int i = 0; i<n; i++) 
    {
        for (int j = 1; j<n ; j++) 
        {
            if (i != j && i < j) 
            {
                mat_A[i][j] = rand() % n + 1;             //assign random value to mat_A
                mat_A[j][i] = mat_A[i][j];
            }
        }
    }
    cout<<"Random Matrix: "<<endl;
    for (int i = 0; i<n; i++)                       //print mat_A
    {
        for (int j = 0; j<n; j++) 
        {
            cout<<setw(2)<<left<<mat_A[i][j]<<" ";
        }
        cout<<endl;
    }
}

int search(int x)
{
    int node  = x, parent, root = x;
    do
    {
        root = set[root];
    }while (root!= set[root]);
    
    do
    {
        parent = set[node];
        set[node] = root;
        node = parent;
    }while (node!=root); 
    
    return root;
}

void op_union(int repx, int repy)
{
    if (height[repx] == height[repy]) 
    {
        height[repx]++;
        set[repy] = repx;
    }
    else if (height[repx] > height[repy])
            set[repy] = repx;
        else set[repx] = repy;
}

void op_insert(int *array, int n)
{
    int temp[3], j;
    for (int i = 1; i < n; i++) 
    {
        temp[2] = array[i*3 + 2];
        temp[1] = array[i*3 + 1];
        temp[0] = array[i*3 + 0];
        if(temp[2] < array[(i-1)*3 +2])
        {
            for (j = i-1; j >= 0 && temp[2] < array[j*3 + 2]; j--) 
            {
                array[(j+1)*3 +2] = array[(j*3) +2];
                 array[(j+1)*3 +1] = array[(j*3) +1];
                 array[(j+1)*3 +0] = array[(j*3) +0];
                
            }
            array[(j+1)*3 +2] = temp[2];
            array[(j+1)*3 +1] = temp[1];
            array[(j+1)*3 +0] = temp[0];
        }
    }
}

void prim_algo(int **graph, int n)
{
    int parent[vertices];            // Array to store constructed MST
    int key[vertices];               // Key values used to pick minimum weight edge in cut
    bool mstSet[vertices];           // To represent set of vertices not yet included in MST
    int min, min_index;
    int **trans;
    trans = new int *[n+1];

    for (int i = 0; i<n; i++) 
    {
        trans[i] = new int[n+1];
    }

    for (int i = 0; i < n; i++)
    {
        mstSet[i] = false;
        key[i] = 99;
    }

    parent[0] = -1;
    key[0] = 0;

    for (int count = 0; count < n-1; count++)
    {
        min = 99;
        min_index = 0;
        
        for (int v = 0; v < n; v++)
        {
            if (mstSet[v] == false && key[v] < min)
            {
                min = key[v];
                min_index = v;
            }
        }
        
        int u = min_index;
        mstSet[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
            {
                parent[v]  = u; 
                key[v] = graph[u][v];
            }
        }
    }

    for (int i = 1; i < n; i++)
    {
        cout<<"V"<<parent[i]<<"---V"<<i<<"  Weight "<<graph[i][parent[i]]<<endl;
        trans[i][parent[i]]=graph[i][parent[i]];
        trans[parent[i]][i]=graph[parent[i]][i];
        trans[parent[i]][i]=graph[i][parent[i]];
    }

    cout<<"Prim's Matrix: "<<endl;              //print Prim's Matrix
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<setw(2)<<left<<trans[i][j]<<" "; 
        }
        cout<<endl;
    }
}
                        
void kruskal_algo(int **mat_A, int n)
{
    int **trans;
    int k = 0;
    trans = new int *[n+1];

    for (int i = 0; i<n; i++) 
    {
        trans[i] = new int[n+1];
    }
    
    for (int i = 0; i<n; i++) 
    {
        for (int j = 1; j<n ; j++) 
        {
            if (i != j && i < j) 
            {
                edge[k][0] = i;
                edge[k][1] = j;
                edge[k][2] = mat_A[i][j];
                k++;
            }
        }
    }
    op_insert(*edge, k);    
    k =0 ;
    
    for (int i = 0; i<n; i++) 
    {
        set[i]= i;
    }
    
    for (int i = 0; i<n-1 ;) 
    {
        int ucomp = search(edge[k][0]);
        int vcomp = search(edge[k][1]);

        if (ucomp != vcomp) 
        {
            T[i][0] = edge[k][0];
            T[i][1] = edge[k][1];
            op_union(ucomp, vcomp);
            
            cout<<"V"<<T[i][0]<<"---V"<<T[i][1]<<"  Weight "<<edge[k][2]<<endl;     //print minimum edge with its weight
            i++;
        }
        k++;
    }  
}

int main() 
{
    creatematrix();
m:  cout<<"Please type name of one of the following Algorithms:"<<endl<<"1. Prim’s Algorithm (Input: prim)"<<endl<<"2. Kruskal’s Algorithm (Input: kruskal)"<<endl<<"3. Exit (Input: exit)"<<endl;
    cin>>choice;
    
    if(strcmp(choice.c_str(),"prim") == 0)
    {   
        cout<<"\nDo you wish to create a new Matrix for this algorithm or use existing matrix? (Input: yes|no)"<<endl;
        cin>>ch;
        if(strcmp(ch.c_str(),"yes") == 0)
        {
            creatematrix();
            prim_algo(mat_A,n);
            cout<<endl<<endl;
        }
        else
        {
            prim_algo(mat_A,n);
            cout<<endl<<endl;
        }
        goto m;
    }
    else if(strcmp(choice.c_str(),"kruskal") == 0)
    {
        cout<<"\nDo you wish to create a new Matrix for this algorithm or use existing matrix? (Input: yes|no)"<<endl;
        cin>>ch;
        if(strcmp(ch.c_str(),"yes") == 0)
        {
            creatematrix();
            kruskal_algo(mat_A,n);
            cout<<endl<<endl;
        }
        else
        {
            kruskal_algo(mat_A,n);
            cout<<endl<<endl;
        }
        goto m;
    }
    else if(strcmp(choice.c_str(),"exit") == 0)
    {
        return 0;
    }
    else
    {
        cout<<endl<<"I only have prim and kruskal algorithm"<<endl<<"****Try again!****"<<endl<<endl;
        goto m;
    }

    return 0; 
}
/*
 Name: Asaif A Butt
 ZNumber: Z23295634
 Date: 7.3.16
 Course: Design Analysis of ALgorithms
 Description: The program creates a 2D table 10 rows and 20000 coloumns of vectors with random elements.
                Then the user is given a choice to run one of the three sorting algorithms. The program then runs the algorithm on each row of the table. So in total there are 10 experiments for each algorithm with number of elements incremented by a 1000 everytime. At the end of each experiment average runtime is calculated. The runtime is calculated in ms.
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <string>

void insertionSortAlgorithm();
void quickSortAlgorithm();
void heapSortAlgorithm();

using namespace std;

//Alg1 = Insertion Sort, Alg2 = Heap Sort, Alg3 = Quick Sort
int ns = 1000;
int nf = 20000;
int theta = 1000;
int m = 10;
double duration = 0;
double avgRT = 0;
int experiment = 0;

vector<vector<int>> table(m, vector<int>(nf));
vector<int> A;

int main()
{
    char exit = 'N';
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < nf; j++)
        {
            table[i][j] = rand();
        }
    }
    
    while(exit != 'Y')
    {
        char userSelection;
        
        cout << "Algorithm RunTime Project" << endl;
        cout << "I -    Run Insertion Sort" << endl;
        cout << "H -    Run Heap Sort" << endl;
        cout << "Q -    Run Quick Sort" << endl;
        cout << "Y -    Exit" << endl;
        cout << endl << endl;
        
        cout << "Select an option: ";
        cin >> userSelection;
        userSelection = toupper(userSelection);
        
        switch(userSelection)
        {
            case 'I':
                insertionSortAlgorithm();
                break;
                
            case 'Q':
                quickSortAlgorithm();
                break;
                
            case 'H':
                heapSortAlgorithm();
                break;
                
            case 'Y':
                return 0;
                
            default:
                cout << "No such option, try again...\n\n\n";
                break;
        }

        
    }
}

//Insertion Sort Algorithm
void insertionSort(vector <int> &array)
{
    int key = 0;
    int i = 0;
    
    for(int j = 1; j < array.size(); j++)
    {
        key = array[j];
        i = j-1;
        
        while ((i> -1)&&(array[i] > key))
        {
            array[i+1] = array[i];
            i = i-1;
        }
        array[i+1] = key;
    }
}

//Partition for the quick sort
int partition(vector<int> &array, int p, int r)
{
    int x = array[r];
    int i = p -1;
    
    
    for (int j = p; j <= r - 1 ; j++)
    {
        if(array[j] <= x)
        {
            i = i + 1;
            int exchange = array[i];
            array[i] = array[j];
            array[j] = exchange;
        }
    }
    int exchange2 = array[i+1];
    array[i+1] = array[r];
    array[r] = exchange2;
    
    return i + 1;
}

//Quick sort algorithm
void quickSort(vector <int> &array, int p, int r)
{
    if( p < r)
    {
        int q = partition(array, p, r);
        quickSort(array, p, q - 1);
        quickSort(array, q+1,r);
    }
}

//Parent node function for heapsort
int parent(int i)
{
    return (int)floor(i/2);
}

//Left node function for heapsort
int left(int i)
{
    return (2 * i);
}

//Right node function for heapsort
int right(int i)
{
    return (2 * i) + 1;
}

//Max Heapify for heapsort
void max_heapify(vector<int> &array, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = 0;
    
    if ((l <= array.size() - 1)&&(array[l] > array[i]))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if ((r <= array.size() - 1)&&(array[r] > array[largest]))
    {
        largest = r;
    }
    if (largest != i)
    {
        int exchange = array[i];
        array[i] = array[largest];
        array[largest] = exchange;
        
        max_heapify(array, largest);
    }
}

//Building max heap
void build_max_heap(vector<int> &array)
{
    int heap_size = (int) array.size() -1;
    for (int i = (int)floor(heap_size/2); i >= 1; i--)
    {
        max_heapify(array, i);
    }
}

//Heap Sort
void heapsort(vector<int> &array)
{
    build_max_heap(array);
    for(int i = (int) array.size() - 1; i >= 1; i--)
    {
        int exchange = array[1];
        array[1] = array[i];
        array[i] = exchange;
        
        array.erase(array.begin() + array.size() - 1);
        max_heapify(array,1);
        
    }
    
}

//running insertion sort algorithm to calculate Running Time
void insertionSortAlgorithm()
{
    experiment = 1;
    cout << "INSERTION SORT" << endl <<endl;
    
    for(int n = ns; n <= nf; n = n + theta)
    {
        cout << "Experiment: " << experiment << endl;
        cout << "Number of Elements: " << n << endl;
        cout << "-----------------------------------" << endl;
        cout << "Running Time in ms" <<endl;
        
        for (int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A.push_back(table[i][j]);
            }
            
            clock_t start = clock();
            
            insertionSort(A);
            
            clock_t end = clock();
            
            duration = (end - start)/ (double)CLOCKS_PER_SEC * 1000; //Returns the time in ms
            cout << "M" << i + 1 << ": " << duration << endl;
            avgRT += duration;
            
            A.clear();
        }
        
        cout << "\nAverage Run Time For Experiment: " << experiment << ": " << avgRT / m << "(ms)" << endl;
        cout << "-------------------------------------" << endl << endl;
        avgRT = 0;
        experiment++;
    }
    
    experiment = 0;
}

//running quick sort algorithm to calculate Running Time
void quickSortAlgorithm()
{
    experiment = 1;
    cout << "QUICK SORT" << endl<<endl;

    for(int n = ns; n <= nf; n = n + theta)
    {
        
        cout << "Experiment: " << experiment << endl;
        cout << "Number of Elements: " << n << endl;
        cout << "-----------------------------------" << endl;
        cout << "Running Time in ms" << endl;
        
        for (int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A.push_back(table[i][j]);
            }
            
            clock_t start = clock();
            
            int n = (int)A.size() - 1;
            quickSort(A, 1, n);
            
            clock_t end = clock();
            
            duration = (end - start)/ (double)CLOCKS_PER_SEC *1000 ; //Returns the time in ms
            cout << "M" << i + 1 << ": " << duration << endl;
            avgRT += duration;
            
            A.clear();
        }
        
        cout << "\nAverage Run Time For Experiment: " << experiment << ": " << avgRT / m << "(ms)" << endl;
        cout << "-------------------------------------" << endl << endl;
        avgRT = 0;
        experiment++;
    }
    
    experiment = 0;

}

//running heap sort algorithm to calculate Running Time
void heapSortAlgorithm()
{
    experiment = 1;
    cout << "HEAP SORT" << endl <<endl;
   

    for(int n = ns; n <= nf; n = n + theta)
    {
        
        cout << "Experiment: " << experiment << endl;
        cout << "Number of Elements: " << n << endl;
        cout << "-----------------------------------" << endl;
        cout << "Running Time in ms" << endl;
        
        for (int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A.push_back(table[i][j]);
            }
            
            clock_t start = clock();
            
            heapsort(A);
            
            clock_t end = clock();
            
            duration = (end - start)/ (double)CLOCKS_PER_SEC * 1000; //Returns the time in ms
            cout << "M" << i + 1 << ": " << duration << endl;
            avgRT += duration;
            
            A.clear();
        }
        
        cout << "\nAverage Run Time For Experiment: " << experiment << ": " << avgRT / m << "(ms)" << endl;
        cout << "-------------------------------------" << endl << endl;
        avgRT = 0;
        experiment++;
    }
    
    experiment = 0;
}






















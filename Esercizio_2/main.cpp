#include "SortingAlgorithm.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <numeric>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace SortLibrary;

double average(vector<double>& v){
    double sum = accumulate(v.begin(), v.end(), 0);
    double media = sum/size(v);
    return media;
}

double durata_BubbleSort (vector<int>& v){

    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    BubbleSort(v);
    chrono::steady_clock::time_point tF = chrono::steady_clock::now();
    double durata = chrono::duration_cast<chrono::microseconds> (tF-t0).count();

    return durata;
}

double durata_MergeSort (vector<int>& v){

    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    MergeSort(v);
    chrono::steady_clock::time_point tF = chrono::steady_clock::now();
    double durata = chrono::duration_cast<chrono::microseconds> (tF-t0).count();

    return durata;
}

int main(int argc, char ** argv)
{
    unsigned int num_misurazioni = 1000;
    unsigned int dim_vettore;
    istringstream converter(argv[1]);
    converter >> dim_vettore;

    cout << scientific << setprecision(4); //imposto il formato con cui visualizzerò in output i tempi medi

// *******************************************************************************************************************************
    //misurazioni con vettore ordinato in maniera crescente
    vector<double> misurazioni_BS_ordinato1(num_misurazioni);
    vector<double> misurazioni_MS_ordinato1(num_misurazioni);
    misurazioni_BS_ordinato1.reserve(num_misurazioni);
    misurazioni_MS_ordinato1.reserve(num_misurazioni);

    for (unsigned int i = 0; i < num_misurazioni; i++){
        vector<int> v1(dim_vettore);
        vector<int> v2(dim_vettore);
        iota(v1.begin(), v1.end(), i);
        v2 = v1;

        misurazioni_BS_ordinato1[i] = durata_BubbleSort(v1);
        misurazioni_MS_ordinato1[i] = durata_MergeSort(v2);
    }

    cout << "Misurazioni con vettore ordinato in maniera crescente di dimensione " << dim_vettore << "." << endl;
    cout << "L'algoritmo Bubble Sort impiega mediamente " << average(misurazioni_BS_ordinato1) << " microseconds." << endl;
    cout << "L'algoritmo Merge Sort impiega mediamente " << average(misurazioni_MS_ordinato1) << " microseconds." << endl;


    cout << endl;

// *******************************************************************************************************************************
    //misurazioni con vettore ordinato in maniera decrescetnte
    vector<double> misurazioni_BS_ordinato2(num_misurazioni);
    vector<double> misurazioni_MS_ordinato2(num_misurazioni);
    misurazioni_BS_ordinato2.reserve(num_misurazioni);
    misurazioni_MS_ordinato2.reserve(num_misurazioni);

    for (unsigned int i = 0; i < num_misurazioni; i++){
        vector<int> v1(dim_vettore);
        vector<int> v2(dim_vettore);
        unsigned int j = 50 + i;
        generate(v1.begin(), v1.end(), [&j] () {return j--;});
        v2 = v1;

        misurazioni_BS_ordinato2[i] = durata_BubbleSort(v1);
        misurazioni_MS_ordinato2[i] = durata_MergeSort(v2);
    }

    cout << "Misurazioni con vettore ordinato in maniera decrescente di dimensione " << dim_vettore << "." << endl;
    cout << "L'algoritmo Bubble Sort impiega mediamente " << average(misurazioni_BS_ordinato2) << " microseconds." << endl;
    cout << "L'algoritmo Merge Sort impiega mediamente " << average(misurazioni_MS_ordinato2) << " microseconds." << endl;

    cout << endl;

// *******************************************************************************************************************************
    //misurazioni con vettore per metà ordinato
    vector<double> misurazioni_BS_semiordinato(num_misurazioni);
    vector<double> misurazioni_MS_semiordinato(num_misurazioni);
    misurazioni_BS_semiordinato.reserve(num_misurazioni);
    misurazioni_MS_semiordinato.reserve(num_misurazioni);

    srand((unsigned) time(NULL)); //imposto il seed per ottenere numeri generati casualmente

    for (unsigned int i = 0; i < num_misurazioni; i++){
        vector<int> v1(dim_vettore);
        vector<int> v2(dim_vettore);

        iota(v1.begin(), v1.end(), i); //la prima metà sarà ordinata
        unsigned int meta_vett = dim_vettore/2;

        //la seconda metà sara generata casualmente nell'intervallo [0; 100]
        for (unsigned int k = meta_vett; k < dim_vettore; k++){
            v1[k] = rand() % 101;
        }

        v2 = v1;

        misurazioni_BS_semiordinato[i] = durata_BubbleSort(v1);
        misurazioni_MS_semiordinato[i] = durata_MergeSort(v2);
    }

    cout << "Misurazioni con vettore ordinato per metà di dimensione " << dim_vettore << "." << endl;
    cout << "L'algoritmo Bubble Sort impiega mediamente " << average(misurazioni_BS_semiordinato) << " microseconds." << endl;
    cout << "L'algoritmo Merge Sort impiega mediamente " << average(misurazioni_MS_semiordinato) << " microseconds." << endl;

    cout << endl;

// *******************************************************************************************************************************
    //misurazioni con vettore non ordinato
    vector<double> misurazioni_BS_nonordinato(num_misurazioni);
    vector<double> misurazioni_MS_nonordinato(num_misurazioni);
    misurazioni_BS_nonordinato.reserve(num_misurazioni);
    misurazioni_MS_nonordinato.reserve(num_misurazioni);

    srand((unsigned) time(NULL)); //imposto il seed per ottenere numeri generati casualmente

    for (unsigned int i = 0; i < num_misurazioni; i++){
        vector<int> v1(dim_vettore);
        vector<int> v2(dim_vettore);

        //genero l'intero vettore casualmente nell'intervallo [0; 100]
        for (unsigned int k = 0; k < dim_vettore; k++){
            v1[k] = rand() % 101;
        }

        v2 = v1;

        misurazioni_BS_nonordinato[i] = durata_BubbleSort(v1);
        misurazioni_MS_nonordinato[i] = durata_MergeSort(v2);
    }

    cout << "Misurazioni con vettore non ordinato di dimensione " << dim_vettore << "." << endl;
    cout << "L'algoritmo Bubble Sort impiega mediamente " << average(misurazioni_BS_nonordinato) << " microseconds." << endl;
    cout << "L'algoritmo Merge Sort impiega mediamente " << average(misurazioni_MS_nonordinato) << " microseconds." << endl;

    cout << endl;

// *******************************************************************************************************************************
    //misurazioni con vettore non ordinato di dimensione raddoppiata
    vector<double> misurazioni_BS_doppiadim(num_misurazioni);
    vector<double> misurazioni_MS_doppiadim(num_misurazioni);
    misurazioni_BS_doppiadim.reserve(num_misurazioni);
    misurazioni_MS_doppiadim.reserve(num_misurazioni);

    unsigned int dim = 2*dim_vettore;

    srand((unsigned) time(NULL)); //imposto il seed per ottenere numeri generati casualmente

    for (unsigned int i = 0; i < num_misurazioni; i++){
        vector<int> v1(dim);
        vector<int> v2(dim);

        //genero l'intero vettore casualmente nell'intervallo [0; 100]
        for (unsigned int k = 0; k < dim; k++){
            v1[k] = rand() % 101;
        }

        v2 = v1;

        misurazioni_BS_doppiadim[i] = durata_BubbleSort(v1);
        misurazioni_MS_doppiadim[i] = durata_MergeSort(v2);
    }

    cout << "Misurazioni con vettore non ordinato di dimensione " << dim << "." << endl;
    cout << "L'algoritmo Bubble Sort impiega mediamente " << average(misurazioni_BS_doppiadim) << " microseconds." << endl;
    cout << "L'algoritmo Merge Sort impiega mediamente " << average(misurazioni_MS_doppiadim) << " microseconds." << endl;

    cout << endl;

// *******************************************************************************************************************************
    //misurazioni con vettore non ordinato di dimensione molto piccola
    vector<double> misurazioni_BS_piccoladim(num_misurazioni);
    vector<double> misurazioni_MS_piccoladim(num_misurazioni);
    misurazioni_BS_piccoladim.reserve(num_misurazioni);
    misurazioni_MS_piccoladim.reserve(num_misurazioni);

    dim = 10;

    srand((unsigned) time(NULL)); //imposto il seed per ottenere numeri generati casualmente

    for (unsigned int i = 0; i < num_misurazioni; i++){
        vector<int> v1(dim);
        vector<int> v2(dim);

        //genero l'intero vettore casualmente nell'intervallo [0; 100]
        for (unsigned int k = 0; k < dim; k++){
            v1[k] = rand() % 101;
        }

        v2 = v1;

        misurazioni_BS_piccoladim[i] = durata_BubbleSort(v1);
        misurazioni_MS_piccoladim[i] = durata_MergeSort(v2);
    }

    cout << "Misurazioni con vettore non ordinato di dimensione " << dim << "." << endl;
    cout << "L'algoritmo Bubble Sort impiega mediamente " << average(misurazioni_BS_piccoladim) << " microseconds." << endl;
    cout << "L'algoritmo Merge Sort impiega mediamente " << average(misurazioni_MS_piccoladim) << " microseconds." << endl;

    cout << endl;
    return 0;
}


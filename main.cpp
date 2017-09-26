#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
const int SIZE=8;
int pivot=0;

void Generador_Pruebas(int arr_PC_Merge[SIZE], int arr_MC_Merge[SIZE], int arr_PC_Quick[SIZE], int arr_MC_Quick[SIZE])
{
    //MEJOR CASO MERGE
    for(int i=0, j=SIZE; j>=1; j--, i++)
        arr_MC_Merge[i] = j;

    //PEOR CASO MERGE
    int j=(SIZE/2)+1, k=1;
    int Inicial=SIZE/2;
    int Inicial2=SIZE;
    for(int i=0, cont=1; i<(SIZE/2); i++, cont++)
    {
        if(cont%2!=0)
        {
            arr_PC_Merge[i] = Inicial;
            Inicial-=2;
        }
        else
        {
            arr_PC_Merge[i] = Inicial2;
            Inicial2-=2;
        }
    }
    int Final=(SIZE/2)-1;
    int Final2=SIZE-1;
    for(int i=SIZE/2, cont=1; i<SIZE; i++, cont++)
    {
        if(cont%2!=0)
        {
            arr_PC_Merge[i] = Final;
            Final-=2;
        }
        else
        {
            arr_PC_Merge[i] = Final2;
            Final2-=2;
        }
    }/*
        4 8 2 6 / 3 7 1 5
        84 62 73 51
        8642 7531
        87654321          */

    //PEOR CASO QUICK
    for(int i=1; i<=SIZE; i++)
        arr_PC_Quick[i-1] = i;

    //MEJOR CASO QUICK
    arr_MC_Quick[0]=SIZE/2;
    for(int i=1, j=SIZE; j>0; j--, i++)
    {
        if(j == arr_MC_Quick[0])
            j--;
        arr_MC_Quick[i] = j;
    }
    5 10 9 8 7 6 4 3 2 1
    8 10 9 7 6 '5' 3 4 2 1
    10 9 '8' 7 6 '5' 4 '3' 2 1
}

void Union(int Arr_Datos[SIZE], int Inicio, int Pivote, int Final)
{
    int Inicio_Aux = Inicio;
    int Piv_Aux = Pivote+1;
    int IT = Inicio;
    int Arr_Aux[SIZE];
    while((Inicio_Aux <= Pivote) and (Piv_Aux <= Final))
    {
        if(Arr_Datos[Inicio_Aux] > Arr_Datos[Piv_Aux])
        {
            Arr_Aux[IT] = Arr_Datos[Inicio_Aux];
            Inicio_Aux++;
        }
        else
        {
            Arr_Aux[IT] = Arr_Datos[Piv_Aux];
            Piv_Aux++;
        }
        IT++;
    }
    while(Inicio_Aux <= Pivote)
    {
        Arr_Aux[IT] = Arr_Datos[Inicio_Aux];
        IT++;
        Inicio_Aux++;
    }
    while(Piv_Aux <= Final)
    {
        Arr_Aux[IT] = Arr_Datos[Piv_Aux];
        IT++;
        Piv_Aux++;
    }
    for(int i = Inicio; i < IT; i++)
        Arr_Datos[i] = Arr_Aux[i];
}


void Merge_Sort(int Arr_Datos[SIZE], int Inicio, int Final, int &Llam_Recurs)
{
    int Pivote;
    if (Inicio < Final)
    {
        Pivote=(Inicio+Final) / 2;
        Llam_Recurs++;
        Merge_Sort(Arr_Datos, Inicio, Pivote, Llam_Recurs);
        Llam_Recurs++;
        Merge_Sort(Arr_Datos, Pivote+1, Final, Llam_Recurs);
        Union(Arr_Datos, Inicio, Pivote, Final);
    }
}

void Particion(int Arr_Datos[SIZE], int Inicio, int Final, int &pivot)
{
    int m;
    int PIV_Mayor = Arr_Datos[Inicio];
    int Aux_Inicial = Inicio;
    for (int i=Inicio+1; i<=Final; i++)
    {
        if (Arr_Datos[i] > PIV_Mayor)
        {
            Aux_Inicial++;
            m = Arr_Datos[i];
            Arr_Datos[i]=Arr_Datos[Aux_Inicial];
            Arr_Datos[Aux_Inicial]=m;
        }
    }
    pivot = Aux_Inicial;
    int g = Arr_Datos[Inicio];
    Arr_Datos[Inicio]=Arr_Datos[pivot];
    Arr_Datos[pivot]=g;
}

void Quick_Sort(int Arr_Datos[SIZE], int Inicio, int Final, int &Llam_Recurs)
{
    if(Inicio < Final)
    {
        Particion(Arr_Datos, Inicio, Final, pivot);
        Llam_Recurs++;
        Quick_Sort(Arr_Datos, Inicio, pivot-1, Llam_Recurs);
        Llam_Recurs++;
        Quick_Sort(Arr_Datos, pivot+1, Final, Llam_Recurs);
    }
}

void imprimir(int arr[SIZE])
{
    for(int i=0; i<SIZE; i++)
        cout << arr[i] << "  ";
    cout << endl;
}

int main()
{
    int arr_PC_Merge[SIZE], arr_MC_Merge[SIZE], arr_PC_Quick[SIZE], arr_MC_Quick[SIZE];
    int Llam_Recurs;

    //FALTA TIEMPO Y COMPARACIONES
    Generador_Pruebas(arr_PC_Merge, arr_MC_Merge, arr_PC_Quick, arr_MC_Quick);

    Llam_Recurs=0;
    clock_t startTime = clock();
    cout << "Merge Sort con PEOR CASO para Merge Sort: " << endl;
    Merge_Sort(arr_PC_Merge, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_PC_Merge);
    cout << double(clock()-startTime)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    Llam_Recurs=0;
    clock_t startTime1 = clock();
    cout << "Merge Sort con MEJOR CASO para Merge Sort: " << endl;
    Merge_Sort(arr_MC_Merge, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_MC_Merge);
    cout << double(clock()-startTime1)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    Llam_Recurs=0;
    clock_t startTime2 = clock();
    cout << "Merge Sort con PEOR CASO para Quick Sort: " << endl;
    Merge_Sort(arr_PC_Quick, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_PC_Quick);
    cout << double(clock()-startTime2)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    Llam_Recurs=0;
    clock_t startTime3 = clock();
    cout << "Merge Sort con MEJOR CASO para Quick Sort: " << endl;
    Merge_Sort(arr_MC_Quick, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_MC_Quick);
    cout << double(clock()-startTime3)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    //FALTA TIEMPO Y COMPARACIONES
    cout << endl << endl;
    Generador_Pruebas(arr_PC_Merge, arr_MC_Merge, arr_PC_Quick, arr_MC_Quick);

    Llam_Recurs=0;
    clock_t startTime4 = clock();
    cout << "Quick Sort con PEOR CASO para Merge Sort: " << endl;
    Quick_Sort(arr_PC_Merge, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_PC_Merge);
    cout << double(clock()-startTime4)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    Llam_Recurs=0;
    clock_t startTime5 = clock();
    cout << "Quick Sort con MEJOR CASO para Merge Sort: " << endl;
    Quick_Sort(arr_MC_Merge, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_MC_Merge);
    cout << double(clock()-startTime5)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    Llam_Recurs=0;
    clock_t startTime6 = clock();
    cout << "Quick Sort con PEOR CASO para Quick Sort: " << endl;
    Quick_Sort(arr_PC_Quick, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_PC_Quick);
    cout << double(clock()-startTime6)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;

    Llam_Recurs=0;
    clock_t startTime7 = clock();
    cout << "Quick Sort con MEJOR CASO para Quick Sort: " << endl;
    Quick_Sort(arr_MC_Quick, 0, SIZE-1, Llam_Recurs);
    imprimir(arr_MC_Quick);
    cout << double(clock()-startTime7)/(double)CLOCKS_PER_SEC << " segundos." << endl;
    cout << "Llamadas recursivas: " << Llam_Recurs << endl << endl;
    return 0;
}

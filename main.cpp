#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// quantas palavras serão lidas do arquivo
#define SIZE 40 * 1000

void bubbleSort(string vet[], int n)
{
    string aux;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (vet[j + 1] < vet[j])
            {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
}

void selectionSort(string vet[], int n)
{
    int menor;
    string aux;

    for (int i = 0; i < n - 1; i++)
    {
        menor = i;

        for (int j = (i + 1); j < n; j++)
            if (vet[j] < vet[menor])
                menor = j;
        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
    }
}

void insertionSort(string vet[], int n)
{
    int j;
    string aux;

    for (int i = 1; i < n; i++)
    {
        aux = vet[i];

        for (j = i - 1; (j >= 0) && (vet[j] > aux); j--)
            vet[j + 1] = vet[j];
        vet[j + 1] = aux;
    }
}

void shellSort(string vet[], int n)
{
    string aux;
    int j, h;
    h = n / 2;

    while (h >= 1)
    {
        for (int i = 1; i < n; i++)
        {
            aux = vet[i];
            for (j = i - h; (j >= 0) && (vet[j] > aux); j = j - h)
                vet[j + h] = vet[j];
            vet[j + h] = aux;
        }

        h = h / 2;
    }
}

void mergeIntercala(string vet[], string aux[], int ini, int meio, int fim)
{
    int atual, fimEsq, n;

    atual = ini;
    fimEsq = meio - 1;
    n = fim - ini + 1;

    while ((ini <= fimEsq) && (meio <= fim))
    {
        if (vet[ini] <= vet[meio])
            aux[atual++] = vet[ini++];
        else
            aux[atual++] = vet[meio++];
    }

    while (ini <= fimEsq)
        aux[atual++] = vet[ini++];

    while (meio <= fim)
        aux[atual++] = vet[meio++];
    for (int i = 0; i < n; i++)
    {
        vet[fim] = aux[fim];
        fim--;
    }
}

void mergeDivide(string vet[], string aux[], int ini, int fim)
{
    int meio;

    if (fim > ini)
    {
        meio = (fim + ini) / 2;

        mergeDivide(vet, aux, ini, meio);
        mergeDivide(vet, aux, meio + 1, fim);

        mergeIntercala(vet, aux, ini, meio + 1, fim);
    }
}

void mergeSort(string vet[], int n)
{
    string aux[n];
    mergeDivide(vet, aux, 0, n - 1);
}

int particiona(string vet[], int esq, int dir)
{
    int i = esq, j = dir;
    string pivo, aux;
    pivo = vet[esq];

    while (i < j)
    {
        while ((vet[i] <= pivo) && (i < dir))
            i++;
        while ((vet[j] >= pivo) && (j > esq))
            j--;

        if (i < j)
        {
            aux = vet[j];
            vet[j] = vet[i];
            vet[i] = aux;
        }
    }

    vet[esq] = vet[j];
    vet[j] = pivo;
    return j;
}

void quickSort(string vet[], int esq, int dir)
{
    if (esq < dir)
    {
        int pivo = particiona(vet, esq, dir);
        quickSort(vet, esq, pivo - 1);
        quickSort(vet, pivo + 1, dir);
    }
}

void sink(string vet[], int n, int i)
{
    int maior;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    string aux;

    maior = i;
    if ((esq < n) && (vet[esq] > vet[maior]))
        maior = esq;
    if ((dir < n) && (vet[dir] > vet[maior]))
        maior = dir;

    if (maior != i)
    {
        aux = vet[i];
        vet[i] = vet[maior];
        vet[maior] = aux;
        sink(vet, n, maior);
    }
}

void createHeap(string vet[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        sink(vet, n, i);
}

void heapSort(string vet[], int n)
{
    string aux;
    createHeap(vet, n);
    for (int i = n - 1; i > 0; i--)
    {
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        sink(vet, --n, 0);
    }
}

void readFromFile(string filename, string vet[])
{
    ifstream aurelio(filename); // abre o arquivo para leitura
    int i = 0;

    if (aurelio.is_open())
    {
        while (aurelio) // le enquanto houver palavras no arquivo
        {
            aurelio >> vet[i++];
        }
    }
    aurelio.close(); // fecha o arquivo
}

int main()
{
    string palavras[40001], palavra;

    readFromFile("aurelio40000.txt", palavras);

    int startTime = (int)clock(); // marca o "tempo" de inicio

    // realiza o algoritmo desejado
    // bubbleSort(palavras, SIZE);
    // selectionSort(palavras, SIZE);
    // insertionSort(palavras, SIZE);
    // shellSort(palavras, SIZE);
    // mergeSort(palavras, SIZE);
    quickSort(palavras, 0, SIZE - 1);
    // heapSort(palavras, SIZE);

    // marca o "tempo" final, realiza a conversão para ms e mostra na tela
    cout << (((int)clock() - startTime) * 1000 / CLOCKS_PER_SEC) << endl;

    return 0;
}
//bibliotecas utilizadas
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include <chrono>

using namespace std;

//função pra gerar vetor do tamanho que o usuário quiser
void gerar_vetor(int v[], int tam) {
    for (int i = 0; i < tam; i++) {
        v[i] = i;
    }
}

void embaralhar_vetor(int v[], int tam) {
    int aux;
    for (int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

void mostrar_vetor(int v[], int tam) {
    for (int i = 0; i < tam; i++) {
        cout << v[i] << "  ";
    }
    cout << endl;
}

void escolher_posicao_pivo(int& pivo) {
    cout << "Escolha a posicao do pivo: " << endl;
    cout << "[1] Primeiro elemento" << endl;
    cout << "[2] Ultimo elemento" << endl;
    cout << "[3] Elemento do meio" << endl;
    cout << "[4] Mediana dos tres elementos" << endl;

    cin >> pivo;
}

//ver qual dos valores entre x, y e z é a mediana
int encontrarMediana(int v[], int a, int b, int c) {
    int x = v[a];
    int y = v[b];
    int z = v[c];

    if (y >= x && x >= z || z >= x && x >= y)
        return a;
    else if (x >= y && y >= z || z >= y && y >= x)
        return b;
    else
        return c;
}

//aqui o pivo estaria da forma como o professor falou, maiores a direita e menores a esquerda
void quicksort(int v[], int esq, int dir, int pivo) {
    int aux;
    int e = esq;
    int d = dir;
    int x = v[(e + d) / 2];

    do {
        while (x > v[e]) e++;
        while (x < v[d]) d--;
        if (e <= d) {
            aux = v[e];
            v[e] = v[d];
            v[d] = aux;
            e++;
            d--;
        }
    } while (e <= d);
    if (esq < d)quicksort(v, esq, d, pivo);
    if (dir > e) quicksort(v, e, dir, pivo);
}

//ordenção no shell
void Shell(int v[], int r, int s, int n) {
    int i, j, k, temp;
    bool achei;

    for (i = s + r; i < n; i += r) {
        j = s;
        achei = false;
        while (j < i && !achei) {
            if (v[i] < v[j])
                achei = true;
            else
                j = j + r;
        }
        if (achei) {
            temp = v[i];
            k = i - r;
            while (k >= j) {
                v[k + r] = v[k];
                k = k - r;
            }
            v[j] = temp;
        }
    }
}

//percorrer os grupos de elementos e utilizar a função anterior p ordernar
void shellsort(int v[], int tam, int grupos) {
    for (int i = grupos - 1; i >= 0; i--) {
        int inc = tam / grupos;
        for (int j = 0; j < inc; j++) {
            Shell(v, inc, j, tam);
        }
        cout << endl;
    }
}

//executar o quicksort com o pivo na posicao desejada e exibir como que tá a ordem dos números antes e depois da execucação
void executar_quicksort(int tam, int qntdCasos, int qntdExecucao) {
    int* v = new int[tam];
    gerar_vetor(v, tam);
    embaralhar_vetor(v, tam);

    for (int caso = 1; caso <= qntdCasos; ++caso) {
        escolher_posicao_pivo(caso);

        for (int exec = 0; exec < qntdExecucao; ++exec) {
            int* v_copy = new int[tam];
            copy(v, v + tam, v_copy);

            cout << "Vetor antes da ordenacao: ";
            mostrar_vetor(v_copy, tam);
            cout << endl;

            auto inicio = chrono::high_resolution_clock::now();
            quicksort(v_copy, 0, tam - 1, caso);
            auto fim = chrono::high_resolution_clock::now();

            cout << "Vetor depois da ordenacao: ";
            mostrar_vetor(v_copy, tam);

            double duracao = chrono::duration<double>(fim - inicio).count();
            cout << "Tempo de execucao: " << duracao << " segundos" << endl;

            delete[] v_copy;
        }
    }

    delete[] v;
}

//mesma coisa só que pro shell
void executar_shellsort(int tam, int qntdExecucao) {
    int* v = new int[tam];
    gerar_vetor(v, tam);
    embaralhar_vetor(v, tam);

    for (int grupos = 4; grupos <= 8; grupos += 2) {
        cout << "Vetor antes da ordenacao com " << grupos << " grupos: ";
        mostrar_vetor(v, tam);

        auto inicio = chrono::high_resolution_clock::now();

        for (int exec = 0; exec < qntdExecucao; ++exec) {
            int* v_copy = new int[tam];
            copy(v, v + tam, v_copy);
            shellsort(v_copy, tam, grupos);
            delete[] v_copy;
        }

        auto fim = chrono::high_resolution_clock::now();

        cout << "Vetor depois da ordenacao: ";
        mostrar_vetor(v, tam);

        double duracao = chrono::duration<double>(fim - inicio).count();
        cout << "Tempo de execucao com " << grupos << " grupos: " << duracao << " segundos" << endl;
    }

    delete[] v;
}


int main()
{
    int opcao = 4, tam, qntdCasos, qntdExecucao;

    while (opcao != 0) {
        cout << "---MENU---\n";
        cout << endl;
        cout << "[1] Metodo QuickSort\n";
        cout << "[2] Metodo Shell Sort\n";
        cout << "[3] Creditos\n";
        cout << "[0] Sair\n";

        cin >> opcao;
        system("cls");

        switch (opcao) {
        case 1:

            cout << "Informe o tamanho do vetor: ";
            cin >> tam;
            cout << endl;
            cout << "Informe a quantidade de execucoes por caso: ";
            cin >> qntdExecucao;
            cout << endl;
            cout << "Informe a quantidade de casos desejados (minimo 3): ";
            cin >> qntdCasos;

            while (qntdCasos < 3) {
                cout << "Informe a quantidade de casos desejados (minimo 3): ";
                cin >> qntdCasos;
            }

            executar_quicksort(tam, qntdCasos, qntdExecucao);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "Informe o tamanho do vetor: ";
            cin >> tam;
            cout << endl;
            cout << "Informe a quantidade de execucoes: ";
            cin >> qntdExecucao;

            executar_shellsort(tam, qntdExecucao);

            system("pause");
            system("cls");
            break;
        case 3:
            cout << "Professor: Marcos Carrard\n";
            cout << "Aluno: Guilherme G. Reis\n";
            system("pause");
            system("cls");
            break;
        default:
            cout << "Opcao invalida. Por favor, escolha uma opcao valida.\n";
            break;
        }
    }
}
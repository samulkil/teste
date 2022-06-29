#include "io.h"
#include <math.h>
#include <stdbool.h>

// By samuel Correia Pedrosa

typedef struct s_int_Array
{
    int length;
    ints data;
    int ix;
} int_Array;

typedef struct s_int_Matrix
{
    int rows;
    int columns;
    ints *data;
    int ix, iy;
} int_Matrix;

typedef struct supermercado
{
    char name[20];
    int codigo;
    float preco;
} mercado;

// 1

bool ordenado(int_Array vetor)
{
    bool ordenado = true;
    int x = 1;
    while (ordenado && x < vetor.length)
    {
        if (vetor.data[x] > vetor.data[x - 1])
        {
            ordenado = false;
        }
        x++;
    }
    return ordenado;
}

int_Array swap(int x, int y, int_Array vetor)
{
    int z = vetor.data[x];
    vetor.data[x] = vetor.data[y];
    vetor.data[y] = z;
    return vetor;
}
int_Array ordenar(int_Array vetor)
{
    int x = 0;
    int y = 0;
    int z = 0;
    while (x < vetor.length - 1)
    {
        z = x;
        y = x + 1;
        while (y < vetor.length)
        {
            if (vetor.data[y] > vetor.data[z])
            {
                z = y;
            }
            y++;
        }
        if (z != x)
        {
            swap(x, z, vetor);
        }
        x++;
    }
    return vetor;
}

// 2

int_Array inverter(int_Array vetor)
{
    int x = 0;
    int y = vetor.length - 1;
    while (x < y)
    {
        swap(x, y, vetor);
        x++;
        y--;
    }

    return vetor;
}

// 3

int segundomenor(int_Array vetor, int x)
{
    int y = 1;
    int menor = vetor.data[0];
    while (y < vetor.length)
    {
        if (vetor.data[y] > x && vetor.data[y] < menor)
        {
            menor = vetor.data[y];
        }
        y++;
    }
    return menor;
}

int menor(int_Array vetor)
{
    int y = 1;
    int menor = vetor.data[0];
    while (y < vetor.length)
    {
        if (vetor.data[y] < menor)
        {
            menor = vetor.data[y];
        }
        y++;
    }
    return menor;
}

// 4

int_Array filtrar(int_Array x, int_Array y)
{
    int_Array z;
    z.length = (x.length <= y.length) ? x.length : y.length;
    z.data = (int *)malloc(z.length * sizeof(int));
    int a = 0;
    int b = 0;
    int c = 0;
    while (a < x.length)
    {
        b = 0;
        bool repetido = false;
        while (!repetido && b < y.length)
        {
            if (x.data[a] == y.data[b])
            {
                z.data[c] = x.data[a];
                c++;
                repetido = true;
            }
            b++;
        }
        a++;
    }
    z.length = c;
    return z;
}

// 5

int parodecimal(int_Array binario)
{
    int resultado = 0;
    int x = 0;
    while (x < binario.length)
    {
        if (binario.data[x] == 1)
        {
            resultado += pow(2, binario.length - 1 - x);
        }
        x++;
    }
    return resultado;
}

// 6 e 7

int_Matrix tridiagonal(int_Array diagonal)
{
    int x = 0;
    int_Matrix y;
    y.rows = sqrt(diagonal.length);
    y.columns = sqrt(diagonal.length);
    y.data = (ints *)calloc(y.rows, sizeof(ints));
    int c = 0;
    while (c < y.rows)
    {
        y.data[c] = (ints)calloc(y.columns, sizeof(int));
        c++;
    }
    c = 0;
    while (x < y.rows)
    {
        if (x == 0)
        {
            y.data[x][x] = diagonal.data[c];
            c++;
            y.data[x][x + 1] = diagonal.data[c];
            c++;
        }
        else if (x == y.rows - 1)
        {
            y.data[x][x - 1] = diagonal.data[c];
            c++;
            y.data[x][x] = diagonal.data[c];
            c++;
        }
        else
        {
            y.data[x][x - 1] = diagonal.data[c];
            c++;
            y.data[x][x] = diagonal.data[c];
            c++;
            y.data[x][x + 1] = diagonal.data[c];
            c++;
        }
        x++;
    }
    return y;
}

// 8

bool potencialinha(int_Matrix matriz)
{
    int x = 0;
    int y;
    bool resposta = true;
    while (x < matriz.rows && resposta)
    {
        y = 0;
        while (y < matriz.columns && resposta)
        {
            if (matriz.data[x][y] != pow(x + 1, y))
            {
                resposta = false;
            }
            y++;
        }
        x++;
    }
    return resposta;
}

// 9

bool potenciacoluna(int_Matrix matriz)
{
    int x = 0;
    int y;
    bool resposta = true;
    while (x < matriz.rows && resposta)
    {
        y = 0;
        while (y < matriz.columns && resposta)
        {
            if (matriz.data[x][y] != pow(y + 1, x))
            {
                resposta = false;
            }
            y++;
        }
        x++;
    }
    return resposta;
}

void method01()
{
    int_Array vetor;
    FILE *arquivo = fopen("Dados1.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = x;
    vetor.data = (int *)malloc(x * sizeof(int));
    int y = 0;
    while (y < x)
    {
        fscanf(arquivo, "%d", &vetor.data[y]);
        y++;
    }
    fclose(arquivo);
    bool ordem = ordenado(vetor);
    if (!ordem)
    {
        vetor = ordenar(vetor);
    }
    arquivo = fopen("Decrescente.txt", "wt");
    fprintf(arquivo, "%d ", vetor.length);
    y = 0;
    while (y < x)
    {
        fprintf(arquivo, "%d ", vetor.data[y]);
        y++;
    }
    fclose(arquivo);
    free(vetor.data);
    IO_pause("Aperte ENTER para continuar");
}

void method02()
{
    int_Array vetor;
    FILE *arquivo = fopen("Decrescente.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = x;
    vetor.data = (int *)malloc(x * sizeof(int));
    int y = 0;
    while (y < x)
    {
        fscanf(arquivo, "%d", &vetor.data[y]);
        y++;
    }
    fclose(arquivo);
    int_Array invertido;
    invertido = inverter(vetor);
    arquivo = fopen("Invertidos.txt", "wt");
    fprintf(arquivo, "%d ", invertido.length);
    y = 0;
    while (y < x)
    {
        fprintf(arquivo, "%d ", invertido.data[y]);
        y++;
    }
    fclose(arquivo);
    free(vetor.data);
    IO_pause("Aperte ENTER para continuar");
}

void method03()
{
    int_Array vetor;
    FILE *arquivo = fopen("Dados1.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = x;
    vetor.data = (int *)malloc(x * sizeof(int));
    int y = 0;
    while (y < x)
    {
        fscanf(arquivo, "%d", &vetor.data[y]);
        y++;
    }
    int z;
    z = segundomenor(vetor, menor(vetor));
    printf("\nO segundo menor valor do arranjo eh: %d", z);
    fclose(arquivo);
    free(vetor.data);
    IO_pause("\nAperte ENTER para continuar");
}

void method04()
{
    int_Array vetor;
    FILE *arquivo = fopen("Dados1.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = x;
    vetor.data = (int *)malloc(x * sizeof(int));
    int y = 0;
    while (y < x)
    {
        fscanf(arquivo, "%d", &vetor.data[y]);
        y++;
    }
    fclose(arquivo);
    int_Array vetor2;
    arquivo = fopen("Dados2.txt", "r");
    fscanf(arquivo, "%d", &x);
    vetor2.length = x;
    vetor2.data = (int *)malloc(x * sizeof(int));
    y = 0;
    while (y < x)
    {
        fscanf(arquivo, "%d", &vetor2.data[y]);
        y++;
    }
    fclose(arquivo);
    int_Array filtro;
    filtro = filtrar(vetor, vetor2);
    y = 0;
    arquivo = fopen("Filtrados.txt", "wt");
    fprintf(arquivo, "%d ", filtro.length);
    while (y < filtro.length)
    {
        printf("\n%d", filtro.data[y]);
        fprintf(arquivo, "%d ", filtro.data[y]);
        y++;
    }
    free(vetor.data);
    free(vetor2.data);
    free(filtro.data);
    fclose(arquivo);
    IO_pause("\nAperte ENTER para continuar");
}
void method05()
{
    int_Array vetor;
    FILE *arquivo = fopen("Binarios1.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = x;
    vetor.data = (int *)malloc(x * sizeof(int));
    int y = 0;
    while (y < x)
    {
        fscanf(arquivo, "%d", &vetor.data[y]);
        y++;
    }
    int z;
    z = parodecimal(vetor);
    printf("\nO valor em decimal eh: %d", z);
    fclose(arquivo);
    free(vetor.data);
    IO_pause("\nAperte ENTER para continuar");
}

void method06()
{
    int_Array vetor;
    FILE *arquivo = fopen("Matriz1.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = pow(x, 2);
    vetor.data = (int *)malloc(vetor.length * sizeof(int));
    int y = 0;
    while (y < vetor.length)
    {
        if (!feof(arquivo))
        {
            fscanf(arquivo, "%d", &vetor.data[y]);
        }
        else
        {
            vetor.data[y] = 0x7EEE;
        }
        y++;
    }
    fclose(arquivo);
    bool ordem = ordenado(vetor);
    if (!ordem)
    {
        vetor = ordenar(vetor);
    }
    int_Matrix matriz = tridiagonal(inverter(vetor));
    y = 0;
    int z;
    arquivo = fopen("Matriz2.txt", "wt");
    while (y < matriz.rows)
    {
        z = 0;
        printf("\n");
        while (z < matriz.columns)
        {
            printf("%d ", matriz.data[y][z]);
            fprintf(arquivo, "%d ", matriz.data[y][z]);
            z++;
        }
        y++;
    }
    fclose(arquivo);
    free(vetor.data);
    y = 0;
    while (y < matriz.rows)
    {
        free(matriz.data[y]);
        y++;
    }
    free(matriz.data);
    IO_pause("\nAperte ENTER para continuar");
}

void method07()
{
    int_Array vetor;
    FILE *arquivo = fopen("Matriz1.txt", "r");
    int x = 0;
    fscanf(arquivo, "%d", &x);
    vetor.length = pow(x, 2);
    vetor.data = (int *)malloc(vetor.length * sizeof(int));
    int y = 0;
    while (y < vetor.length && !feof(arquivo))
    {
        fscanf(arquivo, "%d", &vetor.data[y]);
        y++;
    }
    fclose(arquivo);
    bool ordem = ordenado(vetor);
    if (!ordem)
    {
        vetor = ordenar(vetor);
    }
    int_Matrix matriz = tridiagonal(vetor);
    y = 0;
    int z;
    arquivo = fopen("Matriz2.txt", "wt");
    while (y < matriz.rows)
    {
        z = 0;
        printf("\n");
        while (z < matriz.columns)
        {
            printf("%d ", matriz.data[y][z]);
            fprintf(arquivo, "%d ", matriz.data[y][z]);
            z++;
        }
        y++;
    }
    fclose(arquivo);
    free(vetor.data);
    y = 0;
    while (y < matriz.rows)
    {
        free(matriz.data[y]);
        y++;
    }
    free(matriz.data);
    IO_pause("\nAperte ENTER para continuar");
}

void method08()
{
    int z = 0;
    FILE *arquivo = fopen("Matriz3.txt", "r");
    int_Matrix matriz;
    int linhas = 0;
    fscanf(arquivo, "%d", &linhas);
    int colunas = 0;
    fscanf(arquivo, "%d", &colunas);
    matriz.rows = linhas;
    matriz.columns = colunas;
    matriz.data = (ints *)malloc(linhas * sizeof(ints));
    int c = 0;
    while (c < linhas)
    {
        matriz.data[c] = (ints)malloc(colunas * sizeof(int));
        c++;
    }
    int x = 0;
    int y = 0;
    while (x < linhas)
    {
        y = 0;
        while (y < colunas)
        {

            fscanf(arquivo, "%d", &matriz.data[x][y]);
            y++;
        }
        x++;
    }
    fclose(arquivo);
    bool resposta = potencialinha(matriz);
    if (resposta)
    {
        printf("\nA matriz possui as caracteristicas de potencia por linha");
    }
    else
    {
        printf("\nA matriz nao possui as caracteristicas de potencia por linha");
    }
    c = 0;
    while (c < linhas)
    {
        free(matriz.data[c]);
        c++;
    }
    free(matriz.data);
    IO_pause("\nAperte ENTER para continuar");
}

void method09()
{
    int z = 0;
    FILE *arquivo = fopen("Matriz4.txt", "r");
    int_Matrix matriz;
    int linhas = 0;
    fscanf(arquivo, "%d", &linhas);
    int colunas = 0;
    fscanf(arquivo, "%d", &colunas);
    matriz.rows = linhas;
    matriz.columns = colunas;
    matriz.data = (ints *)malloc(linhas * sizeof(ints));
    int c = 0;
    while (c < linhas)
    {
        matriz.data[c] = (ints)malloc(colunas * sizeof(int));
        c++;
    }
    int x = 0;
    int y = 0;
    while (x < linhas)
    {
        y = 0;
        while (y < colunas)
        {

            fscanf(arquivo, "%d", &matriz.data[x][y]);
            y++;
        }
        x++;
    }
    fclose(arquivo);
    bool resposta = potenciacoluna(matriz);
    if (resposta)
    {
        printf("\nA matriz possui as caracteristicas de potencia por coluna");
    }
    else
    {
        printf("\nA matriz nao possui as caracteristicas de potencia por coluna");
    }
    c = 0;
    while (c < linhas)
    {
        free(matriz.data[c]);
        c++;
    }
    free(matriz.data);
    IO_pause("\nAperte ENTER para continuar");
}

void method10()
{
    FILE *arquivo = fopen("Dados3.txt", "r");
    int n;
    mercado *supermercados;
    fscanf(arquivo, "%d", &n);
    supermercados = (mercado *)malloc(n * sizeof(mercado));
    int x = 0;
    while (x < n)
    {
        fscanf(arquivo, "%s %d %f", supermercados[x].name, &supermercados[x].codigo, &supermercados[x].preco);
        x++;
    }
    float media = 0.0;
    x = 0;
    while (x < n)
    {
        media += supermercados[x].preco;
        x++;
    }
    media = media / n;
    printf("\nSupermecados abaixo da media: \n");
    x = 0;
    while (x < n)
    {
        if (supermercados[x].preco < media)
        {
            printf("\n%s,codigo %d, preco %.2f", supermercados[x].name, supermercados[x].codigo, supermercados[x].preco);
        }
        x++;
    }
    free(supermercados);
    fclose(arquivo);
    IO_pause("\nAperte ENTER para continuar");
}
/**
 * Funcao principal
 * @return codigo de encerramento
 */
int main()
{
    // definir dado
    int x = 0; // definir variavel com valor inicial

    // repetir até desejar parar
    do
    {
        // identificar
        IO_println("\nRecuperacao02 - Programa");

        // ler do teclado
        IO_println("\nOpcoes:");
        IO_println("\nDigite 0 - Terminar programa");
        IO_println("Digite 1 - 1");
        IO_println("Digite 2 - 2");
        IO_println("Digite 3 - 3");
        IO_println("Digite 4 - 4");
        IO_println("Digite 5 - 5");
        IO_println("Digite 6 - 6");
        IO_println("Digite 7 - 7");
        IO_println("Digite 8 - 8");
        IO_println("Digite 9 - 9");
        IO_println("Digite 10 - questao10\n");

        x = IO_readint("Escolha a opcao que deseja: ");

        // testar valor
        switch (x)
        {
        case 0:
            // method00();
            break;
        case 1:
            method01();
            break;
        case 2:
            method02();
            break;
        case 3:
            method03();
            break;
        case 4:
            method04();
            break;
        case 5:
            method05();
            break;
        case 6:
            method06();
            break;
        case 7:
            method07();
            break;
        case 8:
            method08();
            break;
        case 9:
            method09();
            break;
        case 10:
            method10();
            break;
        default:
            IO_println("ERRO: Valor invalido.");
        } // end switch
    } while (x != 0);

    // encerrar
    IO_pause("Aperte ENTER para terminar");
    return (0);
}
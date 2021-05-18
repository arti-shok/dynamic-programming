#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int min(int x, int y);

//12
int levenshtein_disance(char * x_string, char * y_string);
int levenshtein_disance_rec(char * x_string, int m, char * y_string, int n);
int levenshtein_disance_arr(char * x_string, int m, char * y_string, int n);

//14
int matrix_chain_multiplication(int* dims, int n);

//15
int find_min_matrix_path(int x[5][5]); //!�������� � ������������ ��������� �������

int min(int x, int y)
{
 if (x > y){
     return y;
 }
 else{
    return x;
 }
}

int levenshtein_disance(char * x_string, char * y_string) // ���� � �������. ������ 12
{
    // ���� � �����������(?) �������
    int m = strlen(x_string), n = strlen(y_string);
    return levenshtein_disance_arr(x_string, m, y_string, n);
    // return levenshtein_disance_rec(x_string, m, y_string, n);
}

int levenshtein_disance_rec(char * x_string, int m, char * y_string, int n) // ����������� ������� (�� ������). ������ 12
{

    // ������� ������, ����� ������ ������
    if (m == 0){
        return n;
    }
    if (n == 0){
        return m;
    }
    int cost;
    // ���� ��������� �������� �� ���������� - �� ��������� ����� 0
    if (x_string[m - 1] == y_string[n - 1]){
        cost = 0;
    }
    else{
        cost = 1;
    }
    // ����������� ����������� ���� - ������, ������� ��� �������� �������
    return min(min(levenshtein_disance_rec(x_string, m - 1, y_string, n) + 1,
                   levenshtein_disance_rec(x_string, m, y_string, n - 1)),
               levenshtein_disance_rec(x_string, m - 1, y_string, n - 1) + cost);
}

int levenshtein_disance_arr(char * x_string, int m, char * y_string, int n) // ������� � ����������� (������). ������ 12
{
    // ������ ��� ����������, ��� d[i][j] - ���������� ��� ����� x[1...i], y[1...j]
    char D[m + 1][n + 1];
    memset(D, 0, sizeof(D));

    // �������������
    for (int i = 1; i <= m; i++) {
        D[i][0] = i;
    }

    for (int i = 1; i <= n; i++) {
        D[0][i] = i;
    }

    int sub_cost;

    // ����� �� ����������, ��� � � ����������� ��������, �� ������� �� ���� ����������
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x_string[i - 1] == y_string[j - 1]){
                sub_cost = 0;
            }
            else{
                sub_cost = 1;
            }
            D[i][j] = min(min(D[i - 1][j] + 1, D[i][j - 1] + 1),
                          D[i - 1][j - 1] + sub_cost);
        }
    }
    return D[m][n];
}

int matrix_chain_multiplication(int* dims, int n) // !!! �������� � ������ �������, �� ����� ����������� ������ ������� !!! ������ 14
{
    // ������ ��� ����������, ��� c[i][j] - ��� ����������� ��������� ��������� ������������������ ������ Mi*...*Mj, 0 <= i < j <= n
    int C[n + 1][n + 1];

    for (int i = 1; i <= n; i++) {
        C[i][i] = 0;
    }

    // ��������� ��������������������� ���� ���� � ��������� ������� �
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;
            C[i][j] = INT_MAX;

            for (int k = i; j < n && k <= j - 1; k++)
            {
                int cost = C[i][k] + C[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < C[i][j]) {
                    C[i][j] = cost;
                }
            }
        }
    }
    // ������� �[1][n - 1] - ����������� ��������� ��������� ������������������ ������ � ������ �� ���������
    return C[1][n - 1];
}

int find_min_matrix_path(int costs[5][5]) // !!! �������� � ����������� ������� !!! ������ 15
{
    // ����������� ������� ����������, ��� c[i][j] - ����������� ���������� �� �������� �[i][j]
    int C[5][5];
    memset(C, 0, sizeof(C));
    C[0][0] = costs[0][0];

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            //���� ������� � ������ ��� ������� �������
            if (i == 0 && j > 0){
                C[0][j] = C[0][j - 1] + costs[0][j];
            }
            else if (j == 0 && i > 0){
                C[i][0] += C[i - 1][0] + costs[i][0];
            }
            // �������� ����� ������ ��������� �� �������� ���������
            else if (i > 0 && j > 0){
                C[i][j] += min(C[i - 1][j], C[i][j - 1]) + costs[i][j];
            }
        }
    }

    return C[4][4];
}






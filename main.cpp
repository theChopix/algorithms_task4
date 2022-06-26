#include <iomanip>
#include <iostream>
using namespace std;

/* input of columns is numbered from 1;
    array indexes go from 0... */
#define ARRAyOFFSET(x) (x - 1)

struct village_t {
    int numberOfWarriors;
    int price;
    int potential;
};

void get_max_value(village_t **cMatrix, int row, int col, int tPrice,
                   int wPrice);
village_t **get_compute_matrix(int *vlgs, int nVlgs, int tPrice, int wPrice);

void print_compute_matrix(village_t **cMatrix, int nVlgs);

int main()
{
    int numberOfVillages, totemPrice, warriorPrice;
    cin >> numberOfVillages >> totemPrice >> warriorPrice;

    int *villages = new int[numberOfVillages];

    for (int i = 0; i < numberOfVillages; i++)
        cin >> villages[i];

    village_t **computeMatrix = get_compute_matrix(villages, numberOfVillages,
                                                   totemPrice, warriorPrice);

    int res = max(computeMatrix[0][ARRAyOFFSET(numberOfVillages)].price,
                  computeMatrix[0][ARRAyOFFSET(numberOfVillages)].potential);
    cout << res << "\n";

    for (int i = 0; i < numberOfVillages; i++) {
        delete computeMatrix[i];
    }
    delete computeMatrix;
}

village_t **get_compute_matrix(int *vlgs, int nVlgs, int tPrice, int wPrice)
{
    village_t **ret = new village_t *[nVlgs];
    for (int i = 0; i < nVlgs; i++) {
        ret[i] = new village_t[nVlgs];
    }

    /* atfirst filling on the main diagonale */
    for (int i = 0; i < nVlgs; i++) {
        ret[i][i].numberOfWarriors = vlgs[i];
        ret[i][i].price = 0;
        ret[i][i].potential = 0;
    }

    for (int i = 1; i < nVlgs; i++) {
        for (int j = 0; j < nVlgs - i; j++) {
            get_max_value(ret, j, i + j, tPrice, wPrice);
        }
    }
    return ret;
}

void get_max_value(village_t **cMatrix, int row, int col, int tPrice,
                   int wPrice)
{
    int price, potential;
    int tmpPrice, tmpPotential;

    int numberOfWarriors;
    bool undefined = true;

    for (int i = 0; i < col - row; i++) {

        village_t vlg1 = cMatrix[row][col - i - 1];
        village_t vlg2 = cMatrix[col - i][col];

        int warriorDiff = abs(vlg1.numberOfWarriors - vlg2.numberOfWarriors);

        tmpPrice = vlg1.price + vlg2.price - warriorDiff * wPrice + tPrice;
        tmpPotential =
            max(vlg1.price, vlg1.potential) + max(vlg2.price, vlg2.potential);

        if (undefined) {

            price = tmpPrice;
            potential = tmpPotential;
            numberOfWarriors = vlg1.numberOfWarriors + vlg2.numberOfWarriors;
            undefined = false;

        } else {

            if (tmpPrice > price)
                price = tmpPrice;
            if (tmpPotential > potential)
                potential = tmpPotential;
        }
    }
    cMatrix[row][col].price = price;
    cMatrix[row][col].numberOfWarriors = numberOfWarriors;
    cMatrix[row][col].potential = potential;
}

void print_compute_matrix(village_t **cMatrix, int nVlgs)
{
    for (int i = 0; i < nVlgs; i++) {
        for (int j = 0; j < nVlgs; j++) {
            cout << "[" << setw(3) << cMatrix[i][j].numberOfWarriors << ", "
                 << setw(3) << cMatrix[i][j].price << ", " << setw(3)
                 << cMatrix[i][j].potential << "]  ";
        }
        cout << "\n";
    }
}
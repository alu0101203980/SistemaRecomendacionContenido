#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include "math.h"
#include <iomanip>
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

void crearMatriz(std::vector<std::tuple<int, int, std::string, int>> &vTerminos, std::string filename, float &nlineas)
{

    std::fstream file;
    std::string word, line;
    std::ifstream input(filename);
    std::string unused;
    int contDoc = 1, pos, indice = 0, contador = 0, numlines = 1;
    bool exists = false;

    file.open(filename.c_str());
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        while (iss >> word)
        {

            exists = false;
            for (int j = 0; j < vTerminos.size(); j++)
            {
                if (std::get<2>(vTerminos[j]) == word && (std::get<0>(vTerminos[j]) == numlines))
                {
                    exists = true;
                    pos = j;
                }
            }
            if (exists == false /*&& word != "." && word != ","*/)
            {
                vTerminos.push_back(std::make_tuple(numlines, indice, word, 1));
                indice++;
            }
            else
            {
                contador++;
                std::get<3>(vTerminos[pos]) = (std::get<3>(vTerminos[pos]) + contador);
                contador = 0;
            }
        }
        numlines++;
    }

    file.close();
    nlineas = numlines;
}

void calcularResultados(std::vector<std::tuple<int, int, std::string, int>> vTerminos,
                        std::vector<std::tuple<int, int, std::string, int, float, float>> &vFinal, float nlineas)
{
    float aparece = 1, IDF = 0, division = 0, IDF_TF = 0;
    int nArticulo, nIndice, TF;
    std::string termino;
    std::pair<int, std::string> aux;

    for (int i = 1; i < vTerminos.size(); i++)
    {
        aparece = 1;
        aux.first = std::get<0>(vTerminos[i]);
        aux.second = std::get<2>(vTerminos[i]);
        for (int j = 1; j < vTerminos.size(); j++)
        {
            if ((aux.second == std::get<2>(vTerminos[j])) && (aux.first != std::get<0>(vTerminos[j])))
            {
                aparece++;
            }
        }

        division = (nlineas - 1) / aparece;

        IDF = log10(division);

        IDF_TF = std::get<3>(vTerminos[i]) * IDF;

        nArticulo = std::get<0>(vTerminos[i]);
        nIndice = std::get<1>(vTerminos[i]);
        termino = std::get<2>(vTerminos[i]);
        TF = std::get<3>(vTerminos[i]);

        vFinal.push_back(std::make_tuple(nArticulo, nIndice, termino, TF, IDF, IDF_TF));

        division = 0;
        IDF = 0;
        IDF_TF = 0;
    }
}

void mostrarTablas(std::vector<std::tuple<int, int, std::string, int, float, float>> vFinal, float nlineas)
{
    for (int i = 1; i < nlineas; i++)
    {
        std::cout << BOLDYELLOW << "\nARTICULO: " << i << RESET << std::endl;
        std::cout << BOLDRED << "+----------------------------------------------------------+" << RESET << std::endl;
        std::cout << BOLDRED << "|" << BOLDBLUE << std::left << std::setw(15) << "Término" << std::left << std::setw(15) << "Índice" << std::left << std::setw(10) << "TF" << std::left << std::setw(10) << "IDF" << std::left << std::setw(10) << "IDF-TF" << BOLDRED << "|" << RESET << std::endl;
        std::cout << BOLDRED << "+----------------------------------------------------------+" << RESET << std::endl;
        for (int j = 0; j < vFinal.size(); j++)
        {
            if (i == std::get<0>(vFinal[j]))
            {
                std::cout << BOLDRED << "|" << BOLDWHITE << std::left << std::setw(15) << std::get<2>(vFinal[j]) << RESET;
                std::cout << std::left << std::setw(13) << std::get<1>(vFinal[j]);
                std::cout << std::left << std::setw(10) << std::get<3>(vFinal[j]);
                std::cout << std::left << std::setw(10) << std::get<4>(vFinal[j]);
                std::cout << std::left << std::setw(10) << std::get<5>(vFinal[j]) << BOLDRED << "|" << std::endl;
                std::cout << BOLDRED << "+----------------------------------------------------------+" << RESET << std::endl;
            }
        }
    }
}

void normalizarTF(std::vector<std::tuple<int, int, std::string, float, float, float>> &vNormalizado,
                  std::vector<std::tuple<int, int, std::string, int, float, float>> vFinal)
{
    int articulo = 0, indice = 0;
    std::string termino;
    float TF_Normalizado = 0, IDF = 0, IDF_TF = 0;

    for (int i = 0; i < vFinal.size(); i++)
    {
        articulo = std::get<0>(vFinal[i]);
        indice = std::get<1>(vFinal[i]);
        termino = std::get<2>(vFinal[i]);
        TF_Normalizado = 1 + (log10(std::get<3>(vFinal[i])));
        IDF = std::get<4>(vFinal[i]);
        IDF_TF = std::get<5>(vFinal[i]);
        vNormalizado.push_back(std::make_tuple(articulo, indice, termino, TF_Normalizado, IDF, IDF_TF));
    }
}

void longitudVector(std::vector<std::tuple<int, int, std::string, float, float, float>> vNormalizado,
                    std::vector<std::pair<int, float>> &vLongVec, float nlineas)
{
    float sumatorio = 0;

    for (int i = 1; i < nlineas; i++)
    {
        for (int j = 0; j <= vNormalizado.size(); j++)
        {
            if (i == std::get<0>(vNormalizado[j]))
            {
                sumatorio += pow(std::get<3>(vNormalizado[j]), 2);
            }
        }
        sumatorio = sqrt(sumatorio);
        vLongVec.push_back(std::make_pair(i, sumatorio));
        sumatorio = 0;
    }
}

void valoresCoseno(std::vector<std::tuple<int, int, std::string, float, float, float>> vNormalizado, float nlineas,
                   std::vector<std::pair<int, float>> vLongVec, std::vector<std::tuple<int, std::string, float>> &vCalcularCoseno)
{
    float aux = 0;
    for (int i = 1; i < nlineas; i++)
    {
        for (int j = 0; j < vNormalizado.size(); j++)
        {
            if (i == std::get<0>(vNormalizado[j]))
            {
                aux = std::get<3>(vNormalizado[j]) / vLongVec[i - 1].second;
                vCalcularCoseno.push_back(std::make_tuple(i, std::get<2>(vNormalizado[j]), aux));
                aux = 0;
            }
        }
    }
}

void vectoresAuxiliares(int posI, int posJ, std::vector<std::tuple<int, std::string, float>> &aux1,
                        std::vector<std::tuple<int, std::string, float>> &aux2,
                        std::vector<std::tuple<int, std::string, float>> vCalcularCoseno)
{
    aux1.clear();
    aux2.clear();

    for (int i = 0; i < vCalcularCoseno.size(); i++)
    {
        if (std::get<0>(vCalcularCoseno[i]) == posI)
        {
            aux1.push_back(std::make_tuple(std::get<0>(vCalcularCoseno[i]), std::get<1>(vCalcularCoseno[i]), std::get<2>(vCalcularCoseno[i])));
        }
        if (std::get<0>(vCalcularCoseno[i]) == posJ)
        {
            aux2.push_back(std::make_tuple(std::get<0>(vCalcularCoseno[i]), std::get<1>(vCalcularCoseno[i]), std::get<2>(vCalcularCoseno[i])));
        }
    }

    float sumatorio = 0;
    std::pair<int, std::string> aux_par;

    for (int i = 0; i < aux1.size(); i++)
    {
        aux_par.first = i;
        aux_par.second = std::get<1>(aux1[i]);

        for (int j = 0; j < aux2.size(); j++)
        {
            if (aux_par.second == std::get<1>(aux2[j]))
            {

                sumatorio = sumatorio + (std::get<2>(aux1[aux_par.first]) * std::get<2>(aux2[j]));
            }
        }
    }
    std::cout << " Artículos " << BOLDRED << posI << RESET << " y " << BOLDRED << posJ << RESET << BOLDWHITE << " -->  " << sumatorio << RESET << std::endl;
}

int main()
{
    //Creamos el vector para almacenar los documentos
    std::vector<std::string> vDoc;
    std::vector<std::tuple<int, int, std::string, int>> vTerminos = {{NULL, NULL, "", NULL}};
    std::vector<std::tuple<int, int, std::string, int, float, float>> vFinal;
    std::vector<std::tuple<int, int, std::string, float, float, float>> vNormalizado;
    std::vector<std::pair<int, float>> vLongVec;
    std::vector<std::tuple<int, std::string, float>> vCalcularCoseno;
    std::vector<std::tuple<int, std::string, float>> aux1;
    std::vector<std::tuple<int, std::string, float>> aux2;

    // Creamos las variables necesarias para leer los documentos
    std::string word, filename;
    float nlineas = 0, narticulo = 1;
    bool impreso = false;

    std::cout << "\n\033[96mFicheros posibles: \033[0m\n";
    system("ls examples-documents/*.txt");
    std::cout << "\n¿Que documento quiereutilizar?" << std::endl;
    std::cin >> filename;

    filename = "examples-documents/" + filename + ".txt";
    //Creamos el vector con todas las palabras existentes
    crearMatriz(vTerminos, filename, nlineas);
    //Creamos el vector con los resultados
    calcularResultados(vTerminos, vFinal, nlineas);

    mostrarTablas(vFinal, nlineas);

    normalizarTF(vNormalizado, vFinal);

    longitudVector(vNormalizado, vLongVec, nlineas);

    valoresCoseno(vNormalizado, nlineas, vLongVec, vCalcularCoseno);

    std::cout << BOLDGREEN << "\n\nSIMILARIDAD COSENO\n"
              << RESET << std::endl;

    for (int i = 1; i < nlineas; i++)
    {
        for (int j = 1; j < nlineas; j++)
        {
            if (i != j)
            {
                vectoresAuxiliares(i, j, aux1, aux2, vCalcularCoseno);
            }
        }
    }

    return 0;
}
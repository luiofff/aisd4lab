#include <iostream>
#include <iomanip>
#include <cmath>

#define n 5
#define m 3

class Approximation {
    
private:
    float A[m][m], B[m], C[m], Yl[n], D[n], Kr, Dmax, x[5], y[5];
    int IM;
public:
    void performApproximation() {
        setlocale(LC_ALL, "RUS");

        getInputData();
        calculateCoefficients();

        std::cout << "Matrix A vector B:\n";
        printMatrixAndVector();

        solveLinearSystem();

        std::cout << "\nVector C:\n";
        printResultingVector();

        calculateApproximationValues();

        std::cout << "\n\n approximation criterion J = " << Kr;

        findMaxDeviation();

        std::cout << "\n\n maximum deviation = " << std::fixed << std::setprecision(3)
                  << fabs(Dmax) << ", при x[" << IM + 1 << "] = " << x[IM] << "\n\n";
    }

    void getInputData() {
        int i;

        std::cout << "Аппроксимация функции методом наименьших квадратов\n";
        std::cout << "Метод Зейделя\n\n";

        std::cout << "\n x ";
        for (i = 0; i < n; i++)
            std::cin >> x[i];

        std::cout << "\n y ";
        for (i = 0; i < n; i++)
            std::cin >> y[i];
    }

    void calculateCoefficients() {
        int i, j, l;
        float S;

        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++) {
                S = 0;
                for (l = 0; l < n; l++)
                    S = S + basisFunction(x[l], i) * basisFunction(x[l], j);
                A[i][j] = S;
            }
            S = 0;
            for (l = 0; l < n; l++)
                S = S + y[l] * basisFunction(x[l], i);
            B[i] = S;
        }
    }

    void printMatrixAndVector() {
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < m; k++)
                std::cout << std::setw(9) << A[i][k] << " ";
            std::cout << std::setw(9) << B[i] << "\n";
        }
    }

    float basisFunction(float x, int g) {
        if (g == 0)
            return 1;
        else if (g == 1)
            return 2 * x;
        else if (g == 2)
            return 4 * x * x - 2;

        return 0;  // Handle other cases if needed
    }

    void solveLinearSystem() {
        if (isConvergent()) {
            for (int i = 0; i < m; i++)
                C[i] = B[i];
            float test;
            float eps = 0.001;
            do {
                test = 0;
                for (int i = 0; i < m; i++) {
                    float sum = 0;
                    for (int j = 0; j < m; j++)
                        if (j != i)
                            sum += A[i][j] * C[j];
                    float bpx = (B[i] - sum) / A[i][i];
                    test += std::fabs(bpx - C[i]);
                    C[i] = bpx;
                }
            } while (test > eps);
        } else {
            std::cerr << "Linear system is not convergent.\n";
            exit(EXIT_FAILURE);
        }
    }

    bool isConvergent() {
        for (int i = 0; i < m; i++) {
            float Ad = std::fabs(A[i][i]);
            float Sd = 0;
            for (int j = 0; j < m; j++)
                if (j != i)
                    Sd += std::fabs(A[i][j]);
            if (Ad <= Sd)
                return false;
        }
        return true;
    }

    void printResultingVector() {
        for (int i = 0; i < m; i++)
            std::cout << "C[" << i << "]=" << std::setw(6) << C[i] << "\n";
    }

    void calculateApproximationValues() {
        int k, i;
        Kr = 0;
        k = 0;
        Yl[0] = 0;
        for (i = 0; i < n; i++) {
            Yl[i] = C[0] * basisFunction(x[i], k) + C[1] * basisFunction(x[i], k + 1) + C[2] * basisFunction(x[i], k + 2);
            D[i] = y[i] - Yl[i];
            Kr += D[i] * D[i];
        }
        std::cout << "\n values approximating function\n";
        for (i = 0; i < n; i++)
            std::cout << std::fixed << std::setprecision(3) << Yl[i] << " ";
        std::cout << "\n\n deviation values approximating function\n";
        for (i = 0; i < n; i++)
            std::cout << std::fixed << std::setprecision(3) << D[i] << " ";
    }

    void findMaxDeviation() {
        int i;
        Dmax = D[0];
        IM = 0;
        for (i = 0; i < n; i++) {
            if (std::fabs(D[i]) > std::fabs(Dmax)) {
                Dmax = D[i];
                IM = i;
            }
        }
    }

};

int main() {
    Approximation approx;
    approx.performApproximation();

    return 0;
}

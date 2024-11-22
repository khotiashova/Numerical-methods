#include "test/system1.h"
#include "iostream"
#include "SystemOfDifferentialEquations.h"
#include "BoundaryValueProblem.h"
using namespace std;

void differential_equations1_review(double x_0, double y_0,
                                   double (*equation)(double, double), double (*solution)(double)) {
    double x_n, h;
    int n;
    cout << "Enter the right point of the segment - ";
    cin >> x_n;
    cout << "Enter number of grid parts - ";
    cin >> n;
    h = (x_n - x_0) / n;
    vector<vector<double>> runge2 = RUNGE2_1(equation, h, n, x_0, y_0);
    vector<vector<double>> runge4 = RUNGE4_1(equation, h, n, x_0, y_0);
    double acc2 = accuracy1(runge2, n, solution);
    double acc4 = accuracy1(runge4, n, solution);
    cout << "Accuracy for runge 2 is " << acc2 << endl;
    cout << "Accuracy for runge 4 is " << acc4 << endl;
    FILE *output0 = fopen("xoutput", "w");
    FILE *output1 = fopen("y1output", "w");
    FILE *output2 = fopen("y2output", "w");
    for (int i = 0; i <= n; i++) {
        fprintf(output0, "%lf\n", runge2[0][i]);
    }
    for (int i = 0; i <= n; i++) {
        fprintf(output1, "%lf\n", runge2[1][i]);
    }
    for (int i = 0; i <= n; i++) {
        fprintf(output2, "%lf\n", runge4[1][i]);
    }
    fclose(output0);
    fclose(output1);
    fclose(output2);
    system("python3 graph.py 1");
}

void differential_equations2_review(double x_0, double u_0, double v_0,
                                    double (*eq1)(double, double, double), double (*eq2)(double, double, double)) {
    double x_n, h;
    int n;
    cout << "Enter the right point of the segment - ";
    cin >> x_n;
    cout << "Enter number of grid parts - ";
    cin >> n;
    h = (x_n - x_0) / n;
    vector<vector<double>> runge4 = RUNGE4_2(eq1, eq2, h, n, x_0, u_0, v_0);
    FILE *output0 = fopen("xoutput", "w");
    FILE *output1 = fopen("uoutput", "w");
    FILE *output2 = fopen("voutput", "w");
    for (int i = 0; i <= n; i++) {
        fprintf(output0, "%lf\n", runge4[0][i]);
    }
    for (int i = 0; i <= n; i++) {
        fprintf(output1, "%lf\n", runge4[1][i]);
    }
    for (int i = 0; i <= n; i++) {
        fprintf(output2, "%lf\n", runge4[2][i]);
    }
    fclose(output0);
    fclose(output1);
    fclose(output2);
    system("python3 graph.py 2");
}

void
border_problem_review(long double x0, long double xn, long double sigma1, long double sigma2, long double gamma1,
                      long double gamma2, long double delta1, long double delta2, int N) {
    long double h = (xn - x0) / N;

    matrix *A = new_matrix(N + 1, N + 1);
    matrix *fm = new_matrix(N + 1, 1);

    A->elem[0][0] = (sigma1 * h) - gamma1;
    A->elem[1][0] = gamma1;
    fm->elem[0][0] = delta1 * h;

    A->elem[N - 1][N] = -gamma2;
    A->elem[N][N] = (sigma2 * h) + gamma2;
    fm->elem[0][N] = delta2 * h;

    for (int i = 1; i < N; ++i) {
        A->elem[i - 1][i] = 1 - p(x0 + i * h) * h * 0.5;
        A->elem[i][i] = -2 + q(x0 + i * h) * h * h;
        A->elem[i + 1][i] = 1 + p(x0 + i * h) * h * 0.5;
        fm->elem[0][i] = f(x0 + i * h) * h * h;
    }

    long double *ans;
    ans = thomas_algo(A, fm);
    FILE *xoutput = fopen("xoutput", "w");
    for (int i = 0; i <= N; ++i) {
        fprintf(xoutput, "%Lf\n", x0 + h * i);
    }
    fclose(xoutput);

    FILE *youtput = fopen("youtput", "w");
    for (int i = 0; i <= N; ++i) {
        fprintf(youtput, "%Lf\n", ans[i]);
    }
    fclose(youtput);

    system("python3 graphborder.py");

    delete_matrix(A);
    delete_matrix(fm);
    free(ans);

}

int main() {
    differential_equations1_review(x_1_0, y_1_0, func1, sol1);
    differential_equations2_review(x_2_0, u_2_0, v_2_0, func2_1, func2_2);
    border_problem_review(0.4, 0.7, 1, 1, 0, 2, 1.2, 1.4, 500);
    return 0;
}

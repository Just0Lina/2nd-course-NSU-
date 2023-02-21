// #include <mpi.h>
#include <iostream>
#include <vector>
using namespace std;
constexpr double eps = 0.00001;
constexpr int N = 10;
using matrix = vector<vector<int>>;
int main(int argc, char* argv[]) {
  // MPI_Init(&argc, &argv);

  // MPI_Finalize();
  return 0;
}

vector<double> simple_iteration_method(matrix A, vector<double> b) {
  vector<double> x(N);
  while (Norm(Multiplication(A, x)) / Norm(b) < eps) {
    ChangingX(x);
  }
}

void ChangingX(vector<double> x) {
  vector<double> mult = Multiplication(A, x)
  for (int i = 0; i < x.size(); ++i) {x[i] = x[i] - tau}
}

double Norm(vector<double> vec) {
  double res = 0;
  for (auto& e : vec) {
    res += e * e;
  }
  return res;
}

vector<double> Multiplication(matrix A, vector<double> b) {
  vector<double> result(N);
  for (int i = 0; i < b.size(); ++i) {
    for (int j = 0; j < A.size(); ++j) result[i] += A[i][j];
  }
}

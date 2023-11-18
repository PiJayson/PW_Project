#include <iostream>
#include <string>
#include <omp.h>

using namespace std;
 
//     --CLASSES--     //
 
class matrix{
  private:
    int m, n, **tab = nullptr, *tab_temp = nullptr;
  public:
    matrix(int m_ = 0, int n_ = 0);
 
    void scan();
    void print() const;
    void set_id();
 
    int get_m() const;
    int get_n() const;
    int **get_tab() const;
 
    void det_copy(matrix &into, int &col);
    long long determinant();
 
    void operator=(const matrix& A);
    friend matrix operator+(const matrix& A, const matrix& B);
    friend matrix operator*(const matrix& A, const matrix& B);
    friend matrix operator^(const matrix& A, int p);
    friend ostream& operator<<(ostream &stream, const matrix &A);
    friend istream& operator>>(istream &stream, matrix &A);
 
    void clean();
    ~matrix();
};
//     --VARIABLES--     //
 
static int MOD = 10000;
 
//     --FUNCTIONS--     //
matrix *get_matrix();
void read();
 
/////////////////////////MAIN//////////////////////////////
 
int main() {
  ios_base::sync_with_stdio(false);
 
  int n, k;
  cin>>n;
  for(int i = 0; i < n; i++){
    read();
  }
}
 
matrix *get_matrix(){
  int m, n;
  cin >> m >> n;
  return new matrix(m, n);
}
void read(){
  string comm;
  cin >> comm;
 
  int power;
  if(comm == "POWER") cin >> power;
 
  matrix *m_1 = get_matrix();
  m_1->scan();
 
  if(comm == "ADD"){
    matrix *m_2 = get_matrix();
    m_2->scan();
    matrix ans;
    try{
      *m_1 + *m_2;
    }
    catch(const char *a) {cout<<a<<endl;return;}
    m_1->print();
    m_1->clean();
    m_2->clean();
  }
  else if(comm == "MULTIPLY"){
    matrix *m_2 = get_matrix();
    m_2->scan();
    try{
      *m_1 = *m_1 * *m_2;
    }
    catch(const char *a) {cout<<a<<endl;return;}
    m_1->print();
    delete m_1;
    delete m_2;
  }
  else if(comm == "POWER"){
    try{
      *m_1 = *m_1^power;
    }
    catch(const char *a) {cout<<a<<endl;return;}
    m_1->print();
  }
  else if(comm == "DETERMINANT"){
    try{
      cout<<m_1->determinant()<<endl;
    }
    catch(const char *a) {cout<<a<<endl;return;}
  }
}
 
 
 
 
 
 
///////////////////// CLASSESS //////////////////////////
 
matrix::matrix(int m_, int n_){
  m = m_; n = n_;
  tab = new int *[m];
  tab_temp = new int [m*n];
 
  for(int i = 0; i < m*n; i++) tab_temp[i] = 0;
  for(int i = 0; i < m; i++){
    tab[i] = tab_temp +i*n;
  }
}
 
void matrix::scan(){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      cin >> tab[i][j];
    }
  }
}
 
void matrix::print() const{
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      cout << tab[i][j] % 1000<<" ";
    }
    cout<<endl;
  }
}
 
void matrix::set_id(){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      if(i == j) tab[i][j] = 1;
      else tab[i][j] = 0;
    }
  }
}
 
int matrix::get_m() const{
  return m;
}
 
int matrix::get_n() const{
  return n;
}
 
int **matrix::get_tab() const{
  return tab;
}
 
void matrix::det_copy(matrix &into, int &col){
  int **into_tab = into.get_tab();
 
  for(int i = 0; i < m-1; i++){
    for(int j = 0; j < n; j++){
      if(j < col) into_tab[i][j] = tab[i][j];
      else if(j > col) into_tab[i][j-1] = tab[i][j];
    }
  }
}
 
long long matrix::determinant(){
  if(m != n) throw("ERROR DETERMINANT");
 
  if(m == 1 && n == 1) return tab[0][0];
 
  long long sum = 0;
  for(int j = 0; j < n; j++){
    matrix M_new(n-1, n-1);
    det_copy(M_new, j);
    int s = 1;
    if((j+1 + n)%2 == 1) s *= (-1);
 
    if(tab[n-1][j] != 0) sum += s * tab[n-1][j] * M_new.determinant();
  }
  return sum;
}
 
void matrix::operator=(const matrix& A){
  delete tab;
  delete tab_temp;
 
  m = A.get_m();
  n = A.get_n();
 
  tab = new int *[m];
  tab_temp = new int [m*n];
 
  for(int i = 0; i < m; i++){
    tab[i] = tab_temp +i*n;
  }
 
  int **tab_A = A.get_tab();
 
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      tab[i][j] = tab_A[i][j];
    }
  }
}
 
matrix operator+(const matrix& A, const matrix& B){
  if(A.get_m() != B.get_m() || A.get_n() != B.get_n()) throw("ERROR ADD");
 
  int **tab_A = A.get_tab();
  int **tab_B = B.get_tab();
  matrix M;
 
  // #pragma omp parallel for
  // for(int i = 0; i < A.get_m(); i++){
  //   for(int j = 0; j < A.get_n(); j++){
  //     tab_A[i][j] += tab_B[i][j];
  //   }
  // }

  #pragma omp parallel
  {
      for(int i = omp_get_thread_num(); i < A.get_m(); i+= omp_get_num_threads()){
        for(int j = 0; j < A.get_n(); j++){
          tab_A[i][j] += tab_B[i][j];
        }
      }
  }
 
  return M;
}
 
matrix operator*(const matrix& A, const matrix& B){
  if(A.get_n() != B.get_m()) throw("ERROR MULTIPLY");
 
  matrix ans(A.get_m(),B.get_n());
  int **tab_ans = ans.get_tab();
  int **tab_A = A.get_tab();
  int **tab_B = B.get_tab();
 
  #pragma omp parallel for
  for(int i = 0; i < A.get_m(); i++){
    for(int j = 0; j < A.get_n(); j++){
      for(int k = 0; k < B.get_n(); k++){
        tab_ans[i][k] += tab_A[i][j] * tab_B[j][k] % MOD;
        tab_ans[i][k] = tab_ans[i][k] % MOD;
      }
    }
  }
 
  return ans;
}
 
matrix operator^(const matrix& A, int p){
  if(A.get_m() != A.get_n()) throw("ERROR POWER");
 
  matrix W(A.get_m(), A.get_n());
  matrix B;
  B = A;
  W.set_id();
 
  while(p > 0){
    if(p & 1){
      W = W*B;
    }
    B = B*B;
    p >>= 1;
  }
  return W;
}
 
ostream& operator<<(ostream &stream, const matrix &A){
  A.print();
  return stream;
}
 
istream& operator>>(istream &stream, matrix &A){
  A.scan();
  return stream;
}
 
void matrix::clean(){
  delete tab_temp;
  delete tab;
}
 
matrix::~matrix(){
  delete tab_temp;
  delete tab;
}

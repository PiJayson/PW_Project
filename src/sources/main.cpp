#include<bits/stdc++.h>

#include "../headers/Matrix.h"

using namespace std;

long long timeCounter = 0;

class Solution {
    private:
        string command;

        Matrix A, B;

    public:
 
        friend istream& operator>>(istream &stream, Solution &S) {
            stream >> S.command;

            if      (S.command == "ADD") {
                // read two matrices
                stream >> S.A >> S.B;
                
                // Add two matricies
                auto start = std::chrono::high_resolution_clock::now();

                bool result = S.A + S.B;
                
                auto stop = std::chrono::high_resolution_clock::now();
                timeCounter += std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
                
                if (result) {
                    S.A.print_matrix();
                }
                else {
                    cout << "ERROR ADD" << "\n";
                }
            }
            else if (S.command == "MULTIPLY") {
                // read two matrices
                stream >> S.A >> S.B;

                // Multiply two matrices
                auto start = std::chrono::high_resolution_clock::now();

                bool result = S.A * S.B;

                auto stop = std::chrono::high_resolution_clock::now();
                timeCounter += std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
                
                if (result) {
                    S.A.print_matrix();
                }
                else {
                    cout << "ERROR MULTIPLY" << "\n";
                }

            }
            else if (S.command == "POWER") {
                // read power
                long long power;
                stream >> power;

                // read matrix
                stream >> S.A;

                // Power matrix
                auto start = std::chrono::high_resolution_clock::now();

                bool result = S.A ^ power;
                
                auto stop = std::chrono::high_resolution_clock::now();
                timeCounter += std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
                
                if (result) {
                    S.A.print_matrix();
                }
                else {
                    cout << "ERROR POWER" << "\n";
                }

            }
            else if (S.command == "DETERMINANT") {
                // read matrix
                stream >> S.A;

                // calculate determinant
                auto start = std::chrono::high_resolution_clock::now();

                long long result = S.A.determinant();
                
                auto stop = std::chrono::high_resolution_clock::now();
                timeCounter += std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
                
                cout << result << "\n";
            }
            else {
                std::cerr << "Command not found\n";
            }

            return stream;
        }
};
 
 
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    int n;
    cin >> n;
    while (n--) {
        Solution S;
        cin >> S;
    }

    std::cerr << "time spent on methods: " << timeCounter << "\n";
}
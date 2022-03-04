#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
class Point {
	public:
        double h, vx, vy,g;
        void setParametrs(double h, double vx, double vy, double g) {
            this->h = h;
            this->vx = vx;
            this->vy = vy;
            this->g = g;
        }
        double move(double x, double alpha) {
            return h + x * tan(alpha) - (x*x * g) / (2 * vx * vx);
        }
        //return h - pow(-1,n)*(x-recurs(X,n)) * tan(alpha) - ((x - recurs(X, n))*(x - recurs(X, n)) * g) / (2 * vx * vx);
        bool underFirst(vector<double>& x, vector < double > &y) {
            return (this->move(x[0], atan(vy / vx)) <= y[0]) ? true : false;
        }
        bool allIsAbove(vector<double>& x, vector < double >& y) {
            bool isAbove = false;
            for (int i = 0; i < x.size(); i++) {
                if (this->move(x[i], atan(vy / vx)) <= y[i]){
                    isAbove = false;
                    break;
                }
                else{
                    isAbove = true;
                }
            }
            return isAbove;
        }
        void nonTrivialMove(vector<double>& x, vector < double >& y) {
            bool right = true;
            int index = 0;
            int n = 0; // удары
            vector<double> XSaved;
            while (true) {
                if (n % 2 == 0) {
                    for (int i = index; i < x.size(); i++) {
                        right = true;
                        if (this->nthMove(x[i], XSaved, atan(vy / vx), n) < y[i]) {
                            n+=1;
                            XSaved.push_back(x[i]);
                            index = i;
                            break;
                        }
                    }
                }
                else {
                    for (int i = index-1; i >= 0; i--) {
                        right = false;
                        if (this->nthMove(x[i], XSaved, atan(vy / vx), n) < y[i]) {
                            n+=1;
                            XSaved.push_back(x[i]);
                            index = i;
                            break;
                        }
                    }
                }
                if (this->nthMove(x[index], XSaved, atan(vy / vx), n) < 0) {
                    
                    if (right) {
                        cout << index;
                    }
                    else {
                        cout << index + 1;
                    }
                    break;
                }
            }
            
        }
        double recurs(vector<double>& X, int n) {
            if (n == 0) {
                return 0;
            }
            else {
                return 2 * X[n-1] - recurs(X, n - 1);
            }
        }
        double nthMove(double x, vector<double> X, double alpha,int n) {
            return h + pow(-1, n) * (x - recurs(X, n)) * tan(alpha) - ((x - recurs(X, n)) * (x - recurs(X, n)) * g) / (2 * vx * vx);
        }
        
};

int main(int argc, char** argv) {
    if (argc == 2) {
        Point s1;
        double x, y;
        vector <double> x_b, y_b;
        ifstream file(argv[1]);
        double h, vx, vy, g = 9.81;

        if (file.is_open()) {
            file >> h >> vx >> vy;
            s1.setParametrs(h, vx, vy, g);
            while (file >> x >> y) {
                x_b.push_back(x);
                y_b.push_back(y);
            }
            if (x_b.empty()) {
                cout << 0;
                return 0;
            }
            
            /* Шар не долетел даже до первой */
            if (s1.allIsAbove(x_b, y_b)) {
                cout << x_b.size();

            }
            // Шар перелетел все барьеры 
            else if (s1.underFirst(x_b,y_b)) {
                cout << 0;
            }
            else {
                s1.nonTrivialMove(x_b, y_b);
            }

        }
        else {
            cout << "Error";
        }
        file.close();
    }
    else {
        cout << "Wrong arguments";
    }
    return 0;
    
}

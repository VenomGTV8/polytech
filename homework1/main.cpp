#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
class Points {
	public: 
		double maxRight[2] = { 0,0 }, maxLeft[2] = {0,0};
		double x, y;
		void setXY(double x0, double y0) {
			this->x = x0;
			this->y = y0;
		}
		bool isRight(double x0, double y0) {
			if (x0 > 0) return (y0 / x0 * x - y >= 0) ? true : false;
			else return(y - y0 / x0 * x > 0) ? true : false;
		}
		double distance(double x0, double y0){
			return (x0 == 0 && y0 != 0) ? fabs(x) : fabs(y0 / x0 * x - y) / sqrt(y0 * y0 / x0 / x0 + 1);
		}
		void setMaxPoints(double x0, double y0, bool isRight) {
			if (isRight) {
				this->maxRight[0] = x0;
				this->maxRight[1] = y0;
			}
			else {
				this->maxLeft[0] = x0;
				this->maxLeft[1] = y0;
			}
		}
};
int main()
{
	double x0, y0;
	Points point;
	double distance0, distanceR = 0, distanceL = 0;
	ifstream file("in.txt");
	if (!file.is_open()) {
		cout << "OpenError";
	}
	else {
		file >> x0 >> y0;
		double x, y;
		while (file >> x >> y) {
			point.setXY(x, y);
			distance0 = point.distance(x0,y0);
			if (point.isRight(x0,y0)) {
				if (distance0 >= distanceR) {
					distanceR = distance0;
					point.setMaxPoints(x, y, true);
				}
			}
			else {
				if (distance0 >= distanceL) {
					distanceL = distance0;
					point.setMaxPoints(x, y, false);
				}
			}
		}
		cout << "Leftmost: " << point.maxLeft[0] << " " << point.maxLeft[1] << endl;
		cout << "Rightmost: " << point.maxRight[0] << " " << point.maxRight[1] << endl;
	}
	
	return 0;
}

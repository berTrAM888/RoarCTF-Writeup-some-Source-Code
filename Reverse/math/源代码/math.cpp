#include<iostream>
#include<cmath>
#include<cstdio>
#include<random>
#include<iostream>

using namespace std;
const double pi = 3.1415926535897932384626;

typedef struct node {
	double x, y;
}NODE;

inline NODE Vector(NODE A, NODE B) {
	return{ B.x - A.x, B.y - A.y };
}

inline double dis2(NODE a, NODE b) {
	return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

double cross(NODE A, NODE B, NODE P) {
	NODE AB = Vector(A, B);
	NODE AP = Vector(A, P);
	return AB.x * AP.y - AB.y * AP.x;
}

double disLine(NODE A, NODE B, NODE P) {
	return fabs(cross(A, B, P)) / sqrt(dis2(A, B));
}




int main(int argc, char** argv) {

	double R = sqrt(5) - 1;
	//std::cout<< ((3 - sqrt(5)) / 2)/(sqrt(5) - 1) * ((3 - sqrt(5)) / 2) / (sqrt(5) - 1) <<std::endl;
	double rate = 0.0954915;
	std::cout << "You should input sth." << std::endl;
	NODE A;
	double length;
	double angle = 45;
	//角度为45，输出长度须为sqrt(2)，A即是所有点相对原点偏移
	std::cin >> length;

	A.x = length * cos(angle * pi / 180); //1
	A.y = length * sin(angle * pi / 180); //1

	if (fabs(A.x * A.x + A.y * A.y - 2) > 0.00001) {
		//相对原点的偏移，线段长度为99
		//上面角度随便输一个就行了
		std::cout << "You failed!" << std::endl;
		exit(2);
	}

	NODE M;
	M.x = A.x + sqrt(10 + 2 * sqrt(5));
	M.y = A.y + 0;

	NODE O;				//圆心
	O.x = M.x;
	O.y = M.y + sqrt(5) - 1;

	NODE N;
	double N_len;
	double N_angle;
	//std::cout << "N:";
	std::cin >> N_len;  //5.2057298
	//std::cout << "N:";
	std::cin >> N_angle;   //0.67083
	N.x = N_len * cos(N_angle);
	N.y = N_len * sin(N_angle);
	//std::cout << N.x << endl << N.y << endl;

	//std::cin >> N.x;  //N.x = A.x(1) + sqrt(5 + 2 * sqrt(5));   x == 4.07768
	//std::cin >> N.y;  //N.y = A.y(1) + sqrt(5);				  y == 3.23607
	//转换为极坐标 tan == y/x == 3.23607 / 4.07768 == 0.793606     弧度==0.67083
	//			  ρ == sqrt(27.0996232273) == 5.2057298		      长度==5.2057298

	//4.07768 3.23607 输入后有较大可能性通过概率检测

	//圆心到弦MN的距离
	double d = disLine(M, N, O);

	//计算概率
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<>dis(-R, R);
	int cnt1 = 0;
	int cnt2 = 0;
	for (int i = 0; i < 10000000; i++) {
		double x = dis(gen);
		double y = dis(gen);
		if ((x) * (x)+(y) * (y) <= d * d) {
			//在小圆里
			cnt1++;
		}
	}
	for (int i = 0; i < 10000000; i++) {
		double x = dis(gen);
		double y = dis(gen);
		if ((x) * (x)+(y) * (y) <= R * R) {
			//在大圆里
			cnt2++;
		}
	}
	double calc_rate = cnt1 * 1.0 / cnt2;
	//std::cout << "calc_rate: " << calc_rate << std::endl << "rate :" << rate << std::endl;
	//输入的点N需要在圆上，也就是直线AN与圆相切
	if ((disLine(A, N, O) - R > 0.0001)
		|| (disLine(A, N, O) - R < -0.0001)) {
		exit(0);
	}

	//计算出来的概率要求在一个小范围里
	if ((calc_rate - rate) > 0.0001
		|| (calc_rate - rate) < -0.0001) {
		exit(1);
	}

	system("cat ./flag");
	return 0;
	/*
	最终输入：
	1.41421356
	5.2057298
	0.67083
	*/
}
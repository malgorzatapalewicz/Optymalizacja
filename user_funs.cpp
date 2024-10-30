#include"user_funs.h"

matrix ff0T(matrix x, matrix ud1, matrix ud2){ //funkcja testowa
	matrix y;
	y = pow(x(0) - ud1(0), 2) + pow(x(1) - ud1(1), 2);
	return y;
}

matrix ff0R(matrix x, matrix ud1, matrix ud2){ //funkcja problemu rzeczywistego , funckja celu
	matrix y;
	matrix Y0 = matrix(2, 1), MT = matrix(2, new double[2]{ m2d(x),0.5 }); //Y0 - poczatkowy uklad wahadla
    // MT - moment sily i czas
	matrix* Y = solve_ode(df0, 0, 0.1, 10, Y0, ud1, MT); //dwuleementoea tablica ktora zawiera dwia macierze, pierwsza z czasem
    // a druga tablica zawiera dwie kolumny cztli y1 i y2, polozenie i jego predkosc
	int n = get_len(Y[0]);
	double teta_max = Y[1](0, 0); //maksymalne wychylenie
	for (int i = 1; i < n; ++i)
		if (teta_max < Y[1](i, 0))
			teta_max = Y[1](i, 0);
	y = abs(teta_max - m2d(ud1));
	Y[0].~matrix();
	Y[1].~matrix();
	return y;
}

matrix df0(double t, matrix Y, matrix ud1, matrix ud2){
	matrix dY(2, 1); //dwuwymiarowy
	double m = 1, l = 0.5, b = 0.5, g = 9.81; //masa
	double I = m*pow(l, 2); //dlugosc?
	dY(0) = Y(1); //pochodna z y1
	dY(1) = ((t <= ud2(1))*ud2(0) - m*g*l*sin(Y(0)) - b*Y(1)) / I; //(moment sily - czas dzialania sily) / moment bezwladnosci
	return dY;
}



matrix ff1T(matrix x, matrix ud1, matrix ud2){
    matrix y;
    y = pow(x, 2); //x^2
    return y;
}

matrix ff2T(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    int newX = m2d(x);
     y = -cos(0.1 * newX) * exp(-pow(0.1 * newX - 2 * M_PI, 2)) + 0.002 * pow(0.1 * x, 2);

    return y;
}

matrix ff3T(matrix x, matrix ud1, matrix ud2) {
    matrix y(1, 1);
    y(0, 0) = pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * M_PI * x(0)) - cos(2.5 * M_PI * x(1)) + 2;
    return y;
}

std::string replaceDotWithComma(double value) {
    std::ostringstream oss;
    oss << value;
    std::string strValue = oss.str();
    std::replace(strValue.begin(), strValue.end(), '.', ',');
    return strValue;
}

bool ifGlobal(double y){
    return (y < 0.1);
}








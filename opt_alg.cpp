#include"opt_alg.h"

solution MC(matrix(*ff)(matrix, matrix, matrix), int N, matrix lb, matrix ub, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		while (true)
		{
			Xopt = rand_mat(N);
			for (int i = 0; i < N; ++i)
				Xopt.x(i) = (ub(i) - lb(i)) * Xopt.x(i) + lb(i);
			Xopt.fit_fun(ff, ud1, ud2);
			if (Xopt.y < epsilon)
			{
				Xopt.flag = 1;
				break;
			}
			if (solution::f_calls > Nmax)
			{
				Xopt.flag = 0;
				break;
			}
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution MC(...):\n" + ex_info);
	}
}

double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
	try{
		double* p = new double[2]{ 0,0 };

        solution X0(x0), X1(x0+d); //konstruktor
        X0.fit_fun(ff, ud1, ud2); //policzylismy wartosc y w punkcie celu
        X1.fit_fun(ff, ud1, ud2); //zeby porownanc z X1 musimy zrobic to samo

        if(X0.y == X1.y){
            p[0] = m2d(X0.x);
            p[1] = m2d(X1.x);
            return p;
        }

        if (X1.y > X0.y){
            d = -d;
            X1.x = X0.x + d;
            X1.fit_fun(ff, ud1, ud2); //liczymy y

            if(X1.y >= X0.y) {
                p[0] = m2d(X1.x);
                p[1] = m2d(X0.x - d);
                return p;
            }
        }

        int i = 0;
        solution Xi;
        while(true) {

            Xi.x = x0 + pow(alpha, i) * d; //wzor na x(i+1)
            Xi.fit_fun(ff, ud1, ud2);

            if (solution::f_calls > Nmax)
                return nullptr;

            if (X0.y <= Xi.y) break;
            X0.x = X1.x;
            X0.fit_fun(ff, ud1, ud2);
            X1.x = Xi.x;
            i++;
        }

        if(X0.x < Xi.x){
            p[0] = m2d(X0.x);
            p[1] = m2d(Xi.x);
        } else {
            p[0] = m2d(Xi.x);
            p[1] = m2d(X0.x);
        }

        return p;

	} catch (string ex_info) {
		throw ("double* expansion(...):\n" + ex_info);
	}
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
        int n =2  ; //(b-a)/epsilon +1
        int Fib = 0;

        while (true) {
            Fib = (1 / sqrt(5)) * (pow(((1 + sqrt(5)) / 2), n) - pow(((1 - sqrt(5)) / 2), n));
            if (Fib > (b - a) / epsilon)
                break;
            else
                n++;
        }

        int *F = new int[n] {1, 1};
        for (int i = 2; i < n; ++i)
            F[i] = F[i - 2] + F[i - 1];


        solution A(a), B(b), C, D;
        double B0 = (double)((F[(n - 2)]) / (double)(F[(n - 1)]));

        C.x = A.x(0) - B0 * (B.x(0) - A.x(0));
        D.x = A.x(0) + B.x(0) - C.x(0);

        C.y = ff(C.x, ud1, ud2);
        D.y = ff(D.x, ud1, ud2);

        for (int i = 0; i <= n - 3; ++i){
            cout << "Fib iteracja i: " << i << "  b-a= " << B.x(0) - A.x(0) << endl;
            if (C.y(0) < D.y(0)){
                B.x = D.x(0);
            }
            else {
                A.x = C.x(0);
            }
            B0 = (double)((F[n - i - 2]) / (double)(F[n - i - 1]));
            C.x = B.x(0) - B0 * (B.x(0) - A.x(0));
            D.x = A.x(0) + B.x(0) - C.x(0);

            C.y = ff(C.x, ud1, ud2);
            D.y = ff(D.x, ud1, ud2);
        }

        Xopt = C;
        delete[] F;
        return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}

}

solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution lag(...):\n" + ex_info);
	}
}

solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution XB, X, Xopt;
        XB.x = x0;
        XB.y = ff(XB.x, ud1, ud2);
        Xopt = XB;
        cout << "x1: " << XB.x(0) << ", x2: " << XB.x(1) << ", y: " << XB.y << endl;

        while(true){
            solution::f_calls++;
            X = HJ_trial(ff, XB, s, ud1, ud2);

            if(X.y < XB.y){
                XB = X;

                if (XB.y < Xopt.y){
                    Xopt = XB;
                }

                X = HJ_trial(ff, XB, s, ud1, ud2);

                if (X.y >= XB.y)
                    break;

                if (solution::f_calls > Nmax) {
                    Xopt.flag = 0;
                    return Xopt;
                }
            } else {
                s *= alpha; //zmniejszenie kroku
            }

            if (Xopt.y < epsilon){
                Xopt.flag = 1;
                break;
            }
            if (solution::f_calls > Nmax){
                Xopt.flag = 0;
                break;
            }
        }
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	try {
        int *n = get_size(XB.x);
        matrix D = ident_mat(n[0]); //macierz n x n
        solution Xopt;

        for (int i = 0; i < n[0]; ++i) {

            Xopt.x = XB.x + s * D[i];
            Xopt.y = ff(Xopt.x, ud1, ud2);
            if (Xopt.y < XB.y) {
                XB = Xopt;
                continue;
            }

            Xopt.x = XB.x - s * D[i];
            Xopt.y = ff(Xopt.x, ud1, ud2);
            if (Xopt.y < XB.y) {
                XB = Xopt;
            }
        }

		return XB;
	}
	catch (string ex_info)
	{
		throw ("solution HJ_trial(...):\n" + ex_info);
	}
}

solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Rosen(...):\n" + ex_info);
	}
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution pen(...):\n" + ex_info);
	}
}

solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution sym_NM(...):\n" + ex_info);
	}
}

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution SD(...):\n" + ex_info);
	}
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution CG(...):\n" + ex_info);
	}
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
	matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution golden(...):\n" + ex_info);
	}
}

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Powell(...):\n" + ex_info);
	}
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix lb, matrix ub, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution EA(...):\n" + ex_info);
	}
}

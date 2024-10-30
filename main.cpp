/*********************************************
Kod stanowi uzupelnienie materialow do cwiczen
w ramach przedmiotu metody optymalizacji.
Kod udost�pniony na licencji CC BY-SA 3.0
Autor: dr inz. Lukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Gorniczo-Hutnicza
Data ostatniej modyfikacji: 19.09.2023
*********************************************/

#include"opt_alg.h"

void lab0();
void lab1();
void lab2();
void lab3();
void lab4();
void lab5();
void lab6();

int main()
{
	try
	{
		lab2();
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl << endl;
	}
	//system("pause");
	return 0;
}

void lab0(){

	//Funkcja testowa
	double epsilon = 1e-2; //tolerancja błedu
	int Nmax = 10000; //maksymalna liczba iteracji
	matrix lb(2, 1, -5), ub(2, 1, 5), a(2, 1);
	solution opt;
	a(0) = -1;
	a(1) = 2;
	opt = MC(ff0T, 2, lb, ub, epsilon, Nmax, a); //funkcja celu, jej nazwa jest jednoczenise jej adresem, wymiar, ...,
    // epsioln - pierwsze kryterium zatrzymania, Nmax - drugie kryteruym  zatrzymania, a - wposlczynnnik co podaj uzytkownik
	cout << opt << endl << endl;
	solution::clear_calls();

	//Wahadlo
	Nmax = 1000;
	epsilon = 1e-2;
	lb = 0; //lower bound
	ub = 5; //upper bound
	double teta_opt = 1; //1 radian = okolo 57 stopni
	opt = MC(ff0R, 1, lb, ub, epsilon, Nmax, teta_opt);
	cout << opt << endl << endl;
	solution::clear_calls();

	//Zapis symulacji do pliku csv
	matrix Y0 = matrix(2, 1), MT = matrix(2, new double[2]{ m2d(opt.x),0.5 });
	matrix* Y = solve_ode(df0, 0, 0.1, 10, Y0, NAN, MT);
	ofstream Sout("symulacja_lab0.csv");
	Sout << hcat(Y[0], Y[1]);
	Sout.close();
	Y[0].~matrix();
	Y[1].~matrix();
}

void lab1(){

  //  double x0 = -1, d = 2, alfa = 2;
    //double x0 = 1, d = 2, alfa = 2;
    double x0 = 67, d = 1, alfa = 2;
    int Nmax = 10000;

    double *p = expansion(ff2T, x0, d, alfa,Nmax);
    cout << p[0]<< '\t' << p[1] << endl;
    solution::clear_calls();




    //definicja funkcji kwadratowych
    //funckja celu musi miec 3 (x, useerdata,userdata), zwraca y,

    //pierwszy argument to wskaznik do funkcji ff1T y = x^2
    //chcemy policzyc



    //generujemy x0,x1 i wartosci porownac, jelsi sa rowne konczymy
    //obiekt klasy solution sklada sie z x i y,


    //metoda 3 - metda expansive ktora potrafi znalesc przedzial poczatkowy bo te wczenisjesze zawezaja
    // jak dziala?
    // zaczyanmy od punktu x0, sprawdzamy ajka jest relacja miedzy tymi dwoma punktamji

    // albo jednwj jest mniejsze, rowne , wieksze
    // na ss jest opcja pierwsze ze mniejsze
    // dziemy w prawa strone i sprawdzamy , jak jest lepiej to dalej idziemy w prawa strone i tak az do momentu gdzie jest gorzej
    //jesli jest f(x (i+1)) > lub rowny f(x(i))
    // i wtedy wiemy ze jest przedzial od x(i-1)


    // ogolny wzor na x(i+1):
    // alfa - wspolczynik ekspansji, liczba do potegi i tej , czyli numery ityeracji
    // d - pierwsza odleglosc miedzy x0 i x1
    //

    // drugi przypadek kiedy  f(x0) = f(x1)
    //zwracamny po prostu ten przedzial i nic nie liczymy

    //ostratni przypadek, kiedy wartosc funkcji jet wieksza f(x1) > f(
    // wtedy wiemy ze minimum jest po lewej stronue
    // bierzemy d i dajemy d = -d
    // wtedy sprawdzamy jeszcze raz ta relacje f(x0)
    // generujemy x2 analogiczni ejak wczensiej
    // i tak do moemntu az bedzie gorzej


    //metoda 3 - metda expansive ktora potrafi znalesc przedzial poczatkowy bo te wczenisjesze zawezaja
    // jak dziala?
    // zaczyanmy od punktu x0, sprawdzamy ajka jest relacja miedzy tymi dwoma punktamji

    // albo jednwj jest mniejsze, rowne , wieksze
    // na ss jest opcja pierwsze ze mniejsze
    // dziemy w prawa strone i sprawdzamy , jak jest lepiej to dalej idziemy w prawa strone i tak az do momentu gdzie jest gorzej
    //jesli jest f(x (i+1)) > lub rowny f(x(i))
    // i wtedy wiemy ze jest przedzial od x(i-1)


    // ogolny wzor na x(i+1)
    // alfa - wspolczynik ekspansji, liczba do potegi i tej , czyli numery ityeracji
    // d - pierwsza odleglosc miedzy x0 i x1
    //

    // drugi przypadek kiedy  f(x0) = f(x1)
    //zwracamny po prostu ten przedzial i nic nie liczymy

    //ostratni przypadek, kiedy wartosc funkcji jet wieksza f(x1) > f(
    // wtedy wiemy ze minimum jest po lewej stronue
    // bierzemy d i dajemy d = -d
    // wtedy sprawdzamy jeszcze raz ta relacje f(x0)
    // generujemy x2 analogiczni ejak wczensiej
    // i tak do moemntu az bedzie gorzej













    //metoda Fibocianego  epsilon > 0
   // musimy wyznaczyc jakies fi k ktore bedzie mialo wieksza wartosc niz b -a / 2
  //wiekszy niz iloraz

  //przyklad
  //a = 0 , b = 1, epsilon = 0.01
  // musimy znasc fi > 100
  // 1 2 3 4 5 6 7 ... 11 12
  // 1 1 2 3 5 8 13 ... 89 144
  // dwunasty bwyraz jest wiekszy niz ten irloaz , czyli k = 12

  //z gory wiemuy ile razy ma sioe wykonac iteracja, bedziemy zawezac przedzial
  // jak znalesc punkty c i d
  // bierzemy punkty a i b , i wyznaczamy srodkowe punnktuy , bierzemyv puknt b minus

  // wspolredne pierwszego punktuy

  //po wygenerowaniu punktow a i b
  // f(c) > f(a)
  // punkt c blizej punktu a i d b;izej punktu b
  // punkt c to punkt optymalzny tak zakladamy przy zwracaniu
  // w ostatniej iteracji c jest taki sam jak d (nie punkt celu)



  //druga metoda - oprarta o interpolacje lagranga
  // wyznaczamy parabole ktora przechodzi przez 3 punkty
  // i on a ma swoje minimum w punkcie d funckji kwadratowej
  // c/d zawsze musui byc w srodku
  // d wyznaczamy
  // i znowu robimy zawezenie
  // musiny wziac pod uwage 3 inne rzeczy
  // moze sie zdazrzyc ze funkcja ma maxkismum a nie minimim to wtedy wyrzucamhy blad , brak zbierznosci
  // moze sie pojawic sytaucja ze minimum funkcji jest poza obszarem [a,b], jesli puknt d lezy poza obszare to wyrzycay blad
  //m
  // punkt c to srodke przedzialuy, jelsi uzyskamy bminejszy niz epsilon to koncymy mamy wynik
  // gamma soprawdza jaka jest dodleglosc miedzy dwoma iteracjami punkty d, jesli w dwoch iteracji jest taki sam to konczymy oblcizenia
  // nie wiemy ile jest iteracji
  // sprawdzamy czy funkcja ma maksimum jesli mianownik jest ujemny, to funkcja bedzie miala maksimum i zwracamy blad
  // tak samo mianownik nie moze sie zerowac, czyli przypadek funkcji liniowych i tez blad
  //piotr kusiak przy tym jest BLAD, wiec bierz z konspektu

  //mamy juz punkt d ,
  // punknt c zawsze po lewej a d po prawjke  przy fibbocianego, tutaj mamy 4 warunki bo nie wiadomo jak leza punkty
  //sprawdzamyn gdzie znajdyje sie punkt d
  // eroer wystapi jesli d bedzie poza przedzialem [a,b] - linijka 32 w pseudokodzie
}

void lab2(){

    double epsilon = 1e-3;
    int Nmax = 10000; //maksymalna liczba iteracji
    double alpha = 0.5;
    double x1, x2;

//    x1 = -1 + m2d(rand_mat(1, 1)) * 2;
//    x2 = -1 + m2d(rand_mat(1, 1)) * 2;
//
//    matrix x0(2, 1); //macierz 2x1 w przedziale [-1, 1]
//    x0(0, 0) = x1;
//    x0(1, 0) = x2;


  //  solution opt = HJ(ff3T, x0, 0.01, alpha, epsilon, Nmax);
//    cout << "Optymalne x: (" << opt.x(0) << ", " << opt.x(1) << ")"<< endl;
//    cout << "Wartość funkcji celu: " << opt.y << endl;

    std::ofstream file("wyniki_optymalizacji.csv");
    file << "x1(0);x2(0);x1*;x2*;y;Liczba wywołań;Czy Globalne\n";

    for(int i = 0; i < 100; i++){
        x1 = -1 + m2d(rand_mat(1, 1)) * 2;
        x2 = -1 + m2d(rand_mat(1, 1)) * 2;

        matrix x0(2, 1); //macierz 2x1 w przedziale [-1, 1]
        x0(0, 0) = x1;
        x0(1, 0) = x2;
        solution opt = HJ(ff3T, x0, 0.001, alpha, epsilon, Nmax);

        file << replaceDotWithComma(x1) << ";"
             << replaceDotWithComma(x2) << ";"
             << replaceDotWithComma(opt.x(0) ) << ";"
             << replaceDotWithComma(opt.x(1)) << ";"
             << replaceDotWithComma(m2d(opt.y)) << ";"
             << solution::f_calls << ";"
             << (ifGlobal(m2d(opt.y)) ? "TAK" : "NIE") << "\n";

        solution::clear_calls();
    }

    file.close();

}


void lab3()
{

}

void lab4()
{

}

void lab5()
{

}

void lab6()
{

}

//szukamy minimum + dla rzeczywisyefo obiektu (opisanego rownaniem rozniczkowym)
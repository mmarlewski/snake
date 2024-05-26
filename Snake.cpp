
#include <iostream>

#include <cstdlib>

#include <conio.h>

#include <string>

#include <fstream>

#include <windows.h>

#include <time.h>

using namespace std;



bool czyMapa = 0;   //czy zaladowano mape

string jakMapa;   //nazwa mapy

int z; char x;     //( w menu i opcjach ) nr wybranej opcji i znak z klawiatury



int Yg, Xg;        //polozenie glowy weza na mapie

int Ys, Xs;        //polozenie szyji weza na mapie

int Yo, Xo;        //polozenie ogona weza na mapie

int Ym, Xm;        //polozenie mety na mapie ( zamieniona w sciane...

//...jesli 'czyDlug' jest ustawiona na false )

int Yx, Xx;        //polozenie obrabianej czesci weza na mapie ( linijka 448 )

int Ynk, Xnk;      //polozenie nowo powstalego zwyklego klocka na mapie

int Yns, Xns;      //polozenie nowo powstalego klocka specjalnego na mapie



int ilePuste;     //ile jest na mapie pustych pol

int ileZwieksz;   //( po zjedzeniu klocka ) o ile zwiekszyc weza

int ileSzyb;      //aktualna szybkosc weza ( moze sie zmienic )

bool czyZnak;     //czy uzytkownik wprowadzil znak

char jakZnak;     //jaki znak wprowadzil uzytkownik

bool czyNKloc;    //czy jest na mapie zwykly klocek

bool czyNSpec;    //czy jest na mapie klocek specjalny

bool czyKoniec;   //czy zakonczyc gre

int jakKoniec;    //w jaki sposob zakonczono gre

bool czyPrzy;     //czy dziala przyspieszenie

bool czySpow;     //czy dziala spowolnienie



time_t czasSzyb;  //od kiedy mierzyc czas na wykonanie ruchu

time_t czasCzas;  //od kiedy mierzyc ogolny czas w grze

time_t czasPrzy;  //od kiedy mierzyc czas dzialania przyspieszenia

time_t czasSpow;  //od kiedy mierzyc czas dzialania spowolnienia

time_t czasSpec;  //od kiedy mierzyc czas wystepowania klocka spec. na mapie



int ileDlug;      //aktualna dlugosc weza

int ileCzas;      //aktualny czas gry

int ileZyc;       //aktualna ilosc posiadanych zyc

int ile1;         //ilosc zjedzonych klockow po 1

int ile2;         //ilosc zjedzonych klockow po 2

int ile3;         //ilosc zjedzonych klockow po 3

int ile4;         //ilosc zjedzonych klockow po 4

int ile5;         //ilosc zjedzonych klockow po 5

int ileSpec;      //ilosc zjedzonych klockow specjalnych



int jakSzyb = 6; //domyslna szybkosc

int jakZycia = 1; //ilosc zyc na poczatek

bool czyTelep = 0; //czy po przekroczeniu mapy waz ma...

//...przeleportowac sie na drugi koniec mapy

bool czyZjesc = 0; //czy waz po napotkaniu z wlasnym cialem ma je zjesc

bool czyKloc = 0; //czy w grze maja wystepowac klocki po 2,3,4 i 5

bool czySpec = 0; //czy w grze maja wystepowac klocki specjalne

bool czyCzas = 0; //czy gra ma byc "na czas"

double jakCzas = 30.0; //po jakim czasie gra sie skonczy

bool czyDlug = 0; //czy gre mozna przejsc po osiagnieciu jakiejs dlugosci

int jakDlug; //po osiagnieciu jakiej dlugosci pojawi sie meta



int mapa[30][50]; //mapa ( !!! UWAGA UKLAD [Y][X] A NIE [X][Y] !!! )



void menu();      //menu

void pobierz();   //pobiera mape z "mapa.txt"

void gra();       //gra ( po zakonczonej grze wraca do menu )

void ruch();      //ruch glowa i reagowanie na to co napotka waz

void pokaz();     //pokazuje mape i interface

void ogon();      //usuwanie i przesuwanie ogona

void koniec();    //zakonczenie gry oraz pokazanie wyniku i statystyk



void koniec()

{

    czyKoniec = 1; czyMapa = 0;



    system("cls");



    cout << "----------" << (char)254 << (char)187; for (int i = 0; i < 20; i++)cout << "-"; cout << endl;

    cout << "          " << (char)201 << (char)188 << " N A K E          " << endl;

    cout << "----------" << (char)200; for (int i = 0; i < 21; i++)cout << (char)205; cout << endl << endl;



    //pokazuje przyczyne zakonczenia gry

    switch (jakKoniec)

    {

    case 1:cout << " Przegrales!" << endl << endl; break;

    case 2:cout << " Koniec czasu!" << endl << endl; break;

    case 3:cout << " Wygrales!" << endl << endl; break;

    case 4:cout << " Poddales sie!" << endl << endl; break;

    }



    cout << "--------------------------------" << endl;



    cout << " DLUGOSC:   " << ileDlug;

    if (czyDlug)cout << " / " << jakDlug; cout << endl;

    cout << " CZAS:      " << ileCzas;

    if (czyCzas)cout << " / " << jakCzas; cout << endl << endl;



    cout << " Pozostalo zyc: " << ileZyc << endl;

    cout << " Klocki po 1:   " << ile1 << endl;

    cout << " Klocki po 2:   " << ile2 << endl;

    cout << " Klocki po 3:   " << ile3 << endl;

    cout << " Klocki po 4:   " << ile4 << endl;

    cout << " Klocki po 5:   " << ile5 << endl;

    cout << " Klocki spec.:  " << ileSpec << endl << endl;



    cout << " Szybkosc weza:      " << -(jakSzyb - 11) << endl;

    cout << " Ilosc zyc weza:     " << jakZycia << endl;



    cout << " Teleportowanie sie: ";

    if (czyTelep)cout << "TAK"; else cout << "NIE"; cout << endl;



    cout << " Zjadanie ogona:     ";

    if (czyZjesc)cout << "TAK"; else cout << "NIE"; cout << endl;



    cout << " Klocki po kilka p.: ";

    if (czyKloc)cout << "TAK"; else cout << "NIE"; cout << endl;



    cout << " Klocki specjalne:   ";

    if (czySpec)cout << "TAK"; else cout << "NIE"; cout << endl;



    cout << "--------------------------------" << endl;

    cout << " [E]wroc do menu" << endl;



    while (_getch() != 'e') {}

}



void ogon()

{

    //w zaleznosci od ogona weza "usuwa" ogon i "przesuwa" go dalej

    switch (mapa[Yo][Xo])

    {

    case 13:case 15:case 17:

        mapa[Yo][Xo] = 0; if (Yo == 0)Yo = 29; else Yo--; break;

    case 14:case 19:case 21:

        mapa[Yo][Xo] = 0; if (Yo == 29)Yo = 0; else Yo++; break;

    case 11:case 18:case 22:

        mapa[Yo][Xo] = 0; if (Xo == 0)Xo = 49; else Xo--; break;

    case 12:case 16:case 20:

        mapa[Yo][Xo] = 0; if (Xo == 49)Xo = 0; else Xo++; break;

    }

}



void pokaz()

{

    system("cls");



    //tymczasowa zmienna do wyswietlania znaku symbolizujacego przedmiot na mapie

    char tymZnak;



    for (int i = 0; i < 52; i++)cout << (char)176; cout << " Zycia:";

    for (int j = 0; j < ileZyc; j++)cout << " " << (char)254; cout << endl;



    //pokazuje mape

    for (int i = 0; i < 30; i++)

    {

        cout << (char)176;



        for (int j = 0; j < 50; j++)

        {

            //w zaleznosci od przedmiotu na mapie wyswietla inny symbol

            switch (mapa[i][j])

            {

            case 0:tymZnak = ' '; break;

            case 1:tymZnak = '1'; break;

            case 2:tymZnak = '2'; break;

            case 3:tymZnak = '3'; break;

            case 4:tymZnak = '4'; break;

            case 5:tymZnak = '5'; break;

            case 6:tymZnak = 219; break;

            case 7:tymZnak = '#'; break;

            case 8:tymZnak = '@'; break;



            case 10:tymZnak = 254; break;

            case 11:case 12:tymZnak = 205; break;

            case 13:case 14:tymZnak = 186; break;

            case 15:case 16:tymZnak = 200; break;

            case 17:case 18:tymZnak = 188; break;

            case 19:case 20:tymZnak = 201; break;

            case 21:case 22:tymZnak = 187; break;



            case 30:tymZnak = '>'; break;

            case 31:tymZnak = '<'; break;

            case 32:tymZnak = 'X'; break;

            case 33:tymZnak = '-'; break;

            case 34:tymZnak = '+'; break;

            case 35:tymZnak = '='; break;

            }



            cout << tymZnak;

        }



        cout << (char)176 << " ";



        //w zaleznosci od linijki wyswietla informacje obok mapy

        switch (i)

        {

        case 1:cout << "Dlugosc:   " << ileDlug; if (czyDlug)cout << " / " << jakDlug; break;

        case 2:cout << "Czas:      " << ileCzas; if (czyCzas)cout << " / " << jakCzas; break;



        case 4:cout << "Przysp:    "; if (!czyPrzy)cout << "------";

              else cout << double(clock() - czasPrzy) / CLOCKS_PER_SEC; break;



        case 5:cout << "Spowol:    "; if (!czySpow)cout << "------";

              else cout << double(clock() - czasSpow) / CLOCKS_PER_SEC; break;



        case 7:cout << "[W,S,A,D] sterowanie"; break;

        case 8:cout << "[Q] poddanie sie"; break;

        case 9:cout << "[E] pauza"; break;



        case 11:cout << "' ' - pusta przestrzen"; break;

        case 12:cout << "'" << (char)219 << "' - sciana"; break;

        case 13:cout << "'#' - zamknieta meta"; break;

        case 14:cout << "'@' - otwarta meta"; break;



        case 16:cout << "'>' - przyspieszenie"; break;

        case 17:cout << "'<' - spowolnienie"; break;

        case 18:cout << "'X' - skrocenie o 5"; break;

        case 19:cout << "'-' - odjecie zycia"; break;

        case 20:cout << "'+' - dodanie zycia"; break;

        case 21:cout << "'=' - odwrocenie weza"; break;



        case 23:cout << "'1' - zwykly klocek za 1"; break;

        case 24:cout << "'2' - zwykly klocek za 2"; break;

        case 25:cout << "'3' - zwykly klocek za 3"; break;

        case 26:cout << "'4' - zwykly klocek za 4"; break;

        case 27:cout << "'5' - zwykly klocek za 5"; break;



        default:break;

        }



        cout << endl;

    }



    for (int i = 0; i < 52; i++)cout << (char)176; cout << endl;

}



void ruch()

{

    //w zaleznosci od 'jakZnak' i szyji wykonuje lub nie ruch w jakas strone

    switch (jakZnak)

    {

    case 'w':



        //jesli waz napotka (sciane lub zamknieta mete) lub

        //(czesc ciala podczas gdy nie moze ich jesc) lub

        //(koniec mapy podczas gdy nie moze sie teleportowac)

        if

            (

                (mapa[Yg - 1][Xg] == 6 || mapa[Yg - 1][Xg] == 7) ||

                (

                    (Yg - 1 == Yo && Xg == Xo) ? (0) : (!czyZjesc) &&

                    (

                        mapa[Yg - 1][Xg] == 11 || mapa[Yg - 1][Xg] == 12 || mapa[Yg - 1][Xg] == 13 ||

                        mapa[Yg - 1][Xg] == 14 || mapa[Yg - 1][Xg] == 15 || mapa[Yg - 1][Xg] == 16 ||

                        mapa[Yg - 1][Xg] == 17 || mapa[Yg - 1][Xg] == 18 || mapa[Yg - 1][Xg] == 19 ||

                        mapa[Yg - 1][Xg] == 20 || mapa[Yg - 1][Xg] == 21 || mapa[Yg - 1][Xg] == 22

                        )



                    ) ||

                (Yg == 0 && !czyTelep)



                )ileZyc--;

        else

        {

            //jesli waz ma sie wydluzyc : nie skraca ogona

            if (ileZwieksz > 0)

            {

                ileZwieksz--;

                ileDlug++;

            }

            else ogon();



            //tworzy nowa czesc ciala weza

            switch (mapa[Ys][Xs])

            {

            case 13:case 15:case 17:

                czasSzyb -= CLOCKS_PER_SEC; mapa[Yg][Xg] = 13; break;

            case 11:case 18:case 22:mapa[Yg][Xg] = 15; break;

            case 12:case 16:case 20:mapa[Yg][Xg] = 17; break;

            default:break;

            }



            //"przesuniecie" szyji i glowy

            Ys = Yg; Xs = Xg; if (Yg == 0)Yg = 29; else Yg--;

        }



        break;

    case 's':



        if ((mapa[Yg + 1][Xg] == 6 || mapa[Yg + 1][Xg] == 7) ||

            ((Yg + 1 == Yo && Xg == Xo) ? (0) : (!czyZjesc) &&

                (mapa[Yg + 1][Xg] == 11 || mapa[Yg + 1][Xg] == 12 || mapa[Yg + 1][Xg] == 13 ||

                    mapa[Yg + 1][Xg] == 14 || mapa[Yg + 1][Xg] == 15 || mapa[Yg + 1][Xg] == 16 ||

                    mapa[Yg + 1][Xg] == 17 || mapa[Yg + 1][Xg] == 18 || mapa[Yg + 1][Xg] == 19 ||

                    mapa[Yg + 1][Xg] == 20 || mapa[Yg + 1][Xg] == 21 || mapa[Yg + 1][Xg] == 22)) ||

            (Yg == 29 && !czyTelep))ileZyc--;

        else

        {

            if (ileZwieksz > 0)

            {

                ileZwieksz--;

                ileDlug++;

            }

            else ogon();



            switch (mapa[Ys][Xs])

            {

            case 14:case 19:case 21:

                czasSzyb -= CLOCKS_PER_SEC; mapa[Yg][Xg] = 14; break;

            case 11:case 18:case 22:mapa[Yg][Xg] = 19; break;

            case 12:case 16:case 20:mapa[Yg][Xg] = 21; break;

            default:break;

            }



            Ys = Yg; Xs = Xg; if (Yg == 29)Yg = 0; else Yg++;

        }



        break;

    case 'a':



        if ((mapa[Yg][Xg - 1] == 6 || mapa[Yg][Xg - 1] == 7) ||

            ((Yg == Yo && Xg - 1 == Xo) ? (0) : (!czyZjesc) &&

                (mapa[Yg][Xg - 1] == 11 || mapa[Yg][Xg - 1] == 12 || mapa[Yg][Xg - 1] == 13 ||

                    mapa[Yg][Xg - 1] == 14 || mapa[Yg][Xg - 1] == 15 || mapa[Yg][Xg - 1] == 16 ||

                    mapa[Yg][Xg - 1] == 17 || mapa[Yg][Xg - 1] == 18 || mapa[Yg][Xg - 1] == 19 ||

                    mapa[Yg][Xg - 1] == 20 || mapa[Yg][Xg - 1] == 21 || mapa[Yg][Xg - 1] == 22)) ||

            (Xg == 0 && !czyTelep))ileZyc--;

        else

        {

            if (ileZwieksz > 0)

            {

                ileZwieksz--;

                ileDlug++;

            }

            else ogon();



            switch (mapa[Ys][Xs])

            {

            case 11:case 18:case 22:

                czasSzyb -= CLOCKS_PER_SEC; mapa[Yg][Xg] = 11; break;

            case 13:case 15:case 17:mapa[Yg][Xg] = 22; break;

            case 14:case 19:case 21:mapa[Yg][Xg] = 18; break;

            default:break;

            }



            Ys = Yg; Xs = Xg; if (Xg == 0)Xg = 49; else Xg--;

        }



        break;

    case 'd':



        if ((mapa[Yg][Xg + 1] == 6 || mapa[Yg][Xg + 1] == 7) ||

            ((Yg == Yo && Xg + 1 == Xo) ? (0) : (!czyZjesc) &&

                (mapa[Yg][Xg + 1] == 11 || mapa[Yg][Xg + 1] == 12 || mapa[Yg][Xg + 1] == 13 ||

                    mapa[Yg][Xg + 1] == 14 || mapa[Yg][Xg + 1] == 15 || mapa[Yg][Xg + 1] == 16 ||

                    mapa[Yg][Xg + 1] == 17 || mapa[Yg][Xg + 1] == 18 || mapa[Yg][Xg + 1] == 19 ||

                    mapa[Yg][Xg + 1] == 20 || mapa[Yg][Xg + 1] == 21 || mapa[Yg][Xg + 1] == 22)) ||

            (Xg == 49 && !czyTelep))ileZyc--;

        else

        {

            if (ileZwieksz > 0)

            {

                ileZwieksz--;

                ileDlug++;

            }

            else ogon();



            switch (mapa[Ys][Xs])

            {

            case 12:case 16:case 20:

                czasSzyb -= CLOCKS_PER_SEC; mapa[Yg][Xg] = 12; break;

            case 13:case 15:case 17:mapa[Yg][Xg] = 20; break;

            case 14:case 19:case 21:mapa[Yg][Xg] = 16; break;

            default:break;

            }



            Ys = Yg; Xs = Xg; if (Xg == 49)Xg = 0; else Xg++;

        }



        break;

    }



    //w zaleznosci od tego co jest na mapie w miejscu glowy : odpowiednio reaguje

    switch (mapa[Yg][Xg])

    {

        //zwykle klocki : zjedzenie

    case 1:ileZwieksz += 1; ile1++; czyNKloc = 0; break;

    case 2:ileZwieksz += 2; ile2++; czyNKloc = 0; break;

    case 3:ileZwieksz += 3; ile3++; czyNKloc = 0; break;

    case 4:ileZwieksz += 4; ile4++; czyNKloc = 0; break;

    case 5:ileZwieksz += 5; ile5++; czyNKloc = 0; break;



        //meta : wygrana

    case 8:jakKoniec = 3; koniec(); break;



        //czesci ciala weza : "odgryzienie" ogona lub srata zycia i zatrzymanie sie

    case 11:case 12:case 13:case 14:case 15:case 16:

    case 17:case 18:case 19:case 20:case 21:case 22:



        if (czyZjesc)

        {

            while (!(Yg == Yo && Xg == Xo))

            {

                ogon();

                ileDlug--;

                pokaz();



            }



            ogon();

            ileDlug--;

        }



        break;



        //klocki przyspieszenia i spowolnienia

    case 30:czySpow = 0; czyPrzy = 1; czasPrzy = clock(); ileSpec++; czyNSpec = 0; break;

    case 31:czyPrzy = 0; czySpow = 1; czasSpow = clock(); ileSpec++; czyNSpec = 0; break;



        //zmniejszenie dlugosci o 5

    case 32:

    {

        //tymczasowa zmienna : ile zostalo do odjecia

        int tymIle = 5;



        while (ileZwieksz > 0 && tymIle > 0)

        {

            ileZwieksz--;

            tymIle--;

        }



        if (tymIle <= ileDlug - 3)

            for (int i = 0; i < tymIle; i++)

            {

                ogon();

                ileDlug--;

                pokaz();

            }



        ileSpec++; czyNSpec = 0;



    }

    break;



    //odjecie zycia

    case 33:



        ileZyc--;

        ileSpec++; czyNSpec = 0;



        break;



        //dodanie zycia

    case 34:



        if (ileZyc < 5)ileZyc++;



        ileSpec++; czyNSpec = 0;



        break;



        //odwrocenie calego weza czyli zmienienie "kierunkow czesci ciala" i...

        //...zamienienie glowy z ogonem

    case 35:

    {

        ogon();



        //tak jak w linijce

        int tymPoz;



        if (Xg < Xs)tymPoz = 12; else if (Xg > Xs)tymPoz = 11;

        else if (Yg < Ys)tymPoz = 14; else if (Yg > Ys)tymPoz = 13;



        //stara glowa staje sie zwykla czescia ciala

        mapa[Yg][Xg] = tymPoz;



        //miejsce glowy zajmuje ogon

        Yo = Yg; Xo = Xg;



        //obrabianie weza zaczynamy od szyji

        Yx = Ys; Xx = Xs;



        //zamienia kazda obrabiana czesc ciala na taka o przeciwnym kierunku

        for (int i = 0; i < ileDlug - 1; i++)

        {

            //utworzenie nowej szyji i glowy

            if (i == ileDlug - 3) { Ys = Yx; Xs = Xx; }

            if (i == ileDlug - 2) { Yg = Yx; Xg = Xx; }



            //wspomniana zamiana

            switch (mapa[Yx][Xx])

            {

            case 11:mapa[Yx][Xx] = 12; break;

            case 12:mapa[Yx][Xx] = 11; break;

            case 13:mapa[Yx][Xx] = 14; break;

            case 14:mapa[Yx][Xx] = 13; break;

            case 15:mapa[Yx][Xx] = 16; break;

            case 16:mapa[Yx][Xx] = 15; break;

            case 17:mapa[Yx][Xx] = 18; break;

            case 18:mapa[Yx][Xx] = 17; break;

            case 19:mapa[Yx][Xx] = 20; break;

            case 20:mapa[Yx][Xx] = 19; break;

            case 21:mapa[Yx][Xx] = 22; break;

            case 22:mapa[Yx][Xx] = 21; break;

            default:break;

            }



            //przesuniecie obrabianaego obszaru

            switch (mapa[Yx][Xx])

            {

            case 13:case 15:case 17:if (Yx == 0)Yx = 29; else Yx--; break;

            case 14:case 19:case 21:if (Yx == 29)Yx = 0; else Yx++; break;

            case 11:case 18:case 22:if (Xx == 0)Xx = 49; else Xx--; break;

            case 12:case 16:case 20:if (Xx == 49)Xx = 0; else Xx++; break;

            }

        }



        ileSpec++; czyNSpec = 0;



        break;



    default:break;

    }

    }



    //"zamalowanie" glowy

    mapa[Yg][Xg] = 10;

}



void gra()

{

    //jesli nie zaladowano zadnej mapy tworzy cala pusta mape

    if (!czyMapa)

    {

        for (int i = 0; i < 30; i++)

        {

            for (int j = 0; j < 50; j++)

            {

                mapa[i][j] = 0;

            }

        }



        mapa[1][1] = 6; mapa[1][2] = 6; mapa[1][3] = 6;

        mapa[2][1] = 6; mapa[2][2] = 6; mapa[2][3] = 6;



        ilePuste = 1494;

        Yg = 15; Xg = 25;

        Ys = 15; Xs = 26;

        Yo = 15; Xo = 27;

        Ym = 2; Xm = 2;

    }



    jakDlug = 10; z = 1;



    //ustawienia rozgrywki

    while (true)

    {

        system("cls");



        cout << "---------" << (char)254 << (char)187; for (int i = 0; i < 20; i++)cout << "-"; cout << endl;

        cout << "         " << (char)201 << (char)188 << " N A K E          " << endl;

        cout << "---------" << (char)200; for (int i = 0; i < 21; i++)cout << (char)205; cout << endl;



        cout << endl << " Wybierz ustawienia :" << endl << endl;

        cout << "-------------------------------" << endl;



        if (z == 1)cout << " > "; else cout << "  "; cout << "Szybkosc weza :      ";

        cout << -(jakSzyb - 11) << endl;



        if (z == 2)cout << " > "; else cout << "  "; cout << "Ilosc zyc weza :     ";

        cout << jakZycia << endl;



        if (z == 3)cout << " > "; else cout << "  "; cout << "Teleportowanie sie : ";

        if (czyTelep)cout << "TAK"; else cout << "NIE"; cout << endl;



        if (z == 4)cout << " > "; else cout << "  "; cout << "Zjadanie ogona :     ";

        if (czyZjesc)cout << "TAK"; else cout << "NIE"; cout << endl;



        if (z == 5)cout << " > "; else cout << "  "; cout << "Klocki po kilka p. : ";

        if (czyKloc)cout << "TAK"; else cout << "NIE"; cout << endl;



        if (z == 6)cout << " > "; else cout << "  "; cout << "Klocki specjalne :   ";

        if (czySpec)cout << "TAK"; else cout << "NIE"; cout << endl;



        if (z == 7)cout << " > "; else cout << "  "; cout << "Czas na gre :        ";

        if (czyCzas)cout << "TAK"; else cout << "NIE"; cout << endl;



        if (z == 8)cout << " > "; else cout << "  "; cout << "Jaki czas na gre :   ";

        cout << jakCzas << endl;



        if (z == 9)cout << " > "; else cout << "  "; cout << "Wymagana dlugosc :   ";

        if (czyDlug)cout << "TAK"; else cout << "NIE"; cout << endl;



        if (z == 10)cout << " > "; else cout << "  "; cout << "Jaka dlugosc :       ";

        cout << jakDlug << endl;



        cout << "-------------------------------" << endl;

        cout << " [Q]wroc do menu  | [E]dalej   " << endl;

        cout << " [W]gora | [S]dol | [A][D]zmien" << endl;



        x = _getch();



        //w zaleznosci od wybranej opcji i wprowadzonego znaku

        switch (z)

        {

        case 1:



            if (x == 'w')z = 10;

            else if (x == 's')z++;

            else if (x == 'a' && jakSzyb < 10)jakSzyb += 1;

            else if (x == 'd' && jakSzyb > 1)jakSzyb -= 1;



            break;

        case 2:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' && jakZycia > 1)jakZycia -= 1;

            else if (x == 'd' && jakZycia < 5)jakZycia += 1;



            break;

        case 3:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' || x == 'd')czyTelep = !czyTelep;



            break;

        case 4:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' || x == 'd')czyZjesc = !czyZjesc;



            break;

        case 5:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' || x == 'd')czyKloc = !czyKloc;



            break;

        case 6:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' || x == 'd')czySpec = !czySpec;



            break;

        case 7:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' || x == 'd')czyCzas = !czyCzas;



            break;

        case 8:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' && jakCzas > 30)jakCzas -= 10;

            else if (x == 'd' && jakCzas < 300)jakCzas += 10;



            break;

        case 9:



            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'a' || x == 'd')czyDlug = !czyDlug;



            break;

        case 10:



            if (x == 'w')z--;

            else if (x == 's')z = 1;

            else if (x == 'a' && jakDlug > 10)jakDlug -= 10;

            else if (x == 'd' && jakDlug < ilePuste - 10)jakDlug += 10;



            break;

        }



        if (x == 'e')break;

        if (x == 'q')return;



    }



    //tworzy mete

    if (czyDlug) mapa[Ym][Xm] = 7; else mapa[Ym][Xm] = 6;



    //na podstawie polozenia szyji, ogona i glowy decyduje o ich wygladzie

    int tymPoz;



    mapa[Yg][Xg] = 10;



    if (Xg < Xo)

    {

        if (Yg < Yo) { if (Ys < Yo)tymPoz = 22; else tymPoz = 15; }

        else if (Yg > Yo) { if (Yg > Ys)tymPoz = 19; else tymPoz = 18; }

        else if (Yg == Yo)tymPoz = 11;

    }

    else if (Xg > Xo)

    {

        if (Yg < Yo) { if (Ys < Yo)tymPoz = 20; else tymPoz = 17; }

        else if (Yg > Yo) { if (Ys < Yg)tymPoz = 21; else tymPoz = 16; }

        else if (Yg == Yo)tymPoz = 12;

    }

    else if (Xg == Xo)

    {

        if (Yg < Yo)tymPoz = 13;

        else if (Yg > Yo)tymPoz = 14;

    }

    mapa[Ys][Xs] = tymPoz;



    if (Xs < Xo)tymPoz = 11; else if (Xs > Xo)tymPoz = 12;

    else if (Ys < Yo)tymPoz = 13; else if (Ys > Yo)tymPoz = 14;

    mapa[Yo][Xo] = tymPoz;



    //wyzerowanie wszystkich potrzebnych do dzialania gry zmiennych

    ileZwieksz = 0;

    czyKoniec = 0;

    czyPrzy = 0;

    czySpow = 0;

    czyNKloc = 0;

    czyNSpec = 0;



    ileDlug = 3;

    ileZyc = jakZycia;

    ile1 = 0;

    ile2 = 0;

    ile3 = 0;

    ileSpec = 0;

    ileCzas = 0;



    //do 'rand()'

    srand(time(NULL));



    //zaczyna mierzyc ogolny czas w grze

    if (czyCzas)czasCzas = clock();



    //wlasciwa gra

    while (!czyKoniec)

    {

        //#######################################################################//

        //#######################################################################//



        //wyznaczenie aktualnego czasu

        ileCzas = double(clock() - czasCzas) / CLOCKS_PER_SEC; pokaz();



        //jesli nie ma juz zwyklego klocka na mapie : tworzy nowy

        if (!czyNKloc && ileDlug < ilePuste)

        {

            //losuje polozenie dopoki nie natrafi na puste miejsce na mapie

            do

            {

                Ynk = rand() % 30; Xnk = rand() % 50;



            } while (((ileDlug < ilePuste - 10) ? (abs(Ynk - Yg) < 4 && abs(Xnk - Xg) < 4) : (0))

                || mapa[Ynk][Xnk] != 0);



            //wybiera po ile punktow ma byc zwykly klocek

            if (czyKloc)

            {

                mapa[Ynk][Xnk] = rand() % 5 + 1;

            }

            else mapa[Ynk][Xnk] = 1;



            //zwykly klocek jest na mapie

            czyNKloc = 1;

        }



        //jesli nie ma klocka specjalnego na mapie, mozna tworzyc...

        //...klocki specjalne i szczesliwie wylosowano : tworzy nowy klocek spec.

        if (czySpec && !czyNSpec && rand() % 10 == 1 && ileDlug < ilePuste - 10)

        {

            //tak jak przy zwyklym klocku

            do

            {

                Yns = rand() % 30; Xns = rand() % 50;



            } while (((ileDlug < ilePuste - 10) ? (abs(Yns - Yg) < 4 && abs(Xns - Xg) < 4) : (0))

                || mapa[Yns][Xns] != 0);



            //ktory klocek specjalny

            mapa[Yns][Xns] = rand() % 6 + 30;



            //od kiedy instnieje klocek specjalny ( a instnieje 10 s.)

            czasSpec = clock();



            //klocek specjalny jest na mapie

            czyNSpec = 1;

        }



        //sprawdza czy nie skonczyl sie juz czas na efekty przyspieszenia,...

        //...spowolnienia i na klocka specjalnego

        if (czyPrzy && double(clock() - czasPrzy) / CLOCKS_PER_SEC > 30)czyPrzy = 0;

        if (czySpow && double(clock() - czasSpow) / CLOCKS_PER_SEC > 30)czySpow = 0;

        if (czyNSpec && double(clock() - czasSpec) / CLOCKS_PER_SEC > 10)

        {

            mapa[Yns][Xns] = 0;

            czyNSpec = 0;

        }



        //tworzy efekt przyspieszenia lub spowolnienia

        ileSzyb = jakSzyb;

        if (czyPrzy)ileSzyb -= 1;

        if (czySpow)ileSzyb += 1;



        //#######################################################################//

        //#######################################################################//



        //zaczyna mierzyc czas na wykonanie ruchu

        czasSzyb = clock();



        //wyzerowanie

        czyZnak = 0;



        pokaz();



        //wykonanie ruchu

        while ((double(clock() - czasSzyb) / CLOCKS_PER_SEC) <

            ((ileSzyb / 10.0 < 0.1) ? (0.1) : (ileSzyb / 10.0)))

        {

            //jesli uzytkownik wprowadzil jakis znak

            if (_kbhit())

            {

                jakZnak = _getch();



                if (jakZnak == 'e')

                {

                    while (_getch() != 'e') {}

                }

                else if (jakZnak == 'q') { jakKoniec = 4; koniec(); }



                //decyduje na podstawie 'jakiZnak' i szyji weza czy wykonac ruch

                if (jakZnak == 'w' || jakZnak == 's' || jakZnak == 'a' || jakZnak == 'd')

                    switch (mapa[Ys][Xs])

                    {

                    case 13:case 15:case 17:

                        if (jakZnak != 's') { ruch(); czyZnak = 1; }break;

                    case 14:case 19:case 21:

                        if (jakZnak != 'w') { ruch(); czyZnak = 1; }break;

                    case 11:case 18:case 22:

                        if (jakZnak != 'd') { ruch(); czyZnak = 1; }break;

                    case 12:case 16:case 20:

                        if (jakZnak != 'a') { ruch(); czyZnak = 1; }break;

                    }

            }

        }



        //jesli uzytkownik nie wprowadzil znaku : wykonuje samodzielny ruch wezem

        if (!czyZnak)switch (mapa[Ys][Xs])

        {

        case 13:case 15:case 17:jakZnak = 'w'; ruch(); break;

        case 14:case 19:case 21:jakZnak = 's'; ruch(); break;

        case 11:case 18:case 22:jakZnak = 'a'; ruch(); break;

        case 12:case 16:case 20:jakZnak = 'd'; ruch(); break;

        }



        //#######################################################################//

        //#######################################################################//



        //jesli waz zapelnil cala mape

        if (ileDlug == ilePuste)

        {

            ileZwieksz = 0;

        }



        //jesli skonczyly sie zycia

        if (ileZyc < 1)

        {

            jakKoniec = 1; koniec();

        }



        //jesli skonczyl sie czas

        if (czyCzas && ileCzas > jakCzas)

        {

            jakKoniec = 2; koniec();

        }



        //jesli osiagnieto wymagana dlugosc do wygranej : "otwiera" mete

        if (czyDlug && ileDlug == jakDlug)

        {

            mapa[Ym][Xm] = 8;

        }



        //#######################################################################//

        //#######################################################################//

    }

}



void pobierz()

{

    system("cls");



    cout << "---------" << (char)254 << (char)187; for (int i = 0; i < 20; i++)cout << "-"; cout << endl;

    cout << "         " << (char)201 << (char)188 << " N A K E          " << endl;

    cout << "---------" << (char)200; for (int i = 0; i < 21; i++)cout << (char)205; cout << endl;



    cout << " Otworzyc plik: \"mapa.txt \"  " << endl << endl;

    cout << " z folderu ze \"snake.exe\" ?  " << endl;

    cout << "-------------------------------" << endl;

    cout << " [COS INNEGO] NIE  |  [E] TAK  " << endl << endl;



    if (_getch() != 'e')return;



    fstream plikPlik;          //do pliku "mapa.txt"

    string plikLinia;          //do pojedynczych linii tekstu z "mapa.txt"



    //liczniki glow, szyji, ogonow i met (by sprawdzic czy sa lub czy jest za duzo)

    int ileG = 0; int ileS = 0; int ileO = 0; int ileM = 0;

    bool czyBlad = 0;



    //otwarcie "mapa.txt"

    plikPlik.open("mapa.txt", ios::in);



    if (plikPlik.good() == false)

    {

        cout << "---------" << (char)254 << (char)187; for (int i = 0; i < 20; i++)cout << "-"; cout << endl;

        cout << "         " << (char)201 << (char)188 << " N A K E          " << endl;

        cout << "---------" << (char)200; for (int i = 0; i < 21; i++)cout << (char)205; cout << endl << endl;



        cout << " COS POSZLO NIE TAK !!!        " << endl << endl;

        cout << "-------------------------------" << endl;

        cout << " [E] wroc do menu              " << endl << endl;



        while (_getch() != 'e') {}return;

    }



    //pobiera nazwe mapy

    getline(plikPlik, jakMapa);



    //wyzerowanie

    ilePuste = 0; Yg = 0; Xg = 0; Ys = 0; Xs = 0; Yo = 0; Xo = 0; Ym = 0; Xm = 0;



    for (int i = 0; i < 30; i++)

    {

        plikLinia = "00000000000000000000000000000000000000000000000000";



        getline(plikPlik, plikLinia);



        cout << " " << plikLinia << endl;



        for (int j = 0; j < 50; j++)

        {

            //jesli w tekscie znajduje sie niedozwolony znak

            if (plikLinia[j] != '0' && plikLinia[j] != '1' && plikLinia[j] != '2' &&

                plikLinia[j] != '3' && plikLinia[j] != '6' && plikLinia[j] != '7')

            {

                cout << " Niedozwolony znak !!! ( ^ gorna linijka ^ )" << endl;

                czyBlad = 1;

            }



            //specjalne reagowanie na okreslony znak

            switch (plikLinia[j])

            {

            case '0':ilePuste++; break;

            case '1':Yg = i; Xg = j; plikLinia[j] = '0'; ileG++; break;

            case '2':Ys = i; Xs = j; plikLinia[j] = '0'; ileS++; break;

            case '3':Yo = i; Xo = j; plikLinia[j] = '0'; ileO++; break;

            case '7':Ym = i; Xm = j; plikLinia[j] = '0'; ileM++; break;

            }



            mapa[i][j] = plikLinia[j] - '0';

        }

    }



    //do pustych pol doliczamy jeszcze weza

    ilePuste += 3;



    //zamkniecie "mapa.txt"

    plikPlik.close();



    if (ileG == 0) { cout << " Brak glowy !!!" << endl; czyBlad = 1; }

    else if (ileG > 1) { cout << " Za duzo glow !!!" << endl; czyBlad = 1; }



    if (ileS == 0) { cout << " Brak szyji !!!" << endl; czyBlad = 1; }

    else if (ileS > 1) { cout << " Za duzo szyji !!!" << endl; czyBlad = 1; }



    if (ileO == 0) { cout << " Brak ogona !!!" << endl; czyBlad = 1; }

    else if (ileO > 1) { cout << " Za duzo ogonow !!!" << endl; czyBlad = 1; }



    if (ileM == 0) { cout << " Brak mety  !!!" << endl; czyBlad = 1; }

    else if (ileM > 1) { cout << " Za duzo met !!!" << endl; czyBlad = 1; }





    if (abs(Yg - Ys) + abs(Xg - Xs) + abs(Ys - Yo) + abs(Xs - Xo) > 2)

    {

        cout << " Nieprawidlowe polozenie czesci ciala weza !!!" << endl;

        czyBlad = 1;

    }



    //jesli wszystko jest w porzadku : pobrana mapa nie jest nadpisywana

    if (czyBlad == 0)czyMapa = 1;



    _getch();

}



void menu()

{

    system("cls");



    z = 1;



    while (true)

    {

        system("cls");



        cout << "---------" << (char)254 << (char)187; for (int i = 0; i < 20; i++)cout << "-"; cout << endl;

        cout << "         " << (char)201 << (char)188 << " N A K E          " << endl;

        cout << "---------" << (char)200; for (int i = 0; i < 21; i++)cout << (char)205; cout << endl;



        if (czyMapa == false)cout << " Mapa NIEzaladowana" << endl << endl << " ( czysta mapa )" << endl;

        else cout << " Zaladowano mape :" << endl << endl << " \" " << jakMapa << " \"" << endl;



        cout << "-------------------------------" << endl;

        if (z == 1)cout << " > "; else cout << "  "; cout << "Graj" << endl;

        if (z == 2)cout << " > "; else cout << "  "; cout << "Pobierz" << endl;

        if (z == 3)cout << " > "; else cout << "  "; cout << "Wyjdz" << endl;

        cout << "-------------------------------" << endl;

        cout << " [W]gora | [S]dol | [E]wybierz" << endl;



        x = _getch();



        //w zaleznosci od wybranej opcji i wprowadzonego znaku

        switch (z)

        {

        case 1:

        {

            if (x == 'w')z = 3;

            else if (x == 's')z++;

            else if (x == 'e') { gra(); z = 1; }

            break;

        }

        case 2:

        {

            if (x == 'w')z--;

            else if (x == 's')z++;

            else if (x == 'e') { pobierz(); z = 2; }

            break;

        }

        case 3:

        {

            if (x == 'w')z--;

            else if (x == 's')z = 1;

            else if (x == 'e')return;

            break;

        }

        }

    }

}



int main()

{

    ios_base::sync_with_stdio(0);



    menu();



    return 0;

}

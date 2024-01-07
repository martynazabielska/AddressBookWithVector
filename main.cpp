#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline (cin, wejscie);
    return wejscie;
}

char pobierzZnak()
{
    char znak;
    string wejscie = "";

    while(true)
    {
        wejscie = wczytajLinie();
        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Sprobuj ponownie." << endl;
    }
    return znak;
}

int pobierzLiczbe()
{
    int liczba = 0;
    string wejscie = "";

    while(true)
    {
        wejscie = wczytajLinie();

        stringstream myStream(wejscie);
        if (myStream >> liczba) break;

        cout << "To nie jest liczba. Sprobuj ponownie." << endl;
    }
    return liczba;
}

struct Adresat
{
    string imie = "", nazwisko = "", adres = "", mail = "", nrTelefonu = "";
    int id = 0;
};

void zapisanieDanychDoPlikuPoDodaniuAdresata (Adresat osoba)
{
    fstream plik;
    plik.open("Ksiazka_Adresowa.txt", ios::app);

    if (plik.good())
    {
        plik << osoba.id << "|";
        plik << osoba.imie << "|";
        plik << osoba.nazwisko << "|";
        plik << osoba.adres << "|";
        plik << osoba.mail << "|";
        plik << osoba.nrTelefonu << "|"<<endl;
        plik.close();
        cout << "Adresat dodany pomyslnie" << endl;
    }
    else
    {
        cout << "Nie udalo sie utworzyc pliku i zapisac danych" << endl;
    }
}

void zapisanieDanychDoPlikuPoUsunieciuLubEdycjiAdresata(vector <Adresat> ludzie)
{
    fstream plik;
    plik.open("Ksiazka_Adresowa.txt", ios::out);
    if(plik.good())
    {
        for (size_t i =0; i< ludzie.size(); i++)
        {
            plik << ludzie[i].id << "|";
            plik << ludzie[i].imie << "|";
            plik << ludzie[i].nazwisko << "|";
            plik << ludzie[i].adres << "|";
            plik << ludzie[i].mail << "|";
            plik << ludzie[i].nrTelefonu << "|";
            plik << endl;
        }
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie utworzyc pliku i zapisac danych" << endl;
    }
}

void wczytywanieOsobZPliku (vector <Adresat> &ludzie)
{
    Adresat osoba;
    string linia;
    int nrLinii = 1;
    fstream plik;
    plik.open("Ksiazka_Adresowa.txt", ios :: in);

    if(plik.good() == false)
    {
        cout << "Nie mozna otworzyc pliku!" << endl;
    }

    else
    {
        while(getline(plik,linia))
        {
            Adresat osoba;

            stringstream wejscie{linia};
            string fragmentLinii {};
            vector <string> wyjscie;

            while(getline(wejscie, fragmentLinii, '|'))
            {
                wyjscie.push_back(fragmentLinii);
            }

            osoba.id = atoi(wyjscie[0].c_str());
            osoba.imie = wyjscie[1];
            osoba.nazwisko = wyjscie[2];
            osoba.adres = wyjscie[3];
            osoba.mail = wyjscie[4];
            osoba.nrTelefonu = wyjscie[5];

            ludzie.push_back(osoba);
            wyjscie.clear();

            nrLinii++;
        }
    }
    plik.close();
}

void dodawanieAdresata (vector <Adresat> &ludzie)
{
    Adresat osoba;
    int ostatnieId = ludzie.empty() ? 0 : ludzie.back().id;
    string imie, nazwisko, adres, mail, nrTelefonu;

    cout << "Podaj imie: ";
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout  <<  "Podaj adres: ";
    adres = wczytajLinie();
    cout  << "Podaj mail: ";
    mail = wczytajLinie();
    cout  << "Podaj numer telefonu: ";
    nrTelefonu = wczytajLinie();

    osoba.id = ostatnieId+1;
    osoba.imie = imie;
    osoba.nazwisko = nazwisko;
    osoba.adres = adres;
    osoba.mail = mail;
    osoba.nrTelefonu = nrTelefonu;

    ludzie.push_back(osoba);

    zapisanieDanychDoPlikuPoDodaniuAdresata(osoba);
}

void wyszukajAdresatowPoImieniu (vector <Adresat> ludzie)
{
    bool adresatZnaleziony = false;
    string imie;
    cout << "Podaj imie adresata, ktorego chcesz wyszukac: ";
    imie = wczytajLinie();

    for (size_t i = 0; i < ludzie.size(); i++)
    {
        if (ludzie[i].imie == imie)
        {
            cout << ludzie[i].id << "|";
            cout << ludzie[i].imie << "|";
            cout << ludzie[i].nazwisko << "|";
            cout << ludzie[i].adres << "|";
            cout << ludzie[i].mail << "|";
            cout << ludzie[i].nrTelefonu << "|" << endl;

            adresatZnaleziony = true;
        }
    }

    if (!adresatZnaleziony)
    {
        cout << "Nie znaleziono adresata o podanym imieniu" << endl;
    }
    system("pause");
}

void wyszukajAdresatowPoNazwisku (vector <Adresat> ludzie)
{
    bool adresatZnaleziony = false;
    string nazwisko;
    cout << "Podaj nazwisko adresata, ktorego chcesz wyszukac: ";
    nazwisko = wczytajLinie();

    for (size_t i = 0; i < ludzie.size(); i++)
    {
        if (ludzie[i].nazwisko == nazwisko)
        {
            cout << ludzie[i].id << "|";
            cout << ludzie[i].imie << "|";
            cout << ludzie[i].nazwisko << "|";
            cout << ludzie[i].adres << "|";
            cout << ludzie[i].mail << "|";
            cout << ludzie[i].nrTelefonu << "|" << endl;

            adresatZnaleziony = true;
        }

    }
    if (!adresatZnaleziony)
    {
        cout << "Nie odnaleziono adresata o podanym nazwisku" << endl;
    }
    system("pause");
}

void wyswietlWszystkichAdresatow (vector <Adresat> ludzie)
{
    if (ludzie.size() > 0)
    {
        for(size_t i = 0 ; i < ludzie.size() ; i++)
        {
            cout <<  ludzie[i].id << "|";
            cout <<  ludzie[i].imie << "|";
            cout <<  ludzie[i].nazwisko << "|";
            cout <<  ludzie[i].adres << "|";
            cout <<  ludzie[i].mail << "|";
            cout <<  ludzie[i].nrTelefonu << "|" << endl;
        }
    }
    else
    {
        cout << "Brak danych" << endl;
    }
    system ("pause");
}

void usunWybranegoAdresata (vector <Adresat> &ludzie)
{
    int idUsuwanegoAdresata;
    char potwierdzenieWyboru;

    if (ludzie.size() > 0)
    {
        cout << "Podaj id Adresata, ktorego chcesz usunac: ";
        idUsuwanegoAdresata = pobierzLiczbe();

        for (vector <Adresat> :: iterator itr = ludzie.begin(); itr!=ludzie.end(); ++itr)
        {
            if (itr->id == idUsuwanegoAdresata)
            {
                cout << "Wybrales adresata do usuniecia: " << endl;
                cout << itr -> id << "|" << itr -> imie << "|" << itr -> nazwisko << "|" << itr -> adres << "|" << itr -> mail << "|" << itr->nrTelefonu << "|" << endl;
                Sleep(2000);
                cout << "Wcisnij 't' aby potwierdzic usuniecie wybranego adresata: ";
                potwierdzenieWyboru = pobierzZnak();

                if (potwierdzenieWyboru == 't')
                {
                    ludzie.erase(itr);
                    zapisanieDanychDoPlikuPoUsunieciuLubEdycjiAdresata (ludzie);
                    break;
                }

                else if (potwierdzenieWyboru != 't')
                {
                    cout << "Nie potwierdzono usuniecia. Nastepuje powrot do menu glownego" << endl;
                    Sleep(1000);
                    break;
                }
            }
        }
    }
    else
    {
        cout << "Brak danych" << endl;
    }
    system ("pause");
}

void edytujDaneAdresata (vector <Adresat> &ludzie)
{
    bool adresatZnaleziony = false;
    int id;
    string imie, nazwisko, adres, mail, nrTelefonu;
    char wybor;

    cout << "Podaj id adresata, ktorego dane chcesz edytowac: ";
    id = pobierzLiczbe();

    for (size_t i = 0; i < ludzie.size(); i++)
    {
        if (ludzie[i].id == id)
        {
            system("cls");
            cout << "Podaj jedna z ponizszych danych do edycji:" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Adres" << endl;
            cout << "4. Mail" << endl;
            cout << "5. Numer telefonu" << endl;
            cout << "6. Powrot do menu glownego" << endl;
            wybor = pobierzZnak();

            if (wybor == '1')
            {
                cout << "Podaj nowe imie: ";
                imie = wczytajLinie();
                ludzie[i].imie = imie;
            }
            else if (wybor == '2')
            {
                cout << "Podaj nowe nazwisko: ";
                nazwisko = wczytajLinie();
                ludzie[i].nazwisko = nazwisko;
            }
            else if (wybor == '3')
            {
                cout << "Podaj nowy adres: ";
                adres = wczytajLinie();
                ludzie[i].adres = adres;
            }
            else if (wybor == '4')
            {
                cout << "Podaj nowy mail: ";
                mail = wczytajLinie();
                ludzie[i].mail = mail;
            }
            else if (wybor == '5')
            {
                cout << "Podaj nowy numer telefonu: ";
                nrTelefonu = wczytajLinie();
                ludzie[i].nrTelefonu = nrTelefonu;
            }
            else if (wybor == '6')
            {
                break;
            }

            zapisanieDanychDoPlikuPoUsunieciuLubEdycjiAdresata(ludzie);
            adresatZnaleziony = true;
        }
    }

    if (!adresatZnaleziony)
    {
        cout << "Nie odnaleziono adresata o podanym id" << endl;
    }
    system("pause");
}

int main()
{
    vector <Adresat> adresaci;
    char wybor;

    wczytywanieOsobZPliku (adresaci);

    while(1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj adresata po imieniu" << endl;
        cout << "3. Wyszukaj adresata po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        wybor = pobierzZnak();

        if (wybor == '1')
        {
            dodawanieAdresata (adresaci);
        }
        else if (wybor == '2')
        {
            wyszukajAdresatowPoImieniu (adresaci);
        }
        else if (wybor == '3')
        {
            wyszukajAdresatowPoNazwisku (adresaci);
        }
        else if (wybor == '4')
        {
            wyswietlWszystkichAdresatow (adresaci);
        }
        else if (wybor == '5')
        {
            usunWybranegoAdresata(adresaci);
        }
        else if (wybor == '6')
        {
            edytujDaneAdresata (adresaci);
        }
        else if (wybor =='9')
        {
            exit(0);
        }
    }
    return 0;
}

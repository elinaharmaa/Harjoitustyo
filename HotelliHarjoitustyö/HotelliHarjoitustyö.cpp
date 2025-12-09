// Elina Harmaa
// Harjoitustyö

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale>

using namespace std;

// Huoneiden määrät ja hinnat
const int MIN_HUONEET = 30;
const int MAX_HUONEET = 70;
const int MIN_HINTA = 80;
const int MAX_HINTA = 100;

// Tietorakenteet
struct Varaus {
    int numero = 0;  // Varausnumero
    string nimi = "";  // Varaajan nimi
    int yot = 0;  // Öiden määrä
    int summa = 0;  // loppusumma
    int alennus = 0;  // alennus prosentteina
    int huonetyyppi = 0; // 1 = perushuone, 2 = sviitti
    int hintaPerYo = 0;  // Hinta per yö
};

struct Huone {
    int numero = 0; // Huonenumero
    bool varattu = false;  // Onko huone varattu
    Varaus varaus;
};

// Aliohjelma: onko huone vapaa
bool onVapaa(const Huone& h) {
    return !h.varattu;
}

// Aliohjelma: loppusumma
int laskeSumma(int hintaPerYo, int yot, int alennus) {
    int brutto = hintaPerYo * yot;
    return brutto - (brutto * alennus / 100);
}

// Arpoo vapaan huoneen
int arvoVapaaHuone(const vector<Huone>& huoneet) {
    vector<int> vapaat;
    for (size_t i = 0; i < huoneet.size(); i++) {
        if (!huoneet[i].varattu) vapaat.push_back(i);
    }
    if (vapaat.empty()) return -1;
    int idx = rand() % vapaat.size();
    return vapaat[idx];
}

// Aliohjelma: varauksen teko
void teeVaraus(vector<Huone>& huoneet, int huoneMaara) {
    string nimi;
    int yot;

    // Varaajan nimi
    cout << "Anna nimi: ";
    cin >> ws;
    getline(cin, nimi);

    // Öiden määrä
    cout << "Anna yöt: ";
    cin >> yot;
    if (cin.fail() || yot <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Virheellinen määrä" << endl;
        return;
    }

    // Arvotaan vapaa huone
    int huoneNro = arvoVapaaHuone(huoneet);
    if (huoneNro == -1) {
        cout << "Kaikki huoneet ovat varattuja." << endl;
        return;
    }

    cout << "Sinulle arvottiin vapaa huone " << huoneet[huoneNro].numero << endl;

    int tyyppi = rand() % 2 + 1;
    int hintaPerYo = rand() % (MAX_HINTA - MIN_HINTA + 1) + MIN_HINTA;
    int alennus = (rand() % 3) * 10;   // 0, 10, 20 %

    // Tallennetaan varaus
    huoneet[huoneNro].varattu = true;
    huoneet[huoneNro].varaus.numero = rand() % 90000 + 10000;
    huoneet[huoneNro].varaus.nimi = nimi;
    huoneet[huoneNro].varaus.yot = yot;
    huoneet[huoneNro].varaus.huonetyyppi = tyyppi;
    huoneet[huoneNro].varaus.alennus = alennus;
    huoneet[huoneNro].varaus.hintaPerYo = hintaPerYo;
    huoneet[huoneNro].varaus.summa = laskeSumma(hintaPerYo, yot, alennus);

    // Tulostaa varauksen tiedot
    cout << "Varaus tehty huoneeseen " << huoneet[huoneNro].numero << endl;
    cout << "Huonetyyppi: " << (tyyppi == 1 ? "Perushuone" : "Sviitti") << endl;
    cout << "Hinta per yö: " << hintaPerYo << " EUR" << endl;
    cout << "Varausnumero: " << huoneet[huoneNro].varaus.numero << endl;
    cout << "Alennus: " << huoneet[huoneNro].varaus.alennus << " %" << endl;
    cout << "Loppusumma: " << huoneet[huoneNro].varaus.summa << " EUR" << endl;
}

// Aliohjelma: varauksen haku
void haeVaraus(const vector<Huone>& huoneet, int huoneMaara) {
    int haku;
    cout << "Hae numerolla=1 nimellä=2: ";
    cin >> haku;

    if (haku == 1) {
        // Hakee varauksen numerolla
        int numero;
        cout << "Anna varausnumero: ";
        cin >> numero;
        for (int i = 0; i < huoneMaara; i++) {
            if (huoneet[i].varattu && huoneet[i].varaus.numero == numero) {
                cout << "Varaaja: " << huoneet[i].varaus.nimi
                    << ", summa " << huoneet[i].varaus.summa
                    << " EUR (alennus " << huoneet[i].varaus.alennus << " %)" << endl;
                return;
            }
        }
        cout << "Ei löytynyt" << endl;
    }
    else if (haku == 2) {
        // Hakee varauksen nimellä
        string nimi;
        cout << "Anna nimi: ";
        cin >> ws;
        getline(cin, nimi);
        bool loytyi = false;


        for (int i = 0; i < huoneMaara; i++) {
            if (huoneet[i].varattu && huoneet[i].varaus.nimi == nimi) {
                cout << "Huone: " << huoneet[i].numero
                    << " | Varausnumero: " << huoneet[i].varaus.numero
                    << " | Hinta/yö: " << huoneet[i].varaus.hintaPerYo << " EUR"
                    << " | Alennus: " << huoneet[i].varaus.alennus << " %"
                    << " | Summa: " << huoneet[i].varaus.summa << " EUR" << endl;
                loytyi = true;
            }
        }
        if (!loytyi) cout << "Ei löytynyt" << endl;
    }
    else {
        cout << "Virheellinen valinta" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(0)));

    int huoneMaara = rand() % 41 + 30; // 30–70 huonetta
    vector<Huone> huoneet(huoneMaara);

    for (int i = 0; i < huoneMaara; i++) {
        huoneet[i].numero = i + 1;
        huoneet[i].varattu = false;
    }

    // Pääsilmukka, käyttäjä voi tehdä varauksia tai hakea varauksia
    while (true) {
        cout << "1 Tee varaus" << endl;
        cout << "2 Hae varaus" << endl;
        cout << "3 Lopeta" << endl;
        cout << "Valinta: ";
        int valinta;
        cin >> valinta;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Virheellinen syöte!" << endl;
            continue;
        }

        if (valinta == 1) {
            teeVaraus(huoneet, huoneMaara);
        }
        else if (valinta == 2) {
            haeVaraus(huoneet, huoneMaara);
        }
        else if (valinta == 3) {
            cout << "Ohjelma loppuu" << endl;
            break;
        }
        else {
            cout << "Virheellinen valinta" << endl;
        }
    }

    return 0;
}

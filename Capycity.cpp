#include <iostream>
using namespace std;

	int laenge = 0;
	int breite = 0;
	enum Gebaeudetypen {LEER, WASSERKRAFTWERK, WINDKRAFTWERK, SOLARPANELE} gebaeudetyp;		//0 = kein Gebaeude; 1 = Wasserkraftwerk; 2 = Windkraftwerk; 3 = Solarpanele

int main()
{
	//Deklaration der Variablen
	int eingabe = 0;
	char sicher = 'n';

	//Deklaration der Funktionen
	void setzeGebaeude();			//Nachfrage nach Art, Laenge, Breite und Position
	void loescheBereich();			//Gebaeude sollen nicht geloescht, sondern nur verkleinert werden
	void zeigeBauplan(int, int);	//Ausgeben des aktuellen Bauplans
	void beendeProgramm();			//Beenden des Programms

	//Eingabe von laenge und breite fuer den Baubereich
	cout << "Hello Capycity!\n### Definition des Baubereichs ###" << endl;
	cout << "Laenge: ";
	cin >> laenge;
	cout << "Breite: ";
	cin >> breite;
	//Mehrdimensionales Array mit dynamischer Groeße (laenge x breite) anlegen
	int** baubereich = new int* [laenge];
	for (int i = 0; i < laenge; i++)
		baubereich[i] = new int[breite];
	system("cls");
	cout << "Hello Capycity!" << endl;

	//Anzeigen des Menues
	do {
		cout << "### Menue ###" << endl;
		cout << "1: Gebaeude setzen" << endl;
		cout << "2: Bereich loeschen" << endl;
		cout << "3: Aktuellen Bauplan anzeigen" << endl;
		cout << "4: Programm beenden" << endl;
		cout << "Bitte geben Sie eine entsprechende Zahl (1-4) ein: ";
		cin >> eingabe;

		switch (eingabe) {
		case 1:
			setzeGebaeude();
			break;
		case 2:
			loescheBereich();
			break;
		case 3:
			zeigeBauplan(laenge, breite);
			break;
		case 4:
			cout << "Wirklich Beenden? (y/n): ";
			cin >> sicher;
			if (sicher == 'y')
				eingabe *= 10;
			else
				system("cls");
			break;
		default:
			cout << "Falsche Eingabe!\n";
			break;
		};
	} while (eingabe != 40);

	return 0;
}

void setzeGebaeude() {
	//Nachfrage nach Art, Laenge, Breite und Position
	int x = 0;
	int y = 0;
	int art = 0;	//art=Gebaeudetyp

	system("cls");
	cout << "### Gebaeude setzen ###\n"
		"Koordinaten innerhalb des definierten Baubereichs (x = 0-" << laenge << "/y = 0-" << breite << ") eingeben:\n"
		"x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "Es wurden folgende Koordinaten gewaehlt (x, y): (" << x << "," << y << ")" << endl;
	cout << "Waehlen Sie nun einen Gebaeudetyp (1-3):\n" << Gebaeudetypen::WASSERKRAFTWERK << " = Wasserkraftwerk"
		"\n" << Gebaeudetypen::WINDKRAFTWERK << " = Windkraftwerk"
		"\n" << Gebaeudetypen::SOLARPANELE << " = Solarpanele\n" << endl;
	cin >> art;

	//Überarbeiten!!
	switch (art) {
	case 1:
		cout << "Es wurde " << "ENUM" << " ausgewaehlt." << endl;
	};

}

void loescheBereich() {
	//Gebaeude sollen nicht geloescht, sondern nur verkleinert werden
}

void zeigeBauplan(int laenge, int breite) {
	//Ausgeben des aktuellen Bauplans
	system("cls");
	cout << "Die Landflaeche sieht aktuell wie folgt aus:\n"
		"0 = unbesetzt\n"
		"1 = Wasserkraftwerk\n"
		"2 = Windkraftwerk\n"
		"3 = Solarpanele\n\n";
	for (int i = 0; i < laenge; i++) {
		for (int j = 0; j < breite; j++)
			cout << "O";
		cout << "\n";
	}
	cout << "\n" << endl;
}
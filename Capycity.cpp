#include <iostream>
using namespace std;

int laengeBaubereich = 0;
int breiteBaubereich = 0;
enum Gebaeudetypen { LEER, WASSERKRAFTWERK, WINDKRAFTWERK, SOLARPANELE } gebaeudetyp;		//0 = kein Gebaeude; 1 = Wasserkraftwerk; 2 = Windkraftwerk; 3 = Solarpanele

int main()
{
	//Deklaration der Variablen
	int menueAuswahl = 0;	//zur Auswahl im Menue
	char sicher = 'n';		//fuer die Sicherheitsabfrage, ob wirklich beendet werden soll

	//Deklaration der Funktionen
	void setzeGebaeude(int**);		//Nachfrage nach Art, Laenge, Breite und Position
	void loescheBereich(int**);			//Gebaeude sollen nicht geloescht, sondern nur verkleinert werden
	void zeigeBauplan(int**);		//Ausgeben des aktuellen Bauplans
	void beendeProgramm();			//Beenden des Programms

	//Eingabe von Laenge und Breite fuer den Baubereich
	cout << "Hello Capycity!\n### Definition des Baubereichs ###" << endl;
	cout << "Laenge: ";
	cin >> laengeBaubereich;
	cout << "Breite: ";
	cin >> breiteBaubereich;
	//Mehrdimensionales Array mit dynamischer Groeße (Laenge x Breite) anlegen
	int** aBaubereich = new int* [laengeBaubereich];
	for (int i = 0; i < laengeBaubereich; i++)
		aBaubereich[i] = new int[breiteBaubereich];

	//Array mit Gebaeudetyp "NULL" befuellen
	for (int i = 0; i < laengeBaubereich; i++)
		for (int j = 0; j < breiteBaubereich; j++)
			aBaubereich[i][j] = Gebaeudetypen::LEER;

	//Konsoleneintraege loeschen und Willkommensnachricht anzeigen
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
		cin >> menueAuswahl;

		switch (menueAuswahl) {
		case 1:
			setzeGebaeude(aBaubereich);
			break;
		case 2:
			loescheBereich(aBaubereich);
			break;
		case 3:
			zeigeBauplan(aBaubereich);
			break;
		case 4:
			//Programm beenden mit vorheriger Sicherheitsabfrage
			cout << "Wirklich Beenden? (y/n): ";
			cin >> sicher;
			if (sicher == 'y') {
				//Freigeben des mehrdimensionalen Arrays "aBaubereich"
				for (int i = 0; i < laengeBaubereich; i++)
					delete[] aBaubereich[i];	// Zeilen freigeben
				delete[] aBaubereich;			// Array mit Zeigern auf Zeilenanfänge freigeben
				aBaubereich = nullptr;		//delete auf einen nullptr-Zeiger bewirkt nichts und ist unschaedlich (deshalb empfehlenswert)
				menueAuswahl *= 10;
			}
			else
				system("cls");
			break;
		default:
			cout << "Falsche Eingabe!\n";
			break;
		};
	} while (menueAuswahl != 40);
	return 0;
}

void setzeGebaeude(int** aBaubereich) {
	//Nachfrage nach Art, Laenge, Breite und Position
	int x = 0;				//x-Koordinate
	int y = 0;				//y-Koordinate
	int laengeObjekt = 0;
	int breiteObjekt = 0;
	int gebaeudetyp = 0;

	system("cls");

	//Auswahl des Gebaeudetyps
	cout << "Waehlen Sie einen Gebaeudetyp:"
		"\n" << Gebaeudetypen::WASSERKRAFTWERK << " = Wasserkraftwerk"
		"\n" << Gebaeudetypen::WINDKRAFTWERK << " = Windkraftwerk"
		"\n" << Gebaeudetypen::SOLARPANELE << " = Solarpanele\n" << endl;
	cout << "Eingabe (1-3): ";
	cin >> gebaeudetyp;

	switch (gebaeudetyp) {
	case Gebaeudetypen::WASSERKRAFTWERK:
		cout << "Es wurde ein Wasserkraftwerk ausgewaehlt.\n" << endl;
		break;
	case Gebaeudetypen::WINDKRAFTWERK:
		cout << "Es wurde ein Windkraftwerk ausgewaehlt.\n" << endl;
		break;
	case Gebaeudetypen::SOLARPANELE:
		cout << "Es wurden Solarpanele ausgewaehlt.\n" << endl;
		break;
	default:
		cout << "Falsche Eingabe!\n" << endl;
		return;
	};

	//Groesse (Laenge und Breite) des Gebaeudes angeben
	cout << "Wie gross soll das Gebaeude sein: Laenge(1-" << laengeBaubereich << ") x Breite(1-" << breiteBaubereich << ")\n"
		"Laenge: ";
	cin >> laengeObjekt;
	cout << "Breite: ";
	cin >> breiteObjekt;
	cout << "Das Objekt ist also: " << laengeObjekt << "x" << breiteObjekt << "\n" << endl;

	//Pruefung: Falls eingegebene Werte ausserhalb des Zulaessigkeitsbereichs liegen (1 < x < Baubereich)
	if (laengeObjekt < 1 || laengeObjekt > laengeBaubereich || breiteObjekt < 1 || breiteObjekt > breiteBaubereich) {
		cout << "Das Gebaeude (Laenge UND Breite) muss mind. 1 sein und darf nicht groesser als der Bauplan (" << laengeBaubereich << "x" << breiteBaubereich << ") sein!"
			"\nVorgang wird abgebrochen.\n" << endl;
		return;
	}

	//Gebaeude an Position (Koordinaten) setzen
	cout << "### Gebaeude setzen ###\n"
		"Koordinaten innerhalb des definierten Baubereichs (x = 0-" << laengeBaubereich - 1 << " | y = 0-" << breiteBaubereich - 1 << ") eingeben:\n"
		"x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "Es wurden folgende Koordinaten gewaehlt (x|y): (" << x << "|" << y << ")\n" << endl;

	//Pruefung: Falls eingegebene Koordinaten ausserhalb des Zulaessigkeitsbereichs liegen (0 < x < Baubereich)
	if (x < 0 || x >(laengeBaubereich - 1) || y < 0 || y >(breiteBaubereich - 1)) {
		cout << "Falsche Eingabe der Koordinaten (zugelassen: x = 0-" << laengeBaubereich - 1 << " | y = 0-" << breiteBaubereich - 1 << ")!"
			"\nVorgang wird abgebrochen.\n" << endl;
		return;
	}

	//Pruefung: Falls Gebaeude ueber den Baubereich hinausgeht
	if ((x + laengeObjekt) > laengeBaubereich) {
		cout << "Laenge des Objekts geht ueber den Baubereich an der x-Seite hinaus.\nVorgang wird abgebrochen.\n" << endl;
		return;
	}
	if ((y + breiteObjekt) > breiteBaubereich) {
		cout << "Breite des Objekts geht ueber den Baubereich an der y-Seite hinaus.\nVorgang wird abgebrochen.\n" << endl;
		return;
	}

	//Pruefung: Falls Teile eines zu bauenden Gebaeudes mit anderen Gebaeuden kollidiert
	int tempX = x;		//zum Speichern des aktuellen x-Wertes, sodass die eig. Koordinate erhalten bleibt
	int tempY = y;		//zum Speichern des aktuellen y-Wertes, sodass die eig. Koordinate erhalten bleibt
	for (int i = 0; i < laengeObjekt; i++) {
		if (aBaubereich[tempX][tempY] != Gebaeudetypen::LEER) {
			cout << "Zu bauendes Gebaeude wuerde mit einem anderen Gebaeude an Stelle: (" << tempX << "|" << tempY << ") kollidieren.\n"
				"Daher wird der Vorgang abgebrochen.\n" << endl;
			return;
		}
		for (int j = 0; j < breiteObjekt; j++) {
			if (aBaubereich[tempX][tempY] != Gebaeudetypen::LEER) {
				cout << "Zu bauendes Gebaeude wuerde mit einem anderen Gebaeude an Stelle: (" << tempX << "|" << tempY << ") kollidieren.\n"
					"Daher wird der Vorgang abgebrochen.\n" << endl;
				return;
			}
			tempY++;
		}
		tempY = y;
		tempX++;
	}

	//Uebersicht der eingegebenen Daten anzeigen
	system("cls");
	cout << "### Uebersicht der Angaben ###" << endl;
	cout << "Gebaeudeart: " << gebaeudetyp << endl;
	cout << "Groesse: " << laengeObjekt << "x" << breiteObjekt << endl;
	cout << "KO: (" << x << "|" << y << ")\n" << endl;

	//Setzen der Felder des Baubereichs mit entsprechender Gebaeudezahl (1, 2 oder 3)
	tempX = x;		//zum Speichern des aktuellen x-Wertes, sodass die eig. Koordinate erhalten bleibt
	tempY = y;		//zum Speichern des aktuellen y-Wertes, sodass die eig. Koordinate erhalten bleibt
	for (int i = 0; i < laengeObjekt; i++) {
		aBaubereich[tempX][tempY] = gebaeudetyp;
		for (int j = 0; j < breiteObjekt; j++) {
			aBaubereich[tempX][tempY] = gebaeudetyp;
			tempY++;
		}
		tempY = y;
		tempX++;
	}
}

void loescheBereich(int** aBaubereich) {
	//Gebaeude sollen nicht geloescht, sondern nur verkleinert werden

	//Bereich auswählen: Nachfrage nach Laenge, Breite und Position
	int x = 0;				//x-Koordinate
	int y = 0;				//y-Koordinate
	int laengeBereich = 0;
	int breiteBereich = 0;

	system("cls");

	//Groesse (Laenge und Breite) des zu loeschenden Bereichs angeben
	cout << "### Bereich loeschen ###\n"
		"Wie gross soll der zu loeschende Bereich sein: Laenge(1-" << laengeBaubereich << ") x Breite(1-" << breiteBaubereich << ")\n"
		"Laenge: ";
	cin >> laengeBereich;
	cout << "Breite: ";
	cin >> breiteBereich;
	cout << "Der Bereich ist: " << laengeBereich << "x" << breiteBereich << "\n" << endl;

	//Bereich an Position (Koordinaten) setzen
	cout << "Koordinaten innerhalb des definierten Baubereichs (x = 0-" << laengeBaubereich - 1 << " | y = 0-" << breiteBaubereich - 1 << ") eingeben:\n"
		"x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "Es wurden folgende Koordinaten gewaehlt (x, y): (" << x << "," << y << ")\n" << endl;

	//Setzen der Felder des zu loeschenden Bereichs auf Gebaeudetypen::LEER
	if (laengeBereich < 1 || breiteBereich < 1) {
		cout << "Der Bereich (Laenge UND Breite) muss mind. 1 sein!\nFalsche Werte werden entsprechend auf 1 angepasst." << endl;
		if (laengeBereich < 1)
			laengeBereich = 1;
		if (breiteBereich < 1)
			breiteBereich = 1;
	}
	if (laengeBereich == 1 && breiteBereich == 1)
		aBaubereich[x][y] = Gebaeudetypen::LEER;
	else {
		int tempX = x;		//zum Speichern des aktuellen x-Wertes
		int tempY = y;		//zum Speichern des aktuellen y-Wertes
		for (int i = 0; i < laengeBereich; i++) {
			aBaubereich[tempX][tempY] = Gebaeudetypen::LEER;
			for (int j = 0; j < breiteBereich; j++) {
				aBaubereich[tempX][tempY] = Gebaeudetypen::LEER;
				tempY++;
			}
			tempY = y;
			tempX++;
		}
	}
}

void zeigeBauplan(int** aBaubereich) {
	//Ausgeben des aktuellen Bauplans
	system("cls");
	cout << "Die Landflaeche sieht aktuell wie folgt aus:\n"
		"0 = Leer\n"
		"1 = Wasserkraftwerk\n"
		"2 = Windkraftwerk\n"
		"3 = Solarpanele\n\n";

	cout << "   # ";
	for (int ko = 0; ko < breiteBaubereich; ko++)
		cout << "y" << ko << " ";
	cout << "\n#####";
	for (int ko = 0; ko < breiteBaubereich; ko++)
		cout << "###";
	cout << endl;
	for (int i = 0; i < laengeBaubereich; i++) {
		cout << "x" << i << " # ";
		for (int j = 0; j < breiteBaubereich; j++) {
			cout << aBaubereich[i][j] << "  ";
		}
		cout << "\n";
	}
	cout << "\n" << endl;
}
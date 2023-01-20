/*
Fortgeschrittene Programmierung
HS-Coburg
Johnny Mueller
Projekt "Capycity"
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;

int laengeBaubereich;
int breiteBaubereich;
//enum Gebaeudetypen { LEER, WASSERKRAFTWERK, WINDKRAFTWERK, SOLARPANELE };		//0 = kein Gebaeude, 1 = Wasserkraftwerk, 2 = Windkraftwerk, 3 = Solarpanele
//enum Materialien { HOLZ, METALL, KUNSTSTOFF };									//0 = Holz, 1 = Metall, 2 = Kunststoff


// ---------------------------------------------------------------------------
// Klassen fuer Materialien
// 0 = Holz, 1 = Metall, 2 = Kunststoff
// ---------------------------------------------------------------------------
class CMaterial {};

class CHolz : public CMaterial
{
private:
	double price;
	string matName;

public:
	CHolz() : price(70.7), matName("Holz") {
		//cout << "Es wurde " << matName << " gewaehlt." << endl;
	}

	string getName() { return matName; }
	double getPrice() { return price; }
};

class CMetall : public CMaterial
{
private:
	double price;
	string matName;

public:
	CMetall() : price(80.8), matName("Metall") {
		//cout << "Es wurde " << matName << " gewaehlt." << endl;
	}

	string getName() { return matName; }
	double getPrice() { return price; }
};

class CKunststoff : public CMaterial
{
private:
	double price;
	string matName;

public:
	CKunststoff() : price(60.6), matName("Kunststoff") {
		//cout << "Es wurde " << matName << " gewaehlt." << endl;
	}

	string getName() { return matName; }
	double getPrice() { return price; }
};

// ---------------------------------------------------------------------------
// Klassen fuer Gebaeude
// 0 = kein Gebaeude, 1 = Wasserkraftwerk, 2 = Windkraftwerk, 3 = Solarpanele
// Zu Aufgabe aus Kapitel 3: "Gib an für welche Idee du dich entschieden hast und warum."
// Haette ich mehr Zeit gehabt bzw. frueher angefangen, haette ich mich fuer Carlas Variante entschieden und die Verwaltung innerhalb der Gebaeude implementiert.
// Leider hab ich das nicht mehr richtig hinbekommen und dann nur eine "abgespeckte" Variante, aber trotzdem mittels Maps, implementiert.
// 
// Grund fuer Carlas Variante:
// Weil ich es uebersichtlicher gefunden haette und die benoetigten Materialien eig. immer gleich sind, wenn es einmal definiert wurde, also weil die
// Gebaeude ja immer aus den gleichen Materialien gebaut werden und sich das selten aendert.
// Zudem stimme ich Carla zu, dass man dann irgendwann alle Informationen auslagern koennte/wuerde und somit die Kapselung darunter leidet.
// ---------------------------------------------------------------------------
class CBuilding {};

class CWasserkraftwerk : public CBuilding {
public:
	double grundpreis;
	string label;
	string name;
	map<int, string> benMaterialMap;
	vector<string> benMaterial;		//Array bzw. Vektor fuer die benoetigten Materialien

	CWasserkraftwerk() : grundpreis(800.0), label("WASS"), name("Wasserkraftwerk") { }

	string getLabel() const { return label; }
	string getName() const { return name; }
	double getGrundpreis() const { return grundpreis; }

	vector<string> getBenMaterial() {
		// 1 Gebaeude benoetigt 2x Holz, 1x Metall, 1x Kunststoff
		benMaterial.push_back("Holz");
		benMaterial.push_back("Holz");
		benMaterial.push_back("Metall");
		benMaterial.push_back("Kunststoff");
		return benMaterial;
	}

	map<int, string> getBenMaterialMap() {
		benMaterialMap[0] = "Holz";
		benMaterialMap[1] = "Holz";
		benMaterialMap[2] = "Metall";
		benMaterialMap[3] = "Kunststoff";
		return benMaterialMap;
	}
};

class CWindkraftwerk : public CBuilding {
public:
	double grundpreis;
	string label;
	string name;
	map<int, string> benMaterialMap;
	vector<string> benMaterial;		//Array bzw. Vektor fuer die benoetigten Materialien

	CWindkraftwerk() : grundpreis(900.0), label("WIND"), name("Windkraftwerk") {}

	string getLabel() const { return label; }
	string getName() const { return name; }
	double getGrundpreis() const { return grundpreis; }

	vector<string> getBenMaterial() {
		// 1 Gebaeude benoetigt 1x Holz, 2x Metall, 1x Kunststoff
		benMaterial.push_back("Holz");
		benMaterial.push_back("Metall");
		benMaterial.push_back("Metall");
		benMaterial.push_back("Kunststoff");
		return benMaterial;
	}

	map<int, string> getBenMaterialMap() {
		benMaterialMap[0] = "Holz";
		benMaterialMap[1] = "Metall";
		benMaterialMap[2] = "Metall";
		benMaterialMap[3] = "Kunststoff";
		return benMaterialMap;
	}
};

class CSolarpanele : public CBuilding {
public:
	double grundpreis;
	string label;
	string name;
	map<int, string> benMaterialMap;
	vector<string> benMaterial;		//Array bzw. Vektor fuer die benoetigten Materialien

	CSolarpanele() : grundpreis(700.0), label("SOLA"), name("Solarpanele") {}

	string getLabel() const { return label; }
	string getName() const { return name; }
	double getGrundpreis() const { return grundpreis; }

	vector<string> getBenMaterial() {
		// 1 Gebaeude benoetigt 1x Holz, 1x Metall, 2x Kunststoff
		benMaterial.push_back("Holz");
		benMaterial.push_back("Metall");
		benMaterial.push_back("Kunststoff");
		benMaterial.push_back("Kunststoff");
		return benMaterial;
	}

	map<int, string> getBenMaterialMap() {
		benMaterialMap[0] = "Holz";
		benMaterialMap[1] = "Metall";
		benMaterialMap[2] = "Kunststoff";
		benMaterialMap[3] = "Kunststoff";
		return benMaterialMap;
	}
};

// ---------------------------------------------------------------------------
// Klassen zur Gebaeudeverwaltung
// setzeGebaeude
// loescheBereich
// loescheBereich
// zeigeBauplan
// ---------------------------------------------------------------------------
class CapycitySim
{
public:
	static void setzeGebaeude(int** aBaubereich) {
		//Nachfrage nach Art, Laenge, Breite und Position
		int x = 0;				//x-Koordinate
		int y = 0;				//y-Koordinate
		int laengeObjekt = 0;
		int breiteObjekt = 0;
		int gebaeudetyp = 0;
		CWasserkraftwerk oWaKw;
		CWindkraftwerk oWiKw;
		CSolarpanele oSoPn;
		string getGebaeudeName;

		system("cls");

		//Auswahl des Gebaeudetyps
		cout << "Waehlen Sie einen Gebaeudetyp:"
			"\n" << "1 = " << oWaKw.getName() <<
			"\n" << "2 = " << oWiKw.getName() <<
			"\n" << "3 = " << oSoPn.getName() << "\n" << endl;
		cout << "Eingabe (1-3): ";
		cin >> gebaeudetyp;

		switch (gebaeudetyp) {
		case 1:	//Wasser
			getGebaeudeName = oWaKw.getName();
			break;
		case 2: //Wind
			getGebaeudeName = oWiKw.getName();
			break;
		case 3: //Solar
			getGebaeudeName = oSoPn.getName();
			break;
		default:
			cout << "Falsche Eingabe!\n" << endl;
			return;
		};
		cout << "Es wurde ein " << getGebaeudeName << " ausgewaehlt.\n" << endl;

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
			if (aBaubereich[tempX][tempY] != 0) {	//0 = LEER
				cout << "Zu bauendes Gebaeude wuerde mit einem anderen Gebaeude an Stelle: (" << tempX << "|" << tempY << ") kollidieren.\n"
					"Daher wird der Vorgang abgebrochen.\n" << endl;
				return;
			}
			for (int j = 0; j < breiteObjekt; j++) {
				if (aBaubereich[tempX][tempY] != 0) {	//0 = LEER
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
		cout << "Gebaeudeart: " << gebaeudetyp << " (" << getGebaeudeName << ")" << endl;
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

	static void loescheBereich(int** aBaubereich) {
		//Gebaeude sollen nicht komplett geloescht werden, sondern nur verkleinert werden

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
			aBaubereich[x][y] = 0;	//0 = LEER
		else {
			int tempX = x;		//zum Speichern des aktuellen x-Wertes
			int tempY = y;		//zum Speichern des aktuellen y-Wertes
			for (int i = 0; i < laengeBereich; i++) {
				aBaubereich[tempX][tempY] = 0;	//0 = LEER
				for (int j = 0; j < breiteBereich; j++) {
					aBaubereich[tempX][tempY] = 0;	//0 = LEER
					tempY++;
				}
				tempY = y;
				tempX++;
			}
		}
	}

	static void zeigeBauplan(int** aBaubereich) {
		//Ausgeben des aktuellen Bauplans
		int countLeer = 0;
		int countWasser = 0;
		int countWind = 0;
		int countSolar = 0;
		CWasserkraftwerk oWaKw;
		CWindkraftwerk oWiKw;
		CSolarpanele oSoPn;

		system("cls");
		cout << "Die Landflaeche sieht aktuell wie folgt aus:\n"
			"0 = Leer\n"
			"1 = " << oWaKw.getName() << "\n"
			"2 = " << oWiKw.getName() << "\n"
			"3 = " << oSoPn.getName() << "\n\n";

		//Anzeige mit Nummern (kompakter)
		cout << "    # ";
		for (int ko = 0; ko < breiteBaubereich; ko++) {
			if (ko < 10)
				cout << " y" << ko << " ";
			else
				cout << "y" << ko << " ";
		}
		cout << "\n#####";
		for (int ko = 0; ko < breiteBaubereich; ko++)
			cout << "####";
		cout << endl;
		for (int i = 0; i < laengeBaubereich; i++) {
			if (i < 10)
				cout << " x" << i << " # ";
			else
				cout << "x" << i << " # ";
			for (int j = 0; j < breiteBaubereich; j++) {
				cout << " " << aBaubereich[i][j] << "  ";
			}
			cout << "\n";
		}
		cout << endl;

		//Anzeige mit Labels
		cout << "+++ Anzeige mit Labels +++" << endl;
		cout << "    # ";
		for (int ko = 0; ko < breiteBaubereich; ko++) {
			if (ko < 10)
				cout << " y" << ko << "  ";
			else
				cout << " y" << ko << " ";
		}
		cout << "\n#####";
		for (int ko = 0; ko < breiteBaubereich; ko++)
			cout << "#####";
		cout << endl;
		for (int i = 0; i < laengeBaubereich; i++) {
			if (i < 10)
				cout << " x" << i << " # ";
			else
				cout << "x" << i << " # ";
			for (int j = 0; j < breiteBaubereich; j++) {
				if (aBaubereich[i][j] == 0) {	//0 = LEER
					cout << "  -  ";
					countLeer++;
				}
				if (aBaubereich[i][j] == 1) {	//1 = WASSERKRAFTWERK
					cout << CWasserkraftwerk().getLabel() << " ";
					countWasser++;
				}
				if (aBaubereich[i][j] == 2) {	//2 = WINDKRAFTWERK
					cout << CWindkraftwerk().getLabel() << " ";
					countWind++;
				}
				if (aBaubereich[i][j] == 3) {	//3 = SOLARPANELE
					cout << CSolarpanele().getLabel() << " ";
					countSolar++;
				}
			}
			cout << "\n";
		}
		cout << endl;

		// Auflistung der gebauten Gebaeude, benoetigte Materialien und Preise
		cout << "### Auflistung der Gebaeude ###" << endl;

		//Daten aus den Klassen/Funktionen holen und in entsprechende Variablen speichern
		CWasserkraftwerk oWasser;
		map<int, string> benMatWasser = oWasser.getBenMaterialMap();
		//vector<string> benMatWasser = oWasser.getBenMaterial();
		double priceWasser = oWasser.getGrundpreis();

		CWindkraftwerk oWind;
		map<int, string> benMatWind = oWind.getBenMaterialMap();
		//vector<string> benMatWind = oWind.getBenMaterial();
		double priceWind = oWind.getGrundpreis();

		CSolarpanele oSolar;
		map<int, string> benMatSolar = oSolar.getBenMaterialMap();
		//vector<string> benMatSolar = oSolar.getBenMaterial();
		double priceSolar = oSolar.getGrundpreis();

		CHolz oHolz;
		double priceHolz = oHolz.getPrice();
		CMetall oMetall;
		double priceMetall = oMetall.getPrice();
		CKunststoff oKunststoff;
		double priceKunststoff = oKunststoff.getPrice();

		//Ausgabe der Daten in den Vektoren und Berechnung der Preise
		cout.precision(2);
		cout << countLeer << "x Leer" << endl;
		//Wasserkraftwerke
		if (countWasser == 0)
			cout << countWasser << "x " << oWasser.getName() << endl;
		else {
			cout << countWasser << "x " << oWasser.getName() << ":\t";
			for (int i = 0; i < benMatWasser.size(); i++) {
				if (benMatWasser[i] == "Holz")
					priceWasser += priceHolz;
				if (benMatWasser[i] == "Metall")
					priceWasser += priceMetall;
				if (benMatWasser[i] == "Kunststoff")
					priceWasser += priceKunststoff;
				if (i == (benMatWasser.size() - 1))
					cout << benMatWasser[i] << "\t\t(EPreis: " << fixed << priceWasser << " Euro)\n";
				else
					cout << benMatWasser[i] << ", ";
			}
		}
		//Windkraftwerke
		if (countWind == 0)
			cout << countWind << "x " << oWind.getName() << endl;
		else {
			cout << countWind << "x " << oWind.getName() << ":\t";
			for (int i = 0; i < benMatWind.size(); i++) {
				if (benMatWind[i] == "Holz")
					priceWind += priceHolz;
				if (benMatWind[i] == "Metall")
					priceWind += priceMetall;
				if (benMatWind[i] == "Kunststoff")
					priceWind += priceKunststoff;
				if (countWind == 0)
					cout << "";
				else if (i == (benMatWind.size() - 1))
					cout << benMatWind[i] << "\t(EPreis: " << fixed << priceWind << " Euro)\n";
				else
					cout << benMatWind[i] << ", ";
			}
		}
		//Solarpanele
		if (countSolar == 0)
			cout << countSolar << "x " << oSolar.getName() << endl;
		else {
			cout << countSolar << "x " << oSolar.getName() << ":\t\t";
			for (int i = 0; i < benMatSolar.size(); i++) {
				if (benMatSolar[i] == "Holz")
					priceSolar += priceHolz;
				if (benMatSolar[i] == "Metall")
					priceSolar += priceMetall;
				if (benMatSolar[i] == "Kunststoff")
					priceSolar += priceKunststoff;
				if (countSolar == 0)
					cout << "";
				else if (i == (benMatSolar.size() - 1))
					cout << benMatSolar[i] << "\t(EPreis: " << fixed << priceSolar << " Euro)\n";
				else
					cout << benMatSolar[i] << ", ";
			}
		}
		cout << "\n=== Gesamtpreis aller Gebaeude:\t" << fixed << (countWasser * priceWasser) + (countWind * priceWind) + (countSolar * priceSolar) << " Euro ===" << endl;
		cout << endl;
	}
};

// ---------------------------------------------------------------------------
// MAIN
// ---------------------------------------------------------------------------
int main()
{
	//Deklaration der Variablen
	int menueAuswahl = 0;	//zur Auswahl im Menue
	char sicher = 'n';		//fuer die Sicherheitsabfrage, ob wirklich beendet werden soll

	/*	//Deklaration der Funktionen
	void CapycitySim::setzeGebaeude(int**);		//Nachfrage nach Art, Laenge, Breite und Position
	void loescheBereich(int**);					//Gebaeude sollen nicht geloescht, sondern nur verkleinert werden
	void zeigeBauplan(int**);					//Ausgeben des aktuellen Bauplans
	void beendeProgramm();						//Beenden des Programms		*/

	//Eingabe von Laenge und Breite fuer den Baubereich
	cout << "Hello Capycity!\n### Definition des gesamten Baubereichs ###" << endl;
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
			aBaubereich[i][j] = 0;	//0 = LEER

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
			CapycitySim::setzeGebaeude(aBaubereich);
			break;
		case 2:
			CapycitySim::loescheBereich(aBaubereich);
			break;
		case 3:
			CapycitySim::zeigeBauplan(aBaubereich);
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
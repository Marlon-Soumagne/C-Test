#include <chrono>
#include <conio.h> // für _kbhit() und _getch()
#include <iostream>
#include <locale>
#include <string>
#include <thread>

static void clearScreen()
{
	std::cout << "\033[2J\033[1;1H"; 
}

void slowPrint(const std::string& text, int delay_ms = 30)
{
    for (size_t i = 0; i < text.size(); i++) {
        std::cout << text[i] << std::flush;

        // Prüft ob eine Taste gedrückt wurde
        if (_kbhit()) {
            // Taste einlesen, um sie zu entfernen 
            int ch = _getch();
            (void)ch;
            // Rest des Textes sofort ausgeben
            std::cout << text.substr(i + 1) << std::flush;
            break; // Schleife verlassen
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}


bool kampfStarten(
    int& leben,
    int& energie,
	int beweglichkeit,
    int stearke,
    int stearke1,
    int verteidigung,
    int kampfkraft,
    int& leben1,
    int verteidigung1,
    int kampfkraft1,
    int energie1
)
{
    const int KOSTEN_ANGRIFF = 15;
    const int KOSTEN_STARK = 35;

    while (true) {

        slowPrint("\n=====================\n");
        slowPrint("Monster Leben: " + std::to_string(leben1) + "\n");
        slowPrint("Dein Leben: " + std::to_string(leben) + "\n");
        slowPrint("Deine Energie: " + std::to_string(energie) + "\n");
        slowPrint("=====================\n");

        slowPrint("\nAktion wählen:\n");
        slowPrint("A = Angriff\n");
        slowPrint("S = Starker Angriff\n");
        slowPrint("E = Energie sammeln\n");

        char eingabe;
        if (!(std::cin >> eingabe)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            slowPrint("Ungültige Eingabe!\n");
            continue;
        }

        // SPIELER 
        if (eingabe == 'a' || eingabe == 'A') {
            if (energie < KOSTEN_ANGRIFF) {
                slowPrint("Nicht genug Energie!\n");
                continue;
            }
            energie -= KOSTEN_ANGRIFF;
            
            int effektivschaden = static_cast<int>((stearke * 10) * (100.0 / (100.0 + verteidigung1)));
            leben1 -= effektivschaden;
        
            slowPrint("Du hast " + std::to_string(effektivschaden) + " Schaden gemacht!");
        }
        else if (eingabe == 's' || eingabe == 'S') {
            if (energie < KOSTEN_STARK) {
                slowPrint("Nicht genug Energie!\n");
                continue;
            }
            energie -= KOSTEN_STARK;
            
            int effektivschadenS = static_cast<int>(kampfkraft * (100.0 / (100.0 + verteidigung1)));
            leben1 -= effektivschadenS;

            slowPrint("Du hast " + std::to_string(effektivschadenS) + " Schaden gemacht!");
        }
        else if (eingabe == 'e' || eingabe == 'E') {
            energie += 20;
            if (energie > 100) energie = 100;
        }
        else {
            slowPrint("Ungültige Eingabe!\n");
            continue;
        }

        //  Mosnter tot 
        if (leben1 <= 0) {
            slowPrint("\nDas Monster wurde besiegt!\n");
            return true;   // Spieler gewinnt
        }

        // Monster greift an

        int monsterSchaden = static_cast<int>((stearke1 * 10) * (100.0 / (100.0 + verteidigung)));
        int zufallswert = rand() % 100;
        int ausweichChance = beweglichkeit * 10;

        if (zufallswert < ausweichChance)
        {
            slowPrint("Du bist dem Angriff ausgewichen!\n");
        }
        else
        {
            leben -= monsterSchaden;
            energie -= 10;

            if (energie < 0)
                energie = 0;

            slowPrint("Das Monster hat angegriffen... Du hast "
                + std::to_string(monsterSchaden) + " Schaden erlitten!\n");
        }


        if (leben <= 0) {
            slowPrint("\nDu wurdest besiegt...\n");
            return false;  // Spieler verliert
        }
    }
}


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    std::locale::global(std::locale("de_DE.UTF-8"));

    //Skills 
    int intelligenz = 1;
    int stearke = 1;
    int verteidigung = 1;
    int beweglichkeit = 1;
    int leben = 100;
    int energie = 100;

    //Ressourcen
    int chemie = 0;
    int kampfkraft = 0;
    int ressourcen = 0;

    //Funktionen
    int schwierigkeit, charakter, start;
    std::string name;


    //Monster Werte Einäugig 
    int intelligenz1 = 2;
    int stearke1 = 4;
    int verteidigung1 = 3;
    int beweglichkeit1 = 2;
    int leben1 = 100;
    int energie1 = 30;
    int kampfkraft1 = 90;

    //Energiekosten
    const int KOSTEN_ANGRIFF = 15;
    const int KOSTEN_STARK = 35;

    slowPrint("Wie lautet Ihr Charaktername?\n", 30);
    std::cin >> name;
    slowPrint("\nHallo " + name + ", bereit für den Kampf?\n", 30);

    // Schwierigkeit
    schwierigkeit = 0;
    while (true) {
        std::cout << "\nBitte wähle deine Schwierigkeit:\n";
        std::cout << "1 = Einsteiger\n2 = Fortgeschritten\n3 = Experte\n";
        if (!(std::cin >> schwierigkeit)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            slowPrint("Ungültige Eingabe!\n");
            continue;
        }

        if (schwierigkeit == 1) {
            std::cout << "\nEinsteiger gewählt\n";
            intelligenz1 = 2;
            stearke1 = 4;
            verteidigung1 = 3;
            beweglichkeit1 = 2;
            leben1 = 120;
            energie1 = 30;
            kampfkraft1 = 90;
            break; // gültige Wahl, Schleife verlassen
        }
        else if (schwierigkeit == 2) {
            std::cout << "\nFortgeschritten gewählt\n";
            intelligenz1 = 3;
            stearke1 = 5;
            verteidigung1 = 4;
            beweglichkeit1 = 3;
            leben1 = 240;
            energie1 = 45;
            kampfkraft1 = 135;
            break;
        }
        else if (schwierigkeit == 3) {
            std::cout << "\nExperte gewählt\n";
            intelligenz1 = 4;
            stearke1 = 6;
            verteidigung1 = 5;
            beweglichkeit1 = 4;
            leben1 = 360;
            energie1 = 60;
            kampfkraft1 = 210;
            break;
        }
        else {
            std::cout << "Ungültige Schwierigkeit! Bitte erneut versuchen.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }




    // Charakter-Erstellung (Schleife)
    bool gameLoop = true;
    while (gameLoop) {
        bool fertig = false;
        while (!fertig) {



            std::cout << "\nErstelle deinen Charakter!\n";
            slowPrint("Wähle deinen Story-Hintergrund:\n\n");

            slowPrint("1) Der Wissenschaftler\n", 120);
            slowPrint("Ein Wissenschaftler mit außergewöhnlicher Intelligenz.\n");
            slowPrint("Früh vom Militär entdeckt und von seiner Familie getrennt,\n");
            slowPrint("wurde er dazu erzogen, sein Land zur stärksten Macht zu machen.\n");
            slowPrint("Intelligenz: 9 | Stärke: 2 | Verteidigung: 3 | Beweglichkeit: 4\n\n");

            slowPrint("2) Der Soldat\n", 120);
            slowPrint("Sohn eines gefallenen Kriegshelden.\n");
            slowPrint("Schon früh hartes Training, geführt vom Erbe seines Vaters.\n");
            slowPrint("Ein geborener Krieger und Anführer.\n");
            slowPrint("Intelligenz: 2 | Stärke: 8 | Verteidigung: 5 | Beweglichkeit: 3\n\n");

            slowPrint("3) Der Wanderer\n", 120);
            slowPrint("In Armut geboren, lernte er früh zu überleben.\n");
            slowPrint("Kein großer Kämpfer, kein Gelehrter, aber ein Meister des Überlebens.\n");
            slowPrint("Durch List und Taktik kämpfte er sich nach oben.\n");
            slowPrint("Intelligenz: 5 | Stärke: 3 | Verteidigung: 3 | Beweglichkeit: 7\n\n");

            if (!(std::cin >> charakter)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                slowPrint("1 = Intelligenz\n2 = Stärke\n3 = Verteidigung\n4 = Beweglichkeit\n");
                slowPrint("Ungültige Eingabe!\n");
                continue;
            }

            switch (charakter) {
            case 1:

                slowPrint("\nDu hast den Wissenschaftler gewählt.\n");
                //Skills
                intelligenz = 9;
                stearke = 2;
                verteidigung = 3;
                beweglichkeit = 4;
                leben = 100;
                energie = 100;
                //Ressourcen
                chemie = 90;
                kampfkraft = 45;
                ressourcen = 40;
                fertig = true;
                break;

            case 2:

                slowPrint("\nDu hast den Soldaten gewählt.\n");
                //Skills
                intelligenz = 2;
                stearke = 8;
                verteidigung = 5;
                beweglichkeit = 3;
                leben = 100;
                energie = 100;
                //Ressourcen
                chemie = 20;
                kampfkraft = 80;
                ressourcen = 30;
                fertig = true;
                break;

            case 3:

                slowPrint("\nDu hast den Wanderer gewählt.\n");
                //Skills
                intelligenz = 5;
                stearke = 3;
                verteidigung = 3;
                beweglichkeit = 7;
                leben = 100;
                energie = 100;
                //Ressourcen
                chemie = 50;
                kampfkraft = 65;
                ressourcen = 70;
                fertig = true;
                break;

            default:
                slowPrint("Ungültige Auswahl!\n");
                continue;
            }
        }

        std::cout << ("\nDeine Werte:\n");
        slowPrint("Intelligenz: " + std::to_string(intelligenz) + "\n");
        slowPrint("Stärke: " + std::to_string(stearke) + "\n");
        slowPrint("Verteidigung: " + std::to_string(verteidigung) + "\n");
        slowPrint("Beweglichkeit: " + std::to_string(beweglichkeit) + "\n");
        slowPrint("Kampfkraft: " + std::to_string(kampfkraft) + "\n");


        // Bestätigung mit Neu-Wählen-Option
        bool startspiel = false;
        while (!startspiel)
        {
            std::cout << "\n1 = Starten\n2 = Neu wählen\n";

            if (!(std::cin >> start)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                slowPrint("Ungültige Eingabe!\n");
                continue;
            }
            if (start == 1) {
                startspiel = true;
                gameLoop = false;  // Charakter bestätigt, Spiel startet
            }
            else if (start == 2) {
                break;  // Zurück zur Charakter-Erstellung
            }
            else {
                slowPrint("Ungültige Eingabe!\n");
            }
        }
    }
    slowPrint("\nSpiel startet... Viel Erfolg, " + name + "!\n");

    clearScreen();

    slowPrint("\nStarten...");
    slowPrint("....", 270);
    slowPrint("......", 60);
    slowPrint("...", 60);
    slowPrint(".....", 270);

    clearScreen();

    slowPrint("\nDu befindest dich in einer Verlassenen Stadt, vor dir ist ein einäugiges Monster, mach dich für den Kampf bereit.\n");

    std::cout << ("\nMonster Werte:\n");
    slowPrint("Intelligenz: " + std::to_string(intelligenz1) + "\n");
    slowPrint("Stärke: " + std::to_string(stearke1) + "\n");
    slowPrint("Verteidigung: " + std::to_string(verteidigung1) + "\n");
    slowPrint("Beweglichkeit: " + std::to_string(beweglichkeit1) + "\n");
    slowPrint("Kampfkraft: " + std::to_string(kampfkraft1) + "\n");


    slowPrint("\nDu wirst angegriffen und weichst aus. Jetzt bist du dran!\n");


    bool kampf = true;

    bool spielerGewonnen = kampfStarten(
        leben,
        energie,
        beweglichkeit,
        stearke,
        stearke1,
        verteidigung,
        kampfkraft,
        leben1,
        verteidigung1,
        kampfkraft1,
        energie1
    );
    if (spielerGewonnen) {

        slowPrint("\nDu hast den Kampf überlebt!\n");
        slowPrint("Jetzt kannst du leveln!\n");

        bool upgradefertig = false;
        while (!upgradefertig)
        {

            slowPrint("\nDir steht: 1 level punkt zur verfügung\n");

            slowPrint("\nWas möchtesst du leveln?\n");

            slowPrint("\nDeine Werte:\n");
            slowPrint("Intelligenz: " + std::to_string(intelligenz) + "\n");
            slowPrint("Stärke: " + std::to_string(stearke) + "\n");
            slowPrint("Verteidigung: " + std::to_string(verteidigung) + "\n");
            slowPrint("Beweglichkeit: " + std::to_string(beweglichkeit) + "\n");

            int upgrade = 0;

            if (!(std::cin >> upgrade)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                slowPrint("Ungültige Eingabe!\n");
                continue;
            }

            if (upgrade == 1) {
                intelligenz += 1;
                slowPrint("\nDu hast 1 Punkt in Intelligenz gesetzt!\n");                  
                upgradefertig = true;
            }
            else if (upgrade == 2) {
                stearke += 1;
                slowPrint("\nDu hast 1 Punkt in Stärke gesetzt!\n");
                upgradefertig = true;
            }
            else if (upgrade == 3) {
                verteidigung += 1;
                slowPrint("\nDu hast 1 Punkt in Verteidigung gesetzt!\n");
                upgradefertig = true;
            }
            else if (upgrade == 4) {
                beweglichkeit += 1;
                slowPrint("\nDu hast 1 Punkt in Beweglichkeit gesetzt!\n");
                upgradefertig = true;
            }
            else {
                std::cout << "Ungültige Eingabe! Bitte erneut versuchen.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        slowPrint("\nDeine Neuen Werte:\n");
        slowPrint("Intelligenz: " + std::to_string(intelligenz) + "\n");
        slowPrint("Stärke: " + std::to_string(stearke) + "\n");
        slowPrint("Verteidigung: " + std::to_string(verteidigung) + "\n");
        slowPrint("Beweglichkeit: " + std::to_string(beweglichkeit) + "\n");
    }
    else {

        slowPrint("Du konntest mit schweren verletzungen entkommen!\n");


    }

    slowPrint("Das tutorial ist beendet!\n");
    slowPrint("Jetzt beginnt die story...\n");

	slowPrint("\nDrücke Enter um fortzufahren...\n");
	std::cin.get(); // Warten auf Enter
    clearScreen();

    slowPrint("Vor 31 Stunden traf ein Metheor den uns bekannten Planeten Erde.\n");

    slowPrint("Uns unbekannte Monster haben den Planeten besiedelt...\n");
    slowPrint("Mit den Metheor betrat auch eine giftiges Gas die Atmosphäre...\n");
    slowPrint("Erkunde die Welt, Rette sie, Überlebe sie oder Befreie sie...\n");

    slowPrint("Werde zum Held deiner eigenen Geschichte..\n");
    slowPrint("\nDu öffnest langsam die Augen...\n");
    slowPrint("Ein beißender Geruch liegt in der Luft.\n");

    slowPrint("Sirenen heulen in der Ferne, dann Stille.\n");
    slowPrint("\nDein Funkgäret rauscht..\n");
    slowPrint("\"Wenn das jemand hört... wir brauchen Hilfe...\"\n");

    slowPrint("\"Die Regierung ist gefallen... die Städte sind verloren...\"\n");
    slowPrint("\nDu blickst dich um.\n");
    slowPrint("Du bist in einer verlassenen Stadt, die Straßen sind leer.\n");

    slowPrint("Die Gebäude sind beschädigt, einige brennen sogar.\n");
    slowPrint("Etwas hat hier gejagt.\n");

    slowPrint("\nEin Husten kommt über dich.\n");
    slowPrint("Das Gas wirkt bereits auf deinen Körper.\n");

    slowPrint("\nZIEL AKTUALISIERT: \n");
    slowPrint("Finde eine Gasmaske oder einen sicheren Unterschlupf.\n");

    bool storyStadt = true;
    bool storyFunk = false;
    bool storyGebaeude = false;
    bool spielLaeuft = true;
    
    while (spielLaeuft)
    {
        if (storyStadt)
        {
            int wahl;
            slowPrint("\nDu bist in der verlassenen Stadt.\n");
            slowPrint("1) Stadt erkunden\n");
            slowPrint("2) Funksignal verfolgen\n");
            slowPrint("3) Gebäude betreten\n");

            std::cin >> wahl;

            if (wahl == 1)
            {
                slowPrint("\nDu gehst tiefer in die Stadt...\n");
				slowPrint("Du findest eine Gasmaske, aber sie ist beschädigt und unbrauchbar.\n");
				slowPrint("Du kannst sie verwerten, um deine Ressourcen zu verbessern, aber sie schützt dich nicht vor dem Gas.\n");
				int gasmaskenRessourcen = 20;
				ressourcen += gasmaskenRessourcen;
            }
            else if (wahl == 2)
            {
                storyStadt = false;
                storyFunk = true;
            }
            else if (wahl == 3)
            {
                storyStadt = false;
                storyGebaeude = true;
            }
        }

        else if (storyFunk)
        {
            int wahl;
            slowPrint("\nDas Funksignal wird stärker.\n");
            slowPrint("1) Dem Signal folgen\n");
            slowPrint("2) Zurück zur Stadt\n");

            std::cin >> wahl;

            if (wahl == 1)
            {
                slowPrint("\nEtwas antwortet aus der Dunkelheit...\n");
				slowPrint("Du erkennst in der Dunkelheit eine Gestalt, die sich dir nähert.\n");
				slowPrint("Ein Alter Mann mit einem langen Bart und einem zerfetzten Mantel steht vor dir.\n");
				slowPrint("\"Du bist nicht von hier, oder?\"\n");
				slowPrint("Der Mann bittet um hilfe,\"Bitte...ich flehe dich an hilf mir..\"\n");
                spielLaeuft = false; // Beispiel-Ende
            }
            else if (wahl == 2)
            {
                storyFunk = false;
                storyStadt = true;
            }
        }

        else if (storyGebaeude)
        {
            int wahl;
            slowPrint("\nDu betrittst ein zerfallenes Gebäude.\n");
            slowPrint("1) Dich verbarrikadieren\n");
            slowPrint("2) Zurück auf die Straße\n");

            std::cin >> wahl;

            if (wahl == 1)
            {
                slowPrint("\nDu bist vorerst sicher.\n");
                spielLaeuft = false;
            }
            else if (wahl == 2)
            {
                storyGebaeude = false;
                storyStadt = true;
            }
        }
    }




}


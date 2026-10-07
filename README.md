```markdown
# C++ Terminal Survival RPG (Kapitel 1)

Ein textbasiertes Post-Apokalypse-RPG in C++, entwickelt für die Konsole. Das Spiel kombiniert dynamische Charaktererstellung, ein rundenbasiertes Kampfsystem mit Ressourcen-Management (Leben & Energie) sowie verzweigte Story-Pfade nach einem Meteoriteneinschlag.

---

## Features

* **Charaktererstellung:** Wähle aus 3 Klassen (*Wissenschaftler*, *Soldat*, *Wanderer*) mit individuellen Attributen (Intelligenz, Stärke, Verteidigung, Beweglichkeit, Chemie, Kampfkraft, Ressourcen).
* **Rundenbasiertes Kampfsystem:**
  * Schadensberechnung unter Berücksichtigung von Rüstung/Verteidigung.
  * Ausweichchancen basierend auf der Beweglichkeit des Spielers.
  * Ressourcenmanagement (Normale/Starke Angriffe verbrauchen Energie, Energie kann im Kampf gesammelt werden).
* **Dynamisches Leveling:** Steigere nach einem Sieg gezielt deine Attribute.
* **Verzweigte Story:** Freie Entscheidungen in einer postapokalyptischen Stadt mit verschiedenen Schauplätzen und Zielen.
* **Typing-Effekt:** Textausgabe mit Tipp-Animation und Skip-Funktion per Tastendruck.

---

## Architekturübersicht

Das Projekt ist aktuell in einer monolithischen Struktur aufgebaut, um schnelles Testen und Prototyping zu ermöglichen:


```

┌─────────────────────────────────────────────────────────┐
│                      main()                             │
│  ├─ Spiel-Setup & Namenseingabe                         │
│  ├─ Schwierigkeitsgrad-Auswahl                          │
│  ├─ Charaktererstellung (Switch-Klassenwahl)            │
│  ├─ Bosskampf-Initialisierung                           │
│  └─ Story-State-Machine (Stadt / Funk / Gebäude)        │
└──────────────────────────┬──────────────────────────────┘
│
┌─────────────┴─────────────┐
▼                           ▼
┌─────────────────────┐     ┌─────────────────────┐
│   slowPrint()       │     │   kampfStarten()    │
│   - Text-Animation  │     │   - Kampf-Schleife  │
│   - _kbhit() Skip   │     │   - Formel-Berechn. │
└─────────────────────┘     └─────────────────────┘

```

### Kernkomponenten:

1. **`slowPrint(text, delay_ms)`:** 
   Gibt Zeichenfolgen zeitversetzt über `std::this_thread::sleep_for` aus. Nutzt `<conio.h>` (`_kbhit()` & `_getch()`), um die Animation bei Tastendruck sofort abzuschließen.
2. **`kampfStarten(...)`:** 
   Steuert die Kampfschleife. Berechnet den Effektivschaden nach folgender Rüstungsformel:
   $$\text{Schaden} = (\text{Stärke} \times 10) \times \left(\frac{100}{100 + \text{Verteidigung}}\right)$$
3. **Story State-Machine:** 
   Eine Schleife in `main()` nutzt boolesche Flags (`storyStadt`, `storyFunk`, `storyGebaeude`), um den Aufenthaltsort und den Handlungsfortschritt des Spielers zu verwalten.

---

## Installation & Kompilierung

### Voraussetzungen
* **Betriebssystem:** Windows (aufgrund der Verwendung von `<conio.h>`)
* **Compiler:** C++11 oder neuer (MSVC, MinGW, Clang)

### Kompilieren über die Konsole (MinGW / GCC)
```bash
g++ -std=c++11 -O2 main.cpp -o SurvivalRPG.exe

```

### Ausführen

```bash
./SurvivalRPG.exe

```

---

## Code-Beispiele

### 1. Schadensberechnung mit Rüstungsskalierung

Aus der Funktion `kampfStarten`:

```cpp
// Berechnung des Schadens unter Berücksichtigung der Gegner-Verteidigung
int effektivschaden = (staerke * 10) * (100.0 / (100.0 + verteidigung1));
leben1 -= effektivschaden;

slowPrint("Du hast " + std::to_string(effektivschaden) + " Schaden gemacht!\n");

```

### 2. Dynamischer Textdruck mit Überspringen

Nutzt Non-Blocking Key Input, um dem Spieler das Überspringen langer Texte zu ermöglichen:

```cpp
void slowPrint(const std::string& text, int delay_ms = 25) {
    for (size_t i = 0; i < text.size(); i++) {
        std::cout << text[i] << std::flush;
        
        // Wenn eine Taste gedrückt wird, Rest des Textes sofort ausgeben
        if (_kbhit()) {
            int ch = _getch();
            std::cout << text.substr(i + 1) << std::flush;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

```

### 3. Story-Schleife (State Machine)

Beispiel für den Standortwechsel in der Welt:

```cpp
if (storyStadt) {
    int wahl;
    slowPrint("\nDu bist in der verlassenen Stadt.\n");
    slowPrint("1) Stadt erkunden\n2) Funksignal verfolgen\n3) Gebäude betreten\n");
    std::cin >> wahl;

    if (wahl == 2) {
        storyStadt = false;
        storyFunk = true; // Wechselt den Ort in der nächsten Iteration
    }
}

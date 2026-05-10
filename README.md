# 3D OpenGL & SDL2 Tech Demo 

Ez egy C nyelven írt, natív 3D-s alkalmazás/játék, amely az **SDL2**-t használja az ablakkezelésre és a bemenetek olvasására, a grafikáért pedig az **OpenGL** (Fixed-Function Pipeline) felel. A projekt egy bejárható, procedurálisan generált világot mutat be, dinamikus napszak-változással és alapvető ütközésvizsgálattal.

## Fő funkciók

* **FPS Kamera:** Belső nézetes kamera, egérrel történő forgolódással és WASD mozgással.
* **Ütközésvizsgálat (Collision Detection):** A játékos nem tud átmenni a fákon, és nem tudja elhagyni a térkép határait.
* **Procedurális Domborzat:** Szinusz és koszinusz hullámok alapján generált, textúrázott 3D-s talaj.
* **Növényzet:** Véletlenszerűen, de egymást és a kezdőpontot elkerülve elhelyezett 3D-s fák.
* **Dinamikus Nappal/Éjszaka ciklus:** * Automatikus vagy manuálisan vezérelhető időmúlás.
    * Az égbolt színe és a fények (ambient/diffuse) alkalmazkodnak az időhöz.
* **OBJ Modell betöltő:** Saját írású parser a `.obj` 3D modellek (például a Nap) és a hozzájuk tartozó textúrák betöltéséhez.
* **Segédlet menü:** Játék közben gombnyomásra előhívható 2D-s overlay.

## Irányítás

A játékban az alábbi billentyűkkel tudsz navigálni és interakcióba lépni:

| Gomb | Funkció |
| :--- | :--- |
| **W, A, S, D** | Mozgás előre, balra, hátra, jobbra. |
| **Egér mozgás** | Nézelődés (kamera forgatása). |
| **F1** | Súgó (Help) menü megnyitása / bezárása. Megnyitáskor az egér kurzor kiszabadul. |
| **N** | Időmúlás elindítása / megállítása (Nappal-éjszaka ciklus). |
| **Bal / Jobb nyíl** | Idő manuális tekerése vissza / előre (csak ha az időmúlás meg van állítva). |
| **Fel / Le nyíl** | A Nap távolságának (sugarának) növelése / csökkentése. |
| **+ / -** | Fényerősség (Light intensity) növelése és csökkentése. |
| **ESC** | Kilépés a játékból. |

## Projekt struktúra

A kód modularizálva van az átláthatóság érdekében:

* `main.c`: A fő ciklus, inicializálás, eseménykezelés és a renderelési hívások összefogása.
* `camera.c`: A kamera pozíciójának és nézőszögének frissítése, illetve a mozgás logikája.
* `help.c`: A 2D-s "Súgó" képernyő megjelenítése ortografikus projekcióval.
* `model.c`: `.obj` fájlok beolvasása, értelmezése és OpenGL Display List-té alakítása.
* `sun.c`: Az égbolt színének, a fényviszonyoknak és a Nap pozíciójának/modelljének kezelése.
* `terrain.c`: A hullámzó talaj generálása és textúrázása.
* `texture.c`: Képfájlok (JPG, PNG) betöltése SDL_image segítségével és OpenGL textúrává alakítása mipmappeléssel.
* `tree.c`: A fák véletlenszerű koordinátáinak legenerálása és kirajzolása.

## Rendszerkövetelmények és Fordítás

### Függőségek (Dependencies)
A projekt sikeres fordításához és futtatásához a következő könyvtárak szükségesek:
* C fordító (pl. `gcc` vagy `clang`)
* **SDL2** (ablakkezelés, bemenet)
* **SDL2_image** (képek betöltése)
* **OpenGL** (gl, glu)
* Standard Math library (`math.h`)

### Eszközök (Assets) mappa
A futtatható fájl mellett lennie kell egy `assets/` mappának a következő struktúrával, máskülönben a program nem tudja betölteni a szükséges fájlokat:
```text
assets/
 ├── help.jpg
 ├── 2k_sun.jpg
 ├── sol.obj
 └── grass/
      └── grass.jpg

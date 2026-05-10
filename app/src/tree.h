#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

/** @brief A pályán elhelyezendő fák maximális száma. */
#define NUM_TREES 70

/**
 * @brief Véletlenszerűen legenerálja a fák pozícióit a pályán.
 * * A függvény megpróbálja elhelyezni a fákat a megadott világhatárokon belül úgy,
 * hogy azok ne lógjanak egymásba (biztonsági távolság), és szabadon hagyják a kezdőpontot.
 * Maximum 3000 próbálkozást végez a végtelen ciklus és a kifagyás elkerülése végett.
 * * @param worldSize A generálási terület határai.
 */
void generateTrees(float worldSize);

/**
 * @brief Ellenőrzi, hogy egy adott térbeli pont ütközik-e bármelyik fával.
 * * A játékos mozgásának korlátozására szolgál, kör (henger) alapú ütközésvizsgálattal.
 * * @param x Az ellenőrizendő pont X koordinátája.
 * @param z Az ellenőrizendő pont Z koordinátája.
 * @param radius A játékos (vagy az ellenőrzött objektum) sugara.
 * @return true Ha ütközés történt (a pont túl közel van egy fához).
 * @return false Ha a pont biztonságos, nincs ütközés.
 */
bool checkTreeCollision(float x, float z, float radius);

/**
 * @brief Kirajzol egyetlen, kódba égetett (primitívekből álló) fát.
 * * A fát GL_QUADS (törzs) és GL_TRIANGLES (lomb) segítségével építi fel,
 * beállítva a megfelelő normálvektorokat a fényekhez.
 */
void drawTree();

/**
 * @brief Kirajzolja a pályán lévő összes fát a legenerált pozíciókra.
 * * A függvény végigmegy a fák tömbjén, kiszámolja az adott X,Z ponthoz
 * tartozó talajmagasságot (Y), és a megfelelő eltolás (glTranslatef) után
 * kirajzolja a fát. Textúrázást ideiglenesen letiltja a művelet alatt.
 */
void renderAllTrees();

#endif // TREE_H
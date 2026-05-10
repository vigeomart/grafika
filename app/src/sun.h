#ifndef SUN_H
#define SUN_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <GL/gl.h>

/** @brief Globális változó, ami jelzi, hogy az idő (naplemente) magától folyik-e. */
extern bool is_time_flowing; 

/**
 * @brief Kezeli a fényerő (+ és - gombok) manuális szabályozását.
 * * @param state Az SDL_GetKeyboardState által visszaadott gombállapot-tömb.
 */
void handleSunInput(const Uint8 *state);

/**
 * @brief Frissíti a napszakot (time_of_day) és a Nap távolságát.
 * * Ha az is_time_flowing igaz, az idő magától halad. Ha hamis, a Bal/Jobb
 * nyilakkal lehet az időt tekerni, a Fel/Le nyilakkal pedig a Nap távolságát állítani.
 * A napszak értéke szigorúan 0.0 (dél) és 1.0 (éjszaka) között marad.
 * * @param delta_time Az előző képkocka óta eltelt idő másodpercben (Delta Time).
 * @param state Az SDL_GetKeyboardState által visszaadott gombállapot-tömb.
 */
void updateTimeAndSun(float delta_time, const Uint8 *state, bool is_time_flowing);
/**
 * @brief Kiszámítja a világítást, beállítja az égbolt színét és törli a képernyőt.
 * * A napszak alapján Lineáris Interpolációval (LERP) kiszámítja az égbolt 
 * színét (világoskékből feketébe). Meghatározza a Nap térbeli (X, Y, Z) koordinátáit, 
 * és elvégzi a GL_LIGHT0 pozícionálását, valamint intenzitásának beállítását.
 */
void applySkyAndLighting();

/**
 * @brief Kirajzolja a Napot vizuálisan az égre egy fényes 3D gömb formájában.
 * * A függvény a korábban kiszámított Nap pozícióba tolja a mátrixot, 
 * kikapcsolja a fényeket (hogy a Nap ne árnyékolja önmagát), majd 
 * megjeleníti a saját készítésű gömb geometriát.
 */
void renderSun(GLuint sunModel);

#endif // SUN_H
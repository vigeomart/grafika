#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

/**
 * @brief Frissíti a kamera forgatási szögeit az egér mozgása alapján.
 * * A függőleges (pitch) mozgást -89 és +89 fok között korlátozza, 
 * hogy elkerülje a kamera átfordulását (Gimbal lock).
 * * @param xrel Az egér vízszintes elmozdulása az előző képkocka óta.
 * @param yrel Az egér függőleges elmozdulása az előző képkocka óta.
 * @param sensitivity Az egér érzékenysége (szorzótényező).
 */
void updateCameraRotation(float xrel, float yrel, float sensitivity);

/**
 * @brief Kiszámítja és frissíti a kamera (játékos) új pozícióját a billentyűzet alapján.
 * * A W, A, S, D gombok lenyomását figyeli, és trigonometria segítségével 
 * a kamera aktuális nézési iránya felé lépteti a pozíciót. Mozgás előtt 
 * ütközésvizsgálatot (fák, pálya széle) végez.
 * * @param state Az SDL_GetKeyboardState által visszaadott gombállapot-tömb.
 * @param speed A játékos mozgási sebessége.
 * @param mapLimit A pálya maximális határa, amin túl nem mehet a játékos.
 * @param playerRadius A játékos kiterjedése (sugara) az ütközésvizsgálathoz.
 */
void updateCameraPosition(const Uint8 *state, float speed, float mapLimit, float playerRadius);

/**
 * @brief Alkalmazza a kamera forgatását és eltolását az OpenGL Mátrixon.
 * * A függvény kiszámítja a talaj magasságát, hozzáadja a szemmagasságot, 
 * majd elvégzi a szükséges glRotatef és glTranslatef hívásokat, hogy a világot 
 * a játékos nézőpontjából lássuk.
 * * @param eyeLevel A játékos szemmagassága a talajszinthez képest.
 */
void applyCameraView(float eyeLevel);

#endif // CAMERA_H
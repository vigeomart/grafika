#ifndef HELP_H
#define HELP_H

#include <GL/gl.h>

/**
 * @brief Kirajzolja a 2D-s Súgó menüt a képernyő közepére.
 * * A függvény átvált 3D-ből 2D-s ortografikus (merőleges) vetítésre, 
 * kikapcsolja a fényeket és a mélységtesztet (hogy a HUD menü minden 
 * 3D-s objektumot eltakarjon), majd a képernyő aktuális felbontásához 
 * és képarányához dinamikusan igazítva kirajzolja a textúrázott téglalapot.
 * * @param helpTex A súgó képének (pl. help.jpg) OpenGL textúra azonosítója.
 * @param screen_w A képernyő (ablak) aktuális szélessége pixelben.
 * @param screen_h A képernyő (ablak) aktuális magassága pixelben.
 */
void renderHelpMenu(GLuint helpTex, int screen_w, int screen_h);

#endif // HELP_H
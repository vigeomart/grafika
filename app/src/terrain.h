#ifndef TERRAIN_H
#define TERRAIN_H

#include <GL/gl.h>

/** * @brief A virtuális tér kiterjedése (fél-szélesség).
 * A pálya -WORLD_SIZE-tól +WORLD_SIZE-ig tart az X és Z tengelyeken. 
 */
#define WORLD_SIZE 40.0f 

/**
 * @brief Kiszámítja a terep magasságát egy adott 3D-s koordinátán.
 * * Szinuszhullámok és távolságfüggvények matematikai kombinációjával generálja a domborzatot.
 * A játékos induló pozíciója (az origó, azaz 0,0 körül) mesterségesen ki van egyenlítve egy
 * sík területté a könnyebb elindulás érdekében.
 * * @param x Az X tengelyen lévő koordináta.
 * @param z A Z tengelyen lévő koordináta (mélység).
 * @return float A kiszámolt magasság (Y koordináta) értéke az adott pontban.
 */
float getHeight(float x, float z);

/**
 * @brief Kirajzolja a teljes 3D-s talajfelületet.
 * * A függvény felosztja a teret kisebb négyszögekre (GL_QUADS), minden pontban kiszámítja 
 * a magasságokat, valamint a valós idejű árnyékoláshoz elengedhetetlen normálvektorokat. 
 * Végül ismétlődően ráfeszíti a megadott textúrát a felszínre.
 * * @param groundTex A talajra húzandó (tiled) textúra azonosítója (ID).
 */
void drawTerrain(GLuint groundTex);

#endif // TERRAIN_H
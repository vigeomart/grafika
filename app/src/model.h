#ifndef MODEL_H
#define MODEL_H

#include <GL/gl.h>

/**
 * @brief Beolvas egy 3D Wavefront (.obj) modellt és betölti a videókártya memóriájába (VRAM).
 * * Egy leegyszerűsített beolvasó, amely a háromszögekből (Triangles) álló modellek
 * csúcspontjait (v), textúra koordinátáit (vt) és normálvektorait (vn) dolgozza fel.
 * A modellt egy OpenGL Display List-be fordítja az optimális és gyors kirajzolás érdekében.
 * * @param path A betöltendő .obj fájl relatív vagy abszolút elérési útja (pl. "assets/torzs.obj").
 * @param textureID A modellhez rendelendő OpenGL textúra azonosítója. Ha nincs textúra, az érték 0.
 * @return GLuint A generált Display List azonosítója. Hiba esetén 0.
 */
GLuint loadOBJ(const char * path, GLuint textureID);

#endif // MODEL_H
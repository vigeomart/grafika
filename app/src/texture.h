#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

/**
 * @brief Betölt egy képfájlt és OpenGL textúrát generál belőle.
 * * A függvény az SDL2_image könyvtárat használja a kép beolvasására, 
 * majd RGBA32 formátumra konvertálja a biztos színhelyesség érdekében.
 * Támogatja a Mipmap generálást a távoli textúrák rácsozódásának (Moiré-effektus)
 * elkerülése végett.
 * * @param filepath A betöltendő képfájl relatív vagy abszolút elérési útja (pl. "assets/kep.jpg").
 * @return GLuint Az OpenGL által generált textúra azonosítója (ID). Sikertelen betöltés esetén 0.
 */
GLuint loadTexture(const char* filepath);

#endif // TEXTURE_H

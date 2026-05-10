#include "help.h"
#include <SDL2/SDL.h>

void renderHelpMenu(GLuint helpTex, int screen_w, int screen_h) {

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, screen_w, screen_h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, helpTex);
    glColor3f(1.0f, 1.0f, 1.0f);
    

    float target_aspect = 1.5f; 
    float screen_aspect = (float)screen_w / (float)screen_h;
    float max_fraction = 0.8f;
    float help_w, help_h;

    if (screen_aspect > target_aspect) {
        help_h = screen_h * max_fraction;
        help_w = help_h * target_aspect; 
    } else {
        help_w = screen_w * max_fraction;
        help_h = help_w / target_aspect; 
    }

    float start_x = (screen_w - help_w) / 2.0f;
    float start_y = (screen_h - help_h) / 2.0f;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(start_x, start_y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(start_x + help_w, start_y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(start_x + help_w, start_y + help_h);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(start_x, start_y + help_h);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

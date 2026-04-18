#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 350;
    ball->speed_y = 350;
    ball->rotation = 0.0;
    ball->rotation_speed = 180.0;
}

void init_ball_radius(Ball* ball, float r){
    if (r > 10 && r < 100)
    {
        ball->radius = r;
    }
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;

    ball->rotation += ball->rotation_speed * time;
    if (ball->rotation >= 360.0f) {
        ball->rotation -= 360.0f;
    } else if (ball->rotation < 0.0f) {
        ball->rotation += 360.0f;
    }
}

void render_ball(Ball* ball)
{
    double angle;
    double step = 0.2;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    int slice = 0;
    for (angle = 0; angle < 2.0 * M_PI; angle += step) {
        if (slice % 2 == 0) {
            glColor3f(1.0f, 0.9f, 0.8f);
        } else {
            glColor3f(0.8f, 0.4f, 0.2f);
        }
        
        glVertex2f(0.0f, 0.0f);
        glVertex2f(cos(angle) * ball->radius, sin(angle) * ball->radius);
        glVertex2f(cos(angle + step) * ball->radius, sin(angle + step) * ball->radius);
        
        slice++;
    }
    glEnd();
    glPopMatrix();
}

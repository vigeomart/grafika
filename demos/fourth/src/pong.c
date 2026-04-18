#include "pong.h"
#include <GL/gl.h>


void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    pong->score_left = 0;
    pong->score_right = 0;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    // Eredményjelző kirajzolása vonal-primitívekkel
    glLineWidth(4.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Bal játékos pontszáma a pálya bal felén
    render_digit(pong->score_left, pong->width * 0.25f, 50.0f, 30.0f);
    // Jobb játékos pontszáma a pálya jobb felén
    render_digit(pong->score_right, pong->width * 0.75f, 50.0f, 30.0f);
    
    glLineWidth(1.0f); // Visszaállítjuk az alapértelmezett vonalvastagságot

    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

void bounce_ball(Pong* pong)
{
    // Bal oldali ütő ütközésvizsgálat
    if (pong->ball.x - pong->ball.radius < 50) {
        if (pong->ball.y >= pong->left_pad.y && pong->ball.y <= pong->left_pad.y + pong->left_pad.height)
        {
            pong->ball.x = pong->ball.radius + 50;
            pong->ball.speed_x *= -1;
            // Forgás megváltoztatása az ütő mozgása (vagy a becsapódás szöge) alapján
            pong->ball.rotation_speed = -pong->ball.rotation_speed + pong->left_pad.speed * 0.5f;
        }
    }
    
    // Jobb oldali ütő ütközésvizsgálat
    if (pong->ball.x + pong->ball.radius > pong->width - 50) {
        if (pong->ball.y >= pong->right_pad.y && pong->ball.y <= pong->right_pad.y + pong->right_pad.height)
        {
            pong->ball.x = pong->width - pong->ball.radius - 50;
            pong->ball.speed_x *= -1;
            pong->ball.rotation_speed = -pong->ball.rotation_speed + pong->right_pad.speed * 0.5f;
        }
    }
    
    // Falak (alsó / felső) ütközése: a forgás megfordulása ("visszapörgés")
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
        pong->ball.rotation_speed *= -1; // Visszapattanás esetén a forgásirány is változik
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
        pong->ball.rotation_speed *= -1;
    }

    // Pályaelhagyás és pontszerzés vizsgálata
    if (pong->ball.x + pong->ball.radius < 0) {
        pong->score_right++;
        init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
    } else if (pong->ball.x - pong->ball.radius > pong->width) {
        pong->score_left++;
        init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
    }
}

void render_digit(int digit, float x, float y, float size)
{
    // A 7 szegmens be/ki kapcsolási állapotai a 0-9 számjegyekre
    static const int segments[10][7] = {
        {1,1,1,0,1,1,1}, // 0
        {0,0,1,0,0,1,0}, // 1
        {1,0,1,1,1,0,1}, // 2
        {1,0,1,1,0,1,1}, // 3
        {0,1,1,1,0,1,0}, // 4
        {1,1,0,1,0,1,1}, // 5
        {1,1,0,1,1,1,1}, // 6
        {1,0,1,0,0,1,0}, // 7
        {1,1,1,1,1,1,1}, // 8
        {1,1,1,1,0,1,1}  // 9
    };

    if (digit < 0 || digit > 9) return; // Hibakezelés - csak 0-9 megjelenítése

    float w = size;         // Szélesség
    float h = size * 2.0f;  // Magasság (dupla akkora, mint a szélesség)

    glBegin(GL_LINES);
    
    // Top szegmens (0)
    if (segments[digit][0]) { glVertex2f(x, y); glVertex2f(x + w, y); }
    // Top-Left szegmens (1)
    if (segments[digit][1]) { glVertex2f(x, y); glVertex2f(x, y + h/2); }
    // Top-Right szegmens (2)
    if (segments[digit][2]) { glVertex2f(x + w, y); glVertex2f(x + w, y + h/2); }
    // Middle szegmens (3)
    if (segments[digit][3]) { glVertex2f(x, y + h/2); glVertex2f(x + w, y + h/2); }
    // Bottom-Left szegmens (4)
    if (segments[digit][4]) { glVertex2f(x, y + h/2); glVertex2f(x, y + h); }
    // Bottom-Right szegmens (5)
    if (segments[digit][5]) { glVertex2f(x + w, y + h/2); glVertex2f(x + w, y + h); }
    // Bottom szegmens (6)
    if (segments[digit][6]) { glVertex2f(x, y + h); glVertex2f(x + w, y + h); }
    
    glEnd();
}

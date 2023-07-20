#include <GL/freeglut.h>
#include <cmath>
#include <string>


using namespace std;


class Color {
public:
    int red;
    int green;
    int blue;

    explicit Color(int red = 255, int green = 255, int blue = 255) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
};


class Point {
public:
    float x;
    float y;

    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }
};


void boat(float scale = .7, float translate_y = -10, bool vanish = false);

void draw_sun_to_moon(float scale, float translate_x, float translate_y, bool to_moon = false);

void background(bool make_dark);

void draw_star(float scale = .7, float translate_x = 0, float translate_y = 0, bool vanish = false);

void draw_tree(float scale = 1, float rotate = 0, float translate_x = 0, float translate_y = 0, bool make_dark = false);

void house(Color body, Color roof, Color door, float scale = 1, float translate_x = 0, float translate_y = 0,
           bool make_dark = false, bool door_lock = true);

void
draw_circle(Point center, float radius, Color color, bool fill = true, const string &mode = "full", int rotate = 0);

void draw_triangle(Point a, Point b, Point c, Color color, bool fill = true, int rotate = 0, float translate_x = 0,
                   float translate_y = 0);

void
draw_rectangle(Point a, Point b, Point c, Point d, Color color, bool fill = true, int rotate = 0, float translate_x = 0,
               float translate_y = 0);

void glColor_(int r, int g, int b);

const char *Window_Name = "Freeglut Village Scenery";


// Define Dynamic Values
bool night_now = false;
bool to_night_done = false;
float darkness = 0;
bool house_shut = false;


void inputHandler(unsigned char c, int x, int y) {
    if (((char) c) == ' ') {
        //  cout << c << endl;
        night_now = !night_now;
    }


}


// Main Program
void myDisplay() {

    glClear(GL_COLOR_BUFFER_BIT);

    background(to_night_done);

    float scale_s = .49;
    draw_star(scale_s, 90, 84 + darkness, !to_night_done);
    draw_star(scale_s, -100, 70 + darkness);
    draw_star(scale_s, -90, 80 + darkness);
    draw_star(scale_s, -70, 94 + darkness);
    draw_star(scale_s, -90, 50 + darkness);
    draw_star(scale_s, -50, 59 + darkness);
    draw_star(scale_s, -30, 48 + darkness);
    draw_star(scale_s, -40, 85 + darkness);
    draw_star(scale_s, -10, 30 + darkness);
    draw_star(scale_s, -10, 96 + darkness);
    draw_star(scale_s, 20, 59 + darkness);
    draw_star(scale_s, 50, 77 + darkness);
    draw_star(scale_s, 80, 30 + darkness);
    draw_star(scale_s, 94, 44 + darkness);

    draw_sun_to_moon(.8, 33, 35, night_now);

    draw_rectangle(Point(-50, 15), Point(50, 15), Point(50, -15), Point(-50, -15), Color(77, 50, 34), true, 0, 0, -10);
    boat(.7, -45, to_night_done);
    draw_tree(.5, 0, -30, 10, to_night_done);
    draw_tree(.7, 0, -55, 12, to_night_done);
    draw_tree(.7, 0, -66, 1, to_night_done);
    draw_tree(.5, 0, 30, 10, to_night_done);
    draw_tree(.7, 0, 55, 12, to_night_done);
    draw_tree(.7, 0, 66, 1, to_night_done);
    draw_tree(.7, 0, 0, 10, to_night_done);
    house(Color(63, 232, 147), Color(64, 160, 189), Color(100, 107, 7), .7, -40, -10, to_night_done, house_shut);
    house(Color(224, 152, 74), Color(7, 74, 21), Color(135, 47, 235), .7, 50, -15, to_night_done, house_shut);
    house(Color(83, 245, 34), Color(32, 105, 96), Color(224, 74, 149), .7, 0, -20, to_night_done, house_shut);

    glFlush();

}


void updater(int pass) {
    glutPostRedisplay();
    glutTimerFunc(20, updater, pass);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600, 1600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(Window_Name);
    glutDisplayFunc(myDisplay);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutTimerFunc(200, updater, 0); // First Hook
    glutKeyboardFunc(inputHandler);
    glutMainLoop();
    return 0;


}


void glColor_(int r, int g, int b) {
    glColor3f((GLfloat) ((float) r / 255), (GLfloat) ((float) g / 255), (GLfloat) ((float) b / 255));
}


void draw_circle(Point center, float radius, Color color, bool fill, const string &mode, int rotate) {

    glPushMatrix();
    glRotated(rotate, 0, 0, 1);
    float center_x = center.x;
    float center_y = center.y;
    int n = 1000;
    GLfloat R = radius;
    GLfloat double_Pi = 3.1416 * 2;

    !fill ? glBegin(GL_LINE_LOOP) : glBegin(GL_POLYGON);
    glColor_(color.red, color.green, color.blue);
    for (int i = 0; i < n; i++) {


        float x = center_x + R * cos((double_Pi / n) * i);
        float y = center_y + R * sin((double_Pi / n) * i);


        if (mode == "half") {
            if (y > 0) {
                glVertex2f(x, y);
            }


        } else {
            glVertex2f(x, y);
        }


    }
    glEnd();
    glPopMatrix();


}


void
draw_triangle(Point a, Point b, Point c, Color color, bool fill, int rotate, float translate_x, float translate_y) {
    glPushMatrix();
    glRotated(rotate, 0, 0, 1);
    glTranslated(translate_x, translate_y, 1);
    !fill ? glBegin(GL_LINE_LOOP) : glBegin(GL_POLYGON);
    glColor_(color.red, color.green, color.blue);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glEnd();
    glPopMatrix();
}


void draw_rectangle(Point a, Point b, Point c, Point d, Color color, bool fill, int rotate, float translate_x,
                    float translate_y) {
    glPushMatrix();
    glRotated(rotate, 0, 0, 1);
    glTranslated(translate_x, translate_y, 1);
    !fill ? glBegin(GL_LINE_LOOP) : glBegin(GL_POLYGON);
    glColor_(color.red, color.green, color.blue);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glVertex2f(d.x, d.y);
    glEnd();
    glPopMatrix();
}


void draw_tree(float scale, float rotate, float translate_x, float translate_y, bool make_dark) {
    Color leaf = make_dark ? Color(25, 84, 37) : Color(66, 245, 66);
    Color root = make_dark ? Color(64, 34, 27) : Color(138, 72, 22);
    glPushMatrix();
    glScalef(scale, scale, 0.0);
    glRotated(rotate, 0, 0, 1);
    glTranslated(translate_x, translate_y, 1);
    draw_rectangle(Point(-2, 0), Point(2, 0), Point(2, -20), Point(-2, -20), root, true, 0, 1.5);
    draw_circle(Point(-4, 0), 5.5, leaf, true);
    draw_circle(Point(0, 4), 6, leaf, true);
    draw_circle(Point(7, 0), 5, leaf, true);
    draw_circle(Point(7, 3), 5, leaf, true);
    glPopMatrix();
}


void house(Color body, Color roof, Color door, float scale, float translate_x, float translate_y, bool make_dark,
           bool door_lock) {
    static float house_door = .5;
    door_lock ? house_door -= .009 : house_door += .009;
    if (house_door < 0 || house_door > 1) {
        door_lock ? house_door = 0 : house_door = 1;
    }


    roof = make_dark ? Color(roof.red * 1 / 3, roof.green * 1 / 3, roof.blue * 1 / 3) : Color(roof.red, roof.green,
                                                                                              roof.blue);
    body = make_dark ? Color(body.red * 1 / 3, body.green * 1 / 3, body.blue * 1 / 3) : Color(body.red, body.green,
                                                                                              body.blue);
    door = make_dark ? Color(door.red * 1 / 3, door.green * 1 / 3, door.blue * 1 / 3) : Color(door.red, door.green,
                                                                                              door.blue);
    glPushMatrix();
    glScalef(scale, scale, 0.0);
    glTranslated(translate_x, translate_y, 1);
    draw_rectangle(Point(-13, 0), Point(-13, 14), Point(13, 14), Point(13, 0), body);
    draw_triangle(Point(-16, 14), Point(0, 26), Point(16, 14), roof);

    draw_rectangle(Point(-3, 0), Point(-3, 8), Point(3, 8), Point(3, 0), Color(204, 189, 55), true, 0, 0);

    draw_rectangle(Point(-1.5, 0), Point(-1.5, 8), Point(1.5, 8), Point(1.5, 0), door, true, 0, -1.5 - house_door);

    draw_rectangle(Point(-1.5, 0), Point(-1.5, 8), Point(1.5, 8), Point(1.5, 0), door, true, 0, 1.5 + house_door);
    if (house_door == 0) {
        //draw_rectangle(Point(-.6, 0), Point(-.6, 8), Point(.6, 8), Point(.6, 0), Color(166, 71, 55));
        draw_rectangle(Point(-2.5, -2.5), Point(-2.5, 2.5), Point(2.5, 2.5), Point(2.5, -2.5), Color(237, 210, 59),
                       true, 0, -7.5, 7);
        draw_rectangle(Point(-2.5, -2.5), Point(-2.5, 2.5), Point(2.5, 2.5), Point(2.5, -2.5), Color(237, 210, 59),
                       true, 0, 7.5, 7);
    } else {
        draw_rectangle(Point(-2.5, -2.5), Point(-2.5, 2.5), Point(2.5, 2.5), Point(2.5, -2.5), Color(186, 104, 110),
                       true, 0, -7.5, 7);
        draw_rectangle(Point(-2.5, -2.5), Point(-2.5, 2.5), Point(2.5, 2.5), Point(2.5, -2.5), Color(186, 104, 110),
                       true, 0, 7.5, 7);
    }
    glPopMatrix();
}


void draw_star(float scale, float translate_x, float translate_y, bool vanish) {

    static int peek = 0;
    static int glow = 2550;
    static bool do_increase = false;
    static bool activate_peek = false;
    if (!vanish) {
        if (!activate_peek) {
            if (do_increase) {
                glow += 2;


            } else glow -= 2;


            if (glow < 500) {
                do_increase = true;
            }
            if (glow > 2550) {
                do_increase = false;
                peek = 0;
                activate_peek = true;
            }
        }


        if (activate_peek) {
            peek = peek + 3;
        }


        if (peek > 1000) {
            activate_peek = false;
        }


    } else {
        glow < 0 ? glow = 0 : glow -= 50;
    }


    glPushMatrix();


    if (vanish) {
        glColor_(glow / 10, glow / 10, glow / 10);
    } else {
        activate_peek ? glColor_(247, 239, 129) : glColor_(glow / 10, glow / 10, glow / 10);
    }
    glScalef(scale, scale, 0.0);
    glTranslated(translate_x, translate_y, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(1.0, 4.0);
    glVertex2f(3.0, 3.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(-1.0, 2.0);
    glVertex2f(-3.0, 3.0);
    glVertex2f(-1.0, 4.0);
    glVertex2f(0.0, 6.0);
    glEnd();


    glPopMatrix();
}


void boat(float scale, float translate_y, bool vanish) {
    static float up_down = 0;
    static float direction = -100;
    static bool forward = true;
    static bool count_i = true;


    if (up_down < -5) {
        forward = true;
    }
    if (up_down > 5) {
        forward = false;
    }
    if (count_i) {
        forward ? up_down += .3 : up_down -= .3;
        direction > 100 ? direction = -100 : direction += .5;
    }
    if (vanish) {
        if (direction > 100) {
            count_i = false;
            direction = -100;
        }


    } else count_i = true;


    glPushMatrix();
    glScaled(scale, scale, 0);
    glTranslated(direction, translate_y, 0);
    glRotated(up_down, 0, 0, 1);
    draw_circle(Point(2, -2), 7, Color(100, 100, 64), true);
    draw_circle(Point(0, 0), 13.5, Color(46, 46, 41), true, "half", -180);
    glPopMatrix();


}


void draw_sun_to_moon(float scale, float translate_x, float translate_y, bool to_moon) {
    //252, 186, 43
    static int red = 252;
    static int green = 186;
    static int blue = 43;


    static bool sun_execute = true;
    static bool repeat_glow = true;
    static float angel = 0;
    static float scale_ray = 1;
    float center_x = 0;
    float center_y = 0;
    float double_Pi = 3.1416 * 2;
    float R = 11;
    float n = 300;
    glPushMatrix();
    glScaled(scale, scale, 0);
    glTranslated(translate_x, translate_y, 0);
    glPushMatrix();
    glRotated(angel, 0, 0, 1);
    glBegin(GL_TRIANGLES);
    glColor_(247, 62, 37);
    for (int i = 0; i < n; i++) {


        float x = center_x + R * cos((double_Pi / n) * i);
        float y = center_y + R * sin((double_Pi / n) * i);

        if (i % 4 == 0) {
            glVertex2f(x * scale_ray, y * scale_ray);
        } else glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    draw_circle(Point(0, 0), 12, Color(red, green, blue));
    if (!to_moon) {
        to_night_done = false;
        (red > 252) ? red -= 1 : red = 252;
        (green > 186) ? green -= 1 : green = 186;
        (blue > 43) ? blue -= 1 : blue = 43;
        if ((red == 252) && (green == 186) && (blue == 43)) {
            sun_execute = true;
        }


    }


    if (sun_execute) {
        angel += .3;
        repeat_glow ? scale_ray += .005 : scale_ray -= .005;
        if (scale_ray > 2) {
            repeat_glow = false;
        }
        if (scale_ray < 1.25) {
            to_moon ? repeat_glow = false : repeat_glow = true;
        }
        if (angel > 360) {
            angel = 0;
        }
        if (to_moon && (scale_ray < 1)) {
            sun_execute = false;
        }


    }


    if ((scale_ray <= 2) && (scale_ray >= 1.25)) {
        house_shut = false;
    }


    if (!sun_execute && to_moon) {
        // 250, 232, 192
        red < 250 ? red += 1 : red = 250;
        green < 232 ? green += 1 : green = 232;
        blue < 192 ? blue += 1 : blue = 192;
        if (red == 250 && green == 232 && blue == 192) {
            to_night_done = true;
            house_shut = true;


        }
    }


    glPopMatrix();
}


void background(bool make_dark) {
    static float r_red = 0;
    static float r_green = 0;
    static float r_blue = 255;


    static float s_red = 126;
    static float s_green = 227;
    static float s_blue = 242;


    if (!make_dark) {
        // 38, 48, 92
        s_red < 126 ? s_red += 1 : s_red = 126;
        s_green < 227 ? s_green += 1 : s_green = 227;
        s_blue < 242 ? s_blue += 1 : s_blue = 242;


        r_red < 0 ? r_red += 1 : r_red = 0;
        r_green < 0 ? r_green += 1 : r_green = 0;
        r_blue < 255 ? r_blue += 1 : r_blue = 255;


        darkness < 100 ? darkness += 10 : darkness = 100;
    } else {
        darkness > 0 ? darkness -= 5 : darkness = 0;
        s_red > 0 ? s_red -= 5 : s_red = 0;
        s_green > 0 ? s_green -= 5 : s_green = 0;
        s_blue > 0 ? s_blue -= 5 : s_blue = 0;


        r_red > 38 ? r_red -= 5 : r_red = 38;
        r_green > 48 ? r_green -= 5 : r_green = 48;
        r_blue > 92 ? r_blue -= 5 : r_blue = 92;
    }


    draw_rectangle(Point(-50, 50), Point(50, 50), Point(50, -50), Point(-50, -50), Color(r_red, r_green, r_blue));
    draw_rectangle(Point(-50, 50), Point(50, 50), Point(50, -20), Point(-50, -20), Color(s_red, s_green, s_blue));


}
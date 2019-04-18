////////////////////////////////////////////////////////////////////////////////////        
/////// Compilar: g++ -o canvas  canvas.cpp -lglut -lGL -lGLU -lm //////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define POLY_LINE 4
#define CIRCLE 5
#define HEXAGON 6
#define PI 3.14159265358979324
#define NUMBERPRIMITIVES 6

typedef struct {
    float x;
    float y;
}Pnt;

// Currently drag point.
Pnt currentPoint;
Pnt center;

// Use the STL extension of C++.
using namespace std;


// Globals.
static GLsizei width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?


void mousePassiveMotion(int x, int y) {
    // Update the location of the current point as the mouse moves with no button pressed.
    if (pointCount) {
        currentPoint.x = x;
        currentPoint.y = height - y;
    }
    glutPostRedisplay();
}


// Point class.
class Point {
    public:
        Point(int xVal, int yVal) {
            x = xVal;
            y = yVal;
        }

    void drawPoint(void); // Function to draw a point.

private:
    int x, y; // x and y co-ordinates of point.
    static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.
//Function to draw a point.

void Point::drawPoint() {
    glPointSize(size);
        glBegin(GL_POINTS);
        glVertex3f(x, y, 0.0);
    glEnd();
}

// Vector of points.
vector<Point> points;
// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator;
// Function to draw all points in the points array.

void drawPoints(void) {

    // Loop through the points array drawing each point.
    pointsIterator = points.begin();
    while(pointsIterator != points.end()) {
        pointsIterator->drawPoint();
        pointsIterator++;
    }
}

// Line class.
class Line {
    public:
        Line(int x1Val, int y1Val, int x2Val, int y2Val) {
            x1 = x1Val;
            y1 = y1Val;
            x2 = x2Val;
            y2 = y2Val;
        }

    void drawLine();

private:
    int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};


// Function to draw a line.
void Line::drawLine() {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glEnd();
}
// Vector of lines.
vector<Line> lines;
// Iterator to traverse a Line array.
vector<Line>::iterator linesIterator;
// Function to draw all lines in the lines array.
void drawLines(void) {
    // Loop through the lines array drawing each line.
    linesIterator = lines.begin();

    while(linesIterator != lines.end()) {
        linesIterator->drawLine();
        linesIterator++;
    }
}
// Rectangle class.
class Rectangle {
public:
    Rectangle(int x1Val, int y1Val, int x2Val, int y2Val) {
        x1 = x1Val;
        y1 = y1Val;
        x2 = x2Val;
        y2 = y2Val;
    }
    void drawRectangle();

private:
    int x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
};
// Function to draw a rectangle.
void Rectangle::drawRectangle() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(x1, y1, x2, y2);
}
// Vector of rectangles.
vector<Rectangle> rectangles;
// Iterator to traverse a Rectangle array.
vector<Rectangle>::iterator rectanglesIterator;
// Function to draw all rectangles in the rectangles array.
void drawRectangles(void) {
    // Loop through the rectangles array drawing each rectangle.
    rectanglesIterator = rectangles.begin();

    while(rectanglesIterator != rectangles.end()) {
        rectanglesIterator->drawRectangle();
        rectanglesIterator++;
    }
}
// class polyline.
class PolyLine {
public:

    PolyLine(int x1Val, int y1Val, int x2Val, int y2Val) {
        x1 = x1Val;
        y1 = y1Val;
        x2 = x2Val;
        y2 = y2Val;
    }

    void drawPolyLine();


public:
    int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};
// Function to draw lines continua.
void PolyLine::drawPolyLine() {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glEnd();
}
// Vector of lines.
vector<PolyLine> polylines;
// Iterator to traverse a Line array.
vector<PolyLine>::iterator polylinesIterator;
// Function to draw all lines in the lines array.
void drawPolyLines(void) {
    // Loop through the lines array drawing each line.
    polylinesIterator = polylines.begin();

    while(polylinesIterator != polylines.end()) {
        polylinesIterator->drawPolyLine();
        polylinesIterator++;
    }
}



// class polyline.
class Circle {
public:

    Circle(int x1Val, int y1Val, int x2Val, int y2Val) {
        x1 = x1Val;
        y1= y1Val;
        x2= x2Val;
        y2= y2Val;

    }

    void drawCircle();


private:
    int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};

// Function to draw lines continua.
void Circle::drawCircle() {
    float t = 0.0; // Angle parameter.

    float raio;


    raio = x1-x2;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 50; ++i) {
        glColor3ub(0.0, 0.0, 0.0);
        glVertex3f( x1 + raio * cos(t),   y1 + raio * sin(t), 0.0);
        t += 2 * PI / 50;
    }
    glEnd();

}

// Vector of lines.
vector<Circle> circles;
// Iterator to traverse a Line array.
vector<Circle>::iterator circleIterator;

// Function to draw all lines in the lines array.
void drawCircles(void) {
    // Loop through the lines array drawing each line.
    circleIterator = circles.begin();

    while(circleIterator  != circles.end()) {
        circleIterator->drawCircle();
        circleIterator++;
    }
}




// class polyline.
class Hexagon {
public:

    Hexagon(int x1Val, int y1Val, int x2Val, int y2Val) {
        x1 = x1Val;
        y1= y1Val;
        x2= x2Val;
        y2= y2Val;

    }

    void drawHexagon();


private:
    int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};
// Function to draw lines continua.
void Hexagon::drawHexagon() {
    float t = 0.0; // Angle parameter.

    float raio;


    raio = x1-x2;
    cout << "K1222:" << endl;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 5; ++i) {

        glColor3ub(0.0, 0.0, 0.0);
        glVertex3f( x1 + raio * cos(t),   y1 + raio* sin(t), 0.0);
        t += 2 * PI / 5;
    }
    glEnd();

}
// Vector of lines.
vector<Hexagon> hexagons;
// Iterator to traverse a Line array.
vector<Hexagon>::iterator hexagonsIterator;
// Function to draw all lines in the lines array.
void drawHexagons(void) {
    // Loop through the lines array drawing each line.
    hexagonsIterator = hexagons.begin();

    while(hexagonsIterator  != hexagons.end()) {
        hexagonsIterator->drawHexagon();
        hexagonsIterator++;
    }
}
// Function to draw point selection box in left selection area.
void drawPointSelectionBox(void) {

    if (primitive == POINT)
        glColor3f(1.0, 1.0, 1.0); // Highlight.
    else
        glColor3f(0.8, 0.8, 0.8); // No highlight.


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.9*height, 0.1*width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.9*height, 0.1*width, height);

    // Draw point icon.
    glPointSize(pointSize);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POINTS);
    glVertex3f(0.05*width, 0.95*height, 0.0);
    glEnd();
}
// Function to draw line selection box in left selection area.
void drawLineSelectionBox(void) {

    if (primitive == LINE)
        glColor3f(1.0, 1.0, 1.0); // Highlight.
    else
        glColor3f(0.8, 0.8, 0.8); // No highlight.


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

    // Draw line icon.
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.025*width, 0.825*height, 0.0);
    glVertex3f(0.075*width, 0.875*height, 0.0);
    glEnd();
}
// Function to draw rectangle selection box in left selection area.
void drawRectangleSelectionBox(void) {

    if (primitive == RECTANGLE)
        glColor3f(1.0, 1.0, 1.0); // Highlight.
    else
        glColor3f(0.8, 0.8, 0.8); // No highlight.


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

    // Draw rectangle icon.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.025*width, 0.735*height, 0.075*width, 0.765*height);
    glEnd();
}
void drawPolyLineSelectionBox(void) {


    if (primitive == POLY_LINE)
        glColor3f(1.0, 1.0, 1.0); // Highlight.
    else
        glColor3f(0.8, 0.8, 0.8); // No highlight.

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.6 * height, 0.1 * width, 0.7*height);

    // Draw black boundary.
    glColor3f(0.0,  0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.6 * height, 0.1 * width, 0.7 * height);


//     Draw line icon.
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.025 * width, 0.625 * height, 0.0);
    glVertex3f(0.045 * width, 0.675 * height, 0.0);

    glVertex3f(0.045 * width, 0.675 * height, 0.0);
    glVertex3f(0.065 * width, 0.630 * height, 0.0);

    glVertex3f(0.065 * width, 0.630 * height, 0.0);
    glVertex3f(0.085 * width, 0.665 * height, 0.0);
    glEnd();
}
void drawCircleSelectionBox(void) {

    float t = 0.0;

    if (primitive == CIRCLE)
        glColor3f(1.0, 1.0, 1.0); // Highlight.
    else
        glColor3f(0.8, 0.8, 0.8); // No highlight.

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.5 * height, 0.1 * width, 0.6*height);

    // Draw black boundary.
    glColor3f(0.0,  0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.5 * height, 0.1 * width, 0.6 * height);


//     Draw circle icon.
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 100; ++i) {
        glColor3ub(0.0, 0.0, 0.0);
        glVertex3f( (0.050 * width) + 15 * cos(t), (0.550 * height) + 15 * sin(t), 0.0);
        t += 2 * PI / 100;
    }
    glEnd();

}
void drawHexagonSelectionBox(void) {

    float t = 0.0;

    if (primitive == HEXAGON) {
        glColor3f(1.0, 1.0, 1.0); // Highlight.

    } else {
        glColor3f(0.8, 0.8, 0.8); // No highlight.

    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.4 * height, 0.1 * width, 0.5*height);

    // Draw black boundary.
    glColor3f(0.0,  0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.4 * height, 0.1 * width, 0.5 * height);


//     Draw circle icon.
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 5; ++i) {
        glColor3ub(0.0, 0.0, 0.0);
        glVertex3f( (0.040 * width) + 15 * cos(t), (0.450 * height) + 15 * sin(t), 0.0);
        t += 2 * PI / 5;
    }
    glEnd();

}
// Function to draw unused part of left selection area.
void drawInactiveArea(void) {

    glColor3f(0.6, 0.6, 0.6);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.0, 0.1 * width, (1 - NUMBERPRIMITIVES*0.1) * height);

    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.0, 0.1 * width, (1 - NUMBERPRIMITIVES*0.1) * height);
}
// Function to draw temporary point.
void drawTempPoint(void) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(center.x, center.y, 0.0);
    glEnd();
}

// Function to draw a grid.
void drawGrid(void) {
    int i;

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x5555);
    glColor3f(0.75, 0.75, 0.75);

    glBegin(GL_LINES);
    for (i = 2;i <= 9; i++) {
        glVertex3f(i * 0.1 * width, 0.0, 0.0);
        glVertex3f(i * 0.1 * width, height, 0.0);
    }

    for (i = 1; i <= 9; i++) {
        glVertex3f(0.1 * width, i * 0.1 * height, 0.0);
        glVertex3f(width, i * 0.1 * height, 0.0);
    }
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}


//distance(center, currentPoint)
void drawDynamicCircle(){

    float
        t = 0,
        xCenter = center.x,
        yCenter = center.y,
        xCurrent = currentPoint.x,
        R = xCenter - xCurrent;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i <= 100; ++i) {
        t = 2 * PI * i / 100;
        glVertex3f(xCenter + R * cos(t), yCenter+ R * sin(t), 0.0);
    }
    glEnd();

}

void drawDynamicLine() {
    glBegin(GL_LINES);
        glVertex3f(center.x, center.y, 0.0);
        glVertex3f(currentPoint.x, currentPoint.y, 0.0);
    glEnd();
};


void drawFigures(int primitive) {
    switch (primitive) {
        case  CIRCLE:
            drawDynamicCircle();
            break;

        case LINE:
//            nline->drawLine();
            drawDynamicLine();
            break;

        default:
            break;

    }

}

// Drawing routine.
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    drawPointSelectionBox();
    drawLineSelectionBox();
    drawRectangleSelectionBox();
    drawPolyLineSelectionBox();
    drawCircleSelectionBox();
    drawHexagonSelectionBox();

    drawInactiveArea();

    drawPoints();
    drawLines();

    if(pointCount != 0) {
        drawFigures(primitive);
    }



    drawRectangles();
    drawPolyLines();
//   drawCircles();
    drawCircles();
    drawHexagons();


    if (((primitive == LINE) || (primitive == RECTANGLE) || (primitive == CIRCLE)  || (primitive == HEXAGON) )  && (pointCount == 1)) {

        cout << "aqui man:" << endl;
        drawTempPoint();
    }

    if (isGrid) {
        drawGrid();
    }

    glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y) {

    cout << "y = :" << y << endl;
    if ( y < (1 - NUMBERPRIMITIVES*0.1)*height) primitive = INACTIVE;
    else if ( y < (1 - 5*0.1)*height ) primitive = HEXAGON;
    else if ( y < (1 - 4*0.1)*height ) primitive = CIRCLE;
    else if ( y < (1 - 3*0.1)*height ) primitive = POLY_LINE;
    else if ( y < (1 - 2*0.1)*height ) primitive = RECTANGLE;
    else if ( y < (1 - 1*0.1)*height ) primitive = LINE;

    else primitive = POINT;
}
// The mouse callback routine.
vector<PolyLine>::iterator polylinesIteratorTemp;


void mouseControl(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = height - y;  // Correct from mouse to OpenGL co-ordinates.

        // Click outside canvas - do nothing.
        if (x < 0 || x > width || y < 0 || y > height) ;

            // Click in left selection area.
        else if ( x < 0.1*width )
        {
            pickPrimitive(y);
            pointCount = 0;
        }

            // Click in canvas.
        else
        {
            if (primitive == POINT) points.push_back( Point(x,y) );
            else if (primitive == LINE) {

                if (pointCount == 0) {

                    currentPoint.x = x;
                    currentPoint.y = y;
                    center.x = x;
                    center.y = y;
                    pointCount = 1;
                } else {
                    lines.push_back( Line(center.x, center.y, x, y) );
                    center.x = x;
                    center.y = y;
                    currentPoint.x = x;
                    currentPoint.y = y;

                    pointCount = 0;

                }

            }

            else if (primitive == RECTANGLE)
            {
                if (pointCount == 0)
                {
                    center.x = x;
                    center.y = y;
                    pointCount = 1;
                }
                else
                {
                    rectangles.push_back( Rectangle(tempX, tempY, x, y) );
                    pointCount = 0;
                }
            }
            else if(primitive == POLY_LINE)
            {
                cout << "HERE:" << endl;

                if (pointCount  == 0)
                {
                    tempX = x;
                    tempY = y;
                    pointCount++;
                }
                else
                {
                    polylines.push_back( PolyLine(tempX, tempY, x, y) );
                    tempX = x;
                    tempY = y;
                    pointCount++;
                }

            }
            else if(primitive == CIRCLE)
            {


                if (pointCount == 0){
                    center.x = x;
                    center.y = y;
                    pointCount = 1;
                } else {
                    circles.push_back( Circle(center.x, center.y, x, y) );
                    pointCount = 0;
                    center.x = 0;
                    center.y = 0;
                }

            }
            else if(primitive == HEXAGON)
            {
                cout << "yafwefwqfewfwqe" << y << endl;


                if (pointCount  == 0)
                {
                    tempX = x;
                    tempY = y;
                    pointCount++;
                }
                else
                {
                    hexagons.push_back( Hexagon(tempX, tempY, x, y) );
                    pointCount = 0;
                }

            }

        }
    }
    glutPostRedisplay();
}

// Initialization routine.
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
// OpenGL window reshape routine.
void resize(int w, int h) {

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set viewing box dimensions equal to window dimensions.
    glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

    // Pass the size of the OpenGL window to globals.
    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;

        default:
            break;
    }
}
// Clear the canvas and reset for fresh drawing.
void clearAll(void) {
    points.clear();
    lines.clear();
    rectangles.clear();
    polylines.clear();
    circles.clear();
    hexagons.clear();

    primitive = INACTIVE;
    pointCount = 0;
}
// The right button menu callback function.
void rightMenu(int id) {

    if (id == 1) {
        clearAll();
        glutPostRedisplay();
    }

    if (id==2)
        exit(0);
}
// The sub-menu callback function.
void grid_menu(int id) {


    if(id == 3)
        isGrid = 1;


    if(id == 4)
        isGrid = 0;


    glutPostRedisplay();
}
// Function to create menu.
void makeMenu(void) {
    int sub_menu;

    sub_menu = glutCreateMenu(grid_menu);
    glutAddMenuEntry("On", 3);
    glutAddMenuEntry("Off", 4);

    glutCreateMenu(rightMenu);
    glutAddSubMenu("Grid", sub_menu);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Quit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
// Routine to output interaction instructions to the C++ window.
void printInteraction(void) {
    cout << "Interaction:" << endl;
    cout << "Left click on a box on the left to select a primitive." << endl
         << "Then left click on the drawing area: once for point, twice for line or rectangle." << endl
         << "Right click for menu options." <<  endl;
}
// Main routine.
int main(int argc, char **argv)
{

    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);

    glutInitWindowPosition(100, 100);
    glutCreateWindow("canvas.cpp");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    // Register the mouse callback function.
    glutMouseFunc(mouseControl);

    // Register the mouse passive motion callback function.
    glutPassiveMotionFunc(mousePassiveMotion);

    makeMenu(); // Create menu.
    glutMainLoop();

    return 0;
}
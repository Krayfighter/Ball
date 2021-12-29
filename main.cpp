#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace sf;
using namespace std;


int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 400;

int FRAMES_PER_SECOND = 120;

int BALL_POINTS = 50;
int BALL_RADIUS = 25;
#define BALL_DIAMETER 2*BALL_RADIUS



class Ball {
    public:
        Ball(CircleShape *circle, float x, float y) {
            this->circle = circle;
            this->x = x;
            this->y = y;
        }
        void render(RenderWindow *window) {
            y += 10;
            x += floor(dx);
            y += floor(dy);
            friction();
            checkbounds();
            circle->setPosition(x, y);
            window->draw(*circle);
        }
        void acceleratex(float z) {dx += z;}
        void acceleratey(float z) {dy += z;}
        void checkbounds() {
            if(x > WINDOW_WIDTH-BALL_DIAMETER) {
                dx *= -1;
                x = WINDOW_WIDTH-BALL_DIAMETER-1;
            }else if(x < 0) {
                dx *= -1;
                x = 1;
            }
            if(y > WINDOW_HEIGHT-BALL_DIAMETER) {
                dy *= -1;
                y = WINDOW_HEIGHT-BALL_DIAMETER-1;
            }else if(y < 0) {
                dy *= -.3;
                y = 1;
            }
        }
        void friction() {
            // high speed friction
            if (dx < -20) {
                dx += .5;
            }
            if (dx > 20) {
                dx -= .5;
            }
            if (dy < -20) {
                dy += .5;
            }
            if (dy > 20) {
                dy += .5;
            }
            // normal friction
            if (dx < -1) {
                dx += .1;
            }
            if (dx > 1) {
                dx -= .1;
            }
            if (dy < -1) {
                dy += .1;
            }
            if (dy > 1) {
                dy -= .1;
            }
            // low speed friction
            if (dx < 1 && dx > 0) {
                dx -= .05;
            }
            if (dx >-1 && dx < 0) {
                dx += .05;
            }
        }
        void setx(int x) {this->x = x;}
    private:
        CircleShape *circle;
        float x, y;
        float dx, dy = 0.0;
};


int parseInt(string input, int _default, string errtext="invalid integer value") {
        try {
            int val = stoi(input);
            return val;
        }catch (...) {
            cout << errtext << endl;
            return _default;
        }
}

int parseShape(const char *_shape) {
    auto shape = string(_shape);
    if (shape == "tri" || shape == "triangle") {return 3;}
    else if (shape == "square") {return 4;}
    else if (shape == "penta" || shape == "pentagon") {return 5;}
    else if (shape == "hex" || shape == "hexagon") {return 6;}
    else if (shape == "septa" || shape == "septagon") {return 7;}
    else if (shape == "octo" || shape == "octagon") {return 8;}
    else if (shape == "nona" || shape == "nonagon") {return 9;}
    else if (shape == "deca" || shape == "decagon") {return 10;}
    else {
        return parseInt(shape, BALL_POINTS, "invalid side number, using default: "+to_string(BALL_POINTS));
    }
}

Color parseColor(const char *input) {
    string color = string(input);
    if (color == "white") {return Color::White;}
    else if (color == "red") {return Color::Red;}
    else if (color == "green") {return Color::Green;}
    else if (color == "blue") {return Color::Blue;}
    else {
        cout << "invalud color: " << color << ", defaulting to green" << endl;
        return Color::Green;
    }
}


int main(int argc, char **argv) {
    Color fillcolor = Color::Green;
    for(int i = 0; i < argc; i++) {
        string arg = argv[i];
        if(arg == "-s") {
            i++;
            BALL_POINTS = parseShape(argv[i]);
        }
        if(arg == "-w") {
            i++;
            WINDOW_WIDTH = parseInt(string(argv[i]), WINDOW_WIDTH, "Invalid number: "+string(argv[i]));
        }
        if(arg == "-h") {
            i++;
            WINDOW_HEIGHT = parseInt(string(argv[i]), WINDOW_HEIGHT, "Invalid number: "+string(argv[i]));
        }
        if (arg == "-c") {
            i++;
            fillcolor = parseColor(argv[i]);
        }
    }
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Test");
    window.setFramerateLimit(FRAMES_PER_SECOND);

    CircleShape shape(25.f, BALL_POINTS);
    shape.setFillColor(fillcolor);
    float x = WINDOW_WIDTH/2;
    float y = -1;
    Ball ball(&shape, x, y);

    Clock clock;

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
            else if(event.type == Event::EventType::KeyPressed) {
                switch (event.key.code) {
                case 71:
                    cout << "Left Arrow" << endl;
                    ball.acceleratex(-16);
                    break;
                case 72:
                    cout << "Right Arrow" << endl;
                    ball.acceleratex(16);
                    break;
                case 73:
                    cout << "Up Arrow" << endl;
                    ball.acceleratey(-16);
                    break;
                case 74:
                    cout << "Down Arrow" << endl;
                    ball.acceleratey(16);
                    break;
                case 36:
                    cout << "Exiting Program" << endl;
                    exit(0);
                    break;
                default:
                    cout << event.key.code << endl;
                    break;
                }
            }
        }

        // Time ftime = clock.getElapsedTime();
        // cout << ftime.asSeconds() << endl;

        // clock.restart().asSeconds();

        window.clear();
        ball.render(&window);
        window.display();
    }

    return 0;
}
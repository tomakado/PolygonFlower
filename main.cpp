#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#include <SFML/Graphics.hpp>
#include <iostream>
#include "PolygonFlower.hpp"
#include "ini.hpp"
#include <thread>

using namespace std;
using namespace sf;

void startWindow(size_t angleCount, double amplitude, double frequency, double rotSpeed, size_t passPerFrameCount);
void pass(RenderWindow &window, PolygonFlower &pf);

int main()
{
    double amplitude, frequency, rotSpeed;
    size_t angleCount, passPerFrameCount;

    INI config("config.ini");
    angleCount = config.getInt("angle_count");
    amplitude = config.getDouble("amplitude");
    frequency = config.getDouble("frequency");
    rotSpeed = config.getDouble("rotation_speed");
    passPerFrameCount = config.getInt("passes_per_frame");

    cout << "+----------------+" << endl;
    cout << "| Polygon Flower |" << endl;
    cout << "+----------------+" << endl << endl;

    cout << "angle count: " << angleCount << endl;
    cout << "amplitude: " << amplitude << endl;
    cout << "frequency: " << frequency << endl;
    cout << "rotation speed: " << rotSpeed << endl;
    cout << "passes per frame: " << passPerFrameCount << endl;

    startWindow(angleCount, amplitude, frequency, rotSpeed, passPerFrameCount);

    return 0;
}

void startWindow(size_t angleCount, double amplitude, double frequency, double rotSpeed, size_t passPerFrameCount)
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(
        VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Polygon Flower @ OpenGL 60FPS",
        Style::Titlebar | Style::Close,
        settings
    );

    window.setFramerateLimit(60);

    PolygonFlower pf(angleCount);
    pf.setAmplitude(amplitude);
    pf.setFrequency(frequency);
    pf.setRotSpeed(rotSpeed);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        for (size_t i = 0; i < passPerFrameCount; i++)
            pass(window, pf);

        window.display();
    }
}

void pass(RenderWindow &window, PolygonFlower &pf)
{
    PolygonFlowerData data = pf.requestFrame();

    Uint8 colorValue = floor((data.size / pf.getAmplitude()) * 255);
    Color color = Color(colorValue, colorValue, colorValue, 255);

    VertexArray vertices(LineStrip, pf.getAngleCount() + 1);
    vertices[0].position = Vector2f(
        WINDOW_WIDTH / 2 + data.points[0].x,
        WINDOW_HEIGHT / 2 + data.points[0].y
    );
    vertices[0].color = color;

    for (int i = 1; i < pf.getAngleCount(); i++)
    {
        vertices[i].position = Vector2f(
            WINDOW_WIDTH / 2 + data.points[i].x,
            WINDOW_HEIGHT / 2 + data.points[i].y
        );
        
        vertices[i].color = color;
    }

    vertices[pf.getAngleCount()].position = Vector2f(
        WINDOW_WIDTH / 2 + data.points[0].x,
        WINDOW_HEIGHT / 2 + data.points[0].y
    );
    vertices[pf.getAngleCount()].color = color;

    //window.clear();
    window.draw(vertices);
}
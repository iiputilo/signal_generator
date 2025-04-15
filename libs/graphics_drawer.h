#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <optional>

struct Point {
    float x;
    float y;
};

inline std::vector<Point> readData(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Point> data;
    float x, y;
    while (file >> x >> y) {
        data.push_back({x, y});
    }
    return data;
}

inline void drawGraph(sf::RenderWindow &window, const std::vector<Point> &data, sf::Color color, bool invertY = false) {
    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    float minX = std::numeric_limits<float>::max();
    float maxX = 0;
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();
    for (const auto &p : data) {
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    sf::VertexArray line(sf::PrimitiveType::LineStrip, data.size());
    for (size_t i = 0; i < data.size(); i++) {
        float tx = (data[i].x - minX) / (maxX - minX) * windowWidth;
        float ty = (data[i].y - minY) / (maxY - minY) * windowHeight;
        if (invertY)
            ty = windowHeight - ty;
        line[i] = sf::Vertex(sf::Vector2f(tx, ty), color);
    }
    window.draw(line);
}

inline int showGraphics() {
    // Read data from files
    std::vector<Point> signalData = readData("signal.txt");
    std::vector<Point> spectrumData = readData("spectrum.txt");

    // Create two windows of equal size
    const int windowWidth = 1280;
    const int windowHeight = 720;
    sf::RenderWindow signalWindow(sf::VideoMode({windowWidth, windowHeight}), "Signal Graph");
    sf::RenderWindow spectrumWindow(sf::VideoMode({windowWidth, windowHeight}), "Spectrum Graph");

    signalWindow.setFramerateLimit(144);
    spectrumWindow.setFramerateLimit(144);

    // Main loop while at least one window is open
    while (signalWindow.isOpen() || spectrumWindow.isOpen()) {
        // Process events for signal window
        if (signalWindow.isOpen()) {
            while (std::optional event = signalWindow.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    signalWindow.close();
                }
            }
            signalWindow.clear(sf::Color::White);
            drawGraph(signalWindow, signalData, sf::Color::Red, true);
            signalWindow.display();
        }

        // Process events for spectrum window
        if (spectrumWindow.isOpen()) {
            while (std::optional event = spectrumWindow.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    spectrumWindow.close();
                }
            }
            spectrumWindow.clear(sf::Color::White);
            drawGraph(spectrumWindow, spectrumData, sf::Color::Blue, true);
            spectrumWindow.display();
        }
    }
    return 1;
}
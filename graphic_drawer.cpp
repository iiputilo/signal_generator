#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <optional>

struct Point {
    float x;
    float y;
};

std::vector<Point> readData(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Point> data;
    float x, y;
    while (file >> x >> y) {
        data.push_back({x, y});
    }
    return data;
}

int main() {
    // Считываем данные из файлов
    std::vector<Point> signalData = readData("signal.txt");
    std::vector<Point> spectrumData = readData("spectrum.txt");

    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Graphs");
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Отрисовка графика сигнала в верхней половине окна
        float minX = std::numeric_limits<float>::max();
        float maxX = 0;
        float minY = std::numeric_limits<float>::max();
        float maxY = std::numeric_limits<float>::lowest();
        for (const auto &p : signalData) {
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }
        sf::VertexArray signalLine(sf::PrimitiveType::LineStrip, signalData.size());
        for (size_t i = 0; i < signalData.size(); i++) {
            float tx = (signalData[i].x - minX) / (maxX - minX) * windowWidth;
            float ty = (signalData[i].y - minY) / (maxY - minY) * (windowHeight / 2);
            ty = (windowHeight / 2) - ty;
            signalLine[i] = sf::Vertex(sf::Vector2f(tx, ty), sf::Color::Red);
        }
        window.draw(signalLine);

        // Отрисовка графика спектра в нижней половине окна
        minX = std::numeric_limits<float>::max();
        maxX = 0;
        minY = std::numeric_limits<float>::max();
        maxY = std::numeric_limits<float>::lowest();
        for (const auto &p : spectrumData) {
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }
        sf::VertexArray spectrumLine(sf::PrimitiveType::LineStrip, spectrumData.size());
        for (size_t i = 0; i < spectrumData.size(); i++) {
            float tx = (spectrumData[i].x - minX) / (maxX - minX) * windowWidth;
            float ty = (spectrumData[i].y - minY) / (maxY - minY) * (windowHeight / 2);
            ty = windowHeight - ty;
            spectrumLine[i] = sf::Vertex(sf::Vector2f(tx, ty), sf::Color::Blue);
        }
        window.draw(spectrumLine);

        window.display();
    }
    return 0;
}
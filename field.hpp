#pragma once

#include <string>
#include <array>

struct Point
{
    int x, y;
};

class GameField
{
public:
    GameField();
    GameField(GameField&) = delete;
    GameField& operator=(const GameField&) = delete;

    static const size_t fieldWidth = 12;
    static const size_t fieldHeight = 18;
    static const char filler = ' ';

    void placeFigure(const std::string&, Point);
    void removeFigure(const std::string&, Point);
    bool doesFigureFits(std::string, Point);
    void checkLines();
    void draw();

private:
    std::array<std::array<char, fieldWidth>, fieldHeight> field;
};

#include "field.hpp"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

GameField::GameField()
{
    for (size_t i = 0; i < fieldHeight; ++i)
        for (size_t j = 0; j < fieldWidth; ++j)
            field[i][j] = filler;
}

bool GameField::doesFigureFits(std::string tetr, Point crd)
{
    int currentX = crd.x;
    int currentY = crd.y;
    for (size_t i = 0; i < tetr.size(); ++i)
    {

        if (i % 4 == 0 && i != 0)
        {
            currentX = crd.x;
            currentY++;
        }
        bool xOuttaField = currentX < 0 || currentX >= fieldWidth;
        bool yOuttaField = currentY >= fieldHeight;

        if (tetr[i] == 'X' && (field[currentY][currentX] == 'X' || yOuttaField || xOuttaField))
            return false;

        currentX++;
    }
    return true;
}

void GameField::placeFigure(const std::string &figure, Point coords)
{
    int x = coords.x;
    int y = coords.y;
    for (size_t i = 0; i < figure.size(); ++i)
    {
        if (i % 4 == 0 && i != 0)
        {
            x = coords.x;
            y++;
        }
        if (figure[i] == 'X')
            field[y][x] = figure[i];
        x++;
    }
}

void GameField::removeFigure(const std::string &figure, Point coords)
{
    int x = coords.x;
    int y = coords.y;
    for (size_t i = 0; i < figure.size(); ++i)
    {
        if (i % 4 == 0 && i != 0)
        {
            x = coords.x;
            y++;
        }
        if (figure[i] == field[y][x])
            field[y][x] = filler;
        x++;
    }
}

void GameField::checkLines()
{
    int lineToDel = 0;
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            if (field[i][j] == filler)
                break;
            if (j == fieldWidth - 1)
                lineToDel = i;
        }
    }

    if (lineToDel != 0)
    {
        for (char &i : field[lineToDel])
            i = '=';
        draw();
        std::this_thread::sleep_for(300ms);
        for (char &i : field[lineToDel])
            i = filler;
        for (int i = lineToDel; i > 0; --i)
            std::swap(field[i], field[i - 1]);
        lineToDel = 0;
    }
}

void GameField::draw()
{
    for (size_t i = 0; i < fieldHeight; ++i)
    {
        std::cout << '|';
        for (int j = 0; j < fieldWidth; ++j)
            std::cout << field[i][j];
        std::cout << '|' << std::endl;
    }
    for (size_t k = 0; k < fieldWidth + 2; ++k)
        std::cout << '#';
    std::cout << std::endl;
}

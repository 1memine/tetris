#include "tetrominoes.hpp"

#include <ctime>

const std::array<std::string, 7> Tetromino::tetrominoes = {
    ".X...X...X...X..",
    ".X...XX..X,.....",
    ".XX..X...X...,..",
    "..X..XX..X......",
    ".XX..XX.........",
    ".X...X...XX.....",
    ".X...XX...X....."};

Tetromino::Tetromino()
{
    spawn();
}

void Tetromino::rotateLeft()
{
    std::string buff = current;
    int c = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            current[c] = buff[3 - i + (j * 4)];
            c++;
        }
    }
}

void Tetromino::rotateRight()
{
    std::string buff = current;
    int c = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            current[c] = buff[12 + i - (j * 4)];
            c++;
        }
    }
}

void Tetromino::spawn()
{
    std::srand(std::time(nullptr));
    current = tetrominoes[rand() % 7];
}

std::string Tetromino::get()
{
    return current;
}
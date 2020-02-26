#pragma once

#include <array>
#include <string>

class Tetromino
{
public:
    Tetromino();
    Tetromino& operator=(const Tetromino&) = delete;
    Tetromino(const Tetromino&) = delete;

    void rotateLeft();
    void rotateRight();
    void spawn();
    std::string get();

private:
    const static std::array<std::string, 7> tetrominoes;
    std::string current;
};
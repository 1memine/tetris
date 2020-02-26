#include "tetrominoes.hpp"
#include "field.hpp"

#include <thread>
#include <chrono>

#include <SFML/Window.hpp>

using namespace std::chrono_literals;

int main()
{
    GameField field;
    Tetromino figure;
    Point coords = {GameField::fieldWidth / 2 - 2, 0};

    bool landed = false;
    bool gameOver = false;

    int timer = 0;

    while (!gameOver)
    {
        if (timer > 5)
        {
            coords.y++;
            timer = 0;
        }
        timer++;

        landed = !field.doesFigureFits(figure.get(), coords);

        // Prevents placing the figure that collides with elements on the game field
        // Also allows to move tetromino when it almost landed
        coords.y -= static_cast<int>(landed);
        field.placeFigure(figure.get(), coords);

        if (landed)
        {
            figure.spawn();
            coords = {GameField::fieldWidth / 2 - 2, 0};
            landed = false;
            gameOver = !field.doesFigureFits(figure.get(), coords);
        }
        field.draw();
        std::this_thread::sleep_for(75ms);
        field.removeFigure(figure.get(), coords);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            coords.x++;
            if (!field.doesFigureFits(figure.get(), coords))
                coords.x--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            coords.x--;
            if (!field.doesFigureFits(figure.get(), coords))
                coords.x++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            figure.rotateRight();
            if (!field.doesFigureFits(figure.get(), coords))
                figure.rotateLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            timer += 25;

        field.checkLines();
        system("clear");
    }
    field.draw();
}
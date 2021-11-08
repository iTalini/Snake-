#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Food
{
private:
	CircleShape sprite;//еда

public:
	Food();//стандартные параметры для отрисовуемой фигурки "еды"

	void setPosition(Vector2f newCord); // задать параметры для еды
	bool CheckCollision(Vector2f snakeHead, Vector2f foodPos); // проверка на столкноваение со змеёй
	CircleShape getSprite(); // доступ к отрисовываемой окружности
};


#include "Food.h"

Food::Food()
{
	Vector2f startPos(400, 300);
	sprite.setRadius(10);
	sprite.setFillColor(Color::Green);
	sprite.setPosition(startPos);
}

void Food::setPosition(Vector2f newCord)
{
	sprite.setPosition(newCord);
}

bool Food::CheckCollision(Vector2f snakePart, Vector2f foodPos)//проверка на столкновение змеи и еды
{
	//10 - радиус окружностей(змеи и еды)
	//20 - сумма окружностей
	Vector2f one = Vector2f(foodPos.x + 10, foodPos.y + 10);
	Vector2f two = Vector2f(snakePart.x + 10, snakePart.y + 10);

	float dist = std::sqrt((abs(one.x - two.x) * abs(one.x - two.x))
		+ (abs(one.y - two.y) * abs(one.y - two.y)));

	if (dist <= 20)
	{
		return(true);
	}
	return (false);
}

CircleShape Food::getSprite()
{
	return sprite;
}



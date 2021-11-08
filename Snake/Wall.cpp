#include "Wall.h"

Wall::Wall()
{

}

RectangleShape* Wall::getShape(int i)
{
	return &wallShape[i];
}

void Wall::AddShape(Vector2f pos)
{
	wallShape.emplace_back(RectangleShape());

	int i = wallShape.size() - 1;
	wallShape[i].setPosition(pos);
	wallShape[i].setFillColor(Color::Blue);
	wallShape[i].setSize(Vector2f(25, 25));
}

int Wall::GetAmountOfWalls()
{
	return wallShape.size();
}

void Wall::DrawWalls(RenderWindow* window)
{
	for (int i = 0; i < wallShape.size(); i++)
	{
		window->draw(wallShape[i]);
	}
	
}

void Wall::CleanWalls()
{
	wallShape.clear();
}

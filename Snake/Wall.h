#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Wall
{
private:
	vector <RectangleShape> wallShape; // фигуры для отрисовки стен


public:
	Wall();

	RectangleShape* getShape(int i); // передать кусок стены, обычно используеться для проверики возможных столкновений

	void AddShape(Vector2f pos); // добавить стену

	int GetAmountOfWalls(); // колличество стен

	void DrawWalls(RenderWindow* window); // отрисовка стен

	void CleanWalls(); //удаляем стены
};


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Wall
{
private:
	vector <RectangleShape> wallShape; // ������ ��� ��������� ����


public:
	Wall();

	RectangleShape* getShape(int i); // �������� ����� �����, ������ ������������� ��� ��������� ��������� ������������

	void AddShape(Vector2f pos); // �������� �����

	int GetAmountOfWalls(); // ����������� ����

	void DrawWalls(RenderWindow* window); // ��������� ����

	void CleanWalls(); //������� �����
};


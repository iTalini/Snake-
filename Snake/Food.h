#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Food
{
private:
	CircleShape sprite;//���

public:
	Food();//����������� ��������� ��� ������������ ������� "���"

	void setPosition(Vector2f newCord); // ������ ��������� ��� ���
	bool CheckCollision(Vector2f snakeHead, Vector2f foodPos); // �������� �� ������������� �� ����
	CircleShape getSprite(); // ������ � �������������� ����������
};


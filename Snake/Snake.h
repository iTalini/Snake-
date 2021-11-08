#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

using namespace sf;
using namespace std;


class Snake
{
private:
	vector<Vector2f> pos; // ����� ������������ ����
	vector <CircleShape> body_part;//����� ���� ������

	Vector2f currentDir; // ����������� � ������� �������� ������, ����� ������ ���������� �� ����������

	float step; // �� ����� ���������� ���� ������������ �� ���

public:
	Snake(); // ������������� �������� ����������

	void AddBodyPart(Vector2f next_coord); // ���� ������
	void CreatePart(Vector2f coord); // ��������� ���������� ��� ������ ���� ������

	Vector2f GetPosition(int whatPart); // ��������� ����� ������������ ����� ���� ������
	void ChangePosition(); // ����������� ����

	Vector2f GetCurrentDir();

	//������� �� ����������� ����������� � �������� ����������
	void CheckUp();
	void CheckDown();
	void CheckLeft();
	void CheckRight();

	bool SelfCollision();// ��������� �� �� � ����
	bool WallCollision(RectangleShape *wall);//����� � �����

	bool Check_Boundaries(Vector2f next_coord);//���� �� ����� �� ������� ����, ������������ � ��������������� �������

	void DrawSnake(RenderWindow *window);//��������� ����

	void CleanSnake();//������� ������

	CircleShape GetShape(int i);//������ � ������ ���� ����
	int SnakeSize();//���-�� ������ ������

	void Update();//�������� ������ ���� ���������� � �� ������������
};


#pragma once
#include <iostream>
#include "Snake.h"
#include "Wall.h"
#include "Food.h"
#include <fstream>

using namespace sf;

class Game_Window
{


private:
	Vector2f wind_size; // ������ ����
	RenderWindow window; // ���� ������� �� ���������
	const unsigned int FPS = 60;
	static const Time TimePerFrame; // ��� ������� ������

	int lastGameState; // ������� ��������� ����, ��� �����
	int gameState; // ��� �� ������ ������

	Font font; //�����

	//������, ��� � ������
	Text startText;
	Text gameLightText;
	Text gameMiddleText;
	Text gameHardText;
	Text endText;
	Text winText;
	Text scoreText;

	int score; // ����
	
	vector <String> levels;//����� � ���������� ���������

	Wall walls; // �����

	int speed; // �������� ������

	Snake snake;

	Food food;

	bool emptyForFood; // ����� ��� "���" ����������

	Time timeSinceLastMove; // ����� ��� ������ ����� ������� ��������, ��� �������� �������� ����

public:
	enum GameStatuse { StartMenu, Light, Middle, Hard, Paused, FinishMenu, WinMenu };
	Event event;

	Game_Window(); // ������������� �������� ����������

	void GameStart(); // ������/���������� ������

	void Input();

	void Draw(); // ���������

	void DrawWalls();
	void DrawSnake();

	void InitialAllText(); //������ ��������� ��� ������ �� ������
	static void SetUpText(Text *textItem, const Font &font, const String &value, int size, Color colour); // ���������� �������� ��������� ��� ������

	void DrawText();

	void MoveFood(); // ���� ������ "c����" ���, �� ������ ������ ��� �� ����� ����������
	void ChangeSpeed(); // �������� ����

	void CheckLevelFiles(); // ��������� ���������� �� ����� � ��������
	void LoadLevel(int game_state); // ��������� ������

	void Run(); // �������� ����

	void TogglePause(); // ����� ���� �����
};


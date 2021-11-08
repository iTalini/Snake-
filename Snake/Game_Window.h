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
	Vector2f wind_size; // размер окна
	RenderWindow window; // окно которое мы исползуем
	const unsigned int FPS = 60;
	static const Time TimePerFrame; // для частоты кадров

	int lastGameState; // прошлое состояние игры, для паузы
	int gameState; // что мы делаем сейчас

	Font font; //шрифт

	//тексты, что я вывожу
	Text startText;
	Text gameLightText;
	Text gameMiddleText;
	Text gameHardText;
	Text endText;
	Text winText;
	Text scoreText;

	int score; // очки
	
	vector <String> levels;//карты с вариациями сложности

	Wall walls; // стены

	int speed; // скорость змейки

	Snake snake;

	Food food;

	bool emptyForFood; // место для "еды" подходящее

	Time timeSinceLastMove; // время что прошло поцле прошлой итерации, для контроля скорости игры

public:
	enum GameStatuse { StartMenu, Light, Middle, Hard, Paused, FinishMenu, WinMenu };
	Event event;

	Game_Window(); // инициализация основных параметров

	void GameStart(); // запуск/перезапуск змейки

	void Input();

	void Draw(); // отрисовка

	void DrawWalls();
	void DrawSnake();

	void InitialAllText(); //задать параметры для текста на экране
	static void SetUpText(Text *textItem, const Font &font, const String &value, int size, Color colour); // установить заданные параметры для текста

	void DrawText();

	void MoveFood(); // если змейка "cъела" еду, мы должны задать для неё новые координаты
	void ChangeSpeed(); // ускоряем игру

	void CheckLevelFiles(); // проверить существуют ли файлы с уровнями
	void LoadLevel(int game_state); // загружаем уровни

	void Run(); // итерация игры

	void TogglePause(); // пауза есть пауза
};


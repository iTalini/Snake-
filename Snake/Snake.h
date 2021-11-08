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
	vector<Vector2f> pos; // место расположени€ змеи
	vector <CircleShape> body_part;//части тела змейки

	Vector2f currentDir; // направление в котором движетс€ змейка, когда кнопки управлени€ не нажимаютс€

	float step; // на какое рассто€ни€ зме€ перемещаетс€ за раз

public:
	Snake(); // инициализаци€ основных параметров

	void AddBodyPart(Vector2f next_coord); // рост змейки
	void CreatePart(Vector2f coord); // установка параметров дл€ частей тела змейки

	Vector2f GetPosition(int whatPart); // проверить место расположение части тела змейки
	void ChangePosition(); // перемещение змеи

	Vector2f GetCurrentDir();

	//прверка на возможность перемещени€ в заданном напрвлении
	void CheckUp();
	void CheckDown();
	void CheckLeft();
	void CheckRight();

	bool SelfCollision();// врезались ли мы в змею
	bool WallCollision(RectangleShape *wall);//может в стену

	bool Check_Boundaries(Vector2f next_coord);//если мы вышли за пределы окна, возвращаемс€ с противоположной стороны

	void DrawSnake(RenderWindow *window);//отрисовка змеи

	void CleanSnake();//очистка пам€ти

	CircleShape GetShape(int i);//доступ к част€м тела змеи
	int SnakeSize();//кол-во частей змейки

	void Update();//передать част€м тела информацию о их расположении
};


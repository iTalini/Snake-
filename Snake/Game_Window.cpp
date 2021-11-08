#include "Game_Window.h"
#include <random>
#include <thread>

const sf::Time Game_Window::TimePerFrame = seconds(1.0f / 60.f);

Game_Window::Game_Window()
{
	wind_size = Vector2f(600, 600);
	window.create(VideoMode(wind_size.x, wind_size.y), "Snake");
	window.setFramerateLimit(FPS);//����������� �� ������� ������ �� ����������� ������������� �������

	InitialAllText();

	gameState = GameStatuse::StartMenu;
	lastGameState = GameStatuse::StartMenu;

	CheckLevelFiles();
}

void Game_Window::GameStart()
{
	LoadLevel(gameState);

	score = 0;
	speed = 5;

	scoreText.setString("Score: " + to_string(score));

	timeSinceLastMove = Time::Zero;

	lastGameState = gameState;

	//���� �� ������������� ����, �� ����� �������� ������
	snake.CleanSnake();
	snake.AddBodyPart(Vector2f(0, 0));

	//��������� ���
	MoveFood();
}

void Game_Window::Draw()
{
	//��������� ���� ������
	window.clear(Color::Black);

	if (gameState != GameStatuse::StartMenu && gameState != GameStatuse::FinishMenu
		&& gameState != GameStatuse::WinMenu) // ���� �� ��� �������� ������, �� �� ���� ����������. � ���� �������, ��� ����� ������ �����
	{
		walls.DrawWalls(&window);

		snake.DrawSnake(&window);

		window.draw(food.getSprite());
	}

	DrawText();

	window.display();
}

void Game_Window::MoveFood()
{
	Vector2f newFoodLocation;

	srand(time(nullptr));
	emptyForFood = false;//��������� �� �� ��������� ���������� ��� "���"
	while (!emptyForFood)
	{
		//������
		std::random_device rd; //�������� ��������� ����� �� ����������� ����������� 
		std::mt19937 gen(rd()); // ��������� ���������
		std::uniform_int_distribution<> distr(25, 575); // ���������� ��������, ����� ���� 600�600, �� ����� - 25�25

		newFoodLocation.x = (float)(distr(gen));
		newFoodLocation.y = (float)(distr(gen));

		emptyForFood = true;//�������� �� ��������� ��������� �����

		//��������� ��� �� �� ���� ����������� ����
		for (int i = 0; i < snake.SnakeSize(); i++)
		{
			if (food.CheckCollision(snake.GetPosition(i), newFoodLocation))
			{
				//�������� ��������� ����� ��� ���
				emptyForFood = false;
				break;
			}
		}
		//��������� �� ������� ����
		for (int i = 0; i < walls.GetAmountOfWalls(); i++)
		{
			if (food.CheckCollision(walls.getShape(i)->getPosition(), newFoodLocation))
			{
				//�������� ��������� ����� ��� ���
				emptyForFood = false;
				break;
			}
		}

	}
	//���, � ��� ���� ����� ����������
	food.setPosition(newFoodLocation);
}

void Game_Window::ChangeSpeed()
{
	if ((gameState == GameStatuse::Middle || gameState == GameStatuse::Light) && score % 20 == 0)
		speed++;
	else if (gameState == GameStatuse::Hard)
		speed++;
}

void Game_Window::CheckLevelFiles()
{
	//����� �������� ����� � ���������� ����
	ifstream levelsmanifest("levels.txt");

	//����� �������� ����
	ifstream testfile;
	//manifestline - �������� ����� �����, ��� ��� ������ �� levelsmanifest. ������ �������� � ����� ������
	for (string manifestline; getline(levelsmanifest, manifestline);)
	{
		testfile.open(manifestline);
		if (testfile.is_open())
		{
			//��������� ����� � ���� ���������
			levels.emplace_back(manifestline);
			//��������� ��������� ���� ��� ��������� ������
			testfile.close();
		}
	}
}

//����� �� ��������� ��������� ���� � ������ � �� ������ ������������ ������ �����
void Game_Window::LoadLevel(int game_state)
{
	string levelFile = levels[game_state - 1];

	ifstream level(levelFile);

	string line;

	if (level.is_open())
	{
		for (int row = 0; row < 30; row++)
		{
			getline(level, line);
			for (int column = 0; column < 30; column++)
			{
				if (line[column] == 'x')
				{
					walls.AddShape(Vector2f(column * 20, row * 20));
				}
			}
		}
	}
	level.close();
}

void Game_Window::Run()
{
	Clock clock;
	while (window.isOpen())
	{
		Time dt = clock.restart();
		timeSinceLastMove += dt;

		if (gameState == GameStatuse::Paused) // ���� �� �����, ������ ����������
		{
			Input();

			sleep(milliseconds(2));
			continue;
		}
		else if (gameState == GameStatuse::StartMenu || gameState == GameStatuse::FinishMenu || gameState == GameStatuse::WinMenu) // ��������� ����� ����
		{
			Input();
			
			Draw();
			sleep(milliseconds(2));
			continue;
		}

		//����
		if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) // ����������� �������� ������
		{
			Input();

			if (food.CheckCollision(snake.GetPosition(0), food.getSprite().getPosition())) // ��������� �� ������������ ���� � ���
			{
				score += 10; //����
				scoreText.setString("Score: " + to_string(score)); //��������� ����� � ������
				if (score >= 370)
				{
					Draw();
					gameState = GameStatuse::WinMenu;
					continue;
				}

				Vector2f coordNewBodyPart = Vector2f(snake.GetPosition(snake.SnakeSize() - 1));//���������� ��� ������� ����� ���� ������
				
				// ������� ������ � ������
				sf::Thread thread1(&Snake::ChangePosition, &snake);
				thread1.launch();

				snake.AddBodyPart(coordNewBodyPart); // ��������� ����� �����. ���������� �� ��������� �� ����, ��� ����������� ����.
				
				if (speed != 18) // ������������ ��������, � ������ ����������
				{
					ChangeSpeed();
				}

				sf::Thread thread2(&Game_Window::MoveFood, this); // �����
				thread2.launch();
			}
			else if (snake.SelfCollision()) // ������������ ���� �� ������ ������� ����
			{
				gameState = GameStatuse::FinishMenu;
			}
			else // ��������, �� ������ �� ���������, ��������
			{
				for (int i = 0; i < walls.GetAmountOfWalls(); i++) // ��������� �� ������������ ���� �� �������
				{
					if (snake.WallCollision(walls.getShape(i)))
						gameState = GameStatuse::FinishMenu;
				}
				if (gameState != GameStatuse::FinishMenu) // ������ ����� �� ������
				{
					// ������� ������ � ������
					sf::Thread thread1(&Snake::ChangePosition, &snake);
					thread1.launch();
				}
			}
			timeSinceLastMove = Time::Zero;
		}

		Draw();
	}
}

void Game_Window::TogglePause()
{
	if (gameState == GameStatuse::Light || gameState == GameStatuse::Middle
		|| gameState == GameStatuse::Hard)
	{
		lastGameState = gameState;
		gameState = GameStatuse::Paused;
	}
	else if (gameState == GameStatuse::Paused)
		gameState = lastGameState;
}

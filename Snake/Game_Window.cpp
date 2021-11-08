#include "Game_Window.h"
#include <random>
#include <thread>

const sf::Time Game_Window::TimePerFrame = seconds(1.0f / 60.f);

Game_Window::Game_Window()
{
	wind_size = Vector2f(600, 600);
	window.create(VideoMode(wind_size.x, wind_size.y), "Snake");
	window.setFramerateLimit(FPS);//ограничение на частоту кадров до максимально фиксированной частоты

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

	//если мы перезапускаем игру, то лучше обновить змейку
	snake.CleanSnake();
	snake.AddBodyPart(Vector2f(0, 0));

	//добавляем еду
	MoveFood();
}

void Game_Window::Draw()
{
	//заполнить окно чёрным
	window.clear(Color::Black);

	if (gameState != GameStatuse::StartMenu && gameState != GameStatuse::FinishMenu
		&& gameState != GameStatuse::WinMenu) // если мы уже прохолим уровни, то их надо отрисовать. В иных случаях, нам нужен только текст
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
	emptyForFood = false;//правильно ли мы подбираем координаты для "еды"
	while (!emptyForFood)
	{
		//рандом
		std::random_device rd; //получить случайное число от аппаратного обеспечения 
		std::mt19937 gen(rd()); // запустить генератор
		std::uniform_int_distribution<> distr(25, 575); // определить диапазон, рамер окна 600х600, но стена - 25х25

		newFoodLocation.x = (float)(distr(gen));
		newFoodLocation.y = (float)(distr(gen));

		emptyForFood = true;//возможно мы правильно подобрали место

		//проверяем нет ли на этох координатах змеи
		for (int i = 0; i < snake.SnakeSize(); i++)
		{
			if (food.CheckCollision(snake.GetPosition(i), newFoodLocation))
			{
				//поробуем подобрать место ещё раз
				emptyForFood = false;
				break;
			}
		}
		//проверяем на наличее стен
		for (int i = 0; i < walls.GetAmountOfWalls(); i++)
		{
			if (food.CheckCollision(walls.getShape(i)->getPosition(), newFoodLocation))
			{
				//поробуем подобрать место ещё раз
				emptyForFood = false;
				break;
			}
		}

	}
	//ура, у нас есть новые координаты
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
	//место загрузки файла с названиями карт
	ifstream levelsmanifest("levels.txt");

	//место загрузки карт
	ifstream testfile;
	//manifestline - названия файла карты, что был считан из levelsmanifest. Каждое название с новой строки
	for (string manifestline; getline(levelsmanifest, manifestline);)
	{
		testfile.open(manifestline);
		if (testfile.is_open())
		{
			//добавляем карту в нашу программу
			levels.emplace_back(manifestline);
			//закрываем считанный файл для избежания ошибок
			testfile.close();
		}
	}
}

//здесь мы считываем построчно файл с картой и на основе прочитанного создаём стены
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

		if (gameState == GameStatuse::Paused) // игра на паузе, ничего инересного
		{
			Input();

			sleep(milliseconds(2));
			continue;
		}
		else if (gameState == GameStatuse::StartMenu || gameState == GameStatuse::FinishMenu || gameState == GameStatuse::WinMenu) // отрисовка наших меню
		{
			Input();
			
			Draw();
			sleep(milliseconds(2));
			continue;
		}

		//игра
		if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) // регулировка скорости змейки
		{
			Input();

			if (food.CheckCollision(snake.GetPosition(0), food.getSprite().getPosition())) // проверяем на столкновение змеи и еды
			{
				score += 10; //очки
				scoreText.setString("Score: " + to_string(score)); //обновляем текст с очками
				if (score >= 370)
				{
					Draw();
					gameState = GameStatuse::WinMenu;
					continue;
				}

				Vector2f coordNewBodyPart = Vector2f(snake.GetPosition(snake.SnakeSize() - 1));//координаты для будущей части тела змейки
				
				// двигаем змейку в потоке
				sf::Thread thread1(&Snake::ChangePosition, &snake);
				thread1.launch();

				snake.AddBodyPart(coordNewBodyPart); // добавляем новую часть. Координаты мы сохранили до того, как передвинули змею.
				
				if (speed != 18) // максимальная скорость, её вполне достаточно
				{
					ChangeSpeed();
				}

				sf::Thread thread2(&Game_Window::MoveFood, this); // поток
				thread2.launch();
			}
			else if (snake.SelfCollision()) // столкновение змеи со своими частями тела
			{
				gameState = GameStatuse::FinishMenu;
			}
			else // обошлось, мы никуда не врезались, наверное
			{
				for (int i = 0; i < walls.GetAmountOfWalls(); i++) // проверяем на столкновение змеи со стенами
				{
					if (snake.WallCollision(walls.getShape(i)))
						gameState = GameStatuse::FinishMenu;
				}
				if (gameState != GameStatuse::FinishMenu) // теперь точно всё хорошо
				{
					// двигаем змейку в потоке
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

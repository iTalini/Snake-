#include "Game_Window.h"

void Game_Window::Input()
{
	Event event{};

	while (window.pollEvent(event))
	{
		//закрытие окна
		if (event.type == Event::Closed)
		{
			window.close();
			std::cout << "Close\n";
		}

		//входящий вызов с клавиатуры
		if (event.type == Event::KeyPressed)
		{
			if (gameState == GameStatuse::FinishMenu || gameState == GameStatuse::WinMenu)
			{
				if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Numpad1)
				{
					gameState = lastGameState;
					GameStart();
				}
				else if (event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Numpad2)
				{
					gameState = GameStatuse::StartMenu;
					lastGameState = gameState;
					walls.CleanWalls();
					StartMenu();
				}
				else if (event.key.code == Keyboard::Num3 || event.key.code == Keyboard::Numpad3)
					window.close();
			}
			else if (gameState == GameStatuse::StartMenu)
			{
				if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Numpad1)
				{
					gameState = GameStatuse::Light;
					GameStart();
				}
				else if (event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Numpad2)
				{
					gameState = GameStatuse::Middle;
					GameStart();
				}
				else if (event.key.code == Keyboard::Num3 || event.key.code == Keyboard::Numpad3)
				{
					gameState = GameStatuse::Hard;
					GameStart();
				}
				else if (event.key.code == Keyboard::Num4 || event.key.code == Keyboard::Numpad4)
					window.close();
			}

			if (event.key.code == Keyboard::Escape)
			{
				window.close();
			}

			else if (event.key.code == Keyboard::Pause)
			{
				if (gameState != GameStatuse::StartMenu && gameState != GameStatuse::FinishMenu)
					TogglePause();
			}


			else if (event.key.code == Keyboard::Up)
			{
				snake.CheckUp();
			}
			else if (event.key.code == Keyboard::Down)
			{
				snake.CheckDown();
			}
			else if (event.key.code == Keyboard::Left)
			{
				snake.CheckLeft();
			}
			else if (event.key.code == Keyboard::Right)
			{
				snake.CheckRight();
			}

		}
	}
}
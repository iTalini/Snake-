#include "Game_Window.h"

void Game_Window::InitialAllText()
{
	font.loadFromFile("YahfieHeavy.ttf");
	SetUpText(&startText, font, "Press to choose:\n1. Light level\n2. Middle level\n3. Hard level\n4. Exit", 35, Color::White);
	FloatRect titleBox = startText.getLocalBounds(); // для узнавания размера текста
	startText.setPosition(Vector2f(300 - titleBox.width / 2, 300 - titleBox.height / 2)); // координаты для текста

	SetUpText(&gameLightText, font, "Light level", 20, Color::White);
	FloatRect lightBox = gameLightText.getLocalBounds();
	gameLightText.setPosition(Vector2f(600 - lightBox.width - 10, 0));

	SetUpText(&gameMiddleText, font, "Middle level", 20, Color::White);
	FloatRect middleBox = gameMiddleText.getLocalBounds();
	gameMiddleText.setPosition(Vector2f(600 - middleBox.width - 10, 0));

	SetUpText(&gameHardText, font, "Hard level", 20, Color::White);
	FloatRect hardBox = gameHardText.getLocalBounds();
	gameHardText.setPosition(Vector2f(600 - hardBox.width - 10, 0));

	SetUpText(&endText, font, "Press to choose:\n1. Restart\n2. Back to menu\n3. Exit", 35, Color::White);
	FloatRect endBox = endText.getLocalBounds();
	endText.setPosition(Vector2f(300 - endBox.width / 2, 300 - endBox.height / 2));

	SetUpText(&winText, font, "Congratulation!!!\nYour score is 370!\n	You WIN!\nPress to choose:\n1. Restart\n2. Back to menu\n3. Exit", 35, Color::White);
	FloatRect winBox = winText.getLocalBounds();
	winText.setPosition(Vector2f(300 - winBox.width / 2, 300 - winBox.height / 2));

	SetUpText(&scoreText, font, "Score: 0", 20, Color::White);
	FloatRect foodBox = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(10, 0));

}

void Game_Window::SetUpText(Text* textItem, const Font& font, const String& value, int size, Color colour)
{
	textItem->setFont(font); //шрифт
	textItem->setString(value); //текст
	textItem->setCharacterSize(size); //размер шрифта
	textItem->setFillColor(colour); //цвет текста
}

void Game_Window::DrawText()
{
	if (gameState == GameStatuse::StartMenu)
	{
		window.draw(startText);
	}
	else if (gameState == GameStatuse::Light)
	{
		window.draw(gameLightText);
		window.draw(scoreText);
	}
	else if (gameState == GameStatuse::Middle)
	{
		window.draw(gameMiddleText);
		window.draw(scoreText);
	}
	else if (gameState == GameStatuse::Hard)
	{
		window.draw(gameHardText);
		window.draw(scoreText);
	}
	else if (gameState == GameStatuse::FinishMenu)
		window.draw(endText);
	else if (gameState == GameStatuse::WinMenu)
		window.draw(winText);
}

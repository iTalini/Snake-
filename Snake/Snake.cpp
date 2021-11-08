#include "Snake.h"

Snake::Snake()
{
	step = 20;
}

void Snake::AddBodyPart(Vector2f next_coord)
{
	if (body_part.size() == 0) // рождение змейки
	{
		CreatePart(Vector2f(290, 290));
		CreatePart(Vector2f(270, 290));
		CreatePart(Vector2f(250, 290));

		pos.emplace_back(Vector2f(290, 290));
		pos.emplace_back(Vector2f(270, 290));
		pos.emplace_back(Vector2f(250, 290));

		currentDir = Vector2f(step, 0.f);
	}
	else // совсем большой уже стала
	{
		CreatePart(next_coord);
	}
}

void Snake::CreatePart(Vector2f coord)
{
	body_part.emplace_back(CircleShape());

	int i = body_part.size() - 1;

	body_part[i].setPosition(coord);
	body_part[i].setRadius(10);
	if (i == 0)
		body_part[i].setFillColor(Color::Red);
	else
		body_part[i].setFillColor(Color::Yellow);

	pos.emplace_back(coord);
}

Vector2f Snake::GetPosition(int whatPart)
{
	return pos[whatPart];
}

void Snake::ChangePosition()
{
	for (int i = pos.size() - 1; i > 0; i--)
	{
		pos[i].x = pos[i - 1].x;
		pos[i].y = pos[i - 1].y;
	}

	if (!Check_Boundaries(currentDir)) // проверяем на возможный выход змеи за поля окна
	{
		pos[0].x += currentDir.x;
		pos[0].y += currentDir.y;
	}
	Update();
}

Vector2f Snake::GetCurrentDir()
{
	return currentDir;
}


//проверка на движения змеи в противоположную сторону, от задаваемого вектора движений. Змея не может зайти внутри себя
void Snake::CheckUp()
{
	if (!(pos[0].y > pos[1].y))
	{
		currentDir = Vector2f(0.f, -step);
	}
}

void Snake::CheckDown()
{
	if (!(pos[0].y < pos[1].y))
	{
		currentDir = Vector2f(0.f, step);
	}
}

void Snake::CheckLeft()
{
	if (!(pos[0].x > pos[1].x))
	{
		currentDir = Vector2f(-step, 0.f);
	}
}

void Snake::CheckRight()
{
	if (!(pos[0].x < pos[1].x))
	{
		currentDir = Vector2f(step, 0.f);
	}
}


bool Snake::SelfCollision() //проверка на столкновение змеи с частями себя
{
	//10 - радиус
	// тут мы ищем растояние между центрами двух окружностей, если он меньше суммы их радиусов => окружности пересекаются
	Vector2f one = Vector2f(body_part[0].getPosition().x + 10, body_part[0].getPosition().y + 10);
	for (int i = 1; i < body_part.size(); i++)
	{
		Vector2f two = Vector2f(body_part[i].getPosition().x + 10, body_part[i].getPosition().y + 10);

		float dist = std::sqrt((abs(one.x - two.x) * abs(one.x - two.x))
			+ (abs(one.y - two.y) * abs(one.y - two.y)));

		if (dist < 20)
		{
			return(true);
		}
	}
	return false;
}

bool Snake::WallCollision(RectangleShape *wall)//проверка на столкновение со стеной
{
	//25 - стороны квадрата(стены)
	//10 - радиус окружности(головы змеи)
	Vector2f circleDistance;
	circleDistance.x = abs(body_part[0].getPosition().x - wall->getPosition().x);
	circleDistance.y = abs(body_part[0].getPosition().y - wall->getPosition().y);

	if (circleDistance.x > (25 / 2 + 10))
		return false;
	if (circleDistance.y > (25 / 2 + 10))
		return false;

	if (circleDistance.x <= (25 / 2))
		return true;
	if (circleDistance.y <= (25 / 2))
		return true;

	float cornerDistance_sq = ((circleDistance.x - 25 / 2) * (circleDistance.x - 25 / 2)) +
		((circleDistance.y - 20 / 2) * (circleDistance.y - 20 / 2));

	return (cornerDistance_sq <= (10 * 10));

}

bool Snake::Check_Boundaries(Vector2f next_coord) // проверка на выход за пределы поля
{
	if (body_part[0].getPosition().y + next_coord.y <= 0)
	{
		pos[0].y = 600;
		return true;
	}
	else if (body_part[0].getPosition().y + next_coord.y >= 600)
	{
		pos[0].y = 0;
		return true;
	}
	else if (body_part[0].getPosition().x + next_coord.x <= 0)
	{
		pos[0].x = 600;
		return true;
	}
	else if (body_part[0].getPosition().x + next_coord.x >= 600)
	{
		pos[0].x = 0;
		return true;
	}
	return false;
}

void Snake::DrawSnake(RenderWindow* window)
{
	for (int i = 0; i < body_part.size(); i++)
	{
		window->draw(body_part[i]);
	}
}

void Snake::CleanSnake()
{
	pos.clear();
	body_part.clear();
}

CircleShape Snake::GetShape(int i)
{
	return body_part[i];
}

int Snake::SnakeSize() // кол-во частей тела у змеи
{
	return body_part.size();
}


void Snake::Update()
{
	for (int i = 0; i < body_part.size(); i++)
	{
		body_part[i].setPosition(pos[i]);

	}
}

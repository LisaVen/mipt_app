//
// Created by denis on 22.03.18.
//

#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "draw_obj.h"
#include "game_obj.h"

//Это для передвижения, но я не уверена на счет некоторых вещей, таких, как Mob. Возможно, стоит делать все через GameObject, плюс, возможно, стоит прописать еще какие-то штуки для перемещений.

class Vector {
public:
    float x, y;
};

class Mob {
public:
    float x,y;//координаты float, так как движения более точные
    Vector Way;//вектор движения
    
    void AddVector(Vector NewWay);
    void Move();
};

void Mob::AddVector(Vector NewWay) {//добавляем новый вектор
    Way.x+=NewWay.x;//прибавление нового вектора
    Way.y+=NewWay.y;
}

void Mob::Move() {//функция перемещения по вектору
    x+=Way.x;
    y+=Way.y;
}

// Далее идут столкновения, нашла алгоритм на Java, он практически полностью прописан, но нужно его переделать под с++, да и разобраться в нем как следует.

//.h file code:

#include <string>
#include <vector>
#include <cmath>

//Forward class declarations:
class CheckResult;

class Collision2D
{
private:
Vector *mtv;
float mtvLength = 0;
bool_Renamed *collide;

public:
virtual ~Collision2D()
{
	delete mtv;
	delete collide;
}

Collision2D(std::array_Renamed<Vector2*> &first, std:: array_Renamed);

private:
static CheckResult *check(std::array_Renamed<Vector2*> &firstVertices, std::array_Renamed<Vector2*> &secondVertices);

static float getIntersectionLength(Vector2 *firstProjection, Vector2 *secondProjection);

static void setNormal(Vector2 *normal, std::array_Renamed<Vector2*> &firstVertices, std::array_Renamed<Vector2*> &secondVertices, int num);

static void setNormal(Vector2 *normal, std::vector<Vector2*> &vertices, int num);

public:
virtual Vector *getMTV();

virtual float getMTVLength();

virtual bool_Renamed *isCollide();

	std::wstring toString() override;

private:
class CheckResult
{
private:
	Vector *const mtv;
	const float mtvLength;

public:
	virtual ~CheckResult()
	{
		delete mtv;
	}

	CheckResult(Vector *mtv, float mtvLength);
};
};

//.cpp file:

Collision2D::Collision2D(std::array_Renamed<Vector*> &first, std:: array_Renamed)
{
		CheckResult *result = check(first, second);

		if (result == nullptr)
		{
			collide = false;
			return;
		}

		collide = true;
		mtv = result->mtv;
		mtvLength = abs(result->mtvLength);
}

Collision2D::CheckResult *Collision2D::check(std::array_Renamed<Vector*> &firstVertices, std::array_Renamed<Vector*> &secondVertices)
{
		Vector *mtv = nullptr;
		Vector *normal = Vector::getInstance();
		float minMTVLength = 0;
		int count = firstVertices.size() + secondVertices.size();

		for (int i = 0; i < count; i++)
		{
			setNormal(normal, firstVertices, secondVertices, i);

			Vector *firstProjection = normal->getProjection(firstVertices);
			Vector *secondProjection = normal->getProjection(secondVertices);

			if (firstProjection->getX() < secondProjection->getY() || secondProjection->getX() < firstProjection->getY())
			{
				return nullptr;
			}

			if (mtv == nullptr)
			{
				mtv = Vector::getInstance(normal);
				minMTVLength = getIntersectionLength(firstProjection, secondProjection);
			}
			else
			{
				float mtvLength = getIntersectionLength(firstProjection, secondProjection);
				if (std::abs(mtvLength) < std::abs(minMTVLength))
				{
					mtv->setFrom(normal);
					minMTVLength = mtvLength;
				}
			}
		}

		return new CheckResult(mtv, minMTVLength);
}

float Collision2D::getIntersectionLength(Vector *firstProjection, Vector *secondProjection)
{
		return (secondProjection->getY() - firstProjection->getX() > 0) ? secondProjection->getY() - firstProjection->getX() : firstProjection->getY() - secondProjection->getX();
}

void Collision2D::setNormal(Vector *normal, std::array_Renamed<Vector*> &firstVertices, std::array_Renamed<Vector*> &secondVertices, int num)
{
		if (num < firstVertices.size())
		{
			setNormal(normal, firstVertices, num);
		}
		else
		{
			num -= firstVertices.size();
			setNormal(normal, secondVertices, num);
		}
}

void Collision2D::setNormal(Vector *normal, std::vector<Vector*> &vertices, int num)
{
		Vector *firstPoint = vertices[num];
		Vector *secondPoint = vertices[num + 1 == vertices.size() ? 0 : num + 1];

		Vector *edge = secondPoint->getSubtract(firstPoint);

		normal->setX(-edge->getY());
		normal->setY(edge->getX());

		normal->normalize();
}

Vector *Collision2D::getMTV()
{
		return Vector::getInstance(mtv);
}

float Collision2D::getMTVLength()
{
		return mtvLength;
}

bool_Renamed *Collision2D::isCollide()
{
		return collide;
}

std::wstring Collision2D::toString()
{
//TODO TASK: There is no native C++ equivalent to 'toString':
   return std::wstring::format(L"{Mtv:%s, Length:%f}", mtv == nullptr ? L"<null>" : mtv->toString(), mtvLength);
}

Collision2D::CheckResult::CheckResult(Vector2 *mtv, float mtvLength) : mtv(mtv), mtvLength(mtvLength)
{
}

#ifndef MIPT_APP_SIMPLE_PHYSICS_H
#define MIPT_APP_SIMPLE_PHYSICS_H

#endif //MIPT_APP_SIMPLE_PHYSICS_H

/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Source file of the "Point" object with the implementations of operator overloads and auxiliary functions.
 */

#include "../Headers/Point.h"

Point::Point()
{
	xCoordinate = yCoordinate = 0;
}

Point::Point(int xy)
{
	xCoordinate = yCoordinate = xy;
}

Point::Point(int x, int y)
{
	xCoordinate = x;
	yCoordinate = y;
}

Point::Point(const Point& otherPoint)
{
	xCoordinate = otherPoint.xCoordinate;
	yCoordinate = otherPoint.yCoordinate;
}

int Point::X() { return xCoordinate; }
int Point::Y() { return yCoordinate; }

Point Point::operator*(const int& value)
{
	Point result = {
		this->xCoordinate * value,
		this->yCoordinate * value
	};

	return result;
}

Point Point::operator*(const Point& otherPoint)
{
	Point result = {
		this->xCoordinate * otherPoint.xCoordinate,
		this->yCoordinate * otherPoint.yCoordinate
	};

	return result;
}

Point Point::operator+(const Point& otherPoint)
{
	Point result = {
		this->xCoordinate + otherPoint.xCoordinate,
		this->yCoordinate + otherPoint.yCoordinate
	};

	return result;
}

Point Point::operator-(const Point& otherPoint)
{
	Point result = {
		this->xCoordinate - otherPoint.xCoordinate,
		this->yCoordinate - otherPoint.yCoordinate
	};

	return result;
}

Point& Point::operator+=(const Point& otherPoint)
{
	*this = operator+(otherPoint);
	return *this;
}

Point& Point::operator-=(const Point& otherPoint)
{
	*this = operator-(otherPoint);
	return *this;
}


bool Point::operator==(const Point& otherPoint)
{
	return xCoordinate == otherPoint.xCoordinate
		&& yCoordinate == otherPoint.yCoordinate;
}

bool Point::operator!=(const Point& otherPoint)
{
	return xCoordinate != otherPoint.xCoordinate
		|| yCoordinate != otherPoint.yCoordinate;
}

long Point::sqrDistance(const Point& otherPoint)
{
	Point p = operator-(otherPoint);

	return (p.xCoordinate * p.xCoordinate)
		+ (p.yCoordinate * p.yCoordinate);
}
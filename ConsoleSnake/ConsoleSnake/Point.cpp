#include "../Headers/Point.h"

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

Point Point::operator*(const int& value)
{
	Point result {
		this->xCoordinate * value,
		this->yCoordinate * value
	};

	return result;
}

Point Point::operator*(const Point& otherPoint)
{
	Point result{
		this->xCoordinate * otherPoint.xCoordinate,
		this->yCoordinate * otherPoint.yCoordinate
	};

	return result;
}

Point Point::operator+(const Point& otherPoint)
{
	Point result{
		this->xCoordinate + otherPoint.xCoordinate,
		this->yCoordinate + otherPoint.yCoordinate
	};

	return result;
}

Point Point::operator-(const Point& otherPoint)
{
	Point result{
		this->xCoordinate - otherPoint.xCoordinate,
		this->yCoordinate - otherPoint.yCoordinate
	};

	return result;
}

Point Point::operator+=(const Point& otherPoint)
{
	return operator+(otherPoint);
}

Point Point::operator-=(const Point& otherPoint)
{
	return operator-(otherPoint);
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
#pragma once

class Point
{
	private:
		int xCoordinate;
		int yCoordinate;

	public:
		Point(int x, int y);
		Point(const Point& otherPoint);
		Point operator*(const int& value);
		Point operator*(const Point& otherPoint);
		Point operator+(const Point& otherPoint);
		Point operator-(const Point& otherPoint);
		Point operator+=(const Point& otherPoint);
		Point operator-=(const Point& otherPoint);
		bool operator==(const Point& otherPoint);
		bool operator!=(const Point& otherPoint);
		long sqrDistance(const Point& otherPoint);
};
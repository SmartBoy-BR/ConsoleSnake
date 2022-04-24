/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Header of the "Point" object with definitions of the various possible mathematical
 *		operations involving one or more points in the console screen's coordinate system.
 */

#pragma once

class Point
{
	private:
		int xCoordinate;
		int yCoordinate;

	public:
		Point();
		Point(int xy);
		Point(int x, int y);
		Point(const Point& otherPoint);
		int X() const;
		int Y() const;
		Point operator*(const int& value);
		Point operator*(const Point& otherPoint);
		Point operator+(const Point& otherPoint);
		Point operator-(const Point& otherPoint);
		Point& operator+=(const Point& otherPoint);
		Point& operator-=(const Point& otherPoint);
		bool operator==(const Point& otherPoint);
		bool operator!=(const Point& otherPoint);
		long sqrDistance(const Point& otherPoint);
};
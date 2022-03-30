// TestParameterStyle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Box.h"
#include "Circle.h"

int main ()
{
	Circle::BuilderError berr;
	auto circle = Circle::Builder ().centerX ( 10 ).centerY ( 20 ).radius ( -30 ).Build ( berr );
	if ( circle )
		cout << circle->toString () << endl;
	else
		cout << berr.m_error << endl;

	auto box = Box::Builder ().Width ( 100 ).Height ( 50 ).Depth ( 100 );
	cout << box.toString () << " Volume = " << box.getVolume () << endl;

	return 0;
}

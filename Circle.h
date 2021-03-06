#pragma once
#include <sstream>
#include <iostream>
#include "ChainBuilder.h"

using namespace ChainBuilder;

class Circle : ClassBuilder<Circle>
{
	// I don't want let ppl create Circle with no rules, do you?
	Circle () = default;

	// But we must trust in few good friends!
	template <typename T1 , typename T2> friend class ClassBuilder;
	template <typename T1 , typename T2> friend class Parameter;

protected:

	// Here's the circle 
	double m_x = 0.0f;
	double m_y = 0.0f;
	double m_r = 0.0f;

	// I'm lazy to write this everytime
	template <class T> using base = Parameter<T , Circle>;

	// Mandatory  parameter
	template<typename T> struct CenterX : base<T>
	{
		T& centerX ( double X )
		{
			base<T>::getData ().m_x = X;
			return base<T>::getNext ();
		}
	};

	// Mandatory  parameter
	template<typename T> struct CenterY : base<T>
	{
		T& centerY ( double Y )
		{
			base<T>::getData ().m_y = Y;
			return base<T>::getNext ();
		}
	};

	// Mandatory  parameter
	template<typename T> struct Radius : base<T>
	{
		T& radius ( double R )
		{
			base<T>::getData ().m_r = R;
			return base<T>::getNext ();
		}
	};

	// Let's build this circle
	shared_ptr<Circle> build ( IError& error )
	{
		// We can't handle odd circle
		if ( m_r < 0 )
		{
			error.m_error = "Radius cannot be negative!";
			return nullptr;
		}

		// Because make_shared can't be anyone's friend
		shared_ptr<Circle> circle;
		circle.reset ( new Circle () );

		// Just in case something went wrong
		if ( !circle )
			return nullptr;

		circle->m_x = m_x;
		circle->m_y = m_y;
		circle->m_r = m_r;

		// Here is the circle, my friends
		return circle;
	}

public:

	// Please show yourself
	string toString () const
	{
		stringstream ss;
		ss << "Circle(" << m_x << "," << m_y << ")-(" << m_r << ")";
		return ss.str ();
	}

	// Here is how I handle errors
	struct BuilderError : ClassBuilder<Circle>::IError
	{
		operator bool () const
		{
			return !m_error.empty ();
		}
	};

	// Eventually here is how a Circle is built.
	class Builder : public CenterX<CenterY<Radius<ClassBuilder>>>
	{
	};
};

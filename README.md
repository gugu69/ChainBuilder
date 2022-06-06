# Chain Builder with mandatory parameters.

This is what I was looking for:

    auto aCircle = Circle::Builder ().centerX ( 100 ).centerY ( 50 ).radius ( 25 ).Build ();
    
Is a sort of revised *Builder Pattern* with some extra features:

    - They are all mandatory parameters.
    - The sequences is predetermined.

## Description

Everything is in a single header file (that's what I love more...). The usage is quite simple.

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
		template <typename T> friend class ClassBuilder;
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
		shared_ptr<Circle> build ()
		{
			// We can't handle odd circle
			if ( m_r < 0 )
				return nullptr;
	
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
	
		// Eventually here is how a Circle is built.
		class Builder : public CenterX<CenterY<Radius<ClassBuilder>>>
		{
		};
	};


## Getting Started

### Requirements

* Made with with Visual Studio 2022 but it should works in other environments.
* C++17 (because of *constexpr*)

### Where to start

* You can download the sample solution
* or
* Just download "ChainBuilder.h"

### Executing program

* F5
* ahahah, ok stop joking!

## Authors

Just me.

## License

This project is licensed under the [GNU GPLv3] License - see the LICENSE.md file for details

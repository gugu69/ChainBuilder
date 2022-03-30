#pragma once
#include <sstream>
#include "ChainBuilder.h"

using namespace ChainBuilder;

class Box
{
	template <typename T1 , typename T2> friend class Parameter;

	Box () = default;

protected:

	double m_width = 0.0f;
	double m_height = 0.0f;
	double m_depth = 0.0f;

	template <class T> using base = Parameter<T , Box>;

	template<typename T> struct _width : base<T>
	{
		T& Width ( double width )
		{
			base<T>::getData ().m_width = width;
			return base<T>::getNext ();
		}
	};

	template<typename T> struct _height : base<T>
	{
		T& Height ( double height )
		{
			base<T>::getData ().m_height = height;
			return base<T>::getNext ();
		}
	};

	template<typename T> struct _depth : base<T>
	{
		T& Depth ( double depth )
		{
			base<T>::getData ().m_depth = depth;
			return base<T>::getNext ();
		}
	};

public:

	string toString () const
	{
		stringstream ss;
		ss << "Box(" << m_width << "," << m_height << "," << m_depth << ")";
		return ss.str ();
	}

	double getVolume () const
	{
		return m_width * m_height * m_depth;
	}

	class Builder : public _width<_height<_depth<Box>>>
	{
	};
};

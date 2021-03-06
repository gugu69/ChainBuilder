#pragma once
#include <memory>

using namespace std;

namespace ChainBuilder
{
	template <typename T1 , typename T2> class Parameter
	{
		shared_ptr<T1> m_next;
		shared_ptr<T2> m_last;

		template <typename T1 , typename T2> friend class Parameter;

		const shared_ptr<T2>& getLast ()
		{
			if ( !m_last )
				m_last.reset ( new T2 () );

			return m_last;
		}

		void setLast ( const shared_ptr<T2>& last )
		{
			m_last = last;
		}

	protected:

		T2& getData ()
		{
			return *getLast ();
		}

		T1& getNext ()
		{
			if constexpr ( is_same<T1 , T2>::value )
				return *getLast ();
			else
			{
				m_next = make_shared<T1> ();
				m_next->setLast ( getLast () );
				return *m_next;
			}
		}

		Parameter () = default;
	};

	template<typename T1,typename T2 = std::string> class ClassBuilder : public Parameter<T1 , T1>
	{
	public:

		struct IError 
		{
			T2 m_error;
		};

		shared_ptr<T1> Build ()
		{
			auto data = Parameter<T1 , T1>::getData ();
			return data.build ();
		}

		shared_ptr<T1> Build ( IError& error )
		{
			auto data = Parameter<T1 , T1>::getData ();
			return data.build ( error );
		}
	};
}


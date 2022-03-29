#include <memory>
#include <iostream>


using namespace std;

class CC
{
protected:

	long m_valueA;
	long m_valueB;
	long m_valueC;

	template<typename T1 , typename T2 = CC> class ParamA
	{
		shared_ptr<T1> next;
		shared_ptr<T2> last;
	public:
		ParamA ( shared_ptr<T2> pLast = nullptr )
		{
			if ( !pLast )
				pLast.reset ( new T2 );
			last = pLast;
		}
		T1& setValueA ( long valueA )
		{
			last->m_valueA = valueA;
			if ( is_same<T1 , T2>::value )
				return ( T1& ) *last;
			next.reset ( new T1 ( last ) );
			return *next;
		}
	};

	template<typename T1 , typename T2 = CC> class ParamB
	{
		shared_ptr<T1> next;
		shared_ptr<T2> last;
	public:
		ParamB ( shared_ptr<T2> pLast = nullptr )
		{
			if ( !pLast )
				pLast.reset ( new T2 );
			last = pLast;
		}
		T1& setValueB ( long valueB )
		{
			last->m_valueB = valueB;
			if ( is_same<T1 , T2>::value )
				return ( T1& ) *last;
			next.reset ( new T1 ( last ) );
			return *next;
		}
	};

	template<typename T1 , typename T2 = CC> class ParamC
	{
		shared_ptr<T1> next;
		shared_ptr<T2> last;
	public:
		ParamC ( shared_ptr<T2> pLast = nullptr )
		{
			if ( !pLast )
				pLast.reset ( new T2 );
			last = pLast;
		}
		T1& setValueC ( long valueC )
		{
			last->m_valueC = valueC;
			if ( is_same<T1 , T2>::value )
				return ( T1& ) *last;
			else
			{
				next.reset ( new T1 ( last ) );
				return *next;
			}
		}
	};

	friend class ContextClass;

	CC () = default;
	CC ( shared_ptr<CC> ) {};

public:

	void print ()
	{
		cout << "A" << m_valueA << " B" << m_valueB << " C" << m_valueC << endl;
	}

};

class ContextClass : public CC::ParamA< CC::ParamB<CC::ParamC<CC>>>

{
};

void vaffanculo ()
{
	ContextClass ().setValueA ( 1 ).setValueB ( 1 ).setValueC ( 1 ).print ();
}
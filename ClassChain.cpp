#include <iostream>
#include "ChianParametersClass.h"

class DatiRettangolo
{
	friend class Rettangolo;

	#define __CLASS_NAME__ DatiRettangolo
	PREPARE_CLASS
	REQUIRED_PARAMETER ( double , base )
	REQUIRED_PARAMETER ( double , altezza )
	REQUIRED_PARAMETER ( double , spessore )
	OPTIONAL_PARAMETER ( long , colore , 0 )

public:

	[[nodiscard]]
	double volume () const { return m_base * m_altezza * m_spessore; }

};

class Rettangolo : public DatiRettangolo::_base<DatiRettangolo::_altezza<DatiRettangolo::_spessore<DatiRettangolo>>>
{
};


void TestChainParametersClass ()
{
	cout << Rettangolo ().base ( 10 ).altezza ( 10 ).spessore ( 20 ).colore ( 10 ).volume ();
}

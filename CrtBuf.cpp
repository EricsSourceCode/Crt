// Copyright Eric Chauvin 2021 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html




#include "CrtBuf.h"
#include "../CppBase/Casting.h"



void CrtBuf::setToZero()
{
for( Int32 count = 0; count < last; count++ )
  digitAr.setVal( count, 0 );

}



void CrtBuf::setToOne()
{
for( Int32 count = 0; count < last; count++ )
  digitAr.setVal( count, 1 );

}



void CrtBuf::setFromInteger(
                    const Integer& setFrom,
                    IntegerMath& intMath,
                    const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  digitAr.setVal( count, intMath.getMod24(
                 setFrom,
                 sPrimes.getPrimeAt( count )));
  }
}

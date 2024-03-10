// Copyright Eric Chauvin 2021 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#include "Crt.h"
#include "../CppBase/Casting.h"



void Crt::setToZero()
{
for( Int32 count = 0; count < last; count++ )
  digitAr.setVal( count, 0 );

}



void Crt::setToOne()
{
for( Int32 count = 0; count < last; count++ )
  digitAr.setVal( count, 1 );

}



bool Crt::isZero() const
{
for( Int32 count = 0; count < last; count++ )
  {
  if( digitAr.getVal( count ) != 0 )
    return false;

  }

return true;
}



bool Crt::isOne() const
{
for( Int32 count = 0; count < last; count++ )
  {
  if( digitAr.getVal( count ) != 1 )
    return false;

  }

return true;
}



void Crt::copy( const Crt& toCopy )
{
for( Int32 count = 0; count < last; count++ )
  digitAr.setVal( count,
          toCopy.digitAr.getVal( count ));

}



bool Crt::isEqual( const Crt& toCheck ) const
{
for( Int32 count = 0; count < last; count++ )
  {
  if( digitAr.getVal( count ) !=
           toCheck.digitAr.getVal( count ))
    return false;

  }

return true;
}


void Crt::add( const Crt& toAdd,
               const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  // Operations like this could be very fast if
  // they were done on a GPU in parallel.

  Int32 digit = digitAr.getVal( count );
  digit += toAdd.digitAr.getVal( count );
  Int32 prime = sPrimes.getPrimeAt( count );
  digit = digit % prime;
  digitAr.setVal( count, digit );
  }
}



void Crt::subtract( const Crt& toSub,
                    const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 digit = digitAr.getVal( count );
  digit -= toSub.digitAr.getVal( count );
  Int32 prime = sPrimes.getPrimeAt( count );

  if( digit < 0 )
    digit += prime;

  digitAr.setVal( count, digit );
  }
}



void Crt::decrement( const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 digit = digitAr.getVal( count );
  digit -= 1;
  Int32 prime = sPrimes.getPrimeAt( count );
  if( digit < 0 )
    digit += prime;

  digitAr.setVal( count, digit );
  }
}



void Crt::subtractInt( const Int32 toSub,
                        const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 sub = toSub;
  Int32 prime = sPrimes.getPrimeAt( count );
  sub = sub % prime;
  Int32 digit = digitAr.getVal( count );
  digit -= sub;
  if( digit < 0 )
    digit += prime;

  digitAr.setVal( count, digit );
  }
}



void Crt::multiply( const Crt& toMul,
                    const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  // This beats the Karatsuba Multiplication
  // algorithm easily.  It can be done on a GPU
  // too.

  Int32 digit = digitAr.getVal( count );
  digit *= toMul.digitAr.getVal( count );
  digit %= sPrimes.getPrimeAt( count );
  digitAr.setVal( count, digit );
  }
}



void Crt::setFromInteger( const Integer& setFrom,
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



void Crt::setFromInt( const Int32 setFrom,
                      const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 digit = setFrom %
                   sPrimes.getPrimeAt( count );

  digitAr.setVal( count, digit );
  }
}

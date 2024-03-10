// Copyright Eric Chauvin 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#include "GarnerCrt.h"
#include "../CppInt/Division.h"
#include "../CryptoBase/Euclid.h"



#include "../CppMem/MemoryWarnTop.h"



void GarnerCrt::setUpConstants(
                      const SPrimes& sPrimes,
                      IntegerMath& intMath )
{
StIO::putS( "GarnerCrt.setupConstants()." );

m.setToOne();

for( Int32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  m.multiply24( prime );
  }

CharBuf showBuf;
StIO::putS( "m:" );
intMath.toString10( m, showBuf );
StIO::putCharBuf( showBuf );
StIO::putLF();

Integer quotient;
Integer remainder;
Integer gcd; // Should never be > 1.

Integer mi; // Garner's m subscript i.
Integer Ai; // Garner's capital A subscript i.
Integer term; // The whole constant term.

for( Int32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  mi.setFromInt24( prime );

  Division::divide( m, mi, quotient,
                    remainder, intMath );
  if( !remainder.isZero())
    throw "GarnerCrt.setupConstants";

  term.copy( quotient );

  if( !Euclid::multInverse( quotient,
                          mi, // modulus
                          Ai, // inverse
                          gcd,
                          intMath ))
  throw "MultInverse() false with GarnerCrt 1.";

  AArray[count].copy( Ai );
  intMath.multiply( term, Ai ); // Ai(m/mi)
  termC[count].copy( term );
  }
}


void GarnerCrt::toInteger( const Crt& crt,
                           Integer& toSet,
                           IntegerMath& intMath )
{
StIO::putS( "GarnerCrt.toInteger()." );

Integer term;
Integer accum;
accum.setToZero();
for( Int32 count = 0; count < last; count++ )
  {
  term.copy( termC[count] );
  term.multiply24( crt.getD( count ));
  accum.add( term );
  }

Integer quotient;
Integer remainder;
Division::divide( accum, m, quotient,
                  remainder, intMath );

toSet.copy( remainder );
}




#include "../CppMem/MemoryWarnBottom.h"

// Copyright Eric Chauvin 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// Garner's Formula.
// See ericinarizona.github.io/GarnerRsa.htm

// His paper is:
// Harvey L Garner
// 1959 Proceedings of The Western Joint
// Computer Conference
// H. Garner.  The Residue Number System.
// IRE Transactions on Electronic Computers,
// EC-8 (6), pp. 140 - 147, June 1959.




#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/StIO.h"
#include "../Crt/Crt.h"
#include "../Crt/Crt3.h"
#include "../CppInt/Integer.h"
#include "../CppInt/IntegerMath.h"
#include "../CppInt/Mod.h"


class Garner
  {
  private:
  bool testForCopy = false;

  public:
  Garner( void )
    {
    StIO::putS( "Garner constructor." );
    }

  Garner( const Garner& in )
    {
    if( in.testForCopy )
      return;

    throw "Copy constructor: Garner.";
    }

  ~Garner( void )
    {
    }

  // Garner's Formula.
  bool formula(
       const Integer& primeP,
       const Integer& primeQ,
       const Integer& privKInverseExponentDP,
       const Integer& privKInverseExponentDQ,
       const Integer& encryptedNumber,
       Integer& decryptedNumber,
       Mod& mod,
       IntegerMath& intMath );

  // RFC 8017 section 5.1.2.
  bool decryptWithQInverse(
       const Integer& primeP,
       const Integer& primeQ,
       const Integer& privKInverseExponentDP,
       const Integer& privKInverseExponentDQ,
       const Integer& encryptedNumber,
       Integer& decryptedNumber,
       Mod& mod,
       IntegerMath& intMath );

  void testCrt( // const Integer& prime1,
                // const Integer& prime2,
                const Integer& pubKeyN,
                // Mod& mod,
                IntegerMath& intMath,
                const SPrimes& sPrimes,
                const MultInv& multInv,
                const CrtMath& crtMath );

  };

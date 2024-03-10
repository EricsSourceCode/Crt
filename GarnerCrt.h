// Copyright Eric Chauvin, 2023.



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
#include "../CppBase/RangeC.h"
#include "../CppBase/StIO.h"
#include "../CppBase/CharBuf.h"
#include "../CppInt/Integer.h"
#include "../CppInt/IntegerMath.h"
#include "../CryptoBase/SPrimes.h"
#include "CrtConst.h"
#include "Crt.h"
#include "Crt3.h"


#include "../CppMem/MemoryWarnTop.h"


class GarnerCrt
  {
  private:
  bool testForCopy = false;
  // Variable names are from the section of
  // Garner's paper called: Conversion of
  // a Residue Code to a Normal Number
  // Representation.
  Integer* AArray; // A subscript i values.
  Integer* termC; // The whole constant term.
  Integer m; // The product of all the
             // m subscript i values.
  static const Int32 last =
                   CrtConst::DigitArraySize;

  public:
  GarnerCrt( void )
    {
    StIO::putS( "GarnerCrt constructor." );
    AArray = new Integer[last];
    termC = new Integer[last];
    }

  GarnerCrt( const GarnerCrt& in )
    {
    AArray = new Integer[last];
    termC = new Integer[last];

    if( in.testForCopy )
      return;

    throw "Copy constructor for GarnerCrt.";
    }

  ~GarnerCrt( void )
    {
    delete[] AArray;
    delete[] termC;
    }


  void setUpConstants( const SPrimes& sPrimes,
                       IntegerMath& intMath );

  void toInteger( const Crt& crt,
                  Integer& toSet,
                  IntegerMath& intMath );

  };



#include "../CppMem/MemoryWarnBottom.h"

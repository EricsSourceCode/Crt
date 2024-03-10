// Copyright Eric Chauvin, 2021 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppBase/StIO.h"
#include "../CppInt/Integer.h"
#include "../CppInt/IntegerMath.h"
#include "../CryptoBase/SPrimes.h"
#include "CrtBuf.h"


#include "../CppMem/MemoryWarnTop.h"


class CrtMath
  {
  private:
  bool testForCopy = false;
  Integer* baseAr;
  CrtBuf* baseArCrt;

  static const Int32 last = Crt::last;

  void setupBaseArray( IntegerMath& intMath,
                       const SPrimes& sPrimes );

  public:
  CrtMath( void )
    {
    StIO::putS( "CrtMath constructor." );
    baseAr = new Integer[last];
    baseArCrt = new CrtBuf[last];
    }

  CrtMath( const CrtMath& in )
    {
    baseAr = new Integer[last];
    baseArCrt = new CrtBuf[last];

    if( in.testForCopy )
      return;

    throw "Copy constructor for CrtMath.";
    }

  ~CrtMath( void )
    {
    delete[] baseAr;
    delete[] baseArCrt;
    }


  void init( IntegerMath& intMath,
             const SPrimes& sPrimes );


  void copyFromInteger( Integer& copyTo,
                const Int32 where ) const;

  inline Int32 getCrtDigit( const Int32 row,
                            const Int32 col ) const
    {
    RangeC::test2( row, 0, last - 1,
         "CrtMath.getCrtDigit row range." );

    RangeC::test2( col, 0, last - 1,
          "CrtMath.getCrtDigit col range." );

    return baseArCrt[row].getD( col );
    }

  inline Int32 getBaseByte( const Int32 row )
                                          const
    {
    RangeC::test2( row, 0, last - 1,
         "CrtMath.getBaseByte row range." );

    return baseAr[row].getD( 0 ) & 0xFF;
    }

  };

#include "../CppMem/MemoryWarnBottom.h"

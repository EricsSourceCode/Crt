// Copyright Eric Chauvin, 2021 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CryptoBase/SPrimes.h"
#include "../CppInt/Integer.h"
#include "../CppInt/IntegerMath.h"
#include "Crt.h"
#include "../CppBase/StIO.h"


class CrtBuf
  {
  private:
  bool testForCopy = false;
  static const Int32 last = Crt::last;

  Int32Array digitAr;

  public:
  CrtBuf( void )
    {
    // StIO::putS( "CrtBuf constructor." );
    digitAr.setSize( last );
    setToZero();
    // StIO::putS( "End of CrtBuf constructor." );
    }

  CrtBuf( const CrtBuf& in )
    {
    if( in.testForCopy )
      return;

    throw "Copy constructor for CrtBuf.";
    }


  ~CrtBuf( void )
    {
    }

  void setToZero();
  void setToOne();

  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes );


  inline Int32 getD( const Int32 index ) const
    {
    return digitAr.getVal( index );
    }

  inline void setD( const Int32 setTo,
                    const Int32 index )
    {
    RangeC::test2( setTo, 0, 0xFFFFFF,
            "Crt.setD() setTo range." );

    digitAr.setVal( index, setTo );
    }

  };

// Copyright Eric Chauvin, 2021 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "..\CppBase\BasicTypes.h"
#include "..\CppBase\RangeC.h"
#include "..\CryptoBase\SPrimes.h"
#include "..\CppInt\Integer.h"
#include "..\CppInt\IntegerMath.h"
#include "..\CppMem\Int32Array.h"
#include "CrtConst.h"


class Crt
  {
  private:
  bool testForCopy = false;

  Int32Array digitAr;

  public:
  static const Int32 last =
                   CrtConst::DigitArraySize;

  Crt( void )
    {
    digitAr.setSize( last );
    setToZero();
    }


  Crt( const Crt& in )
    {
    if( in.testForCopy )
      return;

    throw "Copy constructor for Crt.";
    }


  ~Crt( void )
    {
    }

  void setToZero();
  void setToOne();
  bool isZero() const;
  bool isOne() const;
  void copy( const Crt& toCopy );
  bool isEqual( const Crt& toCheck ) const;
  void add( const Crt& toAdd,
            const SPrimes& sPrimes );
  void subtract( const Crt& toSub,
                 const SPrimes& sPrimes );
  void decrement( const SPrimes& sPrimes );
  void subtractInt( const Int32 toSub,
                     const SPrimes& sPrimes );
  void multiply( const Crt& toMul,
                 const SPrimes& sPrimes );
  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes );
  void setFromInt( const Int32 setFrom,
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

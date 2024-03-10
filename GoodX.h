// Copyright Eric Chauvin, 2022 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppBase/Casting.h"
#include "../CppMem/BoolArray.h"
#include "../CryptoBase/SPrimes.h"
#include "CrtConst.h"


#include "../CppMem/MemoryWarnTop.h"


class GoodX
  {
  private:
  bool testForCopy = false;

  static const Int32 last = 
                    CrtConst::DigitArraySize;

  BoolArray* bArrays;

  public:
  GoodX( void );
  GoodX( const GoodX& in );
  ~GoodX( void );
  void init( const SPrimes& sPrimes );
  void setAllFalse( void );

  inline bool getVal( const Int32 primeAt,
                      const Int32 where ) const
    {
    RangeC::test2( primeAt, 0, last - 1,
            "GoodX.getVal primeAt range." );

    // BoolArray has its own range check.

    return bArrays[primeAt].getVal( where );
    }

  inline void setVal( const Int32 primeAt,
                      const Int32 where,
                      const bool toSet )
    {
    RangeC::test2( primeAt, 0, last - 1,
           "GoodX.setVal primeAt range." );

    // BoolArray has its own range check.

    bArrays[primeAt].setVal( where, toSet );
    }


  // inline Int32 getLengthAt(
  //                  const Int32 where ) const
  //  {
  //  RangeC::test2( where, 0, last - 1,
  //          "getLengthAt where range." );
  //     return bArrays[where].getSize();
  //  }

  };


#include "../CppMem/MemoryWarnBottom.h"

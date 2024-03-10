// Copyright Eric Chauvin, 2021 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CryptoBase/SPrimes.h"
#include "CrtConst.h"
#include "Crt.h"
#include "CrtMath.h"
#include "MultInv.h"
#include "../CryptoBase/QuadRes.h"
// #include "CrtTreeL.h"
#include "GoodX.h"




class Crt3
  {
  private:
  bool testForCopy = false;

  // If last is too small then toInteger()
  // will come out too small.
  static const Int32 last =
                CrtConst::DigitArraySize;

  Int32Array digitMAr;
  Int32 index = 0;

/*
  inline static Int32 getTestAccum(
                         const Int32 prime,
                         const Int32 accum,
                         const Int32 crtDigit,
                         const Int32 digit )
    {
    Int32 test = crtDigit;
    test = test * digit;
    test  += accum;
    test = test % prime;
    return test;
    }
*/


  public:
  Crt crt;

  Crt3( void )
    {
    digitMAr.setSize( last );
    setToZero();
    }


  Crt3( const Crt3& in )
    {
    if( in.testForCopy )
      return;

    throw "Copy constructor for Crt3.";
    }

  ~Crt3( void )
    {
    }


  inline void setToZero()
    {
    index = 0;
    digitMAr.setVal( 0, 0 );
    }

  inline void setToOne()
    {
    index = 0;
    digitMAr.setVal( 0, 1 );
    }


/*
  inline Int32 getAccumByte( const Int32 row,
                             const CrtMath& crtMath ) const

    {
    // It is either zero or one.
    Int32 result = digitMAr[0];

    for( Int32 count = 1; count <= row; count++ )
      {
      Int32 accumB = crtMath.getBaseByte( count );
      accumB = accumB * digitMAr[count];
      result += accumB;
      result = result & 0xFF;
      }

    return result;
    }
*/


  inline bool isZero() const
    {
    if( index != 0 )
      return false;

    if( digitMAr.getVal( 0 ) != 0 )
      return false;

    return true;
    }

  inline bool isOne() const
    {
    if( index != 0 )
      return false;

    if( digitMAr.getVal( 0 ) != 1 )
      return false;

    return true;
    }


  void copy( const Crt3& toCopy );

  // void copyToCrtBuf( CrtBuf& copyTo );

  bool isEqual( const Crt3& toCheck ) const;

  // M for Magnitude digit.
  inline Int32 getMD( Int32 where ) const
    {
    return digitMAr.getVal( where );
    }

  inline void setMD( Int32 setTo, Int32 where )
    {
    digitMAr.setVal( where, setTo );
    }


  inline Int32 getIndex( void ) const
    {
    return index;
    }

  inline void setIndex( const Int32 setTo )
    {
    RangeC::test2( setTo, 0, last - 1,
             "Crt3.setIndex index range." );

    index = setTo;
    }

  void toInteger( const CrtMath& crtMath,
                  Integer& toSet // ,
                  // IntegerMath& intMath
                  ) const;

  // void setCrt( const CrtMath& crtMath,
  //             const SPrimes& sPrimes );




  void setFromCrtAt( const Int32 where,
                     const Int32 accum,
                     const CrtMath& crtMath,
                     const Int32 prime,
                     const MultInv& multInv )
    {
    RangeC::test2( where, 1, last - 1,
         "Crt3::setFromCrtAt where range." );

    // Int32 prime = sPrimes.getPrimeAt( where );
    Int32 testD = crt.getD( where );

    if( testD < accum )
      testD += prime;

    testD = testD - accum;

    Int32 baseD = crtMath.getCrtDigit(
                               where, where );
    // if( baseD == 0 )
      // throw "Crt3::setFromCrtAt  baseD == 0";

    Int32 inv = multInv.getInv( where, baseD );
    // if( inv == 0 )
      // throw "setFromCrtV6 inv == 0";

    // baseD * inv = 1
    // baseD * inv * testD = testD

    Int32 testInv = inv * testD;
    testInv = testInv % prime;
    digitMAr.setVal( where, testInv );
    }

  // See Crt2.cpp for earlier versions and
  // how this evolved.

  void setFromCrtV6( const Int32 maxIndex,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     const MultInv& multInv );


/*
  bool setInvCrt( Crt3& prime2Crt3,
                  const Int32 maxLen,
                  const Crt3& prod,
                  const SPrimes& sPrimes,
                  const MultInv& multInv,
                  const CrtMath& crtMath );
*/



  // bool incAt( const SPrimes& sPrimes,
    //           const Int32 where );


  Int32 getAccum( const Int32 row,
                  const Int32 col,
                  const Int32 prime,
                  const CrtMath& crtMath ) const
    {
    Int32 top = row;
    if( top > index )
      top = index;

    // The crtDigit is all ones at index 0.
    // So it would be this times 1.
    // This is either one or zero.
    Int32 result = digitMAr.getVal( 0 );

    for( Int32 count = 1; count <= top; count++ )
      {
      Int32 accum = crtMath.getCrtDigit(
                              count, col );

      accum = accum * digitMAr.getVal( count );
      result += accum;
      result = result % prime;
      }

    return result;
    }



/*
  bool setInvDigit( const Int32 where,
                    const Int32 prime,
                    const Int32 fromDigit,
                    const Int32 maxLen,
                    const CrtMath& crtMath,
                    const MultInv& multInv );
*/




  // Str toStr( const CrtMath& crtMath,
  //           IntegerMath& intMath );


  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes,
                       const MultInv& multInv,
                       const CrtMath& crtMath );




/*
  void setFromCrtTree( const CrtTreeL& crtTree,
                       const CrtMath& crtMath,
                       const SPrimes& sPrimes,
                       const MultInv& multInv );
*/



/*
  bool isFullGoodX( const GoodX& goodX,
                    const CrtMath& crtMath,
                    const SPrimes& sPrimes ) const;
*/

  };

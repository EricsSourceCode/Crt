// Copyright Eric Chauvin 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#include "Garner.h"
#include "../CppInt/Division.h"
#include "../CryptoBase/Euclid.h"



// Garner's Formula as it is from his paper.
  // Variable names are from the section of
  // Garner's paper called: Conversion of
  // a Residue Code to a Normal Number
  // Representation.

bool Garner::formula(
       const Integer& primeP,
       const Integer& primeQ,
       const Integer& privKInverseExponentDP,
       const Integer& privKInverseExponentDQ,
       const Integer& encryptedNumber,
       Integer& decryptedNumber,
       Mod& mod,
       IntegerMath& intMath )
{
// The variable names here are as shown in
// Garner's paper, so they are not the same
// as the variable names in RFC 8017
// section 5.1.2.

Integer m;
Integer m1;
Integer m2;
Integer a1;
Integer a2;
Integer A1; // The paper has capital A and
Integer A2; // little a variable names.

Integer gcd; // Should never be > 1.

// a1 here, not m1 as in RFC 8017.
a1.copy( encryptedNumber );
mod.toPower( a1,
             privKInverseExponentDP,
             primeP, intMath );

// a2, not m2.
a2.copy( encryptedNumber );
mod.toPower( a2,
             privKInverseExponentDQ,
             primeQ, intMath );

m1.copy( primeP );
m2.copy( primeQ );
m.copy( primeP );
intMath.multiply( m, primeQ );

// A1 (m / m1) = 1 mod m1
// but m / m1 is m2, so
// A1 (m2) = 1 mod m1
// A1 is the multiplicative inverse
// of m2 mod m1.

if( !Euclid::multInverse( m2,
                          m1, // modulus
                          A1, // inverse
                          gcd,
                          intMath ))
  throw "MultInverse() false with Garner 1.";
  // return false;

if( !Euclid::multInverse( m1,
                          m2,
                          A2,
                          gcd,
                          intMath ))
  throw "MultInverse() false with Garner 2.";
  // return false;

Integer sum1;
Integer sum2;
Integer sum;

sum1.copy( a1 );
intMath.multiply( sum1, A1 );
intMath.multiply( sum1, m2 );

sum2.copy( a2 );
intMath.multiply( sum2, A2 );
intMath.multiply( sum2, m1 );

sum.copy( sum1 );
sum.add( sum2 );

Integer quotient;
Integer remainder;

// The sum mod m.
Division::divide( sum, m, quotient,
                  remainder, intMath );

decryptedNumber.copy( remainder );
return true;
}



bool Garner::decryptWithQInverse(
       const Integer& primeP,
       const Integer& primeQ,
       const Integer& privKInverseExponentDP,
       const Integer& privKInverseExponentDQ,
       const Integer& encryptedNumber,
       Integer& decryptedNumber,
       Mod& mod,
       IntegerMath& intMath )
{
// See RFC 8017 section 5.1.2.
// This description in RFC 8017 is derived from
// using Garner's Formula.
// It is a variation on Garner's Formula.

// The message representative m
// is computed as follows.
// b.  If the second form (p, q, dP,
// dQ, qInv) and (r_i, d_i,
// t_i) of K is used, proceed
// as follows:
// i.   Let m_1 = c^dP mod p and
// m_2 = c^dQ mod q.
// iii. Let h = (m_1 - m_2) * qInv mod p.
// iv.  Let m = m_2 + q * h.
// 3.  Output m.

// See the formula() function to see why
// qInv is used here.

Integer qInv;
Integer gcd;

// qInv is the multiplicative inverse
// of PrimeQ mod PrimeP.
if( !Euclid::multInverse( primeQ,
                          primeP,
                          qInv,
                          gcd,
                          intMath ))
  throw "MultInverse() false with qInv.";
  // return false;


// i.   Let m_1 = c^dP mod p

Integer m1;
m1.copy( encryptedNumber );
mod.toPower( m1,
             privKInverseExponentDP,
             primeP, intMath );

Integer m2;

//      2.3 Let m_2 = c^dQ mod q.

m2.copy( encryptedNumber );
mod.toPower( m2,
             privKInverseExponentDQ,
             primeQ, intMath );


// iii. Let h = (m_1 - m_2) * qInv mod p.
Integer h;
h.copy( m1 );
mod.subtract( h, m2, primeP, intMath );
mod.multiply( h, qInv, primeP, intMath );

// iv.  Let m = m_2 + q * h.
// 3.  Output m.

Integer m;
m.copy( primeQ );
intMath.multiply( m, h );
m.add( m2 );

decryptedNumber.copy( m );
return true;
}



void Garner::testCrt(
                   // const Integer& prime1,
                   // const Integer& prime2,
                   const Integer& pubKeyN,
                   // Mod& mod,
                   IntegerMath& intMath,
                   const SPrimes& sPrimes,
                   const MultInv& multInv,
                   const CrtMath& crtMath )
{
Crt3 testC;

testC.setFromInteger( pubKeyN,
                      intMath,
                      sPrimes,
                      multInv,
                      crtMath );

Integer testI;
testC.toInteger( crtMath, testI );

if( !testI.isEqual( pubKeyN ))
  throw "Garner::testCrt() was bad.";

}

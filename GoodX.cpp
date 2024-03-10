// Copyright Eric Chauvin 2022 - 2023.



#include "GoodX.h"
#include "../CppBase/StIO.h"



#include "../CppMem/MemoryWarnTop.h"




GoodX::GoodX( void )
{
StIO::putS( "GoodX constructor." );

bArrays = new BoolArray[last];
}


GoodX::GoodX( const GoodX& in )
{
bArrays = new BoolArray[last];

if( in.testForCopy )
  return;

throw "Copy constructor for GoodX.";
}


GoodX::~GoodX( void )
{
delete[] bArrays;
}



void GoodX::init( const SPrimes& sPrimes )
{
StIO::putS( "GoodX init()." );

for( Int32 count = 0; count < last; count++ )
  {
  const Int32 prime = sPrimes.
                          getPrimeAt( count );
  bArrays[count].setSize( prime );
  }

setAllFalse();
}



void GoodX::setAllFalse( void )
{
for( Int32 count = 0; count < last; count++ )
  {
  bArrays[count].setAllFalse();
  }
}


#include "../CppMem/MemoryWarnBottom.h"

// Copyright Eric Chauvin 2023



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppInt/IntConst.h"



class CrtConst
  {
  private:

  public:
  // The size of this is how many digits it
  // is, so it might be 4 or 5 bits per
  // digit.
  // This is a rough guesstimate:

  // A fourth of the size of an Integer
  // array.
  static const Int32 DigitArraySize =
    IntConst::DigitArraySize >> 2;
  };

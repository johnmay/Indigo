/****************************************************************************
 * Copyright (C) 2009-2015 EPAM Systems
 *
 * This file is part of Indigo toolkit.
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#ifndef __reaction_gross_formula__
#define __reaction_gross_formula__

namespace indigo {

#include "base_cpp/array.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class BaseReaction;

class DLLEXPORT ReactionGrossFormula
{
public:
   static void collect (BaseMolecule &molecule, Array<int> &gross);
   static void toString (const Array<int> &gross, Array<char> &str);
   static void toString_Hill (const Array<int> &gross, Array<char> &str);

protected:
   struct _ElemCounter
   {
      int elem;
      int counter;
   };

   static void _toString (const Array<int> &gross, Array<char> &str,
                          int (*cmp)(_ElemCounter &, _ElemCounter &, void *));
}

#endif


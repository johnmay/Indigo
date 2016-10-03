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


#include "reaction/reaction_gross_formula.h"

using namespace indigo;

void ReactionGrossFormula::collect (BaseReaction &rxn, std::pair<ObjArray<Array<int> > , ObjArray<Array<int> >> &gross)
{
    gross.first.clear();
    gross.second.clear();
    
    if (rxn.reactantsCount() > 0)
    {
        gross.first.resize(rxn.reactantsCount() + rxn.catalystCount());
        
        for (i = rxn.reactantBegin(); i != rxn.reactantEnd(); i = rxn.reactantNext(i))
        {
            // gross.first.
        }
    }
    if (rxn.productsCount() > 0)
    {
        gross.second.resize(rxn.productsCount());
        
        for (i = rxn.productBegin(); i != rxn.productEnd(); i = rxn.productNext(i))
        {
            // rxn.getMolecule(i)
        }
    }
    if (rxn.catalystCount() > 0)
    {
        for (i = rxn.catalystBegin(); i != rxn.catalystEnd(); i = rxn.catalystNext(i))
        {
            // rxn.getMolecule(i)
        }
    }
}

void ReactionGrossFormula::toString (const std::pair<ObjArray<Array<int> >, ObjArray<Array<int> >> &gross, Array<char> &str)
{
}

void ReactionGrossFormula::toString_Hill (const std::pair<ObjArray<Array<int> >, ObjArray<Array<int> >> &gross, Array<char> &str)
{
}

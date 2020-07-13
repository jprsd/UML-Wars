/**
 * \file IsGoodUMLVisitor.h
 *
 * \author Jaideep Prasad
 *
 * Class for determining if an item is a good UML
 */

#pragma once
#include "ItemVisitor.h"

/**
 * Class for determining if an item is a good UML
 */
class CIsGoodUMLVisitor :
	public CItemVisitor
{
public:
	/**
	* Visits an Item object and determines if it is a GoodUML object
	* \param badUML the CBadUML object in question
	*/
	virtual void VisitGoodUML(CGoodUML* badUML) override { mIsGoodUML = true; }

	/**
	* Getter for whether the item is a GoodUML or not
	* \return true if the item is a GoodUML
	*/
	bool IsGoodUML() const { return mIsGoodUML; }

	/**
	* Resets the visitor
	*/
	void Reset() { mIsGoodUML = false; }

private:
	/// Defaults bool to false to track if this is a good uml
	bool mIsGoodUML = false;
};


/**
 * \file IsBadUMLVisitor.h
 *
 * \author Jaideep Prasad
 *
 * Class for determining if an item is a BadUML object
 */

#pragma once
#include "ItemVisitor.h"

/**
 * Class for determining if an item is a BadUML object
 */
class CIsBadUMLVisitor :
	public CItemVisitor
{
public:
	/**
	* Visits an Item object and determines if it is a BadUML object
	* \param badUML the CBadUML object in question
	*/
	virtual void VisitBadUML(CBadUML* badUML) override { mIsBadUML = true; }

	/**
	* Getter for whether the item is a BadUML or not
	* \return true if the item is a BadUML
	*/
	bool IsBadUML() const { return mIsBadUML; }

	/**
	* Resets the visitor
	*/
	void Reset() { mIsBadUML = false; }

private:
	/// Defaults bool to false to track if this is a bad uml
	bool mIsBadUML = false;
};


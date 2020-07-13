/**
 * \file IsUMLItemVisitor.h
 *
 * \author David Hefty
 * \author Jaideep Prasad
 *
 * Item visitor to determine if an Item is a CUML item
 */

#pragma once
#include "UML.h"
#include "ItemVisitor.h"

 /** visitor class for determining if a CItem object is a CCUML */
class CIsUMLItemVisitor :
	public CItemVisitor
{
public:
	/**
	* Visits an Item object and determines if it is a UML object
	* \param uml the CUML object in question
	*/
	virtual void VisitUML(CUML* uml) override 
	{ 
		mIsUML = true; mIsDeleted = uml->IsDeleted(); 
	}

	/**
	* Determines if a UML object has been visited
	* \return bool for if an UML object was visited
	*/
	bool IsUML() { return mIsUML; }

	/**
	* Determines if a UML object has been hit and deleted
	* \return bool for if an UML object was delted
	*/
	bool IsDelted() { return mIsDeleted; }

	/**
	* Resets the visitor
	*/
	void Reset() { mIsUML = false; mIsDeleted = false; }

private:
	/// if item is UML will be true
	bool mIsUML = false;
	/// if item is delete will be true
	bool mIsDeleted = false;
};

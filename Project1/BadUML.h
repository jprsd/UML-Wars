/**
 * \file BadUML.h
 *
 * \author Team Sarson
 *
 * Class for bad UML objects
 */

#pragma once
#include "UML.h"

/// Incorrect UML object
class CBadUML :
	public CUML
{
private:
	/// string that holds the error for this object
	std::wstring mError;
public:
	/// Constructor
	/// \param name Name of the object
	/// \param attributes List of attributes
	/// \param operations List of operations
	/// \param error Error associated with the bad uml
	/// \param position Position of the object
	/// \param velocity Velocity of the object
	/// \param game Game we are in
	CBadUML::CBadUML(std::shared_ptr<CUMLAttribute> name,
		std::vector<std::shared_ptr<CUMLAttribute> > attributes,
		std::vector<std::shared_ptr<CUMLAttribute> > operations,
		std::wstring error,
		CVector position, CVector velocity, CGame* game);

	/// Accepts Visitor
	/// \param visitor Visitor to be Accepted
	virtual void Accept(CItemVisitor* visitor) override 
	{ 
		CUML::Accept(visitor);
		visitor->VisitBadUML(this); 
	}

	virtual void Draw(Gdiplus::Graphics* graphics, CVector position) override;

	virtual void Effect() override;

	/// Gets Error Message
	/// \returns the error message
	std::wstring GetMessageOnHit() const { return mError; } 
};


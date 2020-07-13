/**
 * \file BadUMLAttribute.h
 *
 * \author Team Sarson
 *
 * Class for Bad UML Attributes
 */

#pragma once
#include "UMLAttribute.h"

/// Incorrect UML attribute
class CBadUMLAttribute :
	public CUMLAttribute
{
private:
	/// Error message string
	std::wstring mErrorMessage;

public:
	
	/// Constructor
	/// \param att Attribute string
	/// \param em Error message string
	CBadUMLAttribute(std::wstring att, std::wstring em) : CUMLAttribute(att) { mErrorMessage = em; }

	/// Getter for the Error message
	/// \returns The error message string
	virtual std::wstring GetErrorMessage() override { return mErrorMessage; }

	/// Setter for the Error message
	/// \param em Error message
	void SetErrorMessage(std::wstring em) { mErrorMessage = em;  }
};


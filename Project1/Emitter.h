/**
 * \file Emitter.h
 *
 * \author Akhil Alluri
 * \author Jaideep Prasad
 *
 * Class for emitting items to the game
 */

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "UMLAttribute.h"
#include "BadUMLAttribute.h"

#include "Item.h"
#include "UML.h"
#include "BadUML.h"
#include "GoodUML.h"

#include "PowerItem.h"
#include "PowerSlow.h"
#include "PowerFast.h"
#include "PowerAllBad.h"
#include "PowerAllGood.h"
#include "PowerAllGone.h"
#include "PowerRapidFire.h"


/**
 * Class for emitting items to the game
 */
class CEmitter
{
public:
	/// Default constructor disabled. DO NOT USE
	CEmitter() = delete;

	/// Disabled  copy constructor. DO NOT USE
	/// \param emitter The other Emitter
	CEmitter(const CEmitter& emitter) = delete;

	/// Constructor
	/// \param game The game we are in
	CEmitter(CGame* game) : mGame(game) {}
	void Load(const std::wstring& filePath);
	void AddUML();

private:
	/// The game the emitter is a part of
	CGame* mGame;

	//pointer to the game this emitter is a part of
	//std::shared_ptr<CGame> mGame;
	//lists to store uml components
	///list of possible good uml names
	std::vector<std::shared_ptr<CUMLAttribute> > mNames;
	///list of possible bad uml names
	std::vector<std::shared_ptr<CUMLAttribute> > mNamesBad;
	///list of possible good uml attributes
	std::vector<std::shared_ptr<CUMLAttribute> > mAttributes;
	///list of possible bad uml attributes
	std::vector<std::shared_ptr<CUMLAttribute> > mAttributesBad;
	///list of possible good uml operations
	std::vector<std::shared_ptr<CUMLAttribute> > mOperations;
	///list of possible bad uml operations
	std::vector<std::shared_ptr<CUMLAttribute> > mOperationsBad;

	/// probability of a good item being spawned
	double mProbability = 0.0;
	
};


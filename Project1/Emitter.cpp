/**
 * \file Emitter.cpp
 *
 * \author Akhil Alluri
 * \author Jaideep Prasad
 * \author Isaac Mayers
 * \author David Hefty
 */

#include "pch.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "Emitter.h"
#include "XmlNode.h"
#include "Game.h"
#include "IsPowerAllBadVisitor.h"
#include "IsPowerAllGoodVisitor.h"
#include "IsPowerAllGoneVisitor.h"
#include "IsPowerFastVisitor.h"
#include "IsPowerSlowVisitor.h"
#include "IsPowerRapidFireVisitor.h"

using namespace std;
using namespace xmlnode;

/// Max probability
const double MaxProbability = 0.50f;
/// Rate that the probability changes
const double ProbChangeRate = 0.025f;
/// Number assossiated with BadName
const int BadName = 1;
/// Number assossiated with BadAtts
const int BadAtts = 2;
/// Number assossiated with BadOps
const int BadOps = 3;

/// Game area width in virtual pixels
const int Width = 1250;
/// Game area height in virtual pixels
const int Height = 1000;

 /// Maximum speed in the X direction in
 /// in pixels per second
const double MaxSpeedX = 40;

 /// Maximum speed in the Y direction in
 /// in pixels per second
const double MaxSpeedY = 60;

 /// Minimum speed in the X direction in
 /// in pixels per second
const double MinSpeedX = -30;

 /// Minimum speed in the Y direction in
 /// in pixels per second
const double MinSpeedY = 30;

/// Maximum starting position in the X direction
const double MaxPosX = Width / 2;

/// Minimum starting position in the X direction
const double MinPosX = -1 * Width / 2;

/**
 * Loads a file containing characteristics for UML objects
 * \param filePath File path for UML data
 */

void CEmitter::Load(const std::wstring& filePath)
{
	

	std::shared_ptr<CUMLAttribute> attribute;
	try
	{
		//Open document to read
		std::shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filePath);



		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT)
			{

				for (auto item : node->GetChildren())
				{
					if (item->GetType() == NODE_ELEMENT) {
						std::wstring itemName = item->GetName();
						//
						std::wstring error = item->GetAttributeValue(L"bad", L"");
						std::wstring text;
						if (item->GetNumChildren() > 0) {
							text = item->GetChild(0)->GetValue();

						}
						else {
							text = L"";
						}

						if (error == L"") {
							attribute = make_shared<CUMLAttribute>(text);
						}
						else {
							attribute = make_shared<CBadUMLAttribute>(text, error);
						}

						if (itemName == L"name") {
							if (error == L"") {
								mNames.push_back(attribute);
							}
							else {
								mNamesBad.push_back(attribute);
							}
						}
						else if (itemName == L"attribute") {
							if (error == L"") {
								mAttributes.push_back(attribute);
							}
							else {
								mAttributesBad.push_back(attribute);
							}
						}
						else if (itemName == L"operation") {
							if (error == L"") {
								mOperations.push_back(attribute);
							}
							else {
								mOperationsBad.push_back(attribute);
							}
						}
					}

				}




			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}
/*
* Emits Random UML and Random Power-Up
*/
void CEmitter::AddUML() 
{
	srand((unsigned int)time(NULL));
	double randomGuess = (rand() % 100 + 1) / 100.0f;
	double powerGuess = (rand() % 100 + 1) / 100.0f;
	double powerSelectionGuess = (rand() % 100 + 1) / 100.0f;

	/// which issue is the case for the UML
	int randIssue; // 0: no issue, goodUML; 1: name Issue; 2: Att issue; 3: Op issue

	if (randomGuess > mProbability)
	{
		randIssue = rand() % 3 + 1; // decides Bad Issue
	}
	else
	{
		randIssue = 0;
	}

	// shuffle all the possible UML parts
	random_shuffle(mAttributes.begin(), mAttributes.end());
	random_shuffle(mAttributesBad.begin(), mAttributesBad.end());
	random_shuffle(mOperations.begin(), mOperations.end());
	random_shuffle(mOperationsBad.begin(), mOperationsBad.end());
	random_shuffle(mNames.begin(), mNames.end());
	random_shuffle(mNamesBad.begin(), mNamesBad.end());


	std::vector<std::shared_ptr<CUMLAttribute> > atts;
	std::vector<std::shared_ptr<CUMLAttribute> > ops;
	std::shared_ptr<CUMLAttribute> name;

	std::wstring badUmlErrorMessage;

	// pick out attributes based on if it is good/bad
	if (randomGuess > mProbability) // Bad Item
	{
		if (randIssue == BadName)
		{
			int numOfAttributes = rand() % 4;
			int numOfOperations = rand() % 4;
			int randName = rand() % 4;
			std::vector<std::shared_ptr<CUMLAttribute> > attsTemp(mAttributes.begin(), mAttributes.begin() + numOfAttributes);
			std::vector<std::shared_ptr<CUMLAttribute> > opsTemp(mOperations.begin(), mOperations.begin() + numOfOperations);
			std::shared_ptr<CUMLAttribute> nameTemp = make_shared<CUMLAttribute>(mNamesBad[randName]->GetAtt());
		
			atts = attsTemp;
			ops = opsTemp;
			name = nameTemp;

			badUmlErrorMessage = mNamesBad[randName]->GetErrorMessage();
		}
		else if (randIssue == BadAtts)
		{
			int numOfAttributes = rand() % 3;
			int numOfOperations = rand() % 4;
			int randName = rand() % 4;
			std::vector<std::shared_ptr<CUMLAttribute> > attsTemp(mAttributes.begin(), mAttributes.begin() + numOfAttributes);
			attsTemp.push_back(mAttributesBad[0]);

			badUmlErrorMessage = mAttributesBad[0]->GetErrorMessage();

			random_shuffle(attsTemp.begin(), attsTemp.end());
			std::vector<std::shared_ptr<CUMLAttribute> > opsTemp(mOperations.begin(), mOperations.begin() + numOfOperations);
			std::shared_ptr<CUMLAttribute> nameTemp = make_shared<CUMLAttribute>(mNames[randName]->GetAtt());
		
			atts = attsTemp;
			ops = opsTemp;
			name = nameTemp;
		}
		else if (randIssue == BadOps)
		{
			int numOfAttributes = rand() % 4;
			int numOfOperations = rand() % 3;
			int randName = rand() % 4;
			std::vector<std::shared_ptr<CUMLAttribute> > attsTemp(mAttributes.begin(), mAttributes.begin() + numOfAttributes);
			std::vector<std::shared_ptr<CUMLAttribute> > opsTemp(mOperations.begin(), mOperations.begin() + numOfOperations);
			opsTemp.push_back(mOperationsBad[0]);

			badUmlErrorMessage = mOperationsBad[0]->GetErrorMessage();

			random_shuffle(opsTemp.begin(), opsTemp.end());
			std::shared_ptr<CUMLAttribute> nameTemp = make_shared<CUMLAttribute>(mNames[randName]->GetAtt());

			atts = attsTemp;
			ops = opsTemp;
			name = nameTemp;
		}
	} // end bad UML
	else // good UML
	{
		int numOfAttributes = rand() % 4;
		int numOfOperations = rand() % 4;
		int randName = rand() % 4;
		std::vector<std::shared_ptr<CUMLAttribute> > attsTemp(mAttributes.begin(), mAttributes.begin() + numOfAttributes);
		std::vector<std::shared_ptr<CUMLAttribute> > opsTemp(mOperations.begin(), mOperations.begin() + numOfOperations);
		std::shared_ptr<CUMLAttribute> nameTemp = make_shared<CUMLAttribute>(mNames[randName]->GetAtt());
	
		atts = attsTemp;
		ops = opsTemp;
		name = nameTemp;
	}

	// Randomize X and Y speeds within limits
	double tempSpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
	double tempSpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);

	// Randomize X position within limits
	double tempPosX = MinPosX + ((double)rand() / RAND_MAX) * (MaxPosX - MinPosX);

	// Limit the X position so that it will not move off the screen with its set X velocity
	if ((tempSpeedX < 0) && (-1 * Width / 2 >= (tempPosX + tempSpeedX * (Height / tempSpeedY))))
	{
		tempPosX = -1 * Width / 2 - (tempSpeedX * (Height / tempSpeedY));
	}

	if ((tempSpeedX > 0) && (Width / 2 <= (tempPosX + tempSpeedX * (Height / tempSpeedY))))
	{
		tempPosX = Width / 2 - (tempSpeedX * (Height / tempSpeedY));
	}

	// Generate a good or bad UML based on the probability

	if (randomGuess > mProbability) // Bad Item
	{
		mGame->AddItem(make_shared<CBadUML>(name, atts, ops, badUmlErrorMessage, CVector(tempPosX, 60), CVector(tempSpeedX, tempSpeedY), mGame));
		
	}
	else // Good Item
	{
		mGame->AddItem(make_shared<CGoodUML>(name, atts, ops, CVector(-tempPosX, 60), CVector(-tempSpeedX, tempSpeedY), mGame));
	}

	if (powerGuess <= 0.60)
	{
		double powerPosX = -tempPosX;
		double powerSpeedX = tempSpeedX * 2;
		double powerSpeedY = tempSpeedY * 2;

		bool exists = false;
		bool moving = false;
		CVector powerVelocity;

		if (powerSelectionGuess <= 0.16)
		{
			CIsPowerAllBadVisitor visitor;
			for (auto item : *mGame)
			{
				item->Accept(&visitor);
				if (visitor.IsPowerAllBad())
				{
					exists = true;
					powerVelocity = item->GetVelocity();
					if (powerVelocity.X() != 0 && powerVelocity.Y() != 0)
						moving = true;
					else
					{
						item->SetLocation(CVector(powerPosX, 60));
						item->SetVelocity(CVector(powerSpeedX, powerSpeedY));
					}
					break;
				}
			}

			if (!exists)
				mGame->AddItem(make_shared<CPowerAllBad>(CVector(powerPosX, 60), CVector(powerSpeedX, powerSpeedY), mGame));

		}
		else if (powerSelectionGuess > 0.16 && powerSelectionGuess <= 0.32)
		{
			CIsPowerAllGoodVisitor visitor;
			for (auto item : *mGame)
			{
				item->Accept(&visitor);
				if (visitor.IsPowerAllGood())
				{
					exists = true;
					powerVelocity = item->GetVelocity();
					if (powerVelocity.X() != 0 && powerVelocity.Y() != 0)
						moving = true;
					else
					{
						item->SetLocation(CVector(powerPosX, 60));
						item->SetVelocity(CVector(powerSpeedX, powerSpeedY));
					}
					break;
				}
			}

			if (!exists)
				mGame->AddItem(make_shared<CPowerAllGood>(CVector(powerPosX, 60), CVector(powerSpeedX, powerSpeedY), mGame));

		}
		else if (powerSelectionGuess > 0.32 && powerSelectionGuess <= 0.48)
		{
			CIsPowerAllGoneVisitor visitor;
			for (auto item : *mGame)
			{
				item->Accept(&visitor);
				if (visitor.IsPowerAllGone())
				{
					exists = true;
					powerVelocity = item->GetVelocity();
					if (powerVelocity.X() != 0 && powerVelocity.Y() != 0)
						moving = true;
					else
					{
						item->SetLocation(CVector(powerPosX, 60));
						item->SetVelocity(CVector(powerSpeedX, powerSpeedY));
					}
					break;
				}
			}

			if (!exists)
				mGame->AddItem(make_shared<CPowerAllGone>(CVector(powerPosX, 60), CVector(powerSpeedX, powerSpeedY), mGame));

		}
		else if (powerSelectionGuess > 0.48 && powerSelectionGuess <= 0.64)
		{
			CIsPowerFastVisitor visitor;
			for (auto item : *mGame)
			{
				item->Accept(&visitor);
				if (visitor.IsPowerFast())
				{
					exists = true;
					powerVelocity = item->GetVelocity();
					if (powerVelocity.X() != 0 && powerVelocity.Y() != 0)
						moving = true;
					else if (!visitor.IsActive())
					{
						item->SetLocation(CVector(powerPosX, 60));
						item->SetVelocity(CVector(powerSpeedX, powerSpeedY));
					}
					break;
				}
			}

			if (!exists)
				mGame->AddItem(make_shared<CPowerFast>(CVector(powerPosX, 60), CVector(powerSpeedX, powerSpeedY), mGame));
		}
		else if (powerSelectionGuess > 0.64 && powerSelectionGuess <= 0.80)
		{
			CIsPowerSlowVisitor visitor;
			for (auto item : *mGame)
			{
				item->Accept(&visitor);
				if (visitor.IsPowerSlow())
				{
					exists = true;
					powerVelocity = item->GetVelocity();
					if (powerVelocity.X() != 0 && powerVelocity.Y() != 0)
						moving = true;
					else if (!visitor.IsActive())
					{
						item->SetLocation(CVector(powerPosX, 60));
						item->SetVelocity(CVector(powerSpeedX, powerSpeedY));
					}
					break;
				}
			}

			if (!exists)
				mGame->AddItem(make_shared<CPowerSlow>(CVector(powerPosX, 60), CVector(powerSpeedX, powerSpeedY), mGame));
		}
		else
		{
			CIsPowerRapidFireVisitor visitor;
			for (auto item : *mGame)
			{
				item->Accept(&visitor);
				if (visitor.IsPowerRapidFire())
				{
					exists = true;
					powerVelocity = item->GetVelocity();
					if (powerVelocity.X() != 0 && powerVelocity.Y() != 0)
						moving = true;
					else if (!visitor.IsActive())
					{
						item->SetLocation(CVector(powerPosX, 60));
						item->SetVelocity(CVector(powerSpeedX, powerSpeedY));
					}
					break;
				}
			}

			if (!exists)
				mGame->AddItem(make_shared<CPowerRapidFire>(CVector(powerPosX, 60), CVector(powerSpeedX, powerSpeedY), mGame));

		}
	}
	
	if (mProbability <= MaxProbability)
	{
		mProbability += ProbChangeRate;
	}
	else
	{
		mProbability = 0.50f;
	}
	
}
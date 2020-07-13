/**
 * \file ItemVisitor.h
 *
 * \author David Hefty
 *
 * Item visitor base class.
 */


#pragma once

 // Forward references to all Item types
class CItem;
class CUML;
class CGoodUML;
class CBadUML;
class CPowerItem;
class CHaroldPen;
class CPowerAllGood;
class CPowerAllBad;
class CPowerAllGone;
class CPowerRapidFire;
class CPowerFast;
class CPowerSlow;

/** Item visitor base class */
class CItemVisitor
{
public:
	/// CItemVisitor destructor
	virtual ~CItemVisitor() {}

	/** Visit a general Item object
	 * \param item The item we are visiting */
	virtual void VisitItem(CItem* item) {}

	/** Visit a CUML object
	 * \param uml UML item we are visiting */
	virtual void VisitUML(CUML* uml) {}

	/** Visit a CUML object
	 * \param goodUML Good UML item we are visiting */
	virtual void VisitGoodUML(CGoodUML* goodUML) {}

	/** Visit a CUML object
	 * \param badUML Bad UML item we are visiting */
	virtual void VisitBadUML(CBadUML* badUML) {}

	/** Visit a CPowerItem object
	 * \param poweritem specific item we are visiting */
	virtual void VisitPowerItem(CPowerItem* poweritem) {}

	/** Visit a CHaroldPen object
	 * \param pen specific HaroldPen we are visiting */
	virtual void VisitHaroldPen(CHaroldPen* pen) {}

	/** Visit a CPowerAllGood object
	 * \param allgood specific AllGood Power item we are visiting */
	virtual void VisitPowerAllGood(CPowerAllGood* allgood) {}

	/** Visit a CPowerAllBad object
	 * \param allbad specific AllBad Power item we are visiting */
	virtual void VisitPowerAllBad(CPowerAllBad* allbad) {}

	/** Visit a CPowerAllGone object
	 * \param allgone specific AllGone Power item we are visiting */
	virtual void VisitPowerAllGone(CPowerAllGone* allgone) {}

	/** Visit a CPowerRapidFire object
	 * \param rapidfire specific RapidFire Power item we are visiting */
	virtual void VisitPowerRapidFire(CPowerRapidFire* rapidfire) {}

	/** Visit a CPowerFast object
	 * \param fast specific Fast Power item we are visiting */
	virtual void VisitPowerFast(CPowerFast* fast) {}

	/** Visit a CPowerSlow object
	 * \param slow specific Slow Power item we are visiting */
	virtual void VisitPowerSlow(CPowerSlow* slow) {}
};
/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id: AliTRDtrackingSector.cxx 23810 2008-02-08 09:00:27Z hristov $ */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  Tracking data container for one sector                                   //
//                                                                           //
//  Authors:                                                                 //
//    Alex Bercuci <A.Bercuci@gsi.de>                                        //
//    Markus Fasel <M.Fasel@gsi.de>                                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "AliTRDtrackingSector.h"
#include "AliTRDcalibDB.h"
#include "AliTRDCommonParam.h"
#include "AliTRDgeometry.h"
#include "AliTRDpadPlane.h"
#include "AliTRDtrackingChamber.h"

ClassImp(AliTRDtrackingSector)

//_____________________________________________________________________________
AliTRDtrackingSector::AliTRDtrackingSector()
  :fSector(-1)
  ,fN(0)
  ,fGeom(0x0)
{
	// Default constructor
	
	for(int ic=0; ic<kNChambersSector; ic++){
		fChamber[ic] = 0x0;
		fIndex[ic]   = -1;
	}
	for(int ip=0; ip<AliTRDgeometry::kNplan; ip++) fX0[ip] = 0.;
}

//_____________________________________________________________________________
AliTRDtrackingSector::AliTRDtrackingSector(AliTRDgeometry *geo, Int_t gs)
  :fSector(gs)
  ,fN(0)
  ,fGeom(geo)
{
  //
  // AliTRDtrackingSector Constructor
  //

	for(int ic=0; ic<kNChambersSector; ic++){
		fChamber[ic] = 0x0;
		fIndex[ic]   = -1;
	}
	for(int ip=0; ip<AliTRDgeometry::kNplan; ip++) fX0[ip] = 0.;
}

//_____________________________________________________________________________
AliTRDtrackingSector::AliTRDtrackingSector(const AliTRDtrackingSector &/*t*/)
  :fSector(-1)
  ,fN(0)
  ,fGeom(0x0)
{
  //
  // Copy constructor
  //

}

//_____________________________________________________________________________
AliTRDtrackingSector::~AliTRDtrackingSector()
{
  //
  // Destructor
  //

}
		
//_____________________________________________________________________________
void AliTRDtrackingSector::Init()
{		
// 	Steer building of tracking chambers and build tracking sector.
// 	Propagate radial position information (calibration/alignment aware) from chambers to sector level
//
	
	AliTRDtrackingChamber *tc = 0x0; int ic = 0; 
	while((ic<kNChambersSector) && (tc = fChamber[ic++])) tc->Build(fGeom);
		
	Int_t np;
	for(int ip=0; ip<AliTRDgeometry::kNplan; ip++){
		fX0[ip] = 0.; np = 0;
		for(int is=0; is<AliTRDgeometry::kNcham; is++){
			Int_t idx = is*AliTRDgeometry::kNplan + ip;
			if(fIndex[idx]<0) continue;
			tc = GetChamber(fIndex[idx]);
			fX0[ip] += tc->GetX(); np++; 
		}
		if(!np){
			//printf("Could not estimate radial position  of plane %d in sector %d.\n", ip, fSector);
			continue;
		}
		fX0[ip] /= Float_t(np);
	}
}
//_____________________________________________________________________________
void AliTRDtrackingSector::Clear(const Option_t *opt)
{
// Reset counters and steer chamber clear

	for(Int_t ich=0; ich<fN; ich++){ 
		fChamber[ich]->Clear(opt);
		delete fChamber[ich]; fChamber[ich] = 0x0;   // I would avoid
	}	
	for(Int_t ich=0; ich<kNChambersSector; ich++) fIndex[ich] = -1;
	fN = 0;
}

//_____________________________________________________________________________
AliTRDtrackingChamber* AliTRDtrackingSector::GetChamber(Int_t stack, Int_t plane, Bool_t build)
{
// Return chamber at position (stack, plane) in current 
// sector or build a new one if it is not already created
	
	Int_t ch = stack*AliTRDgeometry::kNplan + plane;
	if(fIndex[ch] >= 0) return fChamber[Int_t(fIndex[ch])];
	else if(!build) return 0x0;
	
	// CHAMBER HAS TO BE BUILD
	Int_t rch = ch;do rch--; while(rch>=0 && fIndex[rch]<0);
	fIndex[ch] = rch >=0 ? fIndex[rch]+1 : 0; 
	fN++;
	
	memmove(&fChamber[Int_t(fIndex[ch])+1], &fChamber[Int_t(fIndex[ch])], (kNChambersSector-fIndex[ch]-1)*sizeof(void*));
	for(Int_t ic = ch+1; ic<kNChambersSector; ic++) fIndex[ic] += fIndex[ic] >= 0 ? 1 : 0;
	
	return fChamber[Int_t(fIndex[ch])] = new AliTRDtrackingChamber(AliTRDgeometry::GetDetector(plane, stack, fSector));
}

//_____________________________________________________________________________
AliTRDtrackingChamber** AliTRDtrackingSector::GetStack(Int_t stack)
{
// Return chamber at position (stack, plane) in current 
// sector or build a new one if it is not already created
	
	if(stack<0 || stack>=AliTRDgeometry::kNcham) return 0x0;
	
	Int_t ich, n = 0;
	for(int ip=0; ip<AliTRDgeometry::kNplan; ip++){
		ich = stack*AliTRDgeometry::kNplan + ip;
		if(fIndex[ich] < 0) fStack[ip] = 0x0; 
		else{
			fStack[ip] = fChamber[Int_t(fIndex[ich])];
			n++;
		}
	}
	
	return n ? &fStack[0] : 0x0;
}

//_____________________________________________________________________________
void AliTRDtrackingSector::Print(Option_t *)
{
// Dump info about this tracking sector and the tracking chamber within
// 

	printf("\tSector %2d\n", fSector);
	for(int ip=0; ip<6; ip++){
		for(int is =0; is<5; is++){
			Int_t ch = is*AliTRDgeometry::kNplan + ip;
			printf("%2d[%2d] ", fIndex[ch], fIndex[ch]>=0 ? fChamber[Int_t(fIndex[ch])]->GetNClusters() : 0);
		}
		printf("\n");
	}

}

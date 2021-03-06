// $Id$
// $MpId: testPadDimensions.C,v 1.6 2005/10/28 15:36:08 ivana Exp $
//
// Test macro for testing retrieving of pad dimensions from
// the map in AliMpSectorSegmentation.

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "AliMpStation12Type.h"
#include "AliMpPlaneType.h"
#include "AliMpDataProcessor.h"
#include "AliMpDataMap.h"
#include "AliMpDataStreams.h"
#include "AliMpSector.h"
#include "AliMpSectorSegmentation.h"
#include "AliMpSectorReader.h"
#include "TVector2.h"
#include <Riostream.h>

#endif

void testPadDimensions(AliMq::Station12Type station, AliMp::PlaneType plane)
{
  AliMpDataProcessor mp;
  AliMpDataMap* dataMap = mp.CreateDataMap("data");
  AliMpDataStreams dataStreams(dataMap);

  AliMpSectorReader r(station, plane);
  AliMpSector* sector = r.BuildSector(dataStreams);
  AliMpSectorSegmentation segmentation(sector);  
  
  TVector2 previousDimensions;
  for (Int_t i=1; i<segmentation.MaxPadIndexX()+1;i++) 
    for (Int_t j=1;j<segmentation.MaxPadIndexY()+1;++j) {

       if ( segmentation.HasPadByIndices(i,j) ) {

        // Check pad dimensions
	AliMpPad pad = segmentation.PadByIndices(i,j);
	TVector2 dimensions(pad.GetDimensionX()*2,pad.GetDimensionY()*2);
	
	if ( dimensions.X() != previousDimensions.X() || 
	     dimensions.Y() != previousDimensions.Y() ) {

          // Print dimensions
	  cout << "Pad: " << "(" << i << "," << j << ")";
	  cout << "  dimensions: (" << dimensions.X() << ", " << dimensions.Y() << ")" 
	       << endl;
          
	  previousDimensions = dimensions;
        }	     
     }
   }
}

void testSt12PadDimensions()
{
  AliMq::Station12Type  station[2] = { AliMq::kStation1, AliMq::kStation2 }; 
  AliMp::PlaneType      plane[2]   = { AliMp::kBendingPlane, AliMp::kNonBendingPlane };
  
  for ( Int_t is = 0; is < 2; is++ ) {
    for ( Int_t ip = 0; ip < 2; ip++ ) {
    
      cout << "Running testPadDimensions for " 
           << AliMq::Station12TypeName(station[is]) << "  "
           << AliMp::PlaneTypeName(plane[ip])  << " ... " << endl;
       
      testPadDimensions(station[is], plane[ip]);
    
      cout << "... end running " << endl << endl;
    }  
  }   
}  
  

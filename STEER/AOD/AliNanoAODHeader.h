
#ifndef _ALINANOAODHEADER_H_
#define _ALINANOAODHEADER_H_

#include "AliVAODHeader.h"
#include "AliNanoAODStorage.h"
#include <map>


class AliNanoAODHeader : public AliVAODHeader, public AliNanoAODStorage
{
public:
  using AliVHeader::ClassName;
  AliNanoAODHeader();
  AliNanoAODHeader(Int_t size);
  AliNanoAODHeader(Int_t size, Int_t sizeInt);
  virtual ~AliNanoAODHeader(){;}


  // Interface methods
  // AliNanoAODHeader(const AliVHeader& evt); 
  AliNanoAODHeader& operator=(const AliNanoAODHeader& evt);
  
  virtual UShort_t  GetBunchCrossNumber()   const { NotImplemented();return 0;}
  virtual UInt_t    GetOrbitNumber()        const { NotImplemented();return 0;}
  virtual UInt_t    GetPeriodNumber()       const { NotImplemented();return 0;}
  virtual UInt_t    GetTimeStamp()          const { NotImplemented();return 0;}
  virtual ULong64_t GetTriggerMask()        const { NotImplemented();return 0;}
  virtual ULong64_t GetTriggerMaskNext50()  const { NotImplemented();return 0;}
  virtual UChar_t   GetTriggerCluster()     const { NotImplemented();return 0;}
  virtual UInt_t    GetEventType()          const { NotImplemented();return 0;}

  virtual Bool_t   InitMagneticField()             const    {NotImplemented(); return 0;};
  virtual void     SetRunNumber(Int_t /*n*/)                    {NotImplemented();};
  virtual void     SetMagneticField(Double_t /*magFld*/)        {NotImplemented();};
  virtual void     SetMuonMagFieldScale(Double_t /*magFldScl*/) {NotImplemented();};
  virtual void     SetDiamond(Float_t */*xy[2]*/,Float_t */*cov[3]*/) {NotImplemented();}; 
  virtual void     SetDiamondZ(Float_t /*z*/, Float_t /*sig2z*/)    {NotImplemented();};
  virtual Double_t GetMuonMagFieldScale()          const    {NotImplemented(); return 0;};
  virtual Double_t GetDiamondX()                   const    {NotImplemented(); return 0;};
  virtual Double_t GetDiamondY()                   const    {NotImplemented(); return 0;};
  virtual Double_t GetDiamondZ()                   const    {NotImplemented(); return 0;};
  virtual void     GetDiamondCovXY(Float_t */*cov[3]*/) const    {NotImplemented();};
  virtual Double_t GetSigma2DiamondX()             const    {NotImplemented(); return 0;};
  virtual Double_t GetSigma2DiamondY()             const    {NotImplemented(); return 0;};
  virtual Double_t GetSigma2DiamondZ()             const    {NotImplemented(); return 0;};

  virtual void     SetOrbitNumber(UInt_t /* nOr */)           {NotImplemented(); };
  virtual void     SetPeriodNumber(UInt_t /* nPer */)         {NotImplemented(); };
  virtual void     SetBunchCrossNumber(UShort_t /* nBx */)    {NotImplemented(); };
  virtual void     SetTimeStamp(UInt_t /* t */)               {NotImplemented(); };
  virtual void     SetEventType(UInt_t /* evttype */)         {NotImplemented(); };
  virtual void     SetTriggerMask(ULong64_t /* trigMsk */)    {NotImplemented(); };
  virtual void     SetTriggerMaskNext50(ULong64_t /* trigMsk */) {NotImplemented(); };
  virtual void     SetTriggerCluster(UChar_t /* trigClus */)  {NotImplemented(); };
  virtual void     SetFiredTriggerClasses(TString varlist);
  virtual TString  GetFiredTriggerClasses() const;
  virtual Double_t GetZDCN1Energy()         const             {NotImplemented(); return 0;};
  virtual Double_t GetZDCP1Energy()         const             {NotImplemented(); return 0;};
  virtual Double_t GetZDCN2Energy()         const             {NotImplemented(); return 0;};
  virtual Double_t GetZDCP2Energy()         const             {NotImplemented(); return 0;};

  virtual Double_t GetZDCEMEnergy(Int_t /* i */) const            {NotImplemented(); return 0;};
  virtual Int_t    GetNumberOfESDTracks()  const            {NotImplemented(); return 0;};
  virtual Int_t    GetNumberOfTPCClusters() const {NotImplemented(); return 0;};
  virtual Int_t    GetNumberOfTPCTracks()   const {NotImplemented(); return 0;};
  
  virtual UInt_t   GetNumberOfITSClusters(Int_t /* ilay */) const {NotImplemented(); return 0;};
  virtual Float_t  GetT0spread(Int_t /* i */)               const {NotImplemented(); return 0;};
  // FIXME: THIS IS UGLY!!!!
  // FIXME: use dynamic cast in AliAODEVent?
  virtual AliCentrality* GetCentralityP()  const {NotImplemented(); return 0;};
  virtual AliEventplane* GetEventplaneP()  const {NotImplemented(); return 0;};
  virtual Double_t       GetEventplane()     const {NotImplemented(); return 0;};
  virtual const Float_t* GetVZEROEqFactors() const {NotImplemented(); return 0;};
  virtual Float_t        GetVZEROEqFactors(Int_t /* i */) const {NotImplemented(); return 0;};
  virtual void           SetVZEROEqFactors(const Float_t* /*factors*/) {NotImplemented(); } 

  virtual UInt_t GetOfflineTrigger()  { return UInt_t(GetVar(fOfflineTrigger));};

  virtual void Print(Option_t* /*option = ""*/) const  {Printf("I'm a special header!");}
 
  virtual void Clear(Option_t * opt) ;

  virtual Int_t  GetIRInt2ClosestInteractionMap()                  const {NotImplemented(); return 0;};
  virtual Int_t  GetIRInt1ClosestInteractionMap(Int_t /*gap = 3*/) const {NotImplemented(); return 0;};


  virtual Int_t     GetRefMultiplicity()    const { NotImplemented(); return 0; }

  Double_t  GetMagneticField()      const { return GetVar(fMagField); }
  Double_t  GetCentrality () const; 
  Double_t  GetCentr (const char *x) const; 
  virtual Int_t  GetRunNumber() const; 

  TString GetCentralityMethod() const {return fCentralityMethod;}
  void SetCentralityMethod(const char * method)  { fCentralityMethod = method; } 

  void SetCentrIndex      (Int_t var) { fCentr     = var; }
  void SetCentrTRKIndex   (Int_t var) { fCentrTRK  = var; }
  void SetCentrCL0Index   (Int_t var) { fCentrCL0  = var; }
  void SetCentrCL1Index   (Int_t var) { fCentrCL1  = var; }
  void SetFiredTriggerClassesIndex   (Int_t var) { fFiredTriggerClasses  = var; }
  void SetMagFieldIndex   (Int_t var) { fMagField  = var; }
  void SetOfflineTriggerIndex   (Int_t var) { fOfflineTrigger  = var; }
  void SetRunNumberIndex  (Int_t var) { fRunNumber = var; }


  Int_t GetCentrIndex      () { return fCentr     ; }
  Int_t GetCentrTRKIndex   () { return fCentrTRK  ; }
  Int_t GetCentrCL0Index   () { return fCentrCL0  ; }
  Int_t GetCentrCL1Index   () { return fCentrCL1  ; }
  Int_t GetFiredTriggerClassesIndex () { return fFiredTriggerClasses  ; }
  Int_t GetMagFieldIndex   () { return fMagField  ; }
  Int_t GetOfflineTriggerIndex () { return fOfflineTrigger  ; }
  Int_t GetRunNumberIndex  () { return fRunNumber ; }

  std::map<TString,int> GetMapCstVar () { return fMapCstVar; } 
  void SetMapCstVar (std::map<TString,int> cstmap) { fMapCstVar = cstmap; }
  std::map<TString,int> GetMapFiredTriggerClasses () { return fMapFiredTriggerClasses; } 
  void SetMapFiredTriggerClasses (TString trigClasses);

  Int_t GetVarIndex(TString varName); 
  
  ClassDef(AliNanoAODHeader, 4)
private:
  void NotImplemented() const;

  TString fCentralityMethod;


  Int_t fCentr;      // index of stored variable
  Int_t fCentrTRK;   // index of stored variable
  Int_t fCentrCL0;   // index of stored variable
  Int_t fCentrCL1;   // index of stored variable
  Int_t fFiredTriggerClasses;   // index of stored variable
  Int_t fMagField;   // index of stored variable
  Int_t fOfflineTrigger;//index of stored variable
  Int_t fRunNumber;  // index of stored variable 

  std::map<TString,int> fMapCstVar;// Map of indexes of custom variables: CACHE THIS TO CONST INTs IN YOUR TASK TO AVOID CONTINUOUS STRING COMPARISONS

  std::map<TString,int> fMapFiredTriggerClasses;// Map of indexes of fired trigger Classes
};

#endif /* _ALINANOAODHEADER_H_ */

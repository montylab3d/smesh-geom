//NOTE: This is an interface to a function for the Blocks Multi-Transformations.


#include "GEOM_Function.hxx"

#define TRSF_ORIGIN  1

#define TRSF_FACE_1_U  2
#define TRSF_FACE_2_U  3
#define TRSF_NBITER_U  4
#define TRSF_FACE_1_V  5
#define TRSF_FACE_2_V  6
#define TRSF_NBITER_V  7

class GEOMImpl_IBlockTrsf
{
 public:

  GEOMImpl_IBlockTrsf (Handle(GEOM_Function) theFunction): _func(theFunction) {}

  void SetOriginal (Handle(GEOM_Function) theOriginal) { _func->SetReference(TRSF_ORIGIN, theOriginal); }

  Handle(GEOM_Function) GetOriginal() { return _func->GetReference(TRSF_ORIGIN); }

  void SetFace1U  (int theFaceId) { _func->SetInteger(TRSF_FACE_1_U, theFaceId); }
  void SetFace2U  (int theFaceId) { _func->SetInteger(TRSF_FACE_2_U, theFaceId); }
  void SetFace1V  (int theFaceId) { _func->SetInteger(TRSF_FACE_1_V, theFaceId); }
  void SetFace2V  (int theFaceId) { _func->SetInteger(TRSF_FACE_2_V, theFaceId); }
  void SetNbIterU (int theNbIter) { _func->SetInteger(TRSF_NBITER_U, theNbIter); }
  void SetNbIterV (int theNbIter) { _func->SetInteger(TRSF_NBITER_V, theNbIter); }

  int GetFace1U () { return _func->GetInteger(TRSF_FACE_1_U); }
  int GetFace2U () { return _func->GetInteger(TRSF_FACE_2_U); }
  int GetFace1V () { return _func->GetInteger(TRSF_FACE_1_V); }
  int GetFace2V () { return _func->GetInteger(TRSF_FACE_2_V); }
  int GetNbIterU() { return _func->GetInteger(TRSF_NBITER_U); }
  int GetNbIterV() { return _func->GetInteger(TRSF_NBITER_V); }

 private:

  Handle(GEOM_Function) _func;
};
//NOTE: This is an intreface to a function for the vector creation.


#include "GEOM_Function.hxx"

#define PLN_ARG_SIZE 1

#define PLN_ARG_PNT1 2
#define PLN_ARG_PNT2 3
#define PLN_ARG_PNT3 4

#define PLN_ARG_VEC 5

#define PLN_ARG_REF 6

class GEOMImpl_IPlane
{
 public:

  GEOMImpl_IPlane(Handle(GEOM_Function) theFunction): _func(theFunction) {}

  void SetSize(double theSize) { _func->SetReal(PLN_ARG_SIZE, theSize); }

  double GetSize() { return _func->GetReal(PLN_ARG_SIZE); }

  void SetPoint (Handle(GEOM_Function) theRef) { _func->SetReference(PLN_ARG_PNT1, theRef); }
  void SetVector(Handle(GEOM_Function) theRef) { _func->SetReference(PLN_ARG_VEC , theRef); }

  void SetFace  (Handle(GEOM_Function) theRef) { _func->SetReference(PLN_ARG_REF , theRef); }

  void SetPoint1(Handle(GEOM_Function) theRef) { _func->SetReference(PLN_ARG_PNT1, theRef); }
  void SetPoint2(Handle(GEOM_Function) theRef) { _func->SetReference(PLN_ARG_PNT2, theRef); }
  void SetPoint3(Handle(GEOM_Function) theRef) { _func->SetReference(PLN_ARG_PNT3, theRef); }

  Handle(GEOM_Function) GetPoint () { return _func->GetReference(PLN_ARG_PNT1); }
  Handle(GEOM_Function) GetVector() { return _func->GetReference(PLN_ARG_VEC ); }

  Handle(GEOM_Function) GetFace  () { return _func->GetReference(PLN_ARG_REF ); }

  Handle(GEOM_Function) GetPoint1() { return _func->GetReference(PLN_ARG_PNT1); }
  Handle(GEOM_Function) GetPoint2() { return _func->GetReference(PLN_ARG_PNT2); }
  Handle(GEOM_Function) GetPoint3() { return _func->GetReference(PLN_ARG_PNT3); }

 private:

  Handle(GEOM_Function) _func;
};
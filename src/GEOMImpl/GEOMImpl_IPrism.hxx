//NOTE: This is an intreface to a function for the Prism creation.


#include "GEOM_Function.hxx"

#define PRISM_ARG_H     1
#define PRISM_ARG_VEC   2
#define PRISM_ARG_BASE  3
#define PRISM_ARG_PNT_F 4
#define PRISM_ARG_PNT_L 5

class GEOMImpl_IPrism
{
 public:

  GEOMImpl_IPrism(Handle(GEOM_Function) theFunction): _func(theFunction) {}

  void SetBase  (Handle(GEOM_Function) theRefBase  ) { _func->SetReference(PRISM_ARG_BASE, theRefBase); }
  void SetVector(Handle(GEOM_Function) theRefVector) { _func->SetReference(PRISM_ARG_VEC , theRefVector); }
  void SetFirstPoint(Handle(GEOM_Function) thePoint) { _func->SetReference(PRISM_ARG_PNT_F, thePoint); }
  void SetLastPoint (Handle(GEOM_Function) thePoint) { _func->SetReference(PRISM_ARG_PNT_L, thePoint); }

  Handle(GEOM_Function) GetBase  () { return _func->GetReference(PRISM_ARG_BASE); }
  Handle(GEOM_Function) GetVector() { return _func->GetReference(PRISM_ARG_VEC ); }
  Handle(GEOM_Function) GetFirstPoint() { return _func->GetReference(PRISM_ARG_PNT_F ); }
  Handle(GEOM_Function) GetLastPoint () { return _func->GetReference(PRISM_ARG_PNT_L ); }

  void SetH(double theH) { _func->SetReal(PRISM_ARG_H, theH); }

  double GetH() { return _func->GetReal(PRISM_ARG_H); }

 private:

  Handle(GEOM_Function) _func;
};
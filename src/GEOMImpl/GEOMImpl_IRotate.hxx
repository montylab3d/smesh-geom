//NOTE: This is an intreface to a function for the Rotate operation.


#include "GEOM_Function.hxx"

#define ROTATE_ANGLE    1  
#define ROTATE_AXIS     2
#define ROTATE_ORGN     3
#define ROTATE_STEP1      4
#define ROTATE_NBITER1   5
#define ROTATE_NBITER2   6

class GEOMImpl_IRotate
{
 public:
  
  GEOMImpl_IRotate(Handle(GEOM_Function) theFunction): _func(theFunction) {}
  
  void SetAngle(Standard_Real theAngle) { _func->SetReal(ROTATE_ANGLE, theAngle); }
  
  Standard_Real GetAngle() { return _func->GetReal(ROTATE_ANGLE); }
  
  void SetAxis(Handle(GEOM_Function) theVector) { _func->SetReference(ROTATE_AXIS, theVector); }
  
  Handle(GEOM_Function) GetAxis() { return _func->GetReference(ROTATE_AXIS); } 
  
  void SetOriginal(Handle(GEOM_Function) theOriginal) { _func->SetReference(ROTATE_ORGN, theOriginal); }

  Handle(GEOM_Function) GetOriginal() { return _func->GetReference(ROTATE_ORGN); }

  void SetStep(double theStep) { return _func->SetReal(ROTATE_STEP1, theStep); }

  double GetStep() { return _func->GetReal(ROTATE_STEP1); }

  void SetNbIter1(int theNbIter) { _func->SetInteger(ROTATE_NBITER1, theNbIter); }

  int GetNbIter1() { return _func->GetInteger(ROTATE_NBITER1); } 

  void SetNbIter2(int theNbIter) { _func->SetInteger(ROTATE_NBITER2, theNbIter); }

  int GetNbIter2() { return _func->GetInteger(ROTATE_NBITER2); } 

  
 private:
  
  Handle(GEOM_Function) _func;  
};
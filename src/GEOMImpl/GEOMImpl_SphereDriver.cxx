
using namespace std;
#include "GEOMImpl_SphereDriver.hxx"
#include "GEOMImpl_ISphere.hxx"
#include "GEOMImpl_Types.hxx"
#include "GEOM_Function.hxx"

#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRep_Tool.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopAbs.hxx>

//=======================================================================
//function : GetID
//purpose  :
//======================================================================= 
const Standard_GUID& GEOMImpl_SphereDriver::GetID()
{
  static Standard_GUID aSphereDriver("FF1BBB16-5D14-4df2-980B-3A668264EA16");
  return aSphereDriver; 
}


//=======================================================================
//function : GEOMImpl_SphereDriver
//purpose  : 
//=======================================================================
GEOMImpl_SphereDriver::GEOMImpl_SphereDriver() 
{
}

//=======================================================================
//function : Execute
//purpose  :
//======================================================================= 
Standard_Integer GEOMImpl_SphereDriver::Execute(TFunction_Logbook& log) const
{
  if (Label().IsNull()) return 0;    
  Handle(GEOM_Function) aFunction = GEOM_Function::GetFunction(Label());

  GEOMImpl_ISphere aCI (aFunction);
  Standard_Integer aType = aFunction->GetType();

  TopoDS_Shape aShape;

  if (aType == SPHERE_R) {
    aShape = BRepPrimAPI_MakeSphere(aCI.GetR()).Shape();
  }
  else if (aType == SPHERE_PNT_R) {
    Handle(GEOM_Function) aRefPoint  = aCI.GetPoint();
    TopoDS_Shape aShapePnt = aRefPoint->GetValue();
    if (aShapePnt.ShapeType() == TopAbs_VERTEX) {
      gp_Pnt aP = BRep_Tool::Pnt(TopoDS::Vertex(aShapePnt));
      aShape = BRepPrimAPI_MakeSphere(aP, aCI.GetR()).Shape();
    }
  }
  else {
  }

  if (aShape.IsNull()) return 0;

  aFunction->SetValue(aShape);

  log.SetTouched(Label()); 

  return 1;    
}


//=======================================================================
//function :  GEOMImpl_SphereDriver_Type_
//purpose  :
//======================================================================= 
Standard_EXPORT Handle_Standard_Type& GEOMImpl_SphereDriver_Type_()
{

  static Handle_Standard_Type aType1 = STANDARD_TYPE(TFunction_Driver);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(TFunction_Driver);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(MMgt_TShared);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(MMgt_TShared); 
  static Handle_Standard_Type aType3 = STANDARD_TYPE(Standard_Transient);
  if ( aType3.IsNull()) aType3 = STANDARD_TYPE(Standard_Transient);
 

  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,aType3,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("GEOMImpl_SphereDriver",
			                                 sizeof(GEOMImpl_SphereDriver),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}

//=======================================================================
//function : DownCast
//purpose  :
//======================================================================= 
const Handle(GEOMImpl_SphereDriver) Handle(GEOMImpl_SphereDriver)::DownCast(const Handle(Standard_Transient)& AnObject)
{
  Handle(GEOMImpl_SphereDriver) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(GEOMImpl_SphereDriver))) {
       _anOtherObject = Handle(GEOMImpl_SphereDriver)((Handle(GEOMImpl_SphereDriver)&)AnObject);
     }
  }

  return _anOtherObject ;
}

using namespace std;
#include "GEOMImpl_ChamferDriver.hxx"
#include "GEOMImpl_IChamfer.hxx"
#include "GEOMImpl_Types.hxx"
#include "GEOMImpl_ILocalOperations.hxx"
#include "GEOM_Function.hxx"
#include "GEOMImpl_Block6Explorer.hxx"

#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>

#include <Precision.hxx>
#include <gp_Pnt.hxx>
#include <StdFail_NotDone.hxx>

//=======================================================================
//function : GetID
//purpose  :
//=======================================================================
const Standard_GUID& GEOMImpl_ChamferDriver::GetID()
{
  static Standard_GUID aChamferDriver("FF1BBB42-5D14-4df2-980B-3A668264EA16");
  return aChamferDriver;
}


//=======================================================================
//function : GEOMImpl_ChamferDriver
//purpose  :
//=======================================================================
GEOMImpl_ChamferDriver::GEOMImpl_ChamferDriver()
{
}

//=======================================================================
//function : isGoodForChamfer
//purpose  :
//=======================================================================
static Standard_Boolean isGoodForChamfer (const TopoDS_Shape& theShape)
{
  if (theShape.ShapeType() == TopAbs_SHELL ||
      theShape.ShapeType() == TopAbs_SOLID ||
      theShape.ShapeType() == TopAbs_COMPSOLID) {
    return Standard_True;
  }

  if (theShape.ShapeType() == TopAbs_COMPOUND) {
    TopTools_MapOfShape mapShape;
    TopoDS_Iterator It (theShape, Standard_False, Standard_False);
    for (; It.More(); It.Next()) {
      if (mapShape.Add(It.Value())) {
        if (!isGoodForChamfer(It.Value())) {
          return Standard_False;
        }
      }
    }
    return Standard_True;
  }

  return Standard_False;
}

//=======================================================================
//function : Execute
//purpose  :
//=======================================================================
Standard_Integer GEOMImpl_ChamferDriver::Execute(TFunction_Logbook& log) const
{
  if (Label().IsNull()) return 0;
  Handle(GEOM_Function) aFunction = GEOM_Function::GetFunction(Label());

  GEOMImpl_IChamfer aCI (aFunction);
  Standard_Integer aType = aFunction->GetType();

  TopoDS_Shape aShape;

  Handle(GEOM_Function) aRefShape = aCI.GetShape();
  TopoDS_Shape aShapeBase = aRefShape->GetValue();

  // Check the shape type. It have to be shell
  // or solid, or compsolid, or compound of these shapes.
  if (!isGoodForChamfer(aShapeBase)) {
    StdFail_NotDone::Raise
      ("Wrong shape. Must be shell or solid, or compsolid or compound of these shapes");
  }

  BRepFilletAPI_MakeChamfer fill (aShapeBase);

  if (aType == CHAMFER_SHAPE_ALL) {
    // symmetric chamfer on all edges
    double aD = aCI.GetD();
    TopTools_IndexedDataMapOfShapeListOfShape M;
    GEOMImpl_Block6Explorer::MapShapesAndAncestors(aShapeBase, TopAbs_EDGE, TopAbs_FACE, M);
    for (int i = 1; i <= M.Extent(); i++) {
      TopoDS_Edge E = TopoDS::Edge(M.FindKey(i));
      TopoDS_Face F = TopoDS::Face(M.FindFromIndex(i).First());
      if (!BRepTools::IsReallyClosed(E, F) &&
          !BRep_Tool::Degenerated(E) &&
          M.FindFromIndex(i).Extent() == 2)
        fill.Add(aD, E, F);
    }
  } else if (aType == CHAMFER_SHAPE_EDGE) {
    // chamfer on edges, common to two faces, with D1 on the first face
    double aD1 = aCI.GetD1();
    double aD2 = aCI.GetD2();
    TopoDS_Shape aFace1, aFace2;
    if (GEOMImpl_ILocalOperations::GetSubShape(aShapeBase, aCI.GetFace1(), aFace1) &&
        GEOMImpl_ILocalOperations::GetSubShape(aShapeBase, aCI.GetFace2(), aFace2)) {
      TopoDS_Face F = TopoDS::Face(aFace1);

      // fill map of edges of the second face
      TopTools_MapOfShape aMap;
      TopExp_Explorer Exp2 (aFace2, TopAbs_EDGE);
      for (; Exp2.More(); Exp2.Next()) {
        aMap.Add(Exp2.Current());
      }

      // find edges of the first face, common with the second face
      TopExp_Explorer Exp (aFace1, TopAbs_EDGE);
      for (; Exp.More(); Exp.Next()) {
        if (aMap.Contains(Exp.Current())) {
          TopoDS_Edge E = TopoDS::Edge(Exp.Current());
          if (!BRepTools::IsReallyClosed(E, F) && !BRep_Tool::Degenerated(E))
            fill.Add(aD1, aD2, E, F);
        }
      }
    }
  } else if (aType == CHAMFER_SHAPE_FACES) {
    // chamfer on all edges of the selected faces, with D1 on the selected face
    // (on first selected face, if the edge belongs to two selected faces)
    double aD1 = aCI.GetD1();
    double aD2 = aCI.GetD2();
    int aLen = aCI.GetLength();
    int ind = 1;
    TopTools_MapOfShape aMap;
    TopTools_IndexedDataMapOfShapeListOfShape M;
    GEOMImpl_Block6Explorer::MapShapesAndAncestors(aShapeBase, TopAbs_EDGE, TopAbs_FACE, M);
    for (; ind <= aLen; ind++)
    {
      TopoDS_Shape aShapeFace;
      if (GEOMImpl_ILocalOperations::GetSubShape
          (aShapeBase, aCI.GetFace(ind), aShapeFace)) {
        TopoDS_Face F = TopoDS::Face(aShapeFace);
        TopExp_Explorer Exp (F, TopAbs_EDGE);
        for (; Exp.More(); Exp.Next()) {
          if (!aMap.Contains(Exp.Current())) {
            TopoDS_Edge E = TopoDS::Edge(Exp.Current());
            if (!BRepTools::IsReallyClosed(E, F) &&
                !BRep_Tool::Degenerated(E) &&
                M.FindFromKey(E).Extent() == 2)
              fill.Add(aD1, aD2, E, F);
          }
        }
      }
    }
  } else {
  }

  fill.Build();
  if (!fill.IsDone()) {
    StdFail_NotDone::Raise("Chamfer can not be computed on the given shape with the given parameters");
  }
  aShape = fill.Shape();

  if (aShape.IsNull()) return 0;

  aFunction->SetValue(aShape);

  log.SetTouched(Label());

  return 1;
}


//=======================================================================
//function :  GEOMImpl_ChamferDriver_Type_
//purpose  :
//=======================================================================
Standard_EXPORT Handle_Standard_Type& GEOMImpl_ChamferDriver_Type_()
{

  static Handle_Standard_Type aType1 = STANDARD_TYPE(TFunction_Driver);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(TFunction_Driver);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(MMgt_TShared);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(MMgt_TShared);
  static Handle_Standard_Type aType3 = STANDARD_TYPE(Standard_Transient);
  if ( aType3.IsNull()) aType3 = STANDARD_TYPE(Standard_Transient);


  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,aType3,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("GEOMImpl_ChamferDriver",
			                                 sizeof(GEOMImpl_ChamferDriver),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}

//=======================================================================
//function : DownCast
//purpose  :
//=======================================================================
const Handle(GEOMImpl_ChamferDriver) Handle(GEOMImpl_ChamferDriver)::DownCast(const Handle(Standard_Transient)& AnObject)
{
  Handle(GEOMImpl_ChamferDriver) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(GEOMImpl_ChamferDriver))) {
       _anOtherObject = Handle(GEOMImpl_ChamferDriver)((Handle(GEOMImpl_ChamferDriver)&)AnObject);
     }
  }

  return _anOtherObject ;
}
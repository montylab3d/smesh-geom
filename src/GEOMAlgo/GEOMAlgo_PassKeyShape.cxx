// File:	GEOMAlgo_PassKeyShape.cxx
// Created:	
// Author:	Peter KURNEV
//		<pkv@irinox>


#include <GEOMAlgo_PassKeyShape.ixx>

#include <stdio.h>
#include <string.h>

#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TColStd_ListOfInteger.hxx>

//=======================================================================
//function :
//purpose  : 
//=======================================================================
  GEOMAlgo_PassKeyShape::GEOMAlgo_PassKeyShape()
:
  GEOMAlgo_PassKey()
{
  myUpper=432123;
  GEOMAlgo_PassKey::Clear();
}
//=======================================================================
//function :SetIds
//purpose  : 
//=======================================================================
  void GEOMAlgo_PassKeyShape::SetIds(const TopoDS_Shape& aS1)
			       
{
  Standard_Integer anId1;
  //
  anId1=aS1.HashCode(myUpper);
  GEOMAlgo_PassKey::SetIds(anId1);
}
//=======================================================================
//function :SetIds
//purpose  : 
//=======================================================================
  void GEOMAlgo_PassKeyShape::SetIds(const TopoDS_Shape& aS1,
				     const TopoDS_Shape& aS2)
{
  Standard_Integer anId1, anId2;
  //
  anId1=aS1.HashCode(myUpper);
  anId2=aS2.HashCode(myUpper);
  //
  GEOMAlgo_PassKey::SetIds(anId1, anId2);
}
//=======================================================================
//function :SetIds
//purpose  : 
//=======================================================================
  void GEOMAlgo_PassKeyShape::SetIds(const TopoDS_Shape& aS1,
				     const TopoDS_Shape& aS2,
				     const TopoDS_Shape& aS3)
{
  Standard_Integer anId1, anId2, anId3;
  //
  anId1=aS1.HashCode(myUpper);
  anId2=aS2.HashCode(myUpper);
  anId3=aS3.HashCode(myUpper);
  //
  GEOMAlgo_PassKey::SetIds(anId1, anId2, anId3);
}
//=======================================================================
//function :SetIds
//purpose  : 
//=======================================================================
  void GEOMAlgo_PassKeyShape::SetIds(const TopoDS_Shape& aS1,
				const TopoDS_Shape& aS2,
				const TopoDS_Shape& aS3,
				const TopoDS_Shape& aS4)
{
  Standard_Integer anId1, anId2, anId3, anId4;
  //
  anId1=aS1.HashCode(myUpper);
  anId2=aS2.HashCode(myUpper);
  anId3=aS3.HashCode(myUpper);
  anId4=aS4.HashCode(myUpper);
  //
  GEOMAlgo_PassKey::SetIds(anId1, anId2, anId3, anId4);
}
//=======================================================================
//function :SetIds
//purpose  : 
//=======================================================================
  void GEOMAlgo_PassKeyShape::SetIds(const TopTools_ListOfShape& aLS)
{
  Standard_Integer anId;
  TopTools_ListIteratorOfListOfShape aIt;
  TColStd_ListOfInteger aLI;
  //
  //aNb=aLS.Extent();
  //if (aNb<1 || aNb > myNbMax) {
  //  return;
  //}
  //
  //myNbIds=aNb;
  //mySum=0;
  //i=myNbMax-myNbIds;
  
  aIt.Initialize(aLS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    anId=aS.HashCode(myUpper);
    aLI.Append(anId);
  }
  GEOMAlgo_PassKey::SetIds(aLI);
}
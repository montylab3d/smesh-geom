using namespace std;
//  File      : GeometryGUI_Swig.cxx
//  Created   : Tue Mar 26 15:08:38 2002
//  Author    : Nicolas REJNERI, Paul RASCLE
//  Project   : SALOME
//  Module    : GEOM
//  Copyright : Open CASCADE, EDF 2002
//  $Header$

#include "GeometryGUI_Swig.hxx"
#include "utilities.h"

#include "QAD_Application.h"
#include "QAD_Desktop.h"
#include "QAD_Study.h"
#include "QAD_StudyFrame.h"
#include "QAD_RightFrame.h"
#include "SALOMEGUI_ImportOperation.h"

#include "OCCViewer_Viewer3d.h"
#include "VTKViewer_RenderWindowInteractor.h"
#include "VTKViewer_ViewFrame.h"

#include "GEOM_Actor.h"
#include "GEOM_Client.hxx"
#include "GEOM_AISShape.hxx"
#include "GEOM_AssemblyBuilder.h"
#include "GEOM_InteractiveObject.hxx"

#include <TopExp_Explorer.hxx>
#include <TopTools_MapOfShape.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <GeomAbs_CurveType.hxx>
#include <GeomAbs_SurfaceType.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>

static GEOM_Client ShapeReader;

GeometryGUI_Swig::GeometryGUI_Swig()
{
  // MESSAGE("Constructeur");
}

GeometryGUI_Swig::~GeometryGUI_Swig()
{
  // MESSAGE("Destructeur");
}

void GeometryGUI_Swig::createAndDisplayGO(const char* Entry)
{
  // MESSAGE("createAndDisplayGO");
  QAD_Study* ActiveStudy = QAD_Application::getDesktop()->getActiveStudy();
  SALOMEDS::Study_var aStudy = ActiveStudy->getStudyDocument();
  SALOMEDS::StudyBuilder_var aStudyBuilder = aStudy->NewBuilder();

  Engines::Component_var comp = QAD_Application::getDesktop()->getEngine("FactoryServer", "Geometry");
  GEOM::GEOM_Gen_var Geom = GEOM::GEOM_Gen::_narrow(comp);

  Standard_CString Fatherior = "";
  SALOMEDS::SComponent_var father = aStudy->FindComponent("GEOM");
  aStudyBuilder->DefineComponentInstance( father, Geom );
  father->ComponentIOR( Fatherior );

  SALOMEDS::SObject_var fatherSF = aStudy->FindObjectID(ActiveStudy->getActiveStudyFrame()->entry());

  SALOMEDS::SObject_var obj = aStudy->FindObjectID(Entry);
  SALOMEDS::GenericAttribute_var anAttr;
  SALOMEDS::AttributeName_var    aName;
  SALOMEDS::AttributeIOR_var     anIOR;
  // Create new actor
  if ( !obj->FindAttribute(anAttr, "AttributeIOR")) 
    return;
  anIOR = SALOMEDS::AttributeIOR::_narrow(anAttr);
  GEOM::GEOM_Shape_var aShape = Geom->GetIORFromString(anIOR->Value());
  TopoDS_Shape Shape = ShapeReader.GetShape(Geom,aShape);
  
  if ( !obj->_is_nil() ) {
    if (obj->FindAttribute(anAttr, "AttributeName")) {
      aName = SALOMEDS::AttributeName::_narrow(anAttr);
      // open transaction
      QAD_Operation* op = new SALOMEGUI_ImportOperation( ActiveStudy );
      op->start();
      
      SALOMEDS::SObject_var newObj1 = aStudyBuilder->NewObject(fatherSF);
      aStudyBuilder->Addreference(newObj1, obj);
      // commit transaction
      op->finish();
		  
      if ( ActiveStudy->getActiveStudyFrame()->getTypeView() == VIEW_VTK )  { // VTK
	//vtkQGLRenderWindowInteractor* myRenderInter = ActiveStudy->getActiveStudyFrame()->getRightFrame()->getVTKView()->getRWInteractor();
	VTKViewer_RenderWindowInteractor* myRenderInter= ((VTKViewer_ViewFrame*)ActiveStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getRWInteractor();
 	int themode = myRenderInter->GetDisplayMode();
      
	vtkActorCollection* theActors = 
	  GEOM_AssemblyBuilder::BuildActors(Shape,0,themode,Standard_True);
	theActors->InitTraversal();
	vtkActor* anActor = (vtkActor*)theActors->GetNextActor();
	while(!(anActor==NULL)) {
	  GEOM_Actor* GActor = GEOM_Actor::SafeDownCast( anActor );
	  Handle(GEOM_InteractiveObject) IO = new GEOM_InteractiveObject(anIOR->Value(),
									 Fatherior,
									 "GEOM");
	  IO->setEntry(obj->GetID());
	  GActor->setIO( IO );
	  GActor->setName( aName->Value() );
	  
	  myRenderInter->Display(GActor);
	  anActor = (vtkActor*)theActors->GetNextActor();
	}
	myRenderInter->Update();
      } 
      else if ( ActiveStudy->getActiveStudyFrame()->getTypeView() == VIEW_OCC ) // OCC
	{
	  OCCViewer_Viewer3d* v3d = ((OCCViewer_ViewFrame*)ActiveStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getViewer();
	  //	  QAD_Viewer3d* v3d = ActiveStudy->getActiveStudyFrame()->getViewerOCC();
	  Handle(AIS_InteractiveContext) ic = v3d->getAISContext();
	  Handle(GEOM_AISShape) aSh = new GEOM_AISShape(Shape, aName->Value());
	  Handle(GEOM_InteractiveObject) IO = new GEOM_InteractiveObject(anIOR->Value(),
									 Fatherior,
									 "GEOM");
	  
	  IO->setEntry(obj->GetID());
	  aSh->setIO( IO );
	  aSh->setName( aName->Value() );
	  ic->Display (aSh);
	  ic->AddOrRemoveCurrentObject(aSh, true);
	}
    }
  }
  ActiveStudy->updateObjBrowser( true );
}

int  GeometryGUI_Swig::getIndexTopology(const char* SubIOR, const char* IOR)
{
  Engines::Component_var comp = QAD_Application::getDesktop()->getEngine("FactoryServer", "Geometry");
  GEOM::GEOM_Gen_var  Geom = GEOM::GEOM_Gen::_narrow(comp);
 
  GEOM::GEOM_Shape_var aMainShape = Geom->GetIORFromString(IOR);
  TopoDS_Shape shape        = ShapeReader.GetShape(Geom, aMainShape);

  GEOM::GEOM_Shape_var aSubShape = Geom->GetIORFromString(SubIOR);
  TopoDS_Shape subshape    = ShapeReader.GetShape(Geom, aSubShape);

  TopExp_Explorer Exp ( shape, subshape.ShapeType() );
  int index = 1;
  TopTools_MapOfShape M;
  while ( Exp.More() ) {
    if ( M.Add(Exp.Current()) ) {
      if ( Exp.Current().IsSame(subshape) )
	return index;
      index++;
    }
    Exp.Next();
  }
  return -1;
}

const char* GeometryGUI_Swig::getShapeTypeString(const char* IOR)
{
  Engines::Component_var comp = QAD_Application::getDesktop()->getEngine("FactoryServer", "Geometry");
  GEOM::GEOM_Gen_var  Geom = GEOM::GEOM_Gen::_narrow(comp);
 
  GEOM::GEOM_Shape_var aShape = Geom->GetIORFromString(IOR);
  TopoDS_Shape shape    = ShapeReader.GetShape(Geom, aShape);

  if( shape.IsNull() ) {
    return "Null Shape" ;
  }

  switch (shape.ShapeType() )
  {
  case TopAbs_COMPOUND:
    { return "Compound" ;}
  case  TopAbs_COMPSOLID:
    { return "Compound Solid" ;}
  case TopAbs_SOLID:
    { return "Solid" ;}
  case TopAbs_SHELL:
    { return "Shell" ;}
  case TopAbs_FACE:
    { 
      BRepAdaptor_Surface surf(TopoDS::Face(shape));
      if ( surf.GetType() == GeomAbs_Plane ) {
	return "Plane" ;
      } else if ( surf.GetType() == GeomAbs_Cylinder ) {
	return "Cylindrical Face" ;
      } else if ( surf.GetType() == GeomAbs_Sphere ) {
	return "Spherical Face" ;
      } else if ( surf.GetType() == GeomAbs_Torus ) {
	return "Toroidal Face" ;
      } else if ( surf.GetType() == GeomAbs_Cone ) {
	return "Conical Face" ;
      } else {
	return "GEOM::FACE" ;
      }
    }
  case TopAbs_WIRE:
    { return "Wire" ;}
  case TopAbs_EDGE:
    { 
      BRepAdaptor_Curve curv(TopoDS::Edge(shape));
      if ( curv.GetType() == GeomAbs_Line ) {
	if ( (Abs(curv.FirstParameter()) >= 1E6 ) || 
	     (Abs(curv.LastParameter()) >= 1E6 )) {
	  return "Line" ;
	} else
	  return "Edge" ;
      } else if ( curv.GetType() == GeomAbs_Circle ) {
	if ( curv.IsClosed() )
	  return "Circle" ;
	else
	  return "Arc" ;
      } else {
	return "Edge" ;
      }
    }
  case TopAbs_VERTEX:
    { return "Vertex" ;}
  case TopAbs_SHAPE:
    { return "Shape" ;}
  }
}


const char* GeometryGUI_Swig::getShapeTypeIcon(const char* IOR)
{
  Engines::Component_var comp = QAD_Application::getDesktop()->getEngine("FactoryServer", "Geometry");
  GEOM::GEOM_Gen_var  Geom = GEOM::GEOM_Gen::_narrow(comp);
 
  GEOM::GEOM_Shape_var aShape = Geom->GetIORFromString(IOR);

  if( aShape->_is_nil() ) {
    return "None" ;
  }
      
  switch (aShape->ShapeType() )
    {
    case TopAbs_COMPOUND:
      { return "ICON_OBJBROWSER_COMPOUND" ;}
    case  TopAbs_COMPSOLID:
      { return "ICON_OBJBROWSER_COMPSOLID" ;}
    case TopAbs_SOLID:
      { return "ICON_OBJBROWSER_SOLID" ;}
    case TopAbs_SHELL:
      { return "ICON_OBJBROWSER_SHELL" ;}
    case TopAbs_FACE:
      { return "ICON_OBJBROWSER_FACE" ;}
    case TopAbs_WIRE:
      { return "ICON_OBJBROWSER_WIRE" ;}
    case TopAbs_EDGE:
      { return "ICON_OBJBROWSER_EDGE" ;}
    case TopAbs_VERTEX:
      { return "ICON_OBJBROWSER_VERTEX" ;}
    }
  return "None";
}

void GeometryGUI_Swig::setDisplayMode(const char* Entry, int mode)
{
  QAD_Study* myStudy = QAD_Application::getDesktop()->getActiveStudy();
  Handle(SALOME_InteractiveObject) IO = 
    myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame()->FindIObject( Entry );

  if ( myStudy->getActiveStudyFrame()->getTypeView() == VIEW_VTK )  { // VTK
    VTKViewer_RenderWindowInteractor* myRenderInter = 
      ((VTKViewer_ViewFrame*)myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getRWInteractor();
    
    myRenderInter->SwitchRepresentation(IO, mode);
    myRenderInter->Update();
  } 
  else if ( myStudy->getActiveStudyFrame()->getTypeView() == VIEW_OCC ) // OCC
    {
      OCCViewer_Viewer3d* v3d = ((OCCViewer_ViewFrame*)myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getViewer();
      v3d->SwitchRepresentation(IO, mode);
    }
}

void GeometryGUI_Swig::setColor(const char* Entry, int red, int green, int blue)
{
  QAD_Study* myStudy = QAD_Application::getDesktop()->getActiveStudy();
  QColor c = QColor (red, green, blue);
  Handle(SALOME_InteractiveObject) IO = 
    myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame()->FindIObject( Entry );
 
  if ( myStudy->getActiveStudyFrame()->getTypeView() == VIEW_VTK )  { // VTK
    VTKViewer_RenderWindowInteractor* myRenderInter = 
      ((VTKViewer_ViewFrame*)myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getRWInteractor();
    myRenderInter->SetColor(IO,c);
    myRenderInter->Update();
  } 
  else if ( myStudy->getActiveStudyFrame()->getTypeView() == VIEW_OCC ) // OCC
    {
      OCCViewer_Viewer3d* v3d = ((OCCViewer_ViewFrame*)myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getViewer();
      v3d->SetColor(IO,c);
    }
}

void GeometryGUI_Swig::setTransparency(const char* Entry, float transp)
{
  QAD_Study* myStudy = QAD_Application::getDesktop()->getActiveStudy();
  Handle(SALOME_InteractiveObject) IO = 
    myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame()->FindIObject( Entry );
 
  if ( myStudy->getActiveStudyFrame()->getTypeView() == VIEW_VTK )  { // VTK
    VTKViewer_RenderWindowInteractor* myRenderInter = 
      ((VTKViewer_ViewFrame*)myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getRWInteractor();
    myRenderInter->SetTransparency(IO,transp);
    myRenderInter->Update();
  } 
  else if ( myStudy->getActiveStudyFrame()->getTypeView() == VIEW_OCC ) // OCC
    {
      OCCViewer_Viewer3d* v3d = ((OCCViewer_ViewFrame*)myStudy->getActiveStudyFrame()->getRightFrame()->getViewFrame())->getViewer();
      v3d->SetTransparency(IO,transp);
    }
}
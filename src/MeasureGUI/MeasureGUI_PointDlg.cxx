//  GEOM GEOMGUI : GUI for Geometry component
//
//  Copyright (C) 2003  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS 
// 
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public 
//  License as published by the Free Software Foundation; either 
//  version 2.1 of the License. 
// 
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free Software 
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA 
// 
//  See http://www.opencascade.org/SALOME/ or email : webmaster.salome@opencascade.org 
//
//
//
//  File   : MeasureGUI_PointDlg.cxx
//  Author : Lucien PIGNOLONI
//  Module : GEOM
//  $Header$

#include "MeasureGUI_PointDlg.h"
#include "utilities.h"
#include "QAD_Desktop.h"
#include "GEOMBase.h"

#include <TColStd_MapOfInteger.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRep_Tool.hxx>
#include <TopExp.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TColStd_IndexedMapOfInteger.hxx>
#include <gp_Pnt.hxx>

#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qapplication.h>

//=================================================================================
// class    : MeasureGUI_PointDlg()
// purpose  : Constructs a MeasureGUI_PointDlg which is a child of 'parent'
//            
//=================================================================================
MeasureGUI_PointDlg::MeasureGUI_PointDlg( QWidget* parent, SALOME_Selection* Sel )
: MeasureGUI_Skeleton( parent, "MeasureGUI_PointDlg", Sel )
{
  QPixmap iconPnt( QAD_Desktop::getResourceManager()->loadPixmap(
    "GEOM",tr( "ICON_DLG_POINT" ) ) );
  
  QPixmap iconSelect( QAD_Desktop::getResourceManager()->loadPixmap(
    "GEOM",tr( "ICON_SELECT" ) ) );

  setCaption( tr( "CAPTION" ) );

  GroupConstructors->setTitle( tr( "CAPTION" ) );
  RadioButton1->setPixmap( iconPnt );

  QGroupBox* aGrp = new QGroupBox( 2, Qt::Horizontal, tr( "COORDINATES" ), this );
  
  new QLabel( tr( "POINT" ), aGrp );
  QFrame* aFrame = new QFrame( aGrp );
  mySelBtn = new QPushButton( aFrame );
  mySelBtn->setPixmap( iconSelect );
  mySelEdit = new QLineEdit( aFrame );
  QHBoxLayout* aLay = new QHBoxLayout( aFrame, 0, 10 );
  aLay->addWidget( mySelBtn );
  aLay->addWidget( mySelEdit );

  new QLabel( tr( "X" ), aGrp );
  myX = new QLineEdit( aGrp );
  new QLabel( tr( "Y" ), aGrp );
  myY = new QLineEdit( aGrp );
  new QLabel( tr( "Z" ), aGrp );
  myZ = new QLineEdit( aGrp );

  mySelEdit->setReadOnly( true );
  myX->setReadOnly( true );
  myY->setReadOnly( true );
  myZ->setReadOnly( true );

  Layout1->addWidget( aGrp, 1, 0 );

  Init( Sel );
}


//=================================================================================
// function : ~MeasureGUI_PointDlg()
// purpose  : Destroys the object and frees any allocated resources
//======================myX->setReadOnly( true );===========================================================
MeasureGUI_PointDlg::~MeasureGUI_PointDlg()
{
}


//=================================================================================
// function : Init()
// purpose  :
//=================================================================================
void MeasureGUI_PointDlg::Init( SALOME_Selection* Sel )
{
  QSize aSize( size() );
  resize( (int)(aSize.width() *0.75 ), aSize.height() );
  MeasureGUI_Skeleton::Init( Sel );
}

//=================================================================================
// function : activateSelection
// purpose  :
//=================================================================================
void MeasureGUI_PointDlg::activateSelection()
{
  localSelection( GEOM::GEOM_Object::_nil(), TopAbs_VERTEX );
}

//=================================================================================
// function : SelectionIntoArgument
// purpose  :
//=================================================================================
void MeasureGUI_PointDlg::SelectionIntoArgument()
{
  try
  {
    myObj = GEOM::GEOM_Object::_nil();
    mySelEdit->setText( "" );
    myX->setText( "" );
    myY->setText( "" );
    myZ->setText( "" );

    Standard_Boolean testResult = Standard_False;
    GEOM::GEOM_Object_var aSelectedObject =
      GEOMBase::ConvertIOinGEOMObject( mySelection->firstIObject(), testResult );

    if( !testResult || aSelectedObject->_is_nil() )
      return;

    myObj = aSelectedObject;

    TColStd_IndexedMapOfInteger anIndexes;
    mySelection->GetIndex( mySelection->firstIObject(), anIndexes );

    TopoDS_Shape aShape;
    if ( anIndexes.Extent() > 1 || !GEOMBase::GetShape( myObj, aShape ) || aShape.IsNull() )
      return;

    TopoDS_Vertex aPoint;
    QString aName = GEOMBase::GetName( myObj );
    if ( anIndexes.Extent() == 0 )
    {
      if ( aShape.ShapeType() == TopAbs_VERTEX )
        aPoint = TopoDS::Vertex( aShape );
    }
    else
    {
      int i = anIndexes( 1 );

      TopTools_IndexedMapOfShape aShapes;
      TopExp::MapShapes( aShape, aShapes );
      
      if ( aShape != aShapes( i ) )
        aName += QString( ":%1" ).arg( i );

      aPoint = TopoDS::Vertex( aShapes( i ) );
    }

    if ( !aPoint.IsNull() )
    {
      gp_Pnt aPnt = BRep_Tool::Pnt( aPoint );
      mySelEdit->setText( aName );
      myX->setText( QString( "%1" ).arg( aPnt.X() ) );
      myY->setText( QString( "%1" ).arg( aPnt.Y() ) );
      myZ->setText( QString( "%1" ).arg( aPnt.Z() ) );
    }
  }
  catch( ... )
  {
    myObj = GEOM::GEOM_Object::_nil();
    mySelEdit->setText( "" );
    myX->setText( "" );
    myY->setText( "" );
    myZ->setText( "" );
  }
}




















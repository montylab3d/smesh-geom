//  SALOME GEOM : 
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
//  File   : GEOM_VTKTrihedron.h
//  Author : Sergey LITONIN
//  Module : SALOME
//  $Header: 

#ifndef GEOM_VTKTrihedron_H
#define GEOM_VTKTrihedron_H

#include <Geom_Axis2Placement.hxx>
#include "SALOME_Actor.h"
#include "VTKViewer_Trihedron.h"

class vtkActorCollection;
class vtkRenderer;
class vtkPolyDataMapper;

/*
  Class       : GEOM_VTKTrihedron
  Description : Class for displaying trihedron of local CS in VTK viewer.
                Placement of trihedron is chahged with SetPlacement() method
*/

class GEOM_VTKTrihedron : public SALOME_Actor
{

protected:
                                    GEOM_VTKTrihedron();
                                    GEOM_VTKTrihedron( const GEOM_VTKTrihedron& );
  virtual                           ~GEOM_VTKTrihedron();

public:
                                    vtkTypeMacro( GEOM_VTKTrihedron, SALOME_Actor );
  static GEOM_VTKTrihedron*         New();

  virtual float                     GetSize() { return mySize;}

  virtual void                      SetVisibility( VTKViewer_Trihedron::TVisibility theVis );
  virtual void                      VisibilityOff() { SetVisibility( VTKViewer_Trihedron::eOff ); }
  virtual void                      VisibilityOn() { SetVisibility( VTKViewer_Trihedron::eOn ); }

  virtual void                      AddToRender( vtkRenderer* theRenderer );
  virtual void                      RemoveFromRender( vtkRenderer* theRenderer );

  virtual int                       GetVisibleActorCount( vtkRenderer* theRenderer );

  void                              SetPlacement( const Handle(Geom_Axis2Placement)& );

  virtual vtkMapper*                GetMapper();

  virtual void                      Render(vtkRenderer *, vtkMapper *);
  virtual bool                      IsSetCamera() const;
  virtual bool                      IsResizable() const;
  virtual void                      SetSize( float );
  virtual void                      SetCamera( vtkCamera* );

  void                              SetColor( float r, float g, float b );
  void                              GetColor( float& r, float& g, float& b );

  virtual bool                      hasHighlight() { return false; } 

protected:
  vtkActorCollection*               myPresent;
  VTKViewer_Axis*                   myAxis[3];
  vtkPolyDataMapper*                myMapper;
  float                             mySize;
  gp_Pnt                            myLocation;
  gp_Dir                            myDirX, myDirY, myDirZ;
  float                             myColor[ 3 ];
};

#endif
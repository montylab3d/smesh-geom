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
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//
//
//
// File      : GEOMAlgo_FinderShapeOnQuad.hxx
// Created   : Mon Oct 17 17:15:59 2005
// Author    : Edward AGAPOV (eap)

#ifndef GEOMAlgo_FinderShapeOnQuad_HeaderFile
#define GEOMAlgo_FinderShapeOnQuad_HeaderFile

#include "GEOMAlgo_FinderShapeOn1.hxx"

#include <gp_Vec.hxx>

#include <vector>


class GEOMAlgo_FinderShapeOnQuad: public GEOMAlgo_FinderShapeOn1
{
public:

  GEOMAlgo_FinderShapeOnQuad(const gp_Pnt & theTopLeftPoint,
                             const gp_Pnt & theTopRigthPoint,
                             const gp_Pnt & theBottomLeftPoint,
                             const gp_Pnt & theBottomRigthPoint);

protected:

  virtual  void CheckData() ;

  virtual TopAbs_State GetPointState(const gp_Pnt& aP) ;

private:

  bool                         myConcaveQuad;
  vector<bool>                 myConcaveSide;
  vector<gp_Pnt>               myPoints;
  vector<GeomAdaptor_Surface>  myPlanes;
  gp_Vec                       myQuadNormal;
};
#endif
// File generated by CPPExt (Transient)
//
//
//                     Copyright (C) 1991 - 2000 by  
//                      Matra Datavision SA.  All rights reserved.
//  
//                     Copyright (C) 2001 - 2004 by
//                     Open CASCADE SA.  All rights reserved.
// 
// This file is part of the Open CASCADE Technology software.
//
// This software may be distributed and/or modified under the terms and
// conditions of the Open CASCADE Public License as defined by Open CASCADE SA
// and appearing in the file LICENSE included in the packaging of this file.
//  
// This software is distributed on an "AS IS" basis, without warranty of any
// kind, and Open CASCADE SA hereby disclaims all such warranties,
// including without limitation, any warranties of merchantability, fitness
// for a particular purpose or non-infringement. Please see the License for
// the specific terms and conditions governing rights and limitations under the
// License.

#ifndef _GEOMAlgo_ListNodeOfListOfCoupleOfShapes_HeaderFile
#define _GEOMAlgo_ListNodeOfListOfCoupleOfShapes_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_GEOMAlgo_ListNodeOfListOfCoupleOfShapes_HeaderFile
#include <Handle_GEOMAlgo_ListNodeOfListOfCoupleOfShapes.hxx>
#endif

#ifndef _GEOMAlgo_CoupleOfShapes_HeaderFile
#include <GEOMAlgo_CoupleOfShapes.hxx>
#endif
#ifndef _TCollection_MapNode_HeaderFile
#include <TCollection_MapNode.hxx>
#endif
#ifndef _TCollection_MapNodePtr_HeaderFile
#include <TCollection_MapNodePtr.hxx>
#endif
class GEOMAlgo_CoupleOfShapes;
class GEOMAlgo_ListOfCoupleOfShapes;
class GEOMAlgo_ListIteratorOfListOfCoupleOfShapes;


class GEOMAlgo_ListNodeOfListOfCoupleOfShapes : public TCollection_MapNode {

public:

    void* operator new(size_t,void* anAddress) 
      {
        return anAddress;
      }
    void* operator new(size_t size) 
      { 
        return Standard::Allocate(size); 
      }
    void  operator delete(void *anAddress) 
      { 
        if (anAddress) Standard::Free((Standard_Address&)anAddress); 
      }
 // Methods PUBLIC
 // 
GEOMAlgo_ListNodeOfListOfCoupleOfShapes(const GEOMAlgo_CoupleOfShapes& I,const TCollection_MapNodePtr& n);
  GEOMAlgo_CoupleOfShapes& Value() const;
Standard_EXPORT ~GEOMAlgo_ListNodeOfListOfCoupleOfShapes();




 // Type management
 //
 Standard_EXPORT friend Handle_Standard_Type& GEOMAlgo_ListNodeOfListOfCoupleOfShapes_Type_();
 Standard_EXPORT const Handle(Standard_Type)& DynamicType() const;
 Standard_EXPORT Standard_Boolean	       IsKind(const Handle(Standard_Type)&) const;

protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


 // Fields PRIVATE
 //
GEOMAlgo_CoupleOfShapes myValue;


};

#define Item GEOMAlgo_CoupleOfShapes
#define Item_hxx <GEOMAlgo_CoupleOfShapes.hxx>
#define TCollection_ListNode GEOMAlgo_ListNodeOfListOfCoupleOfShapes
#define TCollection_ListNode_hxx <GEOMAlgo_ListNodeOfListOfCoupleOfShapes.hxx>
#define TCollection_ListIterator GEOMAlgo_ListIteratorOfListOfCoupleOfShapes
#define TCollection_ListIterator_hxx <GEOMAlgo_ListIteratorOfListOfCoupleOfShapes.hxx>
#define Handle_TCollection_ListNode Handle_GEOMAlgo_ListNodeOfListOfCoupleOfShapes
#define TCollection_ListNode_Type_() GEOMAlgo_ListNodeOfListOfCoupleOfShapes_Type_()
#define TCollection_List GEOMAlgo_ListOfCoupleOfShapes
#define TCollection_List_hxx <GEOMAlgo_ListOfCoupleOfShapes.hxx>

#include <TCollection_ListNode.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_ListNode
#undef TCollection_ListNode_hxx
#undef TCollection_ListIterator
#undef TCollection_ListIterator_hxx
#undef Handle_TCollection_ListNode
#undef TCollection_ListNode_Type_
#undef TCollection_List
#undef TCollection_List_hxx


// other Inline functions and methods (like "C++: function call" methods)
//


#endif
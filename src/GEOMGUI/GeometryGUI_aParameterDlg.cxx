using namespace std;
//  File      : GeometryGUI_aParameterDlg.cxx
//  Created   : 
//  Author    : Lucien PIGNOLONI
//  Project   : SALOME
//  Module    : GeometryGUI
//  Copyright : Open CASCADE
//  $Header$

#include "GeometryGUI_aParameterDlg.h"
#include "GeometryGUI.h"
#include "QAD_SpinBoxDbl.h"
#include "QAD_Tools.h"

#include <stdio.h>

#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qvalidator.h>

//====================================================================================== 
// function : GeometryGUI_aParameterDlg()
// purpose  : Constructs a GeometryGUI_aParametertDlg which is a child of 'parent', with the 
//            name 'name' and widget flags set to 'f'
//
//  avalue1    : is a float or integer used as default value in edit line
//  aTitle1    : is the prompt for aValue1
//  aTitle     : is the title for the user in dialog box
//
//  bottom     : the minimal value to be entered
//  top        : the maximum value to be entered
//  decimals   : number of decimals to be entered
//
//  The dialog will by default be modeless, unless you set 'modal' to
//  TRUE to construct a modal dialog.
// 
//====================================================================================== 
GeometryGUI_aParameterDlg::GeometryGUI_aParameterDlg( const char *aValue1,
						      const char *aTitle1,
						      QWidget* parent,
						      const char* name,
						      bool modal,
						      WFlags fl,
						      const double bottom,
						      const double top,
						      const int decimals )
  : QDialog( parent, name, modal, WStyle_Customize | WStyle_NormalBorder | WStyle_Title | WStyle_SysMenu )
{
  if ( !name )
    setName( "MyParameterDialog" );
  resize( 288, 81 ); 
  setCaption( name ); /* appears on the title bar */
  setSizeGripEnabled( TRUE );
  
  QGridLayout* topLayout = new QGridLayout( this ); 
  topLayout->setSpacing( 6 );
  topLayout->setMargin( 11 );

  QGroupBox* mainGrp = new QGroupBox( this, "mainGrp" );
  mainGrp->setColumnLayout(0, Qt::Vertical );
  mainGrp->layout()->setSpacing( 0 );
  mainGrp->layout()->setMargin( 0 );
  QGridLayout* mainGrpLayout = new QGridLayout( mainGrp->layout() );
  mainGrpLayout->setAlignment( Qt::AlignTop );
  mainGrpLayout ->setSpacing( 6 );
  mainGrpLayout->setMargin( 11 );
  topLayout->addWidget( mainGrp, 0, 0 );

  /* aTitle1 : text prompt on left of edit line */
  QLabel* TextLabel1 = new QLabel( mainGrp, "TextLabel1" );
  TextLabel1->setText( tr( aTitle1  ) );  
  mainGrpLayout->addWidget( TextLabel1, 0, 0 );

  mySpinBox = new QAD_SpinBoxDbl( mainGrp, "mySpinBox" );
  mySpinBox->setPrecision( 12);
  mySpinBox->setRange( bottom, top );
  (( QDoubleValidator* )(mySpinBox->validator()))->setRange(bottom, top, decimals);
  mySpinBox->setValue(QString(aValue1).toDouble());
  mainGrpLayout->addWidget( mySpinBox, 0, 1 );
  
  QGroupBox* btnGrp = new QGroupBox( this, "btnGrp" );
  btnGrp->setColumnLayout(0, Qt::Vertical );
  btnGrp->layout()->setSpacing( 0 );
  btnGrp->layout()->setMargin( 0 );
  QGridLayout* btnGrpLayout = new QGridLayout( btnGrp->layout() );
  btnGrpLayout->setAlignment( Qt::AlignTop );
  btnGrpLayout->setSpacing( 6 );
  btnGrpLayout->setMargin( 11 );
  topLayout->addWidget( btnGrp, 1, 0 );

  /* Ok button */
  myButtonOk = new QPushButton( btnGrp, "buttonOk" );
  myButtonOk->setText( tr("GEOM_BUT_OK") );
  myButtonOk->setAutoDefault( TRUE );
  myButtonOk->setDefault( TRUE );
  btnGrpLayout->addWidget( myButtonOk, 0, 0 );

  btnGrpLayout->addItem( new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 1 );

  /* Cancel button */
  myButtonCancel = new QPushButton( btnGrp, "buttonCancel" );
  myButtonCancel->setText( tr("GEOM_BUT_CANCEL") );
  myButtonCancel->setAutoDefault( TRUE );
  btnGrpLayout->addWidget( myButtonCancel, 0, 2 );

  /* signals and slots connections */
  connect( myButtonOk,     SIGNAL( clicked() ), this, SLOT( accept() ) );
  connect( myButtonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
 
  /* Retrieve GeomGUI */
  myGeomGUI = GeometryGUI::GetGeometryGUI() ;
  
  /* Move widget on the botton right corner of main widget */
  QAD_Tools::centerWidget(this, parent);
}


//====================================================================================== 
// function : ~GeometryGUI_aParameterDlg() destructor
// purpose  : Destroys the object and frees any allocated resources
//====================================================================================== 
GeometryGUI_aParameterDlg::~GeometryGUI_aParameterDlg()
{    // no need to delete child widgets, Qt does it all for us
}

//====================================================================================== 
// function : GeometryGUI_aParameterDlg::setValue
// purpose  : sets value
//====================================================================================== 
void GeometryGUI_aParameterDlg::setValue( double val )
{
  mySpinBox->setValue( val );
}

//====================================================================================== 
// function : GeometryGUI_aParameterDlg::getValue
// purpose  : gets value
//====================================================================================== 
double GeometryGUI_aParameterDlg::getValue()
{
  return mySpinBox->value();
}

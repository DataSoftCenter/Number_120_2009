//---------------------------------------------------------------------------

#ifndef Form_PeaH
#define Form_PeaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmPea : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox1;
	TRadioButton *RadioButton_RUL_PUN;
	TRadioButton *RadioButton_RUL_MUS;
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TLabel *Label2;
	TBitBtn *BitBtn_RUL_PANUSTAN;
	TLabel *Label3;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TGroupBox *GroupBox6;
	TGroupBox *GroupBox7;
	TDBText *DBText_Kasutaja;
	TDBText *DBText_Nimi;
	TDBText *DBText_Voit;
	TDBText *DBText_Kaot;
	TDBText *DBText_Krediit;
	TLabel *Label4;
	TLabel *Label5;
	TGroupBox *GroupBox8;
	TStatusBar *StatusBar_Pea;
	TGroupBox *GroupBox2;
	TComboBox *ComboBox_RUL_PANUS;
	TLabel *Label_Voit;
	TLabel *Label_Kaotus;
	TLabel *Label8;
	TLabel *Label9;
	TDBText *DBText_Fond;
	TGroupBox *GroupBox9;
	TImage *Image_Punane;
	TImage *Image_Must;
	TImage *Image1;
	TImage *Image2;
	TGroupBox *GroupBox10;
	TRadioButton *RadioButton_NR_1;
	TRadioButton *RadioButton_NR_2;
	TRadioButton *RadioButton_NR_3;
	TRadioButton *RadioButton_NR_4;
	TRadioButton *RadioButton_NR_5;
	TRadioButton *RadioButton_NR_6;
	TGroupBox *GroupBox11;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label10;
	TGroupBox *GroupBox12;
	TBitBtn *BitBtn_NR_PANUSTAN;
	TImage *Image3;
	TLabel *Label_NR_Voit;
	TLabel *Label_NR_Kaotus;
	TImage *Image_1;
	TImage *Image_2;
	TImage *Image_3;
	TImage *Image_4;
	TImage *Image_5;
	TImage *Image_6;
	TLabel *Label11;
	TLabel *Label12;
	void __fastcall BitBtn_RUL_PANUSTANClick(TObject *Sender);
	void __fastcall ComboBox_RUL_PANUSClick(TObject *Sender);
	void __fastcall RadioButton_RUL_PUNClick(TObject *Sender);
	void __fastcall RadioButton_RUL_MUSClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BitBtn_NR_PANUSTANClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmPea(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPea *frmPea;
//---------------------------------------------------------------------------
#endif

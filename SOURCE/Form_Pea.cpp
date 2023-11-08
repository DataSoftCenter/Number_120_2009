//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Form_Pea.h"
#include "DM_Pea.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPea *frmPea;
//---------------------------------------------------------------------------
__fastcall TfrmPea::TfrmPea(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Uuenda(void)
{
DataModule_PEA->ADODataSet_KASUTAJAD->Close();
DataModule_PEA->ADODataSet_KASUTAJAD->Open();

DataModule_PEA->ADODataSet_Fond->Close();
DataModule_PEA->ADODataSet_Fond->Open();

frmPea->StatusBar_Pea->Panels->Items[1]->Text = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsString;
}
//---------------------------------------------------------------------------
bool KREDIIT_FOND_NULLIS(int Krediit, int Fond)
{
   if(Krediit <= 0 || Fond <= 0)
   {
	   return true;
   }
   else{
	   return false;
   }
}
//---------------------------------------------------------------------------
bool KONTROLLI_KREDIITI(int Krediit, int Panus)
{
	if(Krediit < Panus)
    {
		return true;
	}
	else{
		return false;
    }
}
bool KONTROLLI_FONDI(int Panus, int Fond)
{
	if(Panus > Fond)
	{
		return true;
	}
	else{
		return false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPea::BitBtn_RUL_PANUSTANClick(TObject *Sender)
{
//1 = PUNANE //2 = MUST
Uuenda();

int KR, FO, PA, PAx2;

KR = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger;
FO = DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger;
PA = ComboBox_RUL_PANUS->Text.ToInt();
PAx2 = PA * 2;

if(KONTROLLI_KREDIITI(KR, PA) == true) //if(KONTROLLI_FONDI(PAx2, FO) == true)
{
	Application->MessageBox(L"Krediit on panusest väiksem, suurenda krediiti või panusta vähem!", //Application->MessageBox(L"Võidu korral pole fondis piisavalt krediiti!",
	L"Teade!", MB_ICONERROR | MB_OK);
}
else
{
	if(KONTROLLI_FONDI(PAx2, FO) == true)  //if(KONTROLLI_KREDIITI(KR, PA) == true)
	{
		Application->MessageBox(L"Võidu korral pole fondis piisavalt krediiti!",  //Application->MessageBox(L"Krediit on panusest väiksem, suurenda krediiti või panusta vähem!",
		L"Teade!", MB_ICONERROR | MB_OK);
	}
	else
	{
		if(KREDIIT_FOND_NULLIS(KR, FO) == false)
		{
			//Loositakse suvaline arv
			DataModule_PEA->ADODataSet_AnnaNumber->Active = false;
			DataModule_PEA->ADODataSet_AnnaNumber->CommandText = "SELECT TOP 1 NUMBER FROM NUMBER_NUMBRID WHERE NUMBER <= 2 ORDER BY NEWID()";
			DataModule_PEA->ADODataSet_AnnaNumber->Active = true;

			int VARVUS, SUVALINE_ARV, VOIT, VOIDETUD, KAOTUS, KAOTATUD, KREDIIT, PANUS;
			PANUS = ComboBox_RUL_PANUS->Text.ToInt();

			if(RadioButton_RUL_PUN->Checked)
			{
				VARVUS = 1; // Valiti punane
			}
			else
			{
				VARVUS = 2; // Valiti must
			}

			SUVALINE_ARV = DataModule_PEA->ADODataSet_AnnaNumber->FieldByName("NUMBER")->AsInteger;
			//SUVALINE_ARV = 1;
			if(SUVALINE_ARV == 1)
			{
				Image_Punane->Visible = true;
				Image_Must->Visible = false;
			}
			else
			{
				Image_Punane->Visible = false;
				Image_Must->Visible = true;
			}
				if(VARVUS == SUVALINE_ARV)
				{
					//Panus võetakse igal juhul krediidist maha!
					VOIT = PANUS * 2;

					Label_Voit->Caption = AnsiString(VOIT) + AnsiString(" sent(i)");
					Label_Kaotus->Caption = "-";

					VOIDETUD = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("VÕIDETUD")->AsInteger + VOIT;
					KREDIIT =  DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger - PANUS + VOIT;

					DataModule_PEA->ADODataSet_KASUTAJAD->Edit();
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("VÕIDETUD")->AsInteger = VOIDETUD;
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger = KREDIIT;
					DataModule_PEA->ADODataSet_KASUTAJAD->Post();

					DataModule_PEA->ADODataSet_Fond->Edit();
					DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger = DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger + PANUS - VOIT;
					DataModule_PEA->ADODataSet_Fond->Post();
				}
				else
				{
					//Panus võetakse igal juhul krediidist maha!
					KAOTUS = PANUS;

					Label_Kaotus->Caption = AnsiString(KAOTUS) + AnsiString(" sent(i)");
					Label_Voit->Caption = "-";

					KAOTATUD = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KAOTATUD")->AsInteger + KAOTUS;
					KREDIIT =  DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger - PANUS;

					DataModule_PEA->ADODataSet_KASUTAJAD->Edit();
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KAOTATUD")->AsInteger = KAOTATUD;
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger = KREDIIT;
					DataModule_PEA->ADODataSet_KASUTAJAD->Post();

					DataModule_PEA->ADODataSet_Fond->Edit();
					DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger = DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger + KAOTUS;
					DataModule_PEA->ADODataSet_Fond->Post();
				}
		}
		else
		{
		Application->MessageBox(L"Krediit või fond on nullis, edasi mängida ei saa!",
		L"Teade!", MB_ICONERROR | MB_OK);
		}
	}
}
StatusBar_Pea->Panels->Items[1]->Text = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPea::ComboBox_RUL_PANUSClick(TObject *Sender)
{
Uuenda();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPea::RadioButton_RUL_PUNClick(TObject *Sender)
{
Uuenda();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPea::RadioButton_RUL_MUSClick(TObject *Sender)
{
Uuenda();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPea::FormShow(TObject *Sender)
{
Uuenda();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPea::BitBtn_NR_PANUSTANClick(TObject *Sender)
{
Uuenda();

int KR, FO, PA, PAx2;

KR = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger;
FO = DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger;
PA = ComboBox_RUL_PANUS->Text.ToInt();
PAx2 = PA * 4;

if(KONTROLLI_KREDIITI(KR, PA) == true) //if(KONTROLLI_FONDI(PAx2, FO) == true)
{
	Application->MessageBox(L"Krediit on panusest väiksem, suurenda krediiti või panusta vähem!", //Application->MessageBox(L"Võidu korral pole fondis piisavalt krediiti!",
	L"Teade!", MB_ICONERROR | MB_OK);
}
else
{
	if(KONTROLLI_FONDI(PAx2, FO) == true)  //if(KONTROLLI_KREDIITI(KR, PA) == true)
	{
		Application->MessageBox(L"Võidu korral pole fondis piisavalt krediiti!",  //Application->MessageBox(L"Krediit on panusest väiksem, suurenda krediiti või panusta vähem!",
		L"Teade!", MB_ICONERROR | MB_OK);
	}
	else
	{
		if(KREDIIT_FOND_NULLIS(KR, FO) == false)
		{
			//Loositakse suvaline arv
			DataModule_PEA->ADODataSet_AnnaNumber->Active = false;
			DataModule_PEA->ADODataSet_AnnaNumber->CommandText = "SELECT TOP 1 NUMBER FROM NUMBER_NUMBRID ORDER BY NEWID()";
			DataModule_PEA->ADODataSet_AnnaNumber->Active = true;

			int NUMBER, SUVALINE_ARV, VOIT, VOIDETUD, KAOTUS, KAOTATUD, KREDIIT, PANUS;
			PANUS = ComboBox_RUL_PANUS->Text.ToInt();

			if(RadioButton_NR_1->Checked)
			{
				NUMBER = 1;
			}
			if(RadioButton_NR_2->Checked)
			{
				NUMBER = 2;
			}
			if(RadioButton_NR_3->Checked)
			{
				NUMBER = 3;
			}
			if(RadioButton_NR_4->Checked)
			{
				NUMBER = 4;
			}
			if(RadioButton_NR_5->Checked)
			{
				NUMBER = 5;
			}
			if(RadioButton_NR_6->Checked)
			{
				NUMBER = 6;
			}

			SUVALINE_ARV = DataModule_PEA->ADODataSet_AnnaNumber->FieldByName("NUMBER")->AsInteger;
			//SUVALINE_ARV = 1;

			if(SUVALINE_ARV == 1)
			{
				Image_1->Visible = true;
				Image_2->Visible = false;
				Image_3->Visible = false;
				Image_4->Visible = false;
				Image_5->Visible = false;
				Image_6->Visible = false;
			}
			if(SUVALINE_ARV == 2)
			{
				Image_1->Visible = false;
				Image_2->Visible = true;
				Image_3->Visible = false;
				Image_4->Visible = false;
				Image_5->Visible = false;
				Image_6->Visible = false;
			}
			if(SUVALINE_ARV == 3)
			{
				Image_1->Visible = false;
				Image_2->Visible = false;
				Image_3->Visible = true;
				Image_4->Visible = false;
				Image_5->Visible = false;
				Image_6->Visible = false;
			}
			if(SUVALINE_ARV == 4)
			{
				Image_1->Visible = false;
				Image_2->Visible = false;
				Image_3->Visible = false;
				Image_4->Visible = true;
				Image_5->Visible = false;
				Image_6->Visible = false;
			}
			if(SUVALINE_ARV == 5)
			{
				Image_1->Visible = false;
				Image_2->Visible = false;
				Image_3->Visible = false;
				Image_4->Visible = false;
				Image_5->Visible = true;
				Image_6->Visible = false;
			}
			if(SUVALINE_ARV == 6)
			{
				Image_1->Visible = false;
				Image_2->Visible = false;
				Image_3->Visible = false;
				Image_4->Visible = false;
				Image_5->Visible = false;
				Image_6->Visible = true;
			}
				if(NUMBER == SUVALINE_ARV)
				{
					//Panus võetakse igal juhul krediidist maha!
					VOIT = PANUS * 4;

					Label_NR_Voit->Caption = AnsiString(VOIT) + AnsiString(" sent(i)");
					Label_NR_Kaotus->Caption = "-";

					VOIDETUD = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("VÕIDETUD")->AsInteger + VOIT;
					KREDIIT =  DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger - PANUS + VOIT;

					DataModule_PEA->ADODataSet_KASUTAJAD->Edit();
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("VÕIDETUD")->AsInteger = VOIDETUD;
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger = KREDIIT;
					DataModule_PEA->ADODataSet_KASUTAJAD->Post();

					DataModule_PEA->ADODataSet_Fond->Edit();
					DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger = DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger + PANUS - VOIT;
					DataModule_PEA->ADODataSet_Fond->Post();
				}
				else
				{
					//Panus võetakse igal juhul krediidist maha!
					KAOTUS = PANUS;

					Label_NR_Kaotus->Caption = AnsiString(KAOTUS) + AnsiString(" sent(i)");
					Label_NR_Voit->Caption = "-";

					KAOTATUD = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KAOTATUD")->AsInteger + KAOTUS;
					KREDIIT =  DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger - PANUS;

					DataModule_PEA->ADODataSet_KASUTAJAD->Edit();
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KAOTATUD")->AsInteger = KAOTATUD;
					DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsInteger = KREDIIT;
					DataModule_PEA->ADODataSet_KASUTAJAD->Post();

					DataModule_PEA->ADODataSet_Fond->Edit();
					DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger = DataModule_PEA->ADODataSet_Fond->FieldByName("FOND")->AsInteger + KAOTUS;
					DataModule_PEA->ADODataSet_Fond->Post();
				}
		}
		else
		{
		Application->MessageBox(L"Krediit või fond on nullis, edasi mängida ei saa!",
		L"Teade!", MB_ICONERROR | MB_OK);
		}
	}
}
StatusBar_Pea->Panels->Items[1]->Text = DataModule_PEA->ADODataSet_KASUTAJAD->FieldByName("KREDIIT")->AsString;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#ifndef DM_PeaH
#define DM_PeaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TDataModule_PEA : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection_Pea;
	TADODataSet *ADODataSet_KASUTAJAD;
	TDataSource *DataSource_KASUTAJAD;
	TADODataSet *ADODataSet_AnnaNumber;
	TDataSource *DataSource_AnnaNumber;
	TADODataSet *ADODataSet_Fond;
	TDataSource *DataSource_FOND;
	void __fastcall DataModuleCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDataModule_PEA(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataModule_PEA *DataModule_PEA;
//---------------------------------------------------------------------------
#endif

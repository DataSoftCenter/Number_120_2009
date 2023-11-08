object DataModule_PEA: TDataModule_PEA
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Height = 322
  Width = 506
  object ADOConnection_Pea: TADOConnection
    ConnectionString = 
      'DSN=Juurutus;UID=digi;PWD=digi_sgs;APP=Architect;WSID=VIRTUAL7-P' +
      'C;DATABASE=SGS_Juurutus;'
    LoginPrompt = False
    Left = 40
    Top = 160
  end
  object ADODataSet_KASUTAJAD: TADODataSet
    Connection = ADOConnection_Pea
    CursorType = ctStatic
    CommandText = 'SELECT * FROM NUMBER_KASUTAJAD WHERE KASUTAJA = '#39'K4572547'#39
    Parameters = <>
    Left = 176
    Top = 96
  end
  object DataSource_KASUTAJAD: TDataSource
    DataSet = ADODataSet_KASUTAJAD
    Left = 320
    Top = 96
  end
  object ADODataSet_AnnaNumber: TADODataSet
    Connection = ADOConnection_Pea
    CursorType = ctStatic
    CommandText = 
      'SELECT TOP 1 NUMBER FROM NUMBER_NUMBRID'#13#10'WHERE NUMBER <= 2'#13#10'ORDE' +
      'R BY NEWID()'
    Parameters = <>
    Left = 176
    Top = 168
  end
  object DataSource_AnnaNumber: TDataSource
    DataSet = ADODataSet_AnnaNumber
    Left = 320
    Top = 168
  end
  object ADODataSet_Fond: TADODataSet
    Connection = ADOConnection_Pea
    CursorType = ctStatic
    CommandText = 'SELECT * FROM NUMBER_FOND'
    Parameters = <>
    Left = 176
    Top = 232
  end
  object DataSource_FOND: TDataSource
    DataSet = ADODataSet_Fond
    Left = 320
    Top = 232
  end
end

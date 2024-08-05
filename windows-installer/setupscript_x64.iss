[Setup]
  AppId={{EC675BB5-CBDA-4601-8D8F-4FBA242BA836}
  AppName=Asta CMS 
  PrivilegesRequired=lowest
  ArchitecturesInstallIn64BitMode=x64os
  AppVersion=1.0.0
  AppPublisher=Future IK
  AppPublisherURL=https://www.futureik.com
  AppSupportURL=https://www.futureik.com
  AppUpdatesURL=https://www.futureik.com/
  AppendDefaultDirName=no
  DefaultDirName={autopf}\AstaCMSApp
  DefaultGroupName=Future IK
  OutputBaseFilename=Asta_CMS_Setup_x64
  SetupIconFile=..\src\resources\ico.ico
  Compression=lzma
  SolidCompression=yes
  AllowCancelDuringInstall=no
  CloseApplications=force
  SetupLogging=yes
  UninstallLogging=yes
  UsePreviousAppDir=no

[Tasks]
  Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
  Source: "..\builds\x64\release\src\AstaCMSApp.exe"; DestDir: "{app}"; Flags: ignoreversion 64bit; BeforeInstall: TaskKill('AstaCMSApp.exe')
  Source: "..\deploy\x64\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs 64bit;

[Icons]
  Name: "{group}\Asta CMS"; Filename: "{app}\AstaCMSApp.exe"
  Name: "{group}\{cm:UninstallProgram,Asta CMS}"; Filename: "{uninstallexe}"
  Name: "{userdesktop}\Asta CMS"; Filename: "{app}\AstaCMSApp.exe"; Tasks: desktopicon

[Run]
  Filename: "schtasks"; \
      Parameters: "/Create /F /SC MINUTE /MO 15 /TN ""AstaCMS"" /TR ""'{app}\AstaCMSApp.exe' /RU System"; \
      Flags: runhidden runasoriginaluser 
  Filename: "{app}\AstaCMSApp.exe"; Description: "{cm:LaunchProgram,Asta CMS}"; Flags: nowait postinstall
  
[Code]
const
  INTERNET_CONNECTION_MODEM = 1;
  INTERNET_CONNECTION_LAN = 2;
  INTERNET_CONNECTION_PROXY = 4;
  INTERNET_CONNECTION_MODEM_BUSY = 8;

function InternetGetConnectedState(lpdwFlags: LongWord; dwReserved: LongWord): Boolean;
  external 'InternetGetConnectedState@wininet.dll stdcall';

function IsConnectedToInternet(): Boolean;
var
  dwFlags: LongWord;
begin
  Result := InternetGetConnectedState(dwFlags, 0);
end;

procedure HttpPostRequest(const URL, Data: String);
var
  WinHttpReq: Variant;
begin
  try
    WinHttpReq := CreateOleObject('WinHttp.WinHttpRequest.5.1');
    WinHttpReq.Open('POST', URL, False);
    WinHttpReq.SetRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    WinHttpReq.Send(Data);
    if WinHttpReq.Status = 200 then
    begin
      Log('HTTP POST request was successful: ' + WinHttpReq.ResponseText);
      MsgBox('API call was successful.', mbInformation, MB_OK);
    end
    else
    begin
      Log('HTTP POST request failed with status: ' + IntToStr(WinHttpReq.Status));
      MsgBox('API call failed with status: ' + IntToStr(WinHttpReq.Status), mbError, MB_OK);
    end;
  except
    begin
      Log('HTTP POST request failed with error: ' + AddPeriod(GetExceptionMessage));
      MsgBox('API call failed with error: ' + AddPeriod(GetExceptionMessage), mbError, MB_OK);
    end;
  end;
end;

function InitializeUninstall(): Boolean;
var
  URL, PostData: String;

begin
  URL := 'https://astacms.futureIK.ai/v1/uninstall/';
  PostData := 'appid=1x00';

  // Loop until connected to the internet and the request is successful
  while True do
  begin
  Result :=	IsConnectedToInternet()
    if Result then
    begin
      MsgBox('Internet connection is available.', mbInformation, MB_OK);
      Break;
    end
    else
    begin
      MsgBox('Internet connection is not available. Rechecking...', mbError, MB_OK);
    end;

    // Wait for a few seconds before rechecking
    Sleep(1000);
  end;
end;

procedure TaskKill(FileName: String);
var
	ResultCode: Integer;
begin
	Exec(ExpandConstant('{sys}\taskkill.exe'), '/f /im ' + '"' + FileName + '"', ExpandConstant('{sys}'), SW_HIDE, ewWaitUntilTerminated, ResultCode);
end;


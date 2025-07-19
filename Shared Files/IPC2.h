#pragma once

#include < vcclr.h >
#include "ImagerIPC2.h"

using namespace System::Runtime::InteropServices; 

public ref class IPC
{
	public:
		IPC(WORD count)
		{
			SetImagerIPCCount(ImagerCount = count);
		};

		IPC(WORD count, wchar_t *Filename, int LogLevel, bool Append)
		{
			SetLogFile(Filename, LogLevel, Append);
			SetImagerIPCCount(ImagerCount = count);
		};

		IPC(WORD count, int LogLevel)
		{
			ImagerCount = count;
			SetLogging(LogLevel);
			SetImagerIPCCount(ImagerCount);
		};

		delegate HRESULT delOnServerStopped(int);
		delegate HRESULT delOnFrameInit(int, int, int);
		delegate HRESULT delOnNewFrame(char*, int);
		delegate HRESULT delOnNewFrameEx(void*, FrameMetadata*);
		delegate HRESULT delOnInitCompleted(void );
		delegate HRESULT delOnConfigChanged(long);
		delegate HRESULT delOnStringSend(wchar_t*);

		delOnServerStopped^		OnServerStopped;
		delOnFrameInit^			OnFrameIRInit;
		delOnNewFrameEx^		OnNewFrameIREx;
		delOnFrameInit^			OnFrameVisInit;
		delOnNewFrameEx^		OnNewFrameVisEx;
		delOnInitCompleted^		OnInitCompleted;
		delOnConfigChanged^		OnConfigChanged;
		delOnStringSend^		OnFileCommandReady;
		delOnStringSend^		OnNewNMEAString;

		WORD ImagerCount;

#ifdef _WIN64
		literal System::String^ strDLL = "ImagerIPC2x64.dll"; 
#else
		literal System::String^ strDLL = "ImagerIPC2.dll"; 
#endif

		// General functions:
		[ DllImport(strDLL, EntryPoint = "SetImagerIPCCount") ]  			static HRESULT SetImagerIPCCount(WORD count); 
		[ DllImport(strDLL, EntryPoint = "InitImagerIPC") ]  				static HRESULT Init(WORD index); 
		[ DllImport(strDLL, EntryPoint = "InitNamedImagerIPC") ]			static HRESULT Init(WORD index, wchar_t *InstanceName); 
		[ DllImport(strDLL, EntryPoint = "RunImagerIPC") ]  				static HRESULT Run(WORD index); 
		[ DllImport(strDLL, EntryPoint = "ReleaseImagerIPC") ]				static HRESULT Release(WORD index);  
		[ DllImport(strDLL, EntryPoint = "AcknowledgeFrame") ]				static HRESULT AcknowledgeFrame(WORD index);
		[ DllImport(strDLL, EntryPoint = "SetLogFile") ]  					static HRESULT SetLogFile(wchar_t *Filename, int LogLevel, bool Append); 
		[ DllImport(strDLL, EntryPoint = "SetLogging")]  					static HRESULT SetLogging(int LogLevel);
		[ DllImport(strDLL, EntryPoint = "Log")]  							static HRESULT Log(WORD index, char *logstring, int LogLevel);
		[ DllImport(strDLL, EntryPoint = "GetFrameConfig") ]  				static HRESULT GetFrameConfig(WORD index, int *pWidth, int *pHeight, int *pDepth);
		[ DllImport(strDLL, EntryPoint = "GetFrame") ]						static HRESULT GetFrame(WORD index, WORD timeout, void *pBuf, unsigned int BufSize, FrameMetadata *pMetadata);
		[ DllImport(strDLL, EntryPoint = "GetVisibleFrameConfig") ]  		static HRESULT GetVisibleFrameConfig(WORD index, int *pWidth, int *pHeight, int *pDepth);
		[ DllImport(strDLL, EntryPoint = "GetVisibleFrame") ]				static HRESULT GetVisibleFrame(WORD index, WORD timeout, void *pBuf, unsigned int BufSize, FrameMetadata *pMetadata);
		[ DllImport(strDLL, EntryPoint = "GetAvgTimePerFrame") ] 			static ULONG GetAvgTimePerFrame(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVisibleAvgTimePerFrame") ] 	static ULONG GetVisibleAvgTimePerFrame(WORD index);  

		// Callback functions:
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnServerStopped")]	static HRESULT SetCallback_OnServerStopped(WORD index, delOnServerStopped^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnFrameInit")]		static HRESULT SetCallback_OnFrameInit(WORD index, delOnFrameInit^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnNewFrame")] 		static HRESULT SetCallback_OnNewFrame(WORD index, delOnNewFrame^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnNewFrameEx")]		static HRESULT SetCallback_OnNewFrameEx(WORD index, delOnNewFrameEx^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnVisibleFrameInit")]	static HRESULT SetCallback_OnVisibleFrameInit(WORD index, delOnFrameInit^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnNewVisibleFrame")] 	static HRESULT SetCallback_OnNewVisibleFrame(WORD index, delOnNewFrame^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnNewVisibleFrameEx")]static HRESULT SetCallback_OnNewVisibleFrameEx(WORD index, delOnNewFrameEx^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnInitCompleted")]	static HRESULT SetCallback_OnInitCompleted(WORD index, delOnInitCompleted^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnConfigChanged")]	static HRESULT SetCallback_OnConfigChanged(WORD index, delOnConfigChanged^ ptr);  
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnFileCommandReady")] static HRESULT SetCallback_OnFileCommandReady(WORD index, delOnStringSend^ ptr);
		[ DllImport(strDLL, EntryPoint = "SetCallback_OnNewNMEAString")]	static HRESULT SetCallback_OnNewNMEAString(WORD index, delOnStringSend^ ptr);

		// Get & Set Functions
		[ DllImport(strDLL, EntryPoint = "GetVersionApplication") ] 	static long long GetVersionApplication(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVersionHID_DLL") ] 		static long long GetVersionHID_DLL(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVersionCD_DLL") ] 			static long long GetVersionCD_DLL(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVersionIPC_DLL") ]			static long long GetVersionIPC_DLL(WORD index);  

		[ DllImport(strDLL, EntryPoint = "GetFixedEmissivity") ] 		static float GetFixedEmissivity(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetFixedEmissivity") ] 		static float SetFixedEmissivity(WORD index, float Value);  
		[ DllImport(strDLL, EntryPoint = "GetFixedTransmissivity") ] 	static float GetFixedTransmissivity(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetFixedTransmissivity") ] 	static float SetFixedTransmissivity(WORD index, float Value);  
		[ DllImport(strDLL, EntryPoint = "GetFixedTempAmbient") ] 		static float GetFixedTempAmbient(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetFixedTempAmbient") ] 		static float SetFixedTempAmbient(WORD index, float Value);  
		[ DllImport(strDLL, EntryPoint = "SetPifOut") ] 				static float SetPifOut(WORD index, WORD channel, float Value);
		[ DllImport(strDLL, EntryPoint = "FailSafe") ] 					static bool FailSafe(WORD index, bool Value);  

		[ DllImport(strDLL, EntryPoint = "GetTempTec") ] 				static float GetTempTec(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetTempTec") ] 				static float SetTempTec(WORD index, float Value);  
		[ DllImport(strDLL, EntryPoint = "GetFlag") ] 					static bool GetFlag(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetFlag") ] 					static bool SetFlag(WORD index, bool Value);  
		[ DllImport(strDLL, EntryPoint = "GetOpticsIndex") ]			static USHORT GetOpticsIndex(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetOpticsIndex") ]			static USHORT SetOpticsIndex(WORD index, USHORT Value);  
		[ DllImport(strDLL, EntryPoint = "GetTempRangeIndex") ]			static USHORT GetTempRangeIndex(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetTempRangeIndex") ]			static USHORT SetTempRangeIndex(WORD index, USHORT Value);  
		[ DllImport(strDLL, EntryPoint = "GetVideoFormatIndex") ]		static USHORT GetVideoFormatIndex(WORD index);
		[ DllImport(strDLL, EntryPoint = "SetVideoFormatIndex") ]		static USHORT SetVideoFormatIndex(WORD index, USHORT Value);
		[ DllImport(strDLL, EntryPoint = "GetClippedFormatMaxPos")]		static HRESULT GetClippedFormatMaxPos(WORD index, PPOINT Pos);
		[ DllImport(strDLL, EntryPoint = "GetClippedFormatPos")]		static HRESULT GetClippedFormatPos(WORD index, PPOINT Pos);
		[ DllImport(strDLL, EntryPoint = "SetClippedFormatPos")]		static HRESULT SetClippedFormatPos(WORD index, POINT Pos);
		[ DllImport(strDLL, EntryPoint = "GetMainWindowEmbedded")] 		static bool   GetMainWindowEmbedded(WORD index);
		[ DllImport(strDLL, EntryPoint = "SetMainWindowEmbedded") ] 	static bool   SetMainWindowEmbedded(WORD index, bool Value);  
		[ DllImport(strDLL, EntryPoint = "GetMainWindowLocX") ]			static USHORT GetMainWindowLocX(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetMainWindowLocX") ]			static USHORT SetMainWindowLocX(WORD index, USHORT Value);  
		[ DllImport(strDLL, EntryPoint = "GetMainWindowLocY") ]			static USHORT GetMainWindowLocY(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetMainWindowLocY") ]			static USHORT SetMainWindowLocY(WORD index, USHORT Value);  
		[ DllImport(strDLL, EntryPoint = "GetMainWindowWidth") ]		static USHORT GetMainWindowWidth(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetMainWindowWidth") ]		static USHORT SetMainWindowWidth(WORD index, USHORT Value);  
		[ DllImport(strDLL, EntryPoint = "GetMainWindowHeight") ]		static USHORT GetMainWindowHeight(WORD index);  
		[ DllImport(strDLL, EntryPoint = "SetMainWindowHeight") ]		static USHORT SetMainWindowHeight(WORD index, USHORT Value);  
		System::Drawing::Rectangle GetMainWindowRect(WORD index)
		{
			return System::Drawing::Rectangle(
				GetMainWindowLocX(index), 
				GetMainWindowLocY(index), 
				GetMainWindowWidth(index),	
				GetMainWindowHeight(index));
		}
		System::Drawing::Rectangle SetMainWindowRect(WORD index, System::Drawing::Rectangle rect)
		{
			return System::Drawing::Rectangle(
				SetMainWindowLocX(index, rect.X), 
				SetMainWindowLocY(index, rect.Y), 
				SetMainWindowWidth(index, rect.Width), 
				SetMainWindowHeight(index, rect.Height));
		}
		System::Drawing::Rectangle SetMainWindowRect(WORD index, System::Drawing::Rectangle ^rect)
		{
			return System::Drawing::Rectangle(
				SetMainWindowLocX(index, rect->X), 
				SetMainWindowLocY(index, rect->Y), 
				SetMainWindowWidth(index, rect->Width), 
				SetMainWindowHeight(index, rect->Height));
		}


		[ DllImport(strDLL, EntryPoint = "GetHardware_Model") ]			static UCHAR GetHardware_Model(WORD index);    // deprecated
		[ DllImport(strDLL, EntryPoint = "GetHardware_Spec") ]			static UCHAR GetHardware_Spec(WORD index);  // deprecated  
		[ DllImport(strDLL, EntryPoint = "GetSerialNumber") ] 			static ULONG GetSerialNumber(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetSerialNumberULIS")]		static ULONG GetSerialNumberULIS(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetPIFSerialNumber") ]		static ULONG GetPIFSerialNumber(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetPIFVersion") ]				static USHORT GetPIFVersion(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetFirmware_MSP") ] 			static USHORT GetFirmware_MSP(WORD index);  // deprecated
		[ DllImport(strDLL, EntryPoint = "GetFirmware_Cypress")]		static USHORT GetFirmware_Cypress(WORD index);  // deprecated
		[ DllImport(strDLL, EntryPoint = "GetHardwareRev")]				static USHORT GetHardwareRev(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetFirmwareRev")]				static USHORT GetFirmwareRev(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetPID") ]					static USHORT GetPID(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVID") ]					static USHORT GetVID(WORD index);  

		[ DllImport(strDLL, EntryPoint = "GetTempChip") ] 				static float GetTempChip(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetTempFlag") ] 				static float GetTempFlag(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetTempProc") ] 				static float GetTempProc(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetTempBox") ] 				static float GetTempBox(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetTempHousing") ] 			static float GetTempHousing(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetTempTarget") ] 			static float GetTempTarget(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetHumidity")] 				static float GetHumidity(WORD index);
		[ DllImport(strDLL, EntryPoint = "GetTempMinRange") ] 			static float GetTempMinRange(WORD index, ULONG Index);  
		[ DllImport(strDLL, EntryPoint = "GetTempMaxRange") ] 			static float GetTempMaxRange(WORD index, ULONG Index);  
		[ DllImport(strDLL, EntryPoint = "GetTempRangeDecimal") ]		static USHORT GetTempRangeDecimal(WORD index, bool EffectiveValue);  
		[ DllImport(strDLL, EntryPoint = "GetTempRangeCount") ]			static USHORT GetTempRangeCount(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetOpticsFOV") ] 				static USHORT GetOpticsFOV(WORD index, ULONG Index);  
		[ DllImport(strDLL, EntryPoint = "GetOpticsSerialNumber")] 		static ULONG GetOpticsSerialNumber(WORD index, ULONG Index);
		[ DllImport(strDLL, EntryPoint = "GetOpticsCount")]				static USHORT GetOpticsCount(WORD index);
		[ DllImport(strDLL, EntryPoint = "GetMeasureAreaCount")]		static USHORT GetMeasureAreaCount(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVideoFormatCount")]		static USHORT GetVideoFormatCount(WORD index);
		[ DllImport(strDLL, EntryPoint = "GetTempMeasureArea") ]		static float GetTempMeasureArea(WORD index, ULONG Index);  
		[ DllImport(strDLL, EntryPoint = "GetLocMeasureArea") ]			static HRESULT GetLocMeasureArea(WORD index, ULONG Index, PPOINT Loc);  
		[ DllImport(strDLL, EntryPoint = "SetLocMeasureArea") ]			static HRESULT SetLocMeasureArea(WORD index, ULONG Index, POINT Loc);  
		[ DllImport(strDLL, EntryPoint = "GetInitCounter") ]			static USHORT GetInitCounter(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetIPCState") ]				static USHORT GetIPCState(WORD index, bool reset);  
		[ DllImport(strDLL, EntryPoint = "GetIPCMode") ]				static USHORT GetIPCMode(WORD index);
		[ DllImport(strDLL, EntryPoint = "SetIPCMode") ]				static USHORT SetIPCMode(WORD index, USHORT Value);
		[ DllImport(strDLL, EntryPoint = "GetFrameQueue") ]				static USHORT GetFrameQueue(WORD index);  
		[ DllImport(strDLL, EntryPoint = "GetVisibleFrameQueue") ]		static USHORT GetVisibleFrameQueue(WORD index); 
		[ DllImport(strDLL, EntryPoint = "GetVideoFormat") ]			static HRESULT GetVideoFormat(WORD index, ULONG IndexFormat, VideoFormat *videoFormat);
		[ DllImport(strDLL, EntryPoint = "GetIRArranging") ]			static HRESULT GetIRArranging(WORD index, IRArranging *irArranging);
		[ DllImport(strDLL, EntryPoint = "SetIRArranging") ]			static HRESULT SetIRArranging(WORD index, IRArranging *irArranging);
		[ DllImport(strDLL, EntryPoint = "GetPathOfStoredFile") ]		static HRESULT GetPathOfStoredFile(WORD index, wchar_t *path, int maxlen);
		[ DllImport(strDLL, EntryPoint = "GetNewNMEAString")]			static HRESULT GetNewNMEAString(WORD index, wchar_t *NMEAString, int maxlen);
		[ DllImport(strDLL, EntryPoint = "GetMeasureArea") ]			static HRESULT GetMeasureArea(WORD index, ULONG Index, MeasureArea *measureArea);
		[ DllImport(strDLL, EntryPoint = "SetMeasureArea")]				static HRESULT SetMeasureArea(WORD index, ULONG Index, MeasureArea *measureArea, bool addNew);
		[ DllImport(strDLL, EntryPoint = "AddMeasureAreaPoint")]		static HRESULT AddMeasureAreaPoint(WORD index, ULONG Index, POINT point);
		[ DllImport(strDLL, EntryPoint = "RemoveMeasureArea")]			static HRESULT RemoveMeasureArea(WORD index, ULONG Index);
		[ DllImport(strDLL, EntryPoint = "SetMeasureAreaName")]			static HRESULT SetMeasureAreaName(WORD index, ULONG Index, wchar_t *name);
		[ DllImport(strDLL, EntryPoint = "GetMeasureAreaName")]			static HRESULT GetMeasureAreaName(WORD index, ULONG Index, wchar_t *name, int* len, int maxLen);
		// Control commands:
		[ DllImport(strDLL, EntryPoint = "CloseApplication") ]			static void CloseApplication(WORD index);  
		[ DllImport(strDLL, EntryPoint = "ReinitDevice") ]				static void ReinitDevice(WORD index);  
		[ DllImport(strDLL, EntryPoint = "RenewFlag") ]					static bool RenewFlag(WORD index);  
		[ DllImport(strDLL, EntryPoint = "FileSnapshot") ]				static bool FileSnapshot(WORD index);  
		[ DllImport(strDLL, EntryPoint = "FileScreenshot")]				static void FileScreenShot(WORD index);
		[ DllImport(strDLL, EntryPoint = "FileRecord") ]				static bool FileRecord(WORD index);  
		[ DllImport(strDLL, EntryPoint = "FileStop") ]					static bool FileStop(WORD index);  
		[ DllImport(strDLL, EntryPoint = "FilePlay") ]					static bool FilePlay(WORD index);  
		[ DllImport(strDLL, EntryPoint = "FilePause") ]					static bool FilePause(WORD index);  
		[ DllImport(strDLL, EntryPoint = "FileOpen") ]					static USHORT FileOpen(WORD index, wchar_t *Filename);  
		[ DllImport(strDLL, EntryPoint = "LoadLayout") ]				static USHORT LoadLayout(WORD index, wchar_t *Filename);  
        [ DllImport(strDLL, EntryPoint = "LoadCurrentLayout")]			static void LoadCurrentLayout(WORD index);
        [ DllImport(strDLL, EntryPoint = "SaveCurrentLayout")]			static void SaveCurrentLayout(WORD index);
        [ DllImport(strDLL, EntryPoint = "SetStandardLayout")]			static void SetStandardLayout(WORD index);
        [ DllImport(strDLL, EntryPoint = "MasterInstanceName")]		    static USHORT MasterInstanceName(WORD index, wchar_t *Filename);

		static HRESULT Init(WORD index, System::String^ InstanceName) 
		{ 
			wchar_t szInstanceName[MAX_PATH];
			pin_ptr<const wchar_t> ch = PtrToStringChars(InstanceName); 
			wcscpy_s(szInstanceName, MAX_PATH, ch); 
			return Init(index, szInstanceName);
		};

};

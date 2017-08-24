#pragma once
#include "Utils.h"
#include <map>

class VoipConfig
{
public:
	VoipConfig();
	virtual ~VoipConfig();

public:

	static VoipConfig* instance();
	//	static void uninstance();

	void Initialize();
	//	void UnInitialize();

	void AddPhone(CStdString phone, CStdString port, CStdString tenantId);
	void DeletePhone(CStdString phone);

public:
	CStdString m_audioOutputPath;
	CStdString m_deviceName;
	CStdString m_nicip;
	CStdString m_recordip;
	int m_recordport;
	int m_machineno;
	//	CStdString m_recordtype;
	std::list<CStdString> m_maclist;
	std::map<CStdString, CStdString> m_chanStation;
	std::map<CStdString, CStdString> m_PortStation;
	CStdString m_sPcapFilter;
	CStdString m_sSessionTimeOut;

	CStdString m_ctiPort;
	int m_rtpNum;
	CStdString ctiCtrl;
	//	CStdString rtpCtrl;
	int nCtiDelay;

	CStdString gwip_;
	CStdString ciscoip_;

	unsigned short gwport_;

	CStdString recordtime_;


	FileFormatEnum m_storageAudioFormat;
	bool m_stereoRecording;
	int m_tapeNumChannels;
	int m_audioFilePermissions;
	//	int m_captureFileBatchSizeKByte;  //not used
	//	int m_captureFileSizeLimitKb; //not used
	//	int m_immediateProcessingQueueSize;
	int m_tapeDurationMinimumSec;
	int m_batchProcessingQueueSize;
	//	bool m_batchProcessingEnhancePriority;
	//	int m_transcodingSleepEveryNumFrames;
	//	int m_transcodingSleepUs;
	bool m_deleteNativeFile;
	bool m_deleteFailedCaptureFile;
	int 	m_audioGainDb;
	int m_audioGainChannel1Db;
	int m_audioGainChannel2Db;
	bool m_sipTreat200OkAsInvite;
	bool m_sipRequestUriAsLocalParty;
	bool m_sipReportFullAddress;
	bool m_sipDropIndirectInvite;
	std::list<CStdString> m_sipExtractFields;
	bool m_rtpReportDtmf;
	bool m_dahdiIntercept;
	bool m_sipUse200OkMediaAddress;

	IpRanges m_sipIgnoredMediaAddresses;
	bool m_sipInviteCanPutOffHold;
	bool m_sipAllowMultipleMediaAddresses;
	bool m_sipDynamicMediaAddress;
	bool m_sipIgnoreBye;

	//分机信息列表
	//std::map<CStdString, CPhoneGroupRef> m_phoneGroupMap;
	ACE_Thread_Mutex m_mutex;

	//	FILE* f1;
	//	FILE* f2;
	//	FILE* f3;
	//	FILE* f4;
	//	CG729ToPcm g729;

private:
	static VoipConfig m_voipConfig;
};

#define CONFIG (*VoipConfig::instance())


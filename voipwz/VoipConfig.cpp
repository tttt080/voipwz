#include "VoipConfig.h"
#include "LogManager.h"

#define LOOKBACK_RECORDING_DEFAULT true
#define STORAGE_AUDIO_FORMAT_DEFAULT FfGsm
#define TAPE_NUM_CHANNELS_DEFAULT 2


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
VoipConfig VoipConfig::m_voipConfig;
VoipConfig::VoipConfig()
{

	//Á¢ÌåÉù
	m_stereoRecording = false;
	m_storageAudioFormat = STORAGE_AUDIO_FORMAT_DEFAULT;
	m_audioFilePermissions = 0;
	//   m_captureFileSizeLimitKb = 300000;
	//   m_immediateProcessingQueueSize = 500000;
	//   m_batchProcessingQueueSize = 500000;
	m_tapeDurationMinimumSec = 0;
	//   m_batchProcessingEnhancePriority = false;
	//   m_transcodingSleepEveryNumFrames = 0;
	//   m_transcodingSleepUs = 0;
	m_deleteNativeFile = true;
	m_deleteFailedCaptureFile = true;

	m_audioGainDb = 0;
	m_audioGainChannel1Db = 0;
	m_audioGainChannel2Db = 0;
	m_maclist.push_back("000c29d6ebcb");
	m_sipRequestUriAsLocalParty = true;
	m_sipReportFullAddress = true;
	m_sipDropIndirectInvite = true;
	m_rtpReportDtmf = true;
	m_dahdiIntercept = true;
	m_sipUse200OkMediaAddress = true;
	m_sipInviteCanPutOffHold = true;
	m_sipAllowMultipleMediaAddresses = true;
	m_sipDynamicMediaAddress = true;
	m_sipIgnoreBye = false;

}
//--------------------------------------------
//
//===========================================
VoipConfig::~VoipConfig()
{

}

VoipConfig* VoipConfig::instance() {
	return &m_voipConfig;
}
//
void VoipConfig::Initialize() {

	CMarkup xml;
	bool bload = xml.Load("easydialrecord.xml");
	if (bload)
	{

		xml.FindElem("/easydialrecord/config/nic");
		m_nicip = xml.GetData();

		LOG4CXX_INFO(LOG.rootLog, "nic=" + m_nicip);

		xml.FindElem("/easydialrecord/config/lchanaudiogain");
		CStdString lag = xml.GetData();
		m_audioGainChannel1Db = StringToInt(lag);
		//d
		LOG4CXX_INFO(LOG.rootLog, "lchanaudiogain=" + lag);

		xml.FindElem("/easydialrecord/config/rchanaudiogain");
		CStdString rag = xml.GetData();
		m_audioGainChannel2Db = StringToInt(rag);

		LOG4CXX_INFO(LOG.rootLog, "rchanaudiogain=" + rag);

		m_audioGainDb = (m_audioGainChannel1Db + m_audioGainChannel2Db) / 2;

		xml.FindElem("/easydialrecord/config/monitorip");
		m_recordip = xml.GetData();

		LOG4CXX_INFO(LOG.rootLog, "monitorip=" + m_recordip);

		xml.FindElem("/easydialrecord/config/monitorport");
		CStdString port = xml.GetData();
		m_recordport = StringToInt(port);

		LOG4CXX_INFO(LOG.rootLog, "monitorport=" + port);

		xml.FindElem("/easydialrecord/config/outpath");
		m_audioOutputPath = xml.GetData();

		LOG4CXX_INFO(LOG.rootLog, "outpath=" + m_audioOutputPath);

		xml.FindElem("/easydialrecord/config/pacpFilter");
		m_sPcapFilter = xml.GetData();
		if (m_sPcapFilter == "")
			m_sPcapFilter = "udp";

		LOG4CXX_INFO(LOG.rootLog, "pacpFilter=" + m_sPcapFilter);

		xml.FindElem("/easydialrecord/config/SessionTimeOut");
		m_sSessionTimeOut = xml.GetData();
		if (m_sSessionTimeOut == "")
			m_sSessionTimeOut = "3";
		LOG4CXX_INFO(LOG.rootLog, "SessionTimeOut=" + m_sSessionTimeOut);

		xml.FindElem("/easydialrecord/config/startRecordRtp");
		CStdString rtp = xml.GetData();
		m_rtpNum = StringToInt(rtp);

		LOG4CXX_INFO(LOG.rootLog, "startRecordRtp=" + rtp);

		xml.FindElem("/easydialrecord/config/gwip");
		gwip_ = xml.GetData();

		LOG4CXX_INFO(LOG.rootLog, "gwip=" + gwip_);

		xml.FindElem("/easydialrecord/config/ciscoip");
		ciscoip_ = xml.GetData();
		LOG4CXX_INFO(LOG.rootLog, "ciscoip=" + ciscoip_);

		xml.FindElem("/easydialrecord/config/gwport");
		CStdString sgwport = xml.GetData();
		gwport_ = StringToInt(sgwport);

		LOG4CXX_INFO(LOG.rootLog, "gwport=" + sgwport);

		xml.FindElem("/easydialrecord/config/recordtime");
		recordtime_ = xml.GetData();

		LOG4CXX_INFO(LOG.rootLog, "recordtime=" + recordtime_);

	}

}

void VoipConfig::AddPhone(CStdString phone, CStdString port, CStdString tenantId)
{
	CMarkup xml;
	bool bload = xml.Load("easydialrecord.xml");
	if (bload)
	{
		bool bFind = xml.FindElem("/easydialrecord/dmcc/phonegroup");
		if (bFind)
		{
			xml.IntoElem();
			xml.AddElem("phone", "");

			xml.AddAttrib("phoneno", phone);
			xml.AddAttrib("port", port);
			xml.AddAttrib("tenantId", tenantId);
		}
		xml.Save("easydialrecord.xml");
		xml.ResetMainPos();
	}

}

void VoipConfig::DeletePhone(CStdString phone)
{
	CMarkup xml;
	bool bload = xml.Load("easydialrecord.xml");
	if (bload)
	{
		bool bFind = xml.FindElem("/easydialrecord/dmcc/phonegroup");
		if (bFind)
		{
			xml.IntoElem();
			while (xml.FindElem("phone"))
			{
				CStdString phoneno = xml.GetAttrib("phoneno");
				if (phoneno.CompareNoCase(phone) == 0)
				{
					xml.RemoveElem();
					xml.Save("easydialrecord.xml");
				}
			}
		}
	}
}

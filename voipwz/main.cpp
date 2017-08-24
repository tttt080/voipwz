#include "OrkBase.h"
#include "CapturePluginProxy.h"
#include "ImmediateProcessing.h"
#include "BatchProcessing.h"
#include "ace\Thread_Manager.h"
#include "Daemon.h"

void mainthread()
{

	//log
	OrkLogManager::Instance()->Initialize();

	//socket
	int WSA_VERSION = 2;
	WSADATA		WSAData = { 0 };
	if (0 != WSAStartup(WSA_VERSION, &WSAData))
	{
		// Tell the user that we could not find a usable
		// WinSock DLL.
		if (LOBYTE(WSAData.wVersion) != LOBYTE(WSA_VERSION) ||
			HIBYTE(WSAData.wVersion) != HIBYTE(WSA_VERSION))
			::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);

		WSACleanup();
		return;
	}
	//thread 
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	int nCounts = SystemInfo.dwNumberOfProcessors * 2 + 2;

	if (!ACE_Thread_Manager::instance()->spawn_n(nCounts / 2, ACE_THR_FUNC(ImmediateProcessing::ThreadHandler)))
	{
		LOG4CXX_INFO(LOG.rootLog, CStdString("Failed to create immediate processing thread"));
	}
	if (!ACE_Thread_Manager::instance()->spawn_n(nCounts, ACE_THR_FUNC(BatchProcessing::ThreadHandler)))
	{
		LOG4CXX_INFO(LOG.rootLog, CStdString("Failed to create batch processing thread"));
	}

	//VoIpSession
	//处理语音流，抓取RTP包
//	VoIpSingleton::instance()->Initialize();
//	VoIpSingleton::instance()->Run();
	//VoIpSingleton

	//rope
	while (!Daemon::Singleton()->IsStopping())
	{
		ACE_OS::sleep(1);
	}

	LOG4CXX_INFO(LOG.rootLog, "application stop");
}

//定义成int main()就不行
int main(int argc, char** argv)
{
	/*
	CapturePluginProxy::Initialize();
	CapturePluginProxy* t = CapturePluginProxy::Singleton();
	CStdString str;
	AudioChunkRef chunkRef(new AudioChunk());
	t->AudioChunkCallBack(chunkRef,str);
	*/
	//
	printf("dddddddddddddddddddd");
	getchar();

	return 0;
}
#pragma once

#include <obs-module.h>
//#include <util/curl/curl-helper.h>
#include <util/platform.h>
#include <util/base.h>
#include <util/dstr.h>

#include <string>
#include <atomic>
#include <mutex>
#include <thread>

//#include <rtc/rtc.hpp>

#ifdef _WIN32
#ifdef _MSC_VER
#pragma warning(disable:4996) //depricated warnings
#pragma warning(disable:4244) //64bit defensive mechanism, fixed the ones that mattered
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#define SOCKET int
#endif

class VISHAREOutput {
public:
	VISHAREOutput(obs_data_t *settings, obs_output_t *output);
	~VISHAREOutput();

	bool Start();
	void Stop(bool signal = true);
	void Data(struct encoder_packet *packet);

	inline size_t GetTotalBytes() { return total_bytes_sent; }

	inline int GetConnectTime() { return connect_time_ms; }

private:
	void ConfigureAudioTrack(std::string media_stream_id,
				 std::string cname);
	void ConfigureVideoTrack(std::string media_stream_id,
				 std::string cname);
	bool Init();
	bool Setup();
	bool Connect();
	void StartThread();
	void SendDelete();
	void StopThread(bool signal);

#if 1
	void Send(void *data, uintptr_t size, uint64_t duration);
	void SendPacket(uint8_t *buf, size_t size);

#else
	void ParseLinkHeader(std::string linkHeader,
			     std::vector<rtc::IceServer> &iceServers);

	void Send(void *data, uintptr_t size, uint64_t duration,
		  std::shared_ptr<rtc::Track> track,
		  std::shared_ptr<rtc::RtcpSrReporter> rtcp_sr_reporter);
#endif

	obs_output_t *output;

	std::string endpoint_url;
	std::string bearer_token;
	std::string resource_url;

	std::atomic<bool> running;

	std::mutex start_stop_mutex;
	std::thread start_stop_thread;

	uint32_t base_ssrc;
	//std::shared_ptr<rtc::PeerConnection> peer_connection;
	//std::shared_ptr<rtc::Track> audio_track;
	//std::shared_ptr<rtc::Track> video_track;
	//std::shared_ptr<rtc::RtcpSrReporter> audio_sr_reporter;
	//std::shared_ptr<rtc::RtcpSrReporter> video_sr_reporter;

	std::atomic<size_t> total_bytes_sent;
	std::atomic<int> connect_time_ms;
	int64_t start_time_ns;
	int64_t last_audio_timestamp;
	int64_t last_video_timestamp;

	SOCKET sendSocket;
	sockaddr_in serverAddr;

	static constexpr unsigned short SEND_PORT_NUM = 50000;
};

void register_vishare_output();

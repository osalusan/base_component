#pragma once
#include "main.h"
#include <thread>
#include <atomic>
#include <unordered_map>
#include <string>
#include "player.h"


class UDP_Server {
private:
    // �T�[�o�[���[�v
    void ServerLoop();

    SOCKET serverSocket;           // �T�[�o�[�\�P�b�g
    struct sockaddr_in serverAddr; // �T�[�o�[�̃A�h���X���
    std::atomic<bool> running;     // �T�[�o�[�̎��s���
    std::thread serverThread;      // �T�[�o�[�X���b�h
    std::unordered_map<std::string, sockaddr_in> clients; // �N���C�A���g���̊Ǘ�

    OtherPlayerData _AllPlayerData[9] = {};
public:
	UDP_Server();
	~UDP_Server();
	void Start();
	void Stop();
    //�o�C�g�X�g���[���Ƃ��đ��M
    void SendInt_Check(const sockaddr_in& client, int value);
    void SendFloat(const sockaddr_in& client, float value);
    void SendXMFLOAT3(const sockaddr_in& client, const XMFLOAT3& value);
    void SendOtherPlayerData(const sockaddr_in& client, const OtherPlayerData &value);

    void ReturnOtherPlayers(sockaddr_in addsocket,int number);
    void ReturnHost(sockaddr_in addsocket);

    //���̃v���C���[�̓��ꕨ�����
    void ReflectOtherPlayer();
};
#include "udp_server.h"
#include <iostream>
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "otherplayer.h"

#define BUFLEN 1024 
#define PORT (8888)

UDP_Server::UDP_Server() : running(false) {
    // Winsock�̏�����
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Winsock�̏������Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // �\�P�b�g�̍쐬
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        std::cerr << "�\�P�b�g�쐬�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // �T�[�o�[�̃A�h���X�t�@�~���AIP�A�h���X�A�|�[�g�ԍ���ݒ�
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // �\�P�b�g���o�C���h
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "�o�C���h�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }
    Start();
}

UDP_Server::~UDP_Server() {
    Stop(); // �T�[�o�[��~
    closesocket(serverSocket); // �\�P�b�g�����
    WSACleanup(); // Winsock�̃N���[���A�b�v
}

void UDP_Server::Start() {
    if (running) {
        std::cerr << "�T�[�o�[�͂��łɎ��s���ł��B" << std::endl;
        return;
    }
    running = true;
    serverThread = std::thread(&UDP_Server::ServerLoop, this); // �X���b�h���J�n
}

void UDP_Server::Stop() {
    if (!running) {
        std::cerr << "�T�[�o�[�͎��s���ł͂���܂���B" << std::endl;
        return;
    }
    running = false;
    if (serverThread.joinable()) {
        serverThread.join(); // �X���b�h���I��
    }
}

void UDP_Server::SendInt_Check(const sockaddr_in& client, int value)
{
    char buf[sizeof(int)];
    std::memcpy(buf, &value, sizeof(int));

    if (sendto(serverSocket, buf, sizeof(int), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "�ԐM�̑��M�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::SendFloat(const sockaddr_in& client, float value)
{
    char buf[sizeof(float)];
    std::memcpy(buf, &value, sizeof(float));

    if (sendto(serverSocket, buf, sizeof(float), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "�ԐM�̑��M�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::SendXMFLOAT3(const sockaddr_in& client, const XMFLOAT3& value)
{
    char buf[sizeof(XMFLOAT3)];
    std::memcpy(buf, &value, sizeof(XMFLOAT3));

    if (sendto(serverSocket, buf, sizeof(XMFLOAT3), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "�ԐM�̑��M�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::SendOtherPlayerData(const sockaddr_in& client, const OtherPlayerData &value)
{
    char buf[sizeof(OtherPlayerData)];
    std::memcpy(buf, &value, sizeof(OtherPlayerData));

    if (sendto(serverSocket, buf, sizeof(OtherPlayerData), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "�ԐM�̑��M�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::ReturnOtherPlayers(sockaddr_in addsocket,int number)
{
  
    for (int i = 0; i < 8; i++)
    {
        if (Manager::GetClientPlayer() >= i)
        {
            //�N���C�A���g���猩�āA���g�ȊO�̏����擾
            if (number != i)
                SendOtherPlayerData(addsocket, _AllPlayerData[i]);

        }
    }
}

void UDP_Server::ReturnHost(sockaddr_in addsocket)
{
    //�z�X�g�̍��W�𑗐M
    SendXMFLOAT3(addsocket,Manager::GetScene()->GetGameObject<Player>()->_TransForm->_Position);
}

void UDP_Server::ReflectOtherPlayer()
{
    for (auto otherplayer : Manager::GetScene()->GetGameObjects<OtherPlayer>())
    {
         otherplayer->_TransForm->_Position = _AllPlayerData[otherplayer->playerID].pos;
    }
}

void UDP_Server::ServerLoop() {

    char buf[BUFLEN];
    int slen = sizeof(sockaddr_in);
    sockaddr_in clientAddr;

    //UDP�T�[�o�[���N��

    u_long blockmode = 1; //��u���b�L���O���[�h
    ioctlsocket(serverSocket, FIONBIO, &blockmode);

    while (running) {
        // �N���C�A���g����̃��b�Z�[�W����M
        int recvLen = recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr*)&clientAddr, &slen);
        if (recvLen == SOCKET_ERROR) {
            std::cerr << "��M�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
            continue;
        }

        buf[recvLen] = '\0'; // ��M�f�[�^�̏I�[��ݒ�
        std::string clientKey = inet_ntoa(clientAddr.sin_addr) + std::to_string(ntohs(clientAddr.sin_port));

        // �V�����N���C�A���g��ǉ�
        if (clients.find(clientKey) == clients.end()) {
            clients[clientKey] = clientAddr;
            std::cout << "�V�����N���C�A���g���ڑ�����܂���: " << clientKey;
            int count = Manager::GetClientPlayer() + 1;
            SendInt_Check(clientAddr, count);
            Manager::AddOtherPlayer(count);
        }
        
        if(recvLen == sizeof(OtherPlayerData))
        {
            //�z�X�g�̏��͌Œ�
            _AllPlayerData[0].playerID = 0;
            _AllPlayerData[0].pos = Manager::GetScene()->GetGameObject<Player>()->_TransForm->_Position;

            OtherPlayerData value;
            std::memcpy(&value, buf, sizeof(OtherPlayerData));
            _AllPlayerData[value.playerID] = value;
            ReturnOtherPlayers(clientAddr, value.playerID);
            ReflectOtherPlayer();
        }
        if (recvLen == sizeof(bool)) {
            bool value;
            std::memcpy(&value, buf, sizeof(bool));
            //��͎c�邩������������Ȃ��Ƃ����Ȃ�
            Manager::Disconnect();
        }
    }
}


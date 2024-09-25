#include "udp_client.h"
#include "manager.h"
#include "scene.h"
#include "otherplayer.h"

#define BUFLEN 1024 

const std::string coment = "Hello";

UDP_Client::UDP_Client(const std::string& serverIP, int port) {
    WSADATA wsa;
    _ServerLen = sizeof(_Server);

    //Winsock�̏�����
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Winsock�̏������Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    //�\�P�b�g�̍쐬
    if ((_Sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        std::cerr << "�\�P�b�g�쐬�Ɏ��s���܂����B�G���[�R�[�h: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    //�A�h���X�t�@�~���AIP�A�h���X�A�|�[�g�ԍ���ݒ�
    _Server.sin_family = AF_INET;
    _Server.sin_port = htons(port);
    _Server.sin_addr.s_addr = inet_addr(serverIP.c_str());

}

UDP_Client::~UDP_Client() {

    SendDisconnect();
    closesocket(_Sock); // �\�P�b�g�����
    WSACleanup();      // Winsock�̃N���[���A�b�v
}

void UDP_Client::Success()
{
    char buf[BUFLEN];
    int recvLen;



    if ((recvLen = recvfrom(_Sock, buf, BUFLEN, 0, (struct sockaddr*)&_Server, &_ServerLen)) != SOCKET_ERROR) {

        buf[recvLen] = '\0'; // ��M�f�[�^�̏I�[��ݒ�

        if (recvLen == sizeof(OtherPlayerData))
        {
            OtherPlayerData receivedValue;
            std::memcpy(&receivedValue, buf, sizeof(OtherPlayerData));
            //���̃v���C���[�̏�񂪏��߂ė�����
            if (_OtherPlayerData[receivedValue.playerID].playerID == 0)
            {
                _OtherPlayerData[receivedValue.playerID].playerID = receivedValue.playerID;
                Manager::AddOtherClientPlayers(receivedValue.playerID);
            }
            _OtherPlayerData[receivedValue.playerID] = receivedValue;
            ReflectOtherPlayer();
        }
    }
}

void UDP_Client::Check()
{
    if (SendFloat(1.0f)) {
        u_long blockmode = 1; //��u���b�L���O���[�h
        ioctlsocket(_Sock, FIONBIO, &blockmode);
        //��莞�Ԕ���������������ڑ��ҋ@������
        if (ReceiveInt_Check() != 0) {
            _Success = true;
            Manager::ResetConnectionCound();
        }
    }
}

bool UDP_Client::SendDisconnect()
{
    bool value = true;

    char buf[sizeof(bool)];
    std::memcpy(buf, &value, sizeof(bool));

    if (sendto(_Sock, buf, sizeof(bool), 0, (struct sockaddr*)&_Server, _ServerLen) == SOCKET_ERROR) {
        return false;
    }
    return true;
}

bool UDP_Client::SendFloat(const float value)
{
    char buf[sizeof(float)];
    std::memcpy(buf, &value, sizeof(float));

    if (sendto(_Sock, buf, sizeof(float), 0, (struct sockaddr*)&_Server, _ServerLen) == SOCKET_ERROR) {
        return false;
    }
    return true;
}

//�v���C���[�̃f�[�^�𑗂�
bool UDP_Client::SendMyPlayerData(const XMFLOAT3 value,const PLAYER_STATE state)
{//���̓v���C���[�ŌĂ�ł�/��ŕς���
    _MyPlayerData.pos = value;
    _MyPlayerData.playerState = state;

    char buf[sizeof(OtherPlayerData)];
    std::memcpy(buf, &_MyPlayerData, sizeof(OtherPlayerData));

    if (sendto(_Sock, buf, sizeof(OtherPlayerData), 0, (struct sockaddr*)&_Server, _ServerLen) == SOCKET_ERROR) {
        return false;
    }
    return true;
}

int UDP_Client::ReceiveInt_Check()
{
    char buf[sizeof(int)];
    int recvLen;

    if ((recvLen = recvfrom(_Sock, buf, sizeof(int), 0, (struct sockaddr*)&_Server, &_ServerLen)) == SOCKET_ERROR) {
        Manager::AddConnectionCount();
        return 0;
    }

    int receivedValue;
    std::memcpy(&receivedValue, buf, sizeof(int));
    _MyPlayerData.playerID = receivedValue;
    return receivedValue;
}

//�T�[�o�[����󂯎�������̃v���C���[�̃f�[�^��ݒ�
void UDP_Client::ReflectOtherPlayer()
{
    for (auto otherplayer : Manager::GetScene()->GetGameObjects<OtherPlayer>())
    {
        otherplayer->m_TransForm->_Position = _OtherPlayerData[otherplayer->playerID].pos;
        otherplayer->_state = _OtherPlayerData[otherplayer->playerID].playerState;
    }
}

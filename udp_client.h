#pragma once
#include "main.h"
#include <iostream>
#include "player.h"
class UDP_Client {
private:
    SOCKET _Sock = {};                 // �\�P�b�g
    struct sockaddr_in _Server = {};   // �T�[�o�[�̃A�h���X���
    int _ServerLen = {};               // �T�[�o�[�A�h���X�̒���

    OtherPlayerData _MyPlayerData = {};
    OtherPlayerData _OtherPlayerData[MAX_PLAYERS] = {};
public:
    bool _Success = false;
    //IP�A�h���X�ƃ|�[�g���w�肵�ď�����
    UDP_Client(const std::string& serverIP, int port);
    ~UDP_Client();

    void Success();
    void Check();

    //�o�C�g�X�g���[���Ƃ��đ��M
    bool SendDisconnect();
    bool SendFloat(const float value);
    bool SendMyPlayerData(const XMFLOAT3 value, const PLAYER_STATE state);

    //�o�C�g�X�g���[���Ƃ��Ď�M
    int ReceiveInt_Check();
    void ReflectOtherPlayer();
};

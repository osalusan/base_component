#pragma once
#include "main.h"
#include <iostream>
#include "player.h"
class UDP_Client {
private:
    SOCKET _Sock = {};                 // ソケット
    struct sockaddr_in _Server = {};   // サーバーのアドレス情報
    int _ServerLen = {};               // サーバーアドレスの長さ

    OtherPlayerData _MyPlayerData = {};
    OtherPlayerData _OtherPlayerData[MAX_PLAYERS] = {};
public:
    bool _Success = false;
    //IPアドレスとポートを指定して初期化
    UDP_Client(const std::string& serverIP, int port);
    ~UDP_Client();

    void Success();
    void Check();

    //バイトストリームとして送信
    bool SendDisconnect();
    bool SendFloat(const float value);
    bool SendMyPlayerData(const XMFLOAT3 value, const PLAYER_STATE state);

    //バイトストリームとして受信
    int ReceiveInt_Check();
    void ReflectOtherPlayer();
};

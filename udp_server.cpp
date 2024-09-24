#include "udp_server.h"
#include <iostream>
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "otherplayer.h"

#define BUFLEN 1024 
#define PORT (8888)

UDP_Server::UDP_Server() : running(false) {
    // Winsockの初期化
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Winsockの初期化に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // ソケットの作成
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        std::cerr << "ソケット作成に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // サーバーのアドレスファミリ、IPアドレス、ポート番号を設定
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // ソケットをバインド
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "バインドに失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }
    Start();
}

UDP_Server::~UDP_Server() {
    Stop(); // サーバー停止
    closesocket(serverSocket); // ソケットを閉じる
    WSACleanup(); // Winsockのクリーンアップ
}

void UDP_Server::Start() {
    if (running) {
        std::cerr << "サーバーはすでに実行中です。" << std::endl;
        return;
    }
    running = true;
    serverThread = std::thread(&UDP_Server::ServerLoop, this); // スレッドを開始
}

void UDP_Server::Stop() {
    if (!running) {
        std::cerr << "サーバーは実行中ではありません。" << std::endl;
        return;
    }
    running = false;
    if (serverThread.joinable()) {
        serverThread.join(); // スレッドを終了
    }
}

void UDP_Server::SendInt_Check(const sockaddr_in& client, int value)
{
    char buf[sizeof(int)];
    std::memcpy(buf, &value, sizeof(int));

    if (sendto(serverSocket, buf, sizeof(int), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "返信の送信に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::SendFloat(const sockaddr_in& client, float value)
{
    char buf[sizeof(float)];
    std::memcpy(buf, &value, sizeof(float));

    if (sendto(serverSocket, buf, sizeof(float), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "返信の送信に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::SendXMFLOAT3(const sockaddr_in& client, const XMFLOAT3& value)
{
    char buf[sizeof(XMFLOAT3)];
    std::memcpy(buf, &value, sizeof(XMFLOAT3));

    if (sendto(serverSocket, buf, sizeof(XMFLOAT3), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "返信の送信に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::SendOtherPlayerData(const sockaddr_in& client, const OtherPlayerData &value)
{
    char buf[sizeof(OtherPlayerData)];
    std::memcpy(buf, &value, sizeof(OtherPlayerData));

    if (sendto(serverSocket, buf, sizeof(OtherPlayerData), 0, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        std::cerr << "返信の送信に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
    }
}

void UDP_Server::ReturnOtherPlayers(sockaddr_in addsocket,int number)
{
  
    for (int i = 0; i < 8; i++)
    {
        if (Manager::GetClientPlayer() >= i)
        {
            //クライアントから見て、自身以外の情報を取得
            if (number != i)
                SendOtherPlayerData(addsocket, _AllPlayerData[i]);

        }
    }
}

void UDP_Server::ReturnHost(sockaddr_in addsocket)
{
    //ホストの座標を送信
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

    //UDPサーバーが起動

    u_long blockmode = 1; //非ブロッキングモード
    ioctlsocket(serverSocket, FIONBIO, &blockmode);

    while (running) {
        // クライアントからのメッセージを受信
        int recvLen = recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr*)&clientAddr, &slen);
        if (recvLen == SOCKET_ERROR) {
            std::cerr << "受信に失敗しました。エラーコード: " << WSAGetLastError() << std::endl;
            continue;
        }

        buf[recvLen] = '\0'; // 受信データの終端を設定
        std::string clientKey = inet_ntoa(clientAddr.sin_addr) + std::to_string(ntohs(clientAddr.sin_port));

        // 新しいクライアントを追加
        if (clients.find(clientKey) == clients.end()) {
            clients[clientKey] = clientAddr;
            std::cout << "新しいクライアントが接続されました: " << clientKey;
            int count = Manager::GetClientPlayer() + 1;
            SendInt_Check(clientAddr, count);
            Manager::AddOtherPlayer(count);
        }
        
        if(recvLen == sizeof(OtherPlayerData))
        {
            //ホストの情報は固定
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
            //皮は残るから消す処理作らないといけない
            Manager::Disconnect();
        }
    }
}


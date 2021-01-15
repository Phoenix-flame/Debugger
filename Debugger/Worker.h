#pragma once

#include "Network/PracticalSocket.h"
#include "../build/Debugger/debug.pb.h"
#include <Phoenix/core/base.h>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>
#define MAX_INCOMING_PACKET_SIZE 1000
using Phoenix::Ref;
using Phoenix::CreateRef;

struct Variables{
    std::string name;
    float value;
};

template <typename T>
class FIFO{
public:
    FIFO(){

    }
    void Push(T& data){
        std::lock_guard<std::mutex> lck (m_Mutex);
        m_Q.push(data);
    }
    T Pop(){
        std::lock_guard<std::mutex> lck (m_Mutex);
        T ret = m_Q.front();
        if (m_Q.size() == 0) { throw std::runtime_error("no_data"); }
        m_Q.pop();
        return ret;
    }

private:
    std::queue<T> m_Q; 
    std::mutex m_Mutex;
};


class Worker{
public:
    Worker(){
        m_Socket = CreateRef<UDPSocket>(10007);
        m_Socket->joinGroup("224.5.23.16");
        s_Fifo = CreateRef<FIFO<std::vector<Variables>>>();
        std::thread t1(&Worker::Run, this);
        t1.detach();
    }
    void Run(){
        while(true){
            unsigned int size = this->m_Socket->recv(this->incoming_buffer, MAX_INCOMING_PACKET_SIZE);
            this->m_Packet.ParseFromArray(this->incoming_buffer, size);
            for (auto f:this->m_Packet.variables()){
                s_FloatVars[f.name()] = f.value();
            }
            for (auto p:m_Packet.profiles()){
                s_TimeProfiles[p.name()] = p.value();
            }
        }
    }

private:
    Ref<UDPSocket> m_Socket;
    char incoming_buffer[MAX_INCOMING_PACKET_SIZE];
    AI_Debug m_Packet;

public:
    static std::map<std::string, float> s_FloatVars;
    static std::map<std::string, unsigned int> s_TimeProfiles;
    static Ref<FIFO<std::vector<Variables>>> s_Fifo;
};
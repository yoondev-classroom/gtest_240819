// 18_Mocking5.cpp
#include <iostream>

struct Packet { };

// C++에서는 암묵적인 인터페이스를 통해 의존성 주입 설계를 할 수 있습니다.
class PacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "AppendPacket" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketStream2 {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "AppendPacket" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    template <typename IPacketStream>
    void ReadPacket(IPacketStream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
    }
};

int main()
{
    PacketStream2 stream;
    PacketReader reader;

    reader.ReadPacket(&stream, 42);
}

// 18_Mocking5.cpp
#include <iostream>

struct Packet { };

// C++에서는 암묵적인 인터페이스를 통해 의존성 주입 설계를 할 수 있습니다.
// => C++ 단위 전략(Policy Based Design)
//    템플릿 기반으로 정책을 컴파일 시간에 교체할 수 있습니다.
//  장점: 가상 함수 기반이 아니기 때문에, 인라인 최적화가 가능합니다.
//  단점: 실행 시간에 정책을 교체하는 것이 아니라,
//      컴파일 시간에 코드를 생성해서, 정책을 교체할 수 있습니다.

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

#include <gmock/gmock.h>

// 암묵적 인터페이스를 기반으로 모의 객체를 만드는 방법
class MockPacketStream {
public:
    // void AppendPacket(Packet* newPacket)
    // MOCK_METHOD(void, AppendPacket, (Packet * newPacket), ());
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket));

    // const Packet* GetPacket(size_t packetNumber) const
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, ReadPacket)
{
    MockPacketStream stream;
    PacketReader reader;

    EXPECT_CALL(stream, AppendPacket(nullptr));
    EXPECT_CALL(stream, GetPacket(42));

    reader.ReadPacket(&stream, 42);
}

#if 0
int main()
{
    PacketStream stream;
    PacketReader reader;

    reader.ReadPacket(&stream, 42);
}
#endif

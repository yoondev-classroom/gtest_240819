// 15_Fake.cpp
#include <string>

class User {
    std::string name;
    int age;

public:
    User(const std::string& s, int n)
        : name { s }
        , age { n }
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

class IDatabase {
public:
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class Repository {
    IDatabase* database;

public:
    Repository(IDatabase* p)
        : database { p }
    {
    }

    void Save(User* user)
    {
        //...
        database->SaveUser(user->GetName(), user);
        //...
    }

    User* Load(const std::string& name)
    {
        // ...
        return database->LoadUser(name);
    }
};

#include <gtest/gtest.h>
#include <map>

// Fake Object Pattern
//  의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트 되지 않은 요구사항이 존재합니다.
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 통해, 테스트 되지 않은 요구사항을 검증합니다.
class FakeDatebase : public IDatabase {
    std::map<std::string, User*> data;

public:
    void SaveUser(const std::string& name, User* user) override
    {
        data[name] = user;
    }

    User* LoadUser(const std::string& name) override
    {
        // return nullptr;
        return data[name];
    }
};

// 1) 사용자 정의 타입에 대해서, 단언문을 사용할 경우, 단언문이 사용하는 연산자에 대한 재정의가 필요합니다.
bool operator==(const User& lhs, const User& rhs)
{
    return false;
    // return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

// 2) 사용자 정의 객체를 단언문을 통해 검증할 때,
//    테스트가 실패할 경우, 원하는 형태로 표현되기 위한 연산자 재정의 함수가 필요합니다.
std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "(" << user.GetName() << ", "
              << user.GetAge() << ")" << std::endl;
}

TEST(RepositoryTest, Save)
{
    FakeDatebase fake;
    Repository repo { &fake };
    std::string testName = "test_name";
    int testAge = 42;
    User expected { testName, testAge };

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    ASSERT_NE(actual, nullptr);
    EXPECT_EQ(*actual, expected); // ==
}

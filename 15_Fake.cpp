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
        return data[name];
    }
};

TEST(RepositoryTest, Save)
{
    FakeDatebase fake;
    Repository repo { &fake };
    std::string testName = "test_name";
    int testAge = 42;
    User expected { testName, testAge };

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    EXPECT_EQ(*actual, expected);
}

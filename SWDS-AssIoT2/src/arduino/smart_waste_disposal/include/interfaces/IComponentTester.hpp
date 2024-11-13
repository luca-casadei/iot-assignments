class ICompoentTest
{
public:
    ~ICompoentTest(){};
    virtual void test() = 0;
    virtual void init() = 0;
};
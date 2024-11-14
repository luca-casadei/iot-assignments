class ICompoentTester
{
public:
    ~ICompoentTester(){};
    virtual void test() = 0;
    virtual void init() = 0;
};
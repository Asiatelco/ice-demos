// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>

#include <Hello.h>
#include <Discovery.h>

using namespace std;
using namespace Demo;

class DiscoverReplyI : public DiscoverReply, public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    virtual void
    reply(const Ice::ObjectPrx& obj, const Ice::Current&)
    {
        Lock sync(*this);
        if(!_obj)
        {
            _obj = obj;
        }
        notify();
    }

    Ice::ObjectPrx
    waitReply(const IceUtil::Time& timeout)
    {
        Lock sync(*this);
        IceUtil::Time end = IceUtil::Time::now() + timeout;
        while(!_obj)
        {
            IceUtil::Time delay = end - IceUtil::Time::now();
            if(delay > IceUtil::Time::seconds(0))
            {
                timedWait(delay);
            }
            else
            {
                break;
            }
        }
        return _obj;
    }

private:

    Ice::ObjectPrx _obj;
};
typedef IceUtil::Handle<DiscoverReplyI> DiscoverReplyIPtr;

class HelloClient : public Ice::Application
{
public:

    virtual int run(int, char*[]);

private:

    void menu();
};

int
main(int argc, char* argv[])
{
#ifdef ICE_STATIC_LIBS
    Ice::registerIceUDP();
#endif

    HelloClient app;
    return app.main(argc, argv, "config.client");
}

int
HelloClient::run(int, char* argv[])
{
    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("DiscoverReply");
    DiscoverReplyIPtr replyI = new DiscoverReplyI;
    DiscoverReplyPrx reply = DiscoverReplyPrx::uncheckedCast(adapter->addWithUUID(replyI));
    adapter->activate();

    DiscoverPrx discover = DiscoverPrx::uncheckedCast(
        communicator()->propertyToProxy("Discover.Proxy")->ice_datagram());
    discover->lookup(reply);
    Ice::ObjectPrx base = replyI->waitReply(IceUtil::Time::seconds(2));
    if(!base)
    {
        cerr << argv[0] << ": no replies" << endl;
        return 1;
    }
    HelloPrx hello = HelloPrx::checkedCast(base);
    if(!hello)
    {
        cerr << argv[0] << ": invalid reply" << endl;
        return 1;
    }

    hello->sayHello();

    return 0;
}

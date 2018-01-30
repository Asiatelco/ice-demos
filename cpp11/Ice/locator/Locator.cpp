// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>

using namespace std;

namespace
{

class LocatorRegistryI : public Ice::LocatorRegistry
{
public:

    virtual void
    setAdapterDirectProxyAsync(string id, shared_ptr<Ice::ObjectPrx> proxy,
                               function<void()> response,
                               function<void(exception_ptr)>,
                               const Ice::Current&) override
    {
        if(!proxy)
        {
            _adapters.erase(id);
        }
        else
        {
            _adapters[id] = proxy;
        }
        response();
    }

    virtual void
    setReplicatedAdapterDirectProxyAsync(string, string, shared_ptr<Ice::ObjectPrx>, function<void()> response,
                                         function<void(exception_ptr)>, const Ice::Current&) override
    {
        assert(false); // Not used by this demo
        response();
    }

    virtual void
    setServerProcessProxyAsync(string, shared_ptr<Ice::ProcessPrx>, function<void()> response,
                               function<void(exception_ptr)>, const Ice::Current&) override
    {
        assert(false); // Not used by this demo
        response();
    }

    shared_ptr<Ice::ObjectPrx>
    getAdapter(const string& id)
    {
        auto p = _adapters.find(id);
        if(p == _adapters.end())
        {
            throw Ice::AdapterNotFoundException();
        }
        return p->second;
    }

private:

    map<string, shared_ptr<Ice::ObjectPrx>> _adapters;
};

class LocatorI : public Ice::Locator
{
public:

    LocatorI(shared_ptr<LocatorRegistryI> registry,
             shared_ptr<Ice::LocatorRegistryPrx> registryPrx) :
        _registry(move(registry)),
        _registryPrx(move(registryPrx))
    {
    }

    virtual void
    findObjectByIdAsync(Ice::Identity,
                        function<void(const shared_ptr<Ice::ObjectPrx>&)> response,
                        function<void(exception_ptr)>,
                        const Ice::Current&) const override
    {
        response(nullptr);
    }

    virtual void
    findAdapterByIdAsync(string id,
                         function<void(const shared_ptr<Ice::ObjectPrx>&)> response,
                         function<void(exception_ptr)>,
                         const Ice::Current&) const override
    {
        response(_registry->getAdapter(id));
    }

    virtual shared_ptr<Ice::LocatorRegistryPrx>
    getRegistry(const Ice::Current&) const override
    {
        return _registryPrx;
    }

private:

    const shared_ptr<LocatorRegistryI> _registry;
    const shared_ptr<Ice::LocatorRegistryPrx> _registryPrx;
};

}

class LocatorServer : public Ice::Application
{
public:

    virtual int run(int, char*[]) override;
};

int
main(int argc, char* argv[])
{
    LocatorServer app;
    return app.main(argc, argv, "config.locator");
}

int
LocatorServer::run(int argc, char*[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return 1;
    }

    auto adapter = communicator()->createObjectAdapter("Locator");
    auto registry = make_shared<LocatorRegistryI>();

    auto registryPrx = Ice::uncheckedCast<Ice::LocatorRegistryPrx>(
        adapter->add(registry, Ice::stringToIdentity("registry")));

    adapter->add(make_shared<LocatorI>(move(registry), move(registryPrx)),
                 Ice::stringToIdentity("locator"));
    adapter->activate();
    communicator()->waitForShutdown();
    return 0;
}

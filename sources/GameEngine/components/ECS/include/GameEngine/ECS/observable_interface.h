#ifndef OBSERVABLE_INTERFACE_H
#define OBSERVABLE_INTERFACE_H

GE_BEGIN_ENGINE_NAMESPACE

template<class M>
class IObservable
{
public:
    using MessageType = M;
    virtual void Notify(const MessageType& message) = 0;
};

template<class M>
class IObserver
{
public:
    using MessageType = M;
};

GE_END_ENGINE_NAMESPACE

#endif // OBSERVABLE_INTERFACE_H

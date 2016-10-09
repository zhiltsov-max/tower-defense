#ifndef OBSERVABLE_INTERFACE_H
#define OBSERVABLE_INTERFACE_H

namespace GE {

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

} // namespace GE

#endif // OBSERVABLE_INTERFACE_H

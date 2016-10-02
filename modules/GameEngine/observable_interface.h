#ifndef OBSERVABLE_INTERFACE_H
#define OBSERVABLE_INTERFACE_H

namespace GE {

template<class M>
class IObservable
{
protected:
    using MessageType = M;
    virtual void Notify(const MessageType& message) = 0;
};

template<class MT, class MI>
class IObserver
{
protected:
    using MessageType = MT;
    using MessageInfo = MI;
    virtual void RecieveMessage(const MessageType&, const MessageInfo&) = 0;
};

} // namespace GE

#endif // OBSERVABLE_INTERFACE_H

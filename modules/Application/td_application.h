#ifndef TD_APPLICATION_H
#define TD_APPLICATION_H

#include "application.h"
#include "application_task.h"



class TTDApplicationTask;
class TTDApplicationSettings;

class TTowerDefenseApplication : public TApplication
{
public:
    static TTowerDefenseApplication& Create(
        const TApplicationInfo& info = TApplicationInfo());

    static TTowerDefenseApplication* GetInstance();


    TTowerDefenseApplication(const TApplicationInfo& info);
    virtual ~TTowerDefenseApplication() = default;

    const TDAppState& GetState() const;
    void SetState(const TDAppState& value);

    typedef TTDApplicationSettings Settings;
    const Settings& GetSettings() const;
    Settings& GetSettings();

private:
    typedef TApplication parent_type;

protected:
    typedef std::unique_ptr<TTDApplicationTask> Task;
    Task task;
    TDAppState state;

    Settings settings;


    virtual void initialize(const TApplicationInfo& info) override;
    virtual void update() override;
    virtual void release() override;
    virtual void handleEvent(const Event& event) override;
};

TTowerDefenseApplication* TDapp();

#endif // TD_APPLICATION_H

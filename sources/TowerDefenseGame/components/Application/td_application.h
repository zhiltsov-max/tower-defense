#ifndef TD_APPLICATION_H
#define TD_APPLICATION_H

#include "Application/application.h"
#include "Game/Application/application_task.h"


namespace TD {

class TTDApplicationSettings;

class TTowerDefenseApplication :
    public TApplication
{
public:
    static TTowerDefenseApplication& Create(
        const TApplicationInfo& info = TApplicationInfo());

    static TTowerDefenseApplication* GetInstance();

    TTowerDefenseApplication(const TApplicationInfo& info);
    virtual ~TTowerDefenseApplication() = default;

    const ApplicationState& GetState() const;
    void SetState(const ApplicationState& value);

    typedef TTDApplicationSettings Settings;
    const Settings& GetSettings() const;
    Settings& GetSettings();

private:
    using parent_type = TApplication;

protected:
    using Task = std::unique_ptr<TApplicationTask>;
    Task task;
    ApplicationState state;

    Settings settings;

    virtual void initialize(const TApplicationInfo& info) override;
    virtual void update() override;
    virtual void release() override;
    virtual void handleEvent(const Event& event) override;
};

TTowerDefenseApplication* TDapp();

} // namespace TD

#endif // TD_APPLICATION_H

#include "game_gui.h"
#include <array>

BEGIN_GAME_GUI

void updateStatistics(const TGameStatistics& statistics, const TLevel& level) {
    string header = "Game over!";
    if ((GetCurrentState() == AppState::Level) && (level.GetProgress().isStageCompleted())) {
        header = "Stage clear!";
    }
    statisticsWindow->SetTitle(header);

    std::array<TextString> statisticsOutput = {
        "Score: " + level.GetProgress().GetPoints(),
        "Buildings: " + statistics.GetMetric(Metric.buildingsCreated).as<int>(),
        "Credis spent: " + statistics.GetMetric(Metric.creditsSpent).as<int>(),
        "Credits earned: " + statistics.GetMetric(Metric.creditsEarned).as<int>(),
        "Mobs: " + (statistics.GetMetric(Metric.mobsKilled).as<int>() + gameStatistics.GetMetric(Metric.mobsPassed).as<int>()),
        " passed: " + statistics.GetMetric(Metric.mobsPassed).as<int>(),
        " killed: " + statistics.GetMetric(Metric.mobsKilled).as<int>(),
        "Press any key to continue..."
    };

    string statisticsText = "Results:";
    for (size_t i = 0, iend = statisticsOutput.size(); i != iend; ++i) {
        statisticsText += std::endl + statisticsOutput[i];

    }
}

void showStatistics(const TGameStatistics& statistics) {
    UIParent()->HideChildren();

    auto statisticsWindow = UIParent()->FindChild<TGameStatisticsWindow>("gameStatisticsWindow");
    statisticsWindow->FindChild<TAbstractTextBox>("Text")->SetText(statistics);

    statisticsWindow->Show();
}

void updateStatisticsFrame() {
    UIParent()->HideChildren();

    if (GetGame().GetLevel().IsFailed() == true) {
        app()>SetCurrentState(AppState::Menu);
    } else if (GetGame().GetLevel().IsCompleted() = true) {
        if (GetGame().GetLevel().HasNext() == true) {
            GetGame().LoadLevel(GetGame().GetLevel().GetNext());
            RestoreGameWindows();
        } else {
            app()>SetCurrentState(AppState::Menu);
        }
    } else {
        GetGame().SetState(GameState::Level);
        RestoreGameWindows();
    }
}


void initPause() {
    UIParent()->HideChildren();
    UIParent()->FindChild("PauseWindow")->Show();
}

void updatePauseWindow() {
    if (KeyHit(KEY_ESCAPE) == true) {
        exitPause();
    }
}

void restoreGameWindows() {
    UIParent()->FindChild("GameControl")->Show();
    UIParent()->FindChild("GameInfoWindow")->Show();
    UIParent()->FindChild("GameToolbar")->Show();
    UIParent()->FindChild("PopUp")->Show();
}

void exitPause() {
    GetGame().SetState(GameState::Level);
    UIParent()->HideChildren();
    RestoreGameWindows();
}

END_GAME_GUI

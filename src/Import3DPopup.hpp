#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

class Import3DPopup : public Popup<> {
protected:
    std::string m_selectedPath = "";
    CCLabelBMFont* m_pathDisplayLabel = nullptr;
    TextInput* m_groupIdInput = nullptr;
    TextInput* m_simplificationInput = nullptr;
    EventListener<Task<Result<std::filesystem::path>>> m_pickListener;

    bool setup() override;
    void onBrowseFile(CCObject* sender);
    void onImport(CCObject* sender);

public:
    static Import3DPopup* create();
};

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "Import3DPopup.hpp"

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;

        auto btnSpr = CircleButtonSprite::createWithSpriteFrameName(
            "editor_btn01_001.png",
            1.0f,
            CircleBaseColor::Green,
            CircleBaseSize::Small
        );

        auto btn = CCMenuItemSpriteExtra::create(
            btnSpr,
            this,
            menu_selector(MyEditorUI::on3DImporterBtn)
        );

        auto menu = this->getChildByID("editor-buttons-menu");
        if (menu) {
            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }

    void on3DImporterBtn(CCObject* sender) {
        Import3DPopup::create()->show();
    }
};

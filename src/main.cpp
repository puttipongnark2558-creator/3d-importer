#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "Import3DPopup.hpp"

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;

        auto sprite = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(MyEditorUI::onOpen3DImporter)
        );

        auto menu = CCMenu::create();
        menu->setPosition({ 35.0f, 180.0f });
        menu->addChild(btn);
        this->addChild(menu);

        return true;
    }

    void onOpen3DImporter(CCObject* sender) {
        Import3DPopup::create()->show();
    }
};

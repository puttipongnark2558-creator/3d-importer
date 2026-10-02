#include "Import3DPopup.hpp"
#include "OBJImporter.hpp"
#include <Geode/utils/file.hpp>

Import3DPopup* Import3DPopup::create() {
    auto ret = new Import3DPopup();
    if (ret && ret->initAnchored(380.0f, 250.0f, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Import3DPopup::setup() {
    auto winSize = m_mainLayer->getContentSize();

    this->setTitle("3D Model Importer");

    auto subTitle = CCLabelBMFont::create("Dev: Juzu Team | Idea: spu7nix & coopertooddum", "chatFont.fnt");
    subTitle->setPosition({ winSize.width / 2.0f, winSize.height - 42.0f });
    subTitle->setScale(0.55f);
    subTitle->setOpacity(180);
    m_mainLayer->addChild(subTitle);

    auto container = CCNode::create();
    container->setPosition({ winSize.width / 2.0f, winSize.height / 2.0f - 10.0f });
    m_mainLayer->addChild(container);

    auto browseMenu = CCMenu::create();
    browseMenu->setPosition({ 0.0f, 45.0f });
    container->addChild(browseMenu);

    auto browseSpr = ButtonSprite::create("Select .OBJ File");
    auto browseBtn = CCMenuItemSpriteExtra::create(
        browseSpr, this, menu_selector(Import3DPopup::onBrowseFile)
    );
    browseMenu->addChild(browseBtn);

    m_pathDisplayLabel = CCLabelBMFont::create("No file selected", "chatFont.fnt");
    m_pathDisplayLabel->setPosition({ 0.0f, 22.0f });
    m_pathDisplayLabel->setScale(0.45f);
    m_pathDisplayLabel->setOpacity(160);
    container->addChild(m_pathDisplayLabel);

    auto groupLabel = CCLabelBMFont::create("Start Group ID:", "bigFont.fnt");
    groupLabel->setPosition({ -140.0f, -5.0f });
    groupLabel->setScale(0.35f);
    groupLabel->setAnchorPoint({ 0.0f, 0.5f });
    container->addChild(groupLabel);

    m_groupIdInput = TextInput::create(90.0f, "1000", "chatFont.fnt");
    m_groupIdInput->setFilter("0123456789");
    m_groupIdInput->setPosition({ 0.0f, -5.0f });
    container->addChild(m_groupIdInput);

    auto simpLabel = CCLabelBMFont::create("Vertex Reduction %:", "bigFont.fnt");
    simpLabel->setPosition({ -140.0f, -38.0f });
    simpLabel->setScale(0.35f);
    simpLabel->setAnchorPoint({ 0.0f, 0.5f });
    container->addChild(simpLabel);

    m_simplificationInput = TextInput::create(90.0f, "50", "chatFont.fnt");
    m_simplificationInput->setFilter("0123456789");
    m_simplificationInput->setPosition({ 0.0f, -38.0f });
    container->addChild(m_simplificationInput);

    auto buttonMenu = CCMenu::create();
    buttonMenu->setPosition({ winSize.width / 2.0f, 28.0f });
    m_mainLayer->addChild(buttonMenu);

    auto btnSpr = ButtonSprite::create("Import Model");
    auto importBtn = CCMenuItemSpriteExtra::create(
        btnSpr, this, menu_selector(Import3DPopup::onImport)
    );
    buttonMenu->addChild(importBtn);

    return true;
}

void Import3DPopup::onBrowseFile(CCObject* sender) {
    file::FilePickOptions options;
    options.filters.push_back({ "Wavefront 3D Object", { "*.obj" } });

    m_pickListener.bind([this](Task<Result<std::filesystem::path>>::Event* event) {
        if (auto res = event->getValue()) {
            if (res->isOk()) {
                m_selectedPath = res->unwrap().string();
                std::filesystem::path p(m_selectedPath);
                m_pathDisplayLabel->setString(p.filename().string().c_str());
                m_pathDisplayLabel->setOpacity(255);
            }
        }
    });

    m_pickListener.setFilter(file::pick(file::PickMode::OpenFile, options));
}

void Import3DPopup::onImport(CCObject* sender) {
    if (m_selectedPath.empty()) {
        FLAlertLayer::create("Error", "Please select an .obj file first!", "OK")->show();
        return;
    }

    int startGroupId = utils::numFromString<int>(m_groupIdInput->getString()).value_or(1000);
    int reductionPercent = utils::numFromString<int>(m_simplificationInput->getString()).value_or(50);

    CCPoint center = CCDirector::sharedDirector()->getWinSize() / 2.0f;
    bool success = OBJImporter::processAndImport(m_selectedPath, startGroupId, reductionPercent, true, center);

    if (success) {
        FLAlertLayer::create("Success", "3D Model built into GD level successfully!", "OK")->show();
        this->onClose(sender);
    } else {
        FLAlertLayer::create("Error", "Failed to process .obj file!", "OK")->show();
    }
}

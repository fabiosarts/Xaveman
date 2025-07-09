#include "WMainApp.hpp"

#include "../icons.hpp"

WMainApp::WMainApp(int x, int y, uint width, uint height, int screen, Display *display, Window parent, XFontStruct *font)
    : CWidget(x, y, width, height, screen, display, parent, font)
{
    dirListView = new CWItemList(5, 5, getWidth() / 2 - 10, getHeight() - 10, this, getFont());
    AddControl(dirListView);

    fileListView = new CWItemList(getWidth() / 2 + 5, 5, getWidth() / 2 - 10, getHeight() - 10, this, getFont());
    AddControl(fileListView);

    navigateTo("/etc");
}

WMainApp::~WMainApp()
{
}

void WMainApp::navigateTo(std::string newPath)
{
    CIconManager* iconmgr = CIconManager::GetInstance();
    currentPathDirs.clear();

    // add typical .. folder to go back
    dirListView->AddItem(iconmgr->GetIcon(ICON_FOLDER), nullptr, "..");

    for (const auto &entry : std::filesystem::directory_iterator(newPath))
    {
        if (entry.is_directory())
        {
            dirListView->AddItem(
                iconmgr->GetIcon(ICON_FOLDER),
                entry.is_symlink()? iconmgr->GetIcon(ICON_LINK) : nullptr,
                entry.path().filename().string());
        }
        else
        {
            int icon = ICON_FILE;
            if(entry.is_socket()) icon = ICON_SOCKET;
            else if(entry.is_block_file()) icon = ICON_BLOCK;
            else if(entry.is_character_file()) icon = ICON_CHARACTER;

            fileListView->AddItem(
                iconmgr->GetIcon(icon),
                entry.is_symlink()? iconmgr->GetIcon(ICON_LINK) : nullptr,
                entry.path().filename().string());
        }
    }
}

void WMainApp::Draw(Display *display, Drawable window, GC gc)
{
    CWidget::Draw(display, window, gc);
}

void WMainApp::onResize()
{
    dirListView->setRect(5, 5, getWidth() / 2 - 10, getHeight() - 10);
    fileListView->setRect(getWidth() / 2 + 5, 5, getWidth() / 2 - 10, getHeight() - 10);

    CWidget::onResize();
}

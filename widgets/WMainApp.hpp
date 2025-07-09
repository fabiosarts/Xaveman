#ifndef WMAINAPP_HPP
#define WMAINAPP_HPP

#include "Widget.hpp"
#include "WItemList.hpp"
#include <string>
#include <vector>
#include <filesystem>

class WMainApp : public CWidget
{
private:
    CWItemList* dirListView;
    CWItemList* fileListView;
    std::vector<std::filesystem::path> currentPathDirs;
public:
    WMainApp(int x, int y, uint width, uint height, int screen, Display *display, Window parent, XFontStruct *font);
    ~WMainApp();
    void navigateTo(std::string newPath);
    void Draw(Display *display, Drawable window, GC gc) override;
    void onResize() override;
};

#endif // WMAINAPP_HPP

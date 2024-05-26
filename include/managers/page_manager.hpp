#ifndef PAGE_MANAGER_HPP
#define PAGE_MANAGER_HPP

#include "../pages/page.hpp"
#include <vector>
#include <utility>
#include <optional>

class Page;

namespace ShareMe
{
    enum class PageType
    {
        None = 0,
        Login,
        Register,
        Home
    };

    class PageManager
    {
    public:
        using PageData = std::pair<Page*, PageType>;
    public:
        PageManager();
        ~PageManager();
        void addPage(const PageData& page);
        bool switchTo(PageType type);
        PageData getActivePage();
        PageData getPage(PageType type);
        PageData getPage(size_t index);
        size_t getActivePageIndex() const;
    private:
        std::vector<PageData> pages;
        PageType activePageType = PageType::None;
        size_t activePageIndex = 0;
    };
}

#endif
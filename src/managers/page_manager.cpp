#include "../../include/managers/page_manager.hpp"

namespace ShareMe
{
    PageManager::PageManager()
    {
    }

    PageManager::~PageManager()
    {
    }

    void PageManager::addPage(const PageData& page)
    {
        if (activePageType == PageType::None)
            activePageType = page.second;

        pages.push_back(page);
    }

    bool PageManager::switchTo(PageType type)
    {
        if (activePageType != PageType::None)
        {
            for (size_t i = 0; i < pages.size(); i++)
            {
                auto [page, ptype] = pages[i]; 
                if (ptype == type)
                {
                    activePageType = type;
                    activePageIndex = i;
                    return true;
                }
            }
        }

        return false;
    }

    PageManager::PageData PageManager::getActivePage()
    {
        if (activePageType != PageType::None)
            return pages[activePageIndex];
        
        return std::make_pair(nullptr, activePageType);
    }

    PageManager::PageData PageManager::getPage(PageType type)
    {
        for (size_t i = 0; i < pages.size(); i++)
        {
            auto [page, ptype] = pages[i]; 
            if (ptype == type)
            {
                return pages[i];
            }
        }

        return std::make_pair(nullptr, activePageType);
    }

    PageManager::PageData PageManager::getPage(size_t index)
    {
        if (index >= 0 && index < pages.size())
            return pages[index];

        return std::make_pair(nullptr, PageType::None);
    }

    size_t PageManager::getActivePageIndex() const
    {
        return activePageIndex;
    }
}
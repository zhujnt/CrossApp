//
//  CATableView.h
//  CrossApp
//
//  Created by Li Yuanfeng on 14-4-28.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#ifndef __CrossAppx__CATableView__
#define __CrossAppx__CATableView__

#include <iostream>
#include "CAScrollView.h"
#include "control/CAControl.h"
#include <vector>
#include <deque>
#include <set>
#include "cocoa/CCDictionary.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

//typedef enum
//{
//    CATableViewOrientationHorizontal,
//    CATableViewOrientationVertical
//} CATableViewOrientation;

class CATableViewCell;
class CATableView;

class CATableViewDelegate
{
public:
    
    virtual ~CATableViewDelegate(){};
    
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row){};
    
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row){};
    
    virtual void tableViewDidShowPullDownView(CATableView* table){};
    
    virtual void tableViewDidShowPullUpView(CATableView* table){};
};

class CATableViewDataSource
{
public:
    
    virtual ~CATableViewDataSource(){};
    
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, unsigned int section, unsigned int row) = 0;
    
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, unsigned int section){return NULL;}
    
    virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, unsigned int section){return NULL;}
    
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section) = 0;
    
    virtual unsigned int numberOfSections(CATableView *table){return 1;}
    
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) = 0;
    
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section){return 0;}
    
    virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section){return 0;}
};


class CC_DLL CATableView: public CAScrollView
{
    
public:
    
    CATableView();
    
    virtual ~CATableView();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExitTransitionDidStart();

    static CATableView* createWithFrame(const CCRect& rect);
    
    static CATableView* createWithCenter(const CCRect& rect);
    
    virtual bool init();
    
    void reloadData();
    
    CATableViewCell* dequeueReusableCellWithIdentifier(const char* reuseIdentifier);
    
    void setSelectRowAtIndexPath(unsigned int section, unsigned int row);
    
protected:

    inline virtual float maxSpeed(float delay);
    
    inline virtual float maxSpeedCache(float delay);
    
    inline virtual float decelerationRatio(float delay);
    
    inline virtual CCPoint maxBouncesLenght();
    
    void clearData();
    
    void reloadViewSizeData();
    
    virtual void setViewSize(CCSize var);
    
    virtual void setContentSize(const CCSize& var);
    
    virtual void update(float fDelta);
    
protected:
    
    virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);
    
protected:
    
    CC_SYNTHESIZE(CATableViewDataSource*, m_pTableViewDataSource, TableViewDataSource);
    
    CC_SYNTHESIZE(CATableViewDelegate*, m_pTableViewDelegate, TableViewDelegate);
    
    CC_SYNTHESIZE_RETAIN(CAView*, m_pTableHeaderView, TableHeaderView);
    
    CC_SYNTHESIZE_RETAIN(CAView*, m_pTableFooterView, TableFooterView);
    
    CC_SYNTHESIZE_RETAIN(CAView*, m_pTablePullDownView, TablePullDownView);
    
    CC_SYNTHESIZE_RETAIN(CAView*, m_pTablePullUpView, TablePullUpView);
    
    CC_SYNTHESIZE(CAColor4B, m_separatorColor, SeparatorColor);
    
    CC_SYNTHESIZE(unsigned int, m_nTableHeaderHeight, TableHeaderHeight);
    
    CC_SYNTHESIZE(unsigned int, m_nTableFooterHeight, TableFooterHeight);
    
    CC_SYNTHESIZE(unsigned int, m_nTablePullViewHeight, TablePullViewHeight);
    
    CC_SYNTHESIZE(unsigned int, m_nSeparatorViewHeight, SeparatorViewHeight);
    
    CC_SYNTHESIZE_IS(bool, m_bAllowsSelection, AllowsSelection);
    
    CC_SYNTHESIZE_IS(bool, m_bAllowsMultipleSelection, AllowsMultipleSelection);
    
private:
    
    using CAScrollView::setBounceHorizontal;
    
    using CAScrollView::isBounceHorizontal;
    
    using CAScrollView::setBounceVertical;
    
    using CAScrollView::isBounceVertical;
    
    using CAScrollView::setShowsHorizontalScrollIndicator;
    
    using CAScrollView::isShowsHorizontalScrollIndicator;
    
    using CAScrollView::setViewSize;
    
    using CAScrollView::getViewSize;
    
    using CAScrollView::setMinimumZoomScale;
    
    using CAScrollView::getMinimumZoomScale;
    
    using CAScrollView::setMaximumZoomScale;
    
    using CAScrollView::getMaximumZoomScale;
    
    using CAScrollView::getZoomScale;
    
    using CAScrollView::isZooming;
    
    using CAScrollView::addSubview;
    
    using CAScrollView::insertSubview;
    
    using CAScrollView::removeAllSubviews;
    
    using CAScrollView::removeSubview;
    
    using CAScrollView::removeSubviewByTag;
    
    using CAScrollView::getSubviewByTag;
    
    using CAResponder::setTouchSidingDirection;
    
protected:
    
    std::vector<unsigned int> m_nRowsInSections;
    
    std::vector<unsigned int> m_nSectionHeights;
    
    std::vector<unsigned int> m_nSectionHeaderHeights;
    
    std::vector<unsigned int> m_nSectionFooterHeights;
    
    std::vector<std::vector<unsigned int> > m_nRowHeightss;
    
    std::vector<CCRect> m_rSectionRectss;
    
    std::vector<std::vector<CCRect> > m_rTableCellRectss;

    std::deque<CATableViewCell*> m_pTableCells;
    
    std::set<CATableViewCell*> m_pSelectedTableCells;
    
    CATableViewCell* m_pHighlightedTableCells;
    
    CCDictionary* m_pCellDict;
};

class CC_DLL CATableViewCell: public CAControl
{
    
public:
    
    CATableViewCell();
    
    virtual ~CATableViewCell();
    
    static CATableViewCell* create(const char* reuseIdentifier);
    
    bool initWithReuseIdentifier(const char* reuseIdentifier);
    
    void setBackGroundViewForState(CAControlState controlState, CAView *var);
    
protected:

    CC_SYNTHESIZE(std::string, m_sReuseIdentifier, ReuseIdentifier);
    
    CC_SYNTHESIZE(unsigned int, m_nSection, Section);
    
    CC_SYNTHESIZE(unsigned int, m_nRow, Row);

};

NS_CC_END;

#endif /* defined(__CrossAppx__CATableView__) */

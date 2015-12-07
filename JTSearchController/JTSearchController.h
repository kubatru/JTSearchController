//
//  JTSearchController.h
//  JTSearchController
//
//  Created by Jakub Truhlar on 06.12.15.
//  Copyright © 2015 Jakub Truhlar. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface JTSearchController : UIViewController <UITableViewDelegate>

/**
 *  The searchBar and the tableView must be set as well as tableViewTopConstraint.
 *  The tableViewTopConstraint is the one between the tableView.top and the topLayoutGuide.bottom.
 */
@property (nonatomic, weak) IBOutlet UISearchBar *searchBar;
@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *tableViewTopConstraint;

/**
 *  Must be set for tableView resetting case
 */
@property (nonatomic, assign) id<UITableViewDelegate> delegate;

/**
 *  SearchBar visibility
 */
@property (nonatomic, assign, getter=isSearchBarVisible) bool searchBarVisible;

/**
 *  SearchBar positioning
 */
- (void)showSearchBar;
- (void)hideSearchBar;

/**
 *  Do NOT forget to override these UIScrollViewDelegate methods implemented in this class.
 *  - (void)scrollViewDidScroll:(UIScrollView *)scrollView
 *  - (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
 *  - (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView
 *  - (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset
 */

@end
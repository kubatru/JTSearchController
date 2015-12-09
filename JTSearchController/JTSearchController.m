//
//  JTSearchController.m
//  JTSearchController
//
//  Created by Jakub Truhlar on 06.12.15.
//  Copyright © 2015 Jakub Truhlar. All rights reserved.
//

#import "JTSearchController.h"

@interface JTSearchController ()

@property (nonatomic, assign) CGFloat beginOffsetY;
@property (nonatomic, assign) CGFloat beginContentOffsetY;
@property (nonatomic, assign) bool scrollingToTop;

@end

@implementation JTSearchController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.searchBarVisible = true;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - UIScrollViewDelegate
- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    if (scrollView == self.tableView) {
        
        if (self.scrollingToTop) {
            return;
        }
        
        CGPoint translation = [scrollView.panGestureRecognizer translationInView:scrollView];
        
        if (translation.y > 0.0) {
            // More Up then Down
            self.tableViewTopConstraint.constant = MIN(self.beginOffsetY + translation.y, self.searchBar.frame.size.height);
            
            // Scroll of the tableView and changing of the constraint make scrolling faster then the constraint change itself, so we need to compensate it
            if (translation.y <= self.searchBar.frame.size.height && !self.isSearchBarVisible) {
                self.tableView.delegate = nil;
                self.tableView.contentOffset = CGPointMake(self.tableView.contentOffset.x, self.beginContentOffsetY);
                self.tableView.delegate = self.delegate;
            }
            
        } else if (translation.y < 0.0) {
            // More Down then Up
            self.tableViewTopConstraint.constant = MAX(self.beginOffsetY + translation.y, 0.0);
            
            // Scroll of the tableView and changing of the constraint make scrolling faster then the constraint change itself, so we need to compensate it
            if (translation.y >= -self.searchBar.frame.size.height && self.isSearchBarVisible) {
                self.tableView.delegate = nil;
                self.tableView.contentOffset = CGPointMake(self.tableView.contentOffset.x, self.beginContentOffsetY);
                self.tableView.delegate = self.delegate;
            }
        }
        
        [self updateSearchBarAlpha];
    }
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    if (scrollView == self.tableView) {
        self.beginOffsetY = self.tableViewTopConstraint.constant;
        self.beginContentOffsetY = self.tableView.contentOffset.y;
    }
}

- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView {
    if (!self.scrollingToTop) {
        [self showSearchBar];
        self.scrollingToTop = true;
    }
    
    return true;
}

- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView {
    self.scrollingToTop = false;
}

- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset {
    if (scrollView == self.tableView) {
        // Stick effect for the search bar
        CGPoint translation = [scrollView.panGestureRecognizer translationInView:scrollView];
        if (translation.y > 0.0) {
            // More Down then Up
            if (translation.y >= self.searchBar.frame.size.height / 4.0) {
                [self showSearchBar];
                
            } else {
                [self hideSearchBar];
            }
            
        } else {
            // More Up then Down
            if (translation.y < -(self.searchBar.frame.size.height / 4.0)) {
                [self hideSearchBar];
                
            } else {
                [self showSearchBar];
            }
        }
    }
}

#pragma mark - SearchBar handle
- (void)showSearchBar {
    self.tableView.userInteractionEnabled = false;
    self.tableViewTopConstraint.constant = self.searchBar.frame.size.height;
    self.searchBarVisible = true;
    
    [UIView animateWithDuration:0.2 animations:^{
        [self updateSearchBarAlpha];
        [self.view layoutIfNeeded];
        
    } completion:^(BOOL finished) {
        self.tableView.userInteractionEnabled = true;
    }];
}

- (void)hideSearchBar {
    self.tableView.userInteractionEnabled = false;
    self.tableViewTopConstraint.constant = 0.0;
    self.searchBarVisible = false;
    
    [UIView animateWithDuration:0.2 animations:^{
        [self updateSearchBarAlpha];
        [self.view layoutIfNeeded];
        
    } completion:^(BOOL finished) {
        self.tableView.userInteractionEnabled = true;
    }];
}

- (void)updateSearchBarAlpha {
    CGFloat constant = 100.0 / self.searchBar.frame.size.height;
    self.searchBar.alpha = (self.tableViewTopConstraint.constant * constant) / 100.0;
}

@end

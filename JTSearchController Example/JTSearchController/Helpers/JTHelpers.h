//
//  JTHelpers.h
//
//  Created by Jakub Truhlar on 28.2.15.
//  Copyright (c) 2015 Jakub Truhlar. All rights reserved.

#import "Constants.h"
//#import "Flurry.h" // Flurry SDK
//#import "GAI.h" // Google analytics SDK
//#import "GAIFields.h" // Google analytics SDK
//#import "GAITracker.h" // Google analytics SDK
//#import "GAIDictionaryBuilder.h" // Google analytics SDK


#pragma mark - Colors
#define RGBA_R(hex) ((((hex)>>16) & 0xff) * 1.f/255.f)
#define RGBA_G(hex) ((((hex)>> 8) & 0xff) * 1.f/255.f)
#define RGBA_B(hex) ((((hex)>> 0) & 0xff) * 1.f/255.f)
static inline UIColor *UIColorWithHex(NSInteger hex) {return [UIColor colorWithRed:RGBA_R(hex) green:RGBA_G(hex) blue:RGBA_B(hex) alpha:1.0];}
static inline UIColor *UIColorWithHexAndAlpha(NSInteger hex, CGFloat alpha) {return [UIColor colorWithRed:RGBA_R(hex) green:RGBA_G(hex) blue:RGBA_B(hex) alpha:alpha];}
static inline UIColor *UIColorAtPixelOfImage(CGPoint point, UIImage *image) {
    if (!CGRectContainsPoint(CGRectMake(0.0f, 0.0f, image.size.width, image.size.height), point)) {return nil;}
    NSInteger pointX = trunc(point.x);
    NSInteger pointY = trunc(point.y);
    CGImageRef cgImage = image.CGImage;
    NSUInteger width = image.size.width;
    NSUInteger height = image.size.height;
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    int bytesPerPixel = 4;
    int bytesPerRow = bytesPerPixel * 1;
    NSUInteger bitsPerComponent = 8;
    unsigned char pixelData[4] = { 0, 0, 0, 0 };
    CGContextRef context = CGBitmapContextCreate(pixelData, 1, 1, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    CGContextSetBlendMode(context, kCGBlendModeCopy);
    CGContextTranslateCTM(context, -pointX, pointY-(CGFloat)height);
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, (CGFloat)width, (CGFloat)height), cgImage);
    CGContextRelease(context);
    CGFloat red   = (CGFloat)pixelData[0] / 255.0f;
    CGFloat green = (CGFloat)pixelData[1] / 255.0f;
    CGFloat blue  = (CGFloat)pixelData[2] / 255.0f;
    CGFloat alpha = (CGFloat)pixelData[3] / 255.0f;
    return [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
}


#pragma mark - My Regular Fonts
static inline UIFont *CalibreLight(CGFloat size) {return [UIFont fontWithName:@"Calibre-Light" size:size];} // Paid
static inline UIFont *CalibreRegular(CGFloat size) {return [UIFont fontWithName:@"Calibre-Regular" size:size];}
static inline UIFont *CalibreMedium(CGFloat size) {return [UIFont fontWithName:@"Calibre-Medium" size:size];}
static inline UIFont *CalibreSemibold(CGFloat size) {return [UIFont fontWithName:@"Calibre-Semibold" size:size];}

static inline UIFont *ProximaNovaLight(CGFloat size) {return [UIFont fontWithName:@"ProximaNova-Light" size:size];} // Paid
static inline UIFont *ProximaNovaRegular(CGFloat size) {return [UIFont fontWithName:@"ProximaNova-Regular" size:size];}
static inline UIFont *ProximaNovaSemibold(CGFloat size) {return [UIFont fontWithName:@"ProximaNova-Semibold" size:size];}
static inline UIFont *ProximaNovaBold(CGFloat size) {return [UIFont fontWithName:@"ProximaNova-Bold" size:size];}

static inline UIFont *MontserratHairline(CGFloat size) {return [UIFont fontWithName:@"Montserrat-Hairline" size:size];} // Free
static inline UIFont *MontserratRegular(CGFloat size) {return [UIFont fontWithName:@"Montserrat-Regular" size:size];}
static inline UIFont *MontserratLight(CGFloat size) {return [UIFont fontWithName:@"Montserrat-Light" size:size];}
static inline UIFont *MontserratBold(CGFloat size) {return [UIFont fontWithName:@"Montserrat-Bold" size:size];}
static inline UIFont *MontserratBlack(CGFloat size) {return [UIFont fontWithName:@"Montserrat-Black" size:size];}


#pragma mark - Screen and Frame geometry
static inline CGFloat ScreenWidth() {return [[UIScreen mainScreen] bounds].size.width;}
static inline CGFloat ScreenHeight() {return [[UIScreen mainScreen] bounds].size.height;}

static inline CGFloat WindowWidth() {return [UIApplication sharedApplication].delegate.window.bounds.size.width;}
static inline CGFloat WindowHeight() {return [UIApplication sharedApplication].delegate.window.bounds.size.height;}

static inline CGFloat ViewWidth(UIView *view) {return view.frame.size.width;}
static inline CGFloat ViewHeight(UIView *view) {return view.frame.size.height;}

static inline CGFloat X(UIView *view) {return view.frame.origin.x;}
static inline CGFloat Y(UIView *view) {return view.frame.origin.y;}
static inline CGFloat LeftEdge(UIView *view) {return view.frame.origin.x;}
static inline CGFloat TopEdge(UIView *view) {return view.frame.origin.y;}
static inline CGFloat BottomEdge(UIView *view) {return view.frame.origin.y + view.frame.size.height;}
static inline CGFloat RightEdge(UIView *view) {return view.frame.origin.x + view.frame.size.width;}

static inline CGFloat NavigationOrTabBarHeight() {if (UIDeviceOrientationIsLandscape([UIDevice currentDevice].orientation)){ return 32;} else {return 44;}}


#pragma mark - Devices
static inline BOOL IsIPAD() {return ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad);}
static inline BOOL IsIPHONE() {return ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone);}

static inline BOOL IsIPHONE4() {return (IsIPHONE() && [[UIScreen mainScreen] bounds].size.height == 480);}
static inline BOOL IsIPHONE5() {return (IsIPHONE() && [[UIScreen mainScreen] bounds].size.height == 568);}
static inline BOOL IsIPHONE6() {return (IsIPHONE() && [[UIScreen mainScreen] bounds].size.height == 667);}
static inline BOOL IsIPHONE6PLUS() {return (IsIPHONE() && [[UIScreen mainScreen] bounds].size.height == 736);}


#pragma mark - Versions
static inline BOOL IsIOS7() {return ([[UIDevice currentDevice].systemVersion floatValue] >= 7.0 && [[UIDevice currentDevice].systemVersion floatValue] < 8.0);}
static inline BOOL IsIOS8() {return ([[UIDevice currentDevice].systemVersion floatValue] >= 8.0 && [[UIDevice currentDevice].systemVersion floatValue] < 9.0);}
static inline BOOL IsIOS9() {return ([[UIDevice currentDevice].systemVersion floatValue] >= 9.0 && [[UIDevice currentDevice].systemVersion floatValue] < 10.0);}
static inline BOOL IsIOS8_OR_NEWER() {return [[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0;}
static inline BOOL IsIOS9_OR_NEWER() {return [[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0;}

#pragma mark - NSNumber
static inline NSNumber *NumberWithInteger(NSInteger number) {return [NSNumber numberWithInteger:number];}
static inline NSNumber *NumberWithFloat(CGFloat number) {return [NSNumber numberWithFloat:number];}
static inline NSNumber *NumberWithBool(BOOL number) {return [NSNumber numberWithBool:number];}


#pragma mark - Notifications
static inline void AddNotificationObserverWithObject(id observer, SEL selector, NSString *notificationName, id object) {[[NSNotificationCenter defaultCenter] addObserver:observer selector:selector name:notificationName object:object];}
static inline void AddNotificationObserver(id observer, SEL selector, NSString *notificationName) {AddNotificationObserverWithObject(observer, selector, notificationName, nil);}
static inline void PostNotificationWithObjectAndInfo(NSString *notificationName, id object, NSDictionary *info) {[[NSNotificationCenter defaultCenter] postNotificationName:notificationName object:object userInfo:info];}
static inline void PostNotification(NSString *notificationName) {PostNotificationWithObjectAndInfo(notificationName, nil, nil);}
static inline void RemoveNotificationObserver(id observer) {[[NSNotificationCenter defaultCenter] removeObserver:observer];}


#pragma mark - Simple dialog
static inline void ShowSimpleDialog(NSString *title, NSString *message, NSString *buttonText, id delegate) {
    NSString *titleString = title ? title : @"";
    NSString *messageString = title ? message : [NSString stringWithFormat:@"%@", message];
    NSString *buttonString = buttonText ? buttonText : @"OK";
    if (IsIOS8_OR_NEWER()) {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:titleString message:messageString preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *cancel = [UIAlertAction actionWithTitle:buttonString style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {[alert dismissViewControllerAnimated:YES completion:nil];}];
        [alert addAction:cancel];
        [delegate presentViewController:alert animated:YES completion:nil];
    } else {
        //[[[UIAlertView alloc] initWithTitle:titleString message:messageString delegate:delegate cancelButtonTitle:buttonString otherButtonTitles:nil] show];
    }
}

#pragma mark - Converts
static inline CGFloat DegreesToRadians(NSInteger degrees) {return degrees * M_PI / 180;}

static inline NSString *YoutubeUrlStringToVideoId(NSString *urlString) {
    
    NSMutableArray *parsedMediaURL = [[urlString componentsSeparatedByCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"/=?"]] mutableCopy]; // Parse it
    NSString *youtubeID;
    if ([urlString rangeOfString:@"?t="].location == NSNotFound) {
        youtubeID = [NSString stringWithFormat:@"%@", [parsedMediaURL lastObject]];
    } else {
        youtubeID = [NSString stringWithFormat:@"%@", [parsedMediaURL objectAtIndex:[parsedMediaURL count] - 3]];
    }
    return youtubeID;
}


#pragma mark - Localization String without a comment
#define LocalizedString(string) NSLocalizedString(string, nil)


#pragma mark - Debug log
#ifdef DEBUG
#   define DLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#   define DLog(...)
#endif

    
#pragma mark - Flurry Event
#ifdef DEBUG
#define FlurryLogEvent(eventName) DLog(@"Flurry debug log event '%@'.", eventName);
#else
#define FlurryLogEvent(eventName) [Flurry logEvent:eventName];
#endif


#pragma mark - Google analytics Screen name
#ifdef DEBUG
#define GoogleAnalyticsScreenName(screenName) DLog(@"Google Analytics debug screen name set to: '%@'.", screenName);
#else
#define GoogleAnalyticsScreenName(screenName) [[[GAI sharedInstance] defaultTracker] set:kGAIScreenName value:screenName];\
                                              [[[GAI sharedInstance] defaultTracker] send:[[GAIDictionaryBuilder createScreenView] build]];
                                              // end of the macro
#endif

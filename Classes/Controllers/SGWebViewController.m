//
//  SGWebViewController.m
//  SGiPhoneSDK
//
//  Created by Derek Smith on 11/13/09.
//  Copyright 2009 SimpleGeo. All rights reserved.
//

#import "SGWebViewController.h"


@implementation SGWebViewController

- (id) init
{
    if(self = [super init]) {
        
        webView = [[UIWebView alloc] initWithFrame:CGRectZero];
        webView.scalesPageToFit = YES;
        webView.delegate = self;
    }
    
    return self;
}

- (void) loadURLString:(NSString*)stringURL
{
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:stringURL]];
    [webView loadRequest:request];
}

- (void) viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"about:blank"]]];
}

- (void) loadView
{
    [super loadView];
    
    webView.frame = self.view.bounds;
    [self.view addSubview:webView];
    
}


////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark UIWebView delegate methods 
//////////////////////////////////////////////////////////////////////////////////////////////// 

- (void) webViewDidStartLoad:(UIWebView*)webview
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
}

- (void) webViewDidFinishLoad:(UIWebView*)webview
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
}


- (void) dealloc
{
    [webView release];
    
    [super dealloc];
}

@end
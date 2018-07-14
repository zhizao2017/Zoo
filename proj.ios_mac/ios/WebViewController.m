//
//  WebViewController.m
//  HeloCC3-mobile
//
//  Created by 王为 on 2018/7/14.
//

#import "WebViewController.h"
#import <WebKit/WebKit.h>

@interface WebViewController ()<WKNavigationDelegate, WKUIDelegate>

@property (nonatomic, weak) UIButton *forwardBtn;
@property (nonatomic, weak) UIButton *backBtn;
@property (nonatomic, weak) WKWebView *webView;
@property (nonatomic, weak) UIButton *cancelBtn;
@property (nonatomic, weak) UIButton *refreshBtn;

@end

@implementation WebViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self setupUI];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)gotoURL:(NSString *)url{
    NSURLRequest *urlReq = [[NSURLRequest alloc] initWithURL:[NSURL URLWithString:url]];
    [self.webView loadRequest:urlReq];
}


-(void)forwardBtnTapped:(UIButton *)button{
    [self.webView goForward];
    
}


-(void)backBtnTapped:(UIButton *)button{
    [self.webView goBack];
}


-(void)cancelBtnTapped:(UIButton *)button{
    [self.webView stopLoading];
}

-(void)refreshBtnTapped:(UIButton *)button{
    [self.webView reload];
}


-(void)webView:(WKWebView *)webView decidePolicyForNavigationAction:(WKNavigationAction *)navigationAction decisionHandler:(void (^)(WKNavigationActionPolicy))decisionHandler{
    decisionHandler(WKNavigationActionPolicyAllow);
    NSLog(@"%@", navigationAction.request.URL);
}


-(void)setupUI{

    UIButton *forwardBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [forwardBtn setTitle:@"前进" forState:UIControlStateNormal];
    [forwardBtn addTarget:self action:@selector(forwardBtnTapped:) forControlEvents:UIControlEventTouchUpInside];
    [forwardBtn sizeToFit];
    
    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [backBtn setTitle:@"回退" forState:UIControlStateNormal];
    [backBtn addTarget:self action:@selector(backBtnTapped:) forControlEvents:UIControlEventTouchUpInside];
    [backBtn sizeToFit];
    
    UIButton *cancelBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [cancelBtn setTitle:@"停止" forState:UIControlStateNormal];
    [cancelBtn addTarget:self action:@selector(cancelBtnTapped:) forControlEvents:UIControlEventTouchUpInside];
    [cancelBtn sizeToFit];
    
    UIButton *refreshBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [refreshBtn setTitle:@"刷新" forState:UIControlStateNormal];
    [refreshBtn addTarget:self action:@selector(refreshBtnTapped:) forControlEvents:UIControlEventTouchUpInside];
    [refreshBtn sizeToFit];
    
    WKWebViewConfiguration *webViewConfig = [[WKWebViewConfiguration alloc] init];
    WKWebView *webView = [[WKWebView alloc] initWithFrame:CGRectZero configuration:webViewConfig];
    webView.navigationDelegate = self;
    webView.UIDelegate = self;
    
    [self.view addSubview:webView];
    [self.view addSubview:forwardBtn];
    [self.view addSubview:backBtn];
    [self.view addSubview:cancelBtn];
    [self.view addSubview:refreshBtn];

    self.forwardBtn = forwardBtn;
    self.backBtn = backBtn;
    self.cancelBtn = cancelBtn;
    self.refreshBtn = refreshBtn;
    self.webView = webView;
}


-(void)viewWillLayoutSubviews{
    [super viewWillLayoutSubviews];
    
    CGRect fFrame = self.forwardBtn.frame;
    CGRect bFrame = self.backBtn.frame;
    CGRect cFrame = self.cancelBtn.frame;
    
    CGRect cNewFrame = CGRectMake(10, self.view.bounds.size.height - cFrame.size.height, cFrame.size.width, cFrame.size.height);
    CGRect bNewFrame = CGRectMake(cNewFrame.origin.x + cNewFrame.size.width + 10, cNewFrame.origin.y-2, bFrame.size.width, bFrame.size.width);
    CGRect fNewFrame = CGRectMake(bNewFrame.origin.x + bNewFrame.size.width + 10, cNewFrame.origin.y, fFrame.size.width, fFrame.size.height);
    
    self.cancelBtn.frame = cNewFrame;
    self.forwardBtn.frame = fNewFrame;
    self.backBtn.frame = bNewFrame;
    
    CGRect wkFrame = CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height - fNewFrame.size.height);
    self.webView.frame = wkFrame;
    
    CGRect rFrame = self.refreshBtn.frame;
    CGRect rNewFrame = CGRectMake(self.view.bounds.size.width - 10 - fFrame.size.width, cNewFrame.origin.y, fFrame.size.width, rFrame.size.height);
    self.refreshBtn.frame = rNewFrame;
}


@end

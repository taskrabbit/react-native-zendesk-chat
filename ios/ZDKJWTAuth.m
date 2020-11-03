#import "ZDKJWTAuth.h"

@implementation ZDKJWTAuth

-(void)setUrl:(NSString *)urlString{
    AlfUrl=urlString;
}

- (void)getToken:(void (^ _Nonnull)(NSString * _Nullable, NSError * _Nullable))completion {
    NSError *error;

    NSURL *url = [NSURL URLWithString:AlfUrl];

    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];

    [request setHTTPMethod:@"POST"];

    [request setURL:url];

    [request addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];


    NSData *postData = NULL;

    [request setHTTPBody:postData];

    NSData *finalDataToDisplay = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:&error];

    NSMutableDictionary *abc = [NSJSONSerialization JSONObjectWithData: finalDataToDisplay
                                                               options: NSJSONReadingMutableContainers
                                                                error: &error];
    completion(abc[@"jwt"],NULL);
}

@end

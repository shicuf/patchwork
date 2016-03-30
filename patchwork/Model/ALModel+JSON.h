//
//  ALModel.h
//  patchwork
//
//  Created by Alex Lee on 2/18/16.
//  Copyright © 2016 Alex Lee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ALModel_Define.h"
#import "YYModel.h"

NS_ASSUME_NONNULL_BEGIN

//extern NSString * const kInternalObjectPrefix;
typedef id _Nullable (^ModelCustomTransformToJSON)(NSString *_Nonnull propertyName, id _Nullable value);

@interface ALCustomTransformMethodInfo : NSObject {
    @package
    YYClassPropertyInfo *_property;
    SEL                  _selector;
    Class                _classType;
}
@end

@interface ALModel (JSON) <YYModel>

#pragma mark - model copy
/**
 *  Create a new Model instance and copy properties from 'other'
 *  @see "-modelCopyProperties:fromModel:"
 */
+ (nullable instancetype)modelCopyFromModel:(__kindof ALModel *)other;

/**
 *  Create a new Model instance and copy specified properties from 'other'
 *  @see "-modelCopyProperties:fromModel:"
 */
+ (nullable instancetype)modelCopyFromModel:(__kindof ALModel *)other withProperties:(NSArray<NSString *> *)properties;

/**
 *  Create a new Model instance and copy properties from 'other', ignore the specified properties
 *  @see "-modelCopyProperties:fromModel:"
 */
+ (nullable instancetype)modelCopyFromModel:(__kindof ALModel *)other
                          excludeProperties:(NSArray<NSString *> *)properties;

/**
 *  Copy properties' value from &lt; other &gt; model.
 *  Copy rules:
 *      find out the 'last common ancestor' class of the 'self' and 'other' model
 *      ignore the properties that specified by param 'properties' but not belongs to the 'last common ancestor' class
 *      copy properties values
 *
 *  @param properties properties to copy
 *  @param other      model that copy from
 */
- (void)modelCopyProperties:(nullable NSArray<NSString *> *)properties fromModel:(__kindof ALModel *)other;

#pragma mark JSON -> Model
+ (nullable instancetype)modelWithJSON:(id)json;
- (nullable instancetype)initWithJSON:(id)json;

- (BOOL)modelSetWithJSON:(id)json;

+ (nullable NSArray *)modelArrayWithJSON:(id)json;
+ (nullable NSDictionary *)modelDictionaryWithJSON:(id)json;
- (nullable NSDictionary<NSString *, NSArray<ALCustomTransformMethodInfo *> *> *)modelCustomFromJSONTransformers;

#pragma mark Model -> JSON
- (nullable id)modelToJSONObject;
- (nullable id)modelToJSONObjectWithCustomTransformers:
    (nullable NSDictionary<NSString *, ModelCustomTransformToJSON> *)customTransformers;

- (nullable NSData *)modelToJSONData;
- (nullable NSData *)modelToJSONDataWithCustomTransformers:
    (nullable NSDictionary<NSString *, ModelCustomTransformToJSON> *)customTransformers;

- (nullable NSString *)modelToJSONString;
- (nullable NSString *)modelToJSONStringWithCustomTransformers:
    (nullable NSDictionary<NSString *, ModelCustomTransformToJSON> *)customTransformers;

#pragma mark -

- (nullable NSArray<NSString *> *)mappedKeysForProperty:(NSString *)propertyName;

#pragma mark - supper class method wrapper
- (NSString *)modelDescription;
//- (instancetype)copyModel;


@end

NS_ASSUME_NONNULL_END


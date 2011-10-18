#import <Foundation/Foundation.h>
#import "sqlite3.h"
#import "FMResultSet.h"

@interface FMDatabase : NSObject 
{
	sqlite3*    db;
	NSString*   databasePath;
    BOOL        logsErrors;
    BOOL        crashOnErrors;
    BOOL        raisesErrors;
    BOOL        inUse;
    BOOL        inTransaction;
    BOOL        traceExecution;
    BOOL        checkedOut;
    int         busyRetryTimeout;
    BOOL        shouldCacheStatements;
    NSMutableDictionary *cachedStatements;
}


+ (id)databaseWithPath:(NSString*)inPath;
- (id)initWithPath:(NSString*)inPath;

- (BOOL)open;
#if SQLITE_VERSION_NUMBER >= 3005000
- (BOOL)openWithFlags:(int)flags;
#endif
- (BOOL)close;
- (BOOL)goodConnection;
- (void)clearCachedStatements;

// encryption methods.  You need to have purchased the sqlite encryption extensions for these to work.
- (BOOL)setKey:(NSString*)key;
- (BOOL)rekey:(NSString*)key;


- (NSString *)databasePath;

- (NSString*)lastErrorMessage;

- (int)lastErrorCode;
- (BOOL)hadError;
- (sqlite_int64)lastInsertRowId;

- (sqlite3*)sqliteHandle;

- (BOOL)update:(NSString*)sql error:(NSError**)outErr bind:(id)bindArgs, ...;
- (BOOL)executeUpdate:(NSString*)sql, ...;
- (BOOL)executeUpdate:(NSString*)sql withArgumentsInArray:(NSArray *)arguments;

- (FMResultSet *)executeQuery:(NSString*)sql, ...;
- (FMResultSet *)executeQuery:(NSString *)sql withArgumentsInArray:(NSArray *)arguments;
- (FMResultSet *)executeQuery:(NSString *)sql withArgumentsInDictionary:(NSDictionary *)arguments;

- (BOOL)rollback;
- (BOOL)commit;
- (BOOL)beginTransaction;
- (BOOL)beginDeferredTransaction;

- (BOOL)logsErrors;
- (void)setLogsErrors:(BOOL)flag;

- (BOOL)raisesErrors;
- (void)setRaisesErrors:(BOOL)flag;

- (BOOL)crashOnErrors;
- (void)setCrashOnErrors:(BOOL)flag;

- (BOOL)inUse;
- (void)setInUse:(BOOL)value;

- (BOOL)inTransaction;
- (void)setInTransaction:(BOOL)flag;

- (BOOL)traceExecution;
- (void)setTraceExecution:(BOOL)flag;

- (BOOL)checkedOut;
- (void)setCheckedOut:(BOOL)flag;

- (int)busyRetryTimeout;
- (void)setBusyRetryTimeout:(int)newBusyRetryTimeout;

- (BOOL)shouldCacheStatements;
- (void)setShouldCacheStatements:(BOOL)value;

- (NSMutableDictionary *)cachedStatements;
- (void)setCachedStatements:(NSMutableDictionary *)value;


+ (NSString*)sqliteLibVersion;

- (int)changes;

@end

@interface FMStatement : NSObject {
    sqlite3_stmt *statement;
    NSString *query;
    long useCount;
}


- (void)close;
- (void)reset;

- (sqlite3_stmt *)statement;
- (void)setStatement:(sqlite3_stmt *)value;

- (NSString *)query;
- (void)setQuery:(NSString *)value;

- (long)useCount;
- (void)setUseCount:(long)value;


@end


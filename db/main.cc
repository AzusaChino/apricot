#include <assert.h>
#include "rocksdb/db.h"
#include "rocksdb/options.h"

int main(void)
{
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;

    // Set compression options
    options.compression = rocksdb::kSnappyCompression;

    // Set compression options for different levels
    options.compression_per_level = {
        rocksdb::kNoCompression,     // Level 0
        rocksdb::kSnappyCompression, // Level 1
        rocksdb::kZlibCompression,   // Level 2
        rocksdb::kBZip2Compression,  // Level 3
        rocksdb::kLZ4Compression,    // Level 4
        rocksdb::kLZ4HCCompression,  // Level 5
        rocksdb::kZSTD               // Level 6
    };

    // Open a RocksDB database
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    // Close the database
    delete db;
    return 0;
}

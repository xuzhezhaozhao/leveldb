#include <cassert>
#include <iostream>
#include <string>

#include "leveldb/db.h"

int main(int argc, char *argv[])
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()) {
        std::cerr << status.ToString() << std::endl;
    }
    if (status.ok()) status = db->Put(leveldb::WriteOptions(), "abc", "bcd");
    std::string value;
    if (status.ok()) status = db->Get(leveldb::ReadOptions(), "abc", &value);

    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << ":" << it->value().ToString() << std::endl;
    }
    delete it;
    delete db;

    return 0;
}

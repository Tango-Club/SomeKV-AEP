#pragma once

#include <glog/logging.h>

#include <cstdlib>
#include <mutex>

#include "io/readable_file.h"
#include "schema.h"
#include "storage/disk_storage.h"
#include "storage/memory_storage.h"

const std::string WAL_PATH_SUFFIX = std::string("/wal.dat");

class StorageEngine {
public:
    StorageEngine(const std::string& aep_dir)
            : _storage_path(aep_dir + WAL_PATH_SUFFIX),
              _memtable(ReadableFile(_storage_path).recover()),
              _wal(_storage_path) {
        LOG(INFO) << "Create StorageEngine. aep_dir=" << _storage_path;
    }

    ~StorageEngine() { LOG(INFO) << "Destroy StorageEngine. aep_dir=" << _storage_path; }

    void write(const void* data) {
        std::unique_lock lock(_mtx);
        const Schema::Row* row_ptr = static_cast<const Schema::Row*>(data);
        _memtable.write(row_ptr);
        _wal.write(row_ptr);
    }

    size_t read(int32_t select_column, int32_t where_column, const void* column_key,
                size_t column_key_len, void* res) {
        std::unique_lock lock(_mtx);
        return _memtable.read(select_column, where_column, column_key, column_key_len, res);
    }

private:
    std::string _storage_path;
    MemoryStorage _memtable;
    DiskStorage _wal;
    std::mutex _mtx;
};
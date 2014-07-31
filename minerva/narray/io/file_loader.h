#pragma once

#include "op/physical.h"
#include "op/logical.h"

namespace minerva {

class NArray;

class IFileLoader {
 public:
  virtual void Load(const std::string& fname, const Scale& size, DataList& out_shards) = 0;
  virtual ~IFileLoader() {}
};

struct FileLoaderClosure {
  std::string fname;
  Scale size;
  IFileLoader* loader;
};

class FileLoaderOp :
  public LogicalDataGenFn,
  public PhysicalComputeFn,
  public ClosureTrait<FileLoaderClosure> {
 public:
  void Execute(DataList& inputs, DataList& outputs, IMPL_TYPE impl_type);
  NVector<Chunk> Expand(const NVector<Scale>& part_sizes);
  std::string Name() const;
};

class SimpleFileLoader : public IFileLoader {
 public:
  void Load(const std::string& fname, const Scale& size, DataList& out_shards);
};

}

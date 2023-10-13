#include "store/storage_engine.h"

namespace SimCache {

class CacheManager {
public:

private:
  LocalStorageEngine<std::string, std::string> local_storage_engine_;
  
};

} // namespace SimCache
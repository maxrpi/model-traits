#ifndef BC_BACKEND_SIMMETRIX_H__
#define BC_BACKEND_SIMMETRIX_H__
#include "bcModelTraits.h"
#include "bcModelTraitsIO.h"

namespace mt {
struct SIMMETRIX : Backend {};

template <>
std::unique_ptr<ModelTraits> ReadFromFile(const std::string &filename,
                                          SIMMETRIX *backend);

} // namespace mt

#endif

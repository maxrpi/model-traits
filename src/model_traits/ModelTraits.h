#ifndef BC_MODEL_TRAITS_H__
#define BC_MODEL_TRAITS_H__
#include "CategoryNode.h"
#include <memory>
#include <string>

namespace mt {
/**
 * ModelTraits object is the root object that stores any boundary conditions, or
 * other attributes that may be stored on a model.
 */
class ModelTraits : public Convertible<ModelTraits> {
public:
  /**
   * @param [in] name of the root model traits object
   */
  ModelTraits(const std::string &name) : name_(name) {}
  /**
   * @param [in] name the root model traits object
   */
  ModelTraits(std::string &&name) : name_(std::move(name)) {}
  /**
   * @brief Add case to model traits object
   * @param [in] name
   * @return pointer to the inserted value if it wasn't already in the map or
   * nullptr
   *
   * Adds a case if it doesn't exist and returns a pointer to it's
   * INode. If the case does exist, the pointer to the case is returned.
   */
  CategoryNode *AddCase(const std::string &name) {
    return cases_.AddNode(std::make_unique<CategoryNode>(name));
  }
  CategoryNode *AddCase(std::string &&name) {
    return cases_.AddNode(std::make_unique<CategoryNode>(std::move(name)));
  }
  CategoryNode *GetCase(const std::string &name) {
    return cases_.FindNode(name);
  }
  const CategoryNode *GetCase(const std::string &name) const {
    return cases_.FindNode(name);
  }
  /**
   * Removes a case from ModelTraits by it's name
   */
  std::unique_ptr<CategoryNode> RemoveCase(const std::string &name) {
    return std::move(std::unique_ptr<CategoryNode>(
        static_cast<CategoryNode *>(cases_.RemoveNode(name).release())));
  }
  const auto &GetCases() const { return cases_; }
  auto &GetCases() { return cases_; }
  int NumCases() { return cases_.Size(); }
  const std::string &GetName() const noexcept { return name_; }

  friend fmt::formatter<ModelTraits>;

protected:
  NodeSet<CategoryNode, BC_VEC_WORKAROUND> cases_;
  std::string name_;
};

} // namespace mt

#endif

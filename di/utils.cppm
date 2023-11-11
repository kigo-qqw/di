export module di:utils;

import <type_traits>;


export namespace di::utils {
  template <typename T, typename... Ts>
  concept one_of = std::disjunction_v<std::is_same<T, Ts>...>;
}  // namespace di::utils

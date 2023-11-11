export module di:resolve_dependency;

import :bean;


export namespace di {
  template <typename T, template <typename> typename Bean = bean_t>
    requires bean<Bean<T>>
  struct resolve_dependency_t {
      using type = T;
  };

  template <template <typename...> typename T, typename... Ts,
            template <typename> typename Bean>
    requires bean<Bean<T<Ts...>>>
  struct resolve_dependency_t<T<Ts...>, Bean> {
      using type = T<typename resolve_dependency_t<typename Bean<Ts>::type,
                                                   Bean>::type...>;
  };
}  // namespace di::utils

export module di:fwd;

import :lifetime;
import :bean;


export namespace di {
  template <template <typename> typename Bean, typename... Interfaces>
    requires(bean<Bean<Interfaces>> && ...)
  class basic_service_container_t;

  template <typename... Interfaces>
  using service_container_t = basic_service_container_t<bean_t, Interfaces...>;

  template <typename T, template <typename> typename Bean>
  concept basic_service_container = true;  // TODO

  template <typename T>
  concept service_container = basic_service_container<T, bean_t>;

  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, class Interface,
            lifetime Lifetime = Bean<Interface>::lifetime_type>
  struct basic_lifetime_manager_t;

  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, typename Interface>
    requires bean<Bean<Interface>>
  class basic_service_factory_t;
}  // namespace di

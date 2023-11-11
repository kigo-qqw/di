export module di:lifetime_manager;

import <optional>;

import :fwd;
import :lifetime;
import :service_factory;
import :resolve_dependency;

export namespace di {
  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, class Interface>
  struct basic_lifetime_manager_t<Bean, ServiceContainer, Interface,
                                  transient_t> {
      using service_container_type = ServiceContainer;
      using service_interface_type = Bean<Interface>::type;
      using service_type = resolve_dependency_t<service_interface_type, Bean>::type;

      constexpr service_type
      get(const service_container_type &container) const {
        return basic_service_factory_t<
                Bean, service_container_type,
                service_interface_type>::create(container);
      }
  };

  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, class Interface>
  struct basic_lifetime_manager_t<Bean, ServiceContainer, Interface, scoped_t> {
      using service_container_type = ServiceContainer;
      using service_interface_type = Bean<Interface>::type;
      using service_type = resolve_dependency_t<service_interface_type, Bean>::type;

      constexpr service_type
      get(const service_container_type &container) const {
        if (!instance_.has_value()) [[unlikely]] {
          instance_ = basic_service_factory_t<
                  Bean, service_container_type,
                  service_interface_type>::create(container);
        }
        return instance_.value();
      }

    private:
      mutable std::optional<service_type> instance_;
  };

  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, class Interface>
  struct basic_lifetime_manager_t<Bean, ServiceContainer, Interface,
                                  singleton_t> {
      using service_container_type = ServiceContainer;
      using service_interface_type = Bean<Interface>::type;
      using service_type = resolve_dependency_t<service_interface_type, Bean>::type;

      constexpr service_type
      get(const service_container_type &container) const {
        static const auto instance = basic_service_factory_t<
                Bean, service_container_type,
                service_interface_type>::create(container);
        return instance;
      }
  };

  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, class Interface>
  struct basic_lifetime_manager_t<Bean, ServiceContainer, Interface,
                                  thread_local_t> {
      using service_container_type = ServiceContainer;
      using service_interface_type = Bean<Interface>::type;
      using service_type = resolve_dependency_t<service_interface_type, Bean>::type;

      constexpr service_type
      get(const service_container_type &container) const {
        static thread_local const auto instance = basic_service_factory_t<
                Bean, service_container_type,
                service_interface_type>::create(container);
        return instance;
      }
  };
}  // namespace di

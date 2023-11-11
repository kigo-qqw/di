export module di:service_factory;

import <concepts>;

import :fwd;
import :bean;
// import :service_container;
import :resolve_dependency;


export namespace di {
  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer, typename Interface>
    requires bean<Bean<Interface>>
  class basic_service_factory_t {
    public:
      using service_container_type = ServiceContainer;
      using service_type = resolve_dependency_t<Interface, Bean>::type;

      static constexpr service_type
      create([[maybe_unused]] const service_container_type &container)
        requires std::default_initializable<service_type>
      {
        return service_type();
      }
  };

  template <template <typename> typename Bean,
            basic_service_container<Bean> ServiceContainer,
            template <typename...> typename Interface, typename... Arguments>
    requires bean<Bean<Interface<Arguments...>>>
  class basic_service_factory_t<Bean, ServiceContainer,
                                Interface<Arguments...>> {
    public:
      using service_container_type = ServiceContainer;
      using service_type =
              resolve_dependency_t<Interface<Arguments...>, Bean>::type;

      static constexpr service_type
      create([[maybe_unused]] const service_container_type &container)
        requires std::constructible_from<
                service_type,
                decltype(container.template resolve<Arguments>())...>
      {
        return service_type(container.template resolve<Arguments>()...);
      }
  };

}  // namespace di

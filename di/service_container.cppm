export module di:service_container;

import <concepts>;
import <tuple>;

import :resolve_dependency;
import :bean;
import :fwd;
import :utils;
import :lifetime_manager;


export namespace di {
  template <template <typename> typename Bean, typename... Interfaces>
    requires(bean<Bean<Interfaces>> && ...)
  class basic_service_container_t {
    private:
      template <typename Interface>
      constexpr auto resolve_impl() const
              -> resolve_dependency_t<typename Bean<Interface>::type,
                                      Bean>::type {
        return std::get<basic_lifetime_manager_t<
                Bean, basic_service_container_t<Bean, Interfaces...>,
                Interface>>(lifetime_managers_)
                .get(*this);
      }

    public:
      template <typename Interface>
      constexpr auto resolve() const -> decltype(resolve_impl<Interface>()) {
        return resolve_impl<Interface>();
      }

    private:
      std::tuple<basic_lifetime_manager_t<
              Bean, basic_service_container_t<Bean, Interfaces...>,
              Interfaces>...>
              lifetime_managers_;
  };

  //  template <typename... Interfaces>
  //  using service_container_t = basic_service_container_t<bean_t,
  //  Interfaces...>;
  //
  //  template <typename T, template <typename> typename Bean>
  //  concept basic_service_container = true;  // TODO
  //
  //  template <typename T>
  //  concept service_container = basic_service_container<T, bean_t>;

  //  template <template <template <typename> typename, typename...> typename T,
  //            template <typename> typename Bean, typename Interface,
  //            typename... Interfaces>
  //  concept basic_service_container_resolve =
  //          requires(T<Bean, Interfaces...> container) {
  //            {
  //              container.template resolve<Interface>()
  //            } -> std::convertible_to<
  //                    typename resolve_dependency_t<Interface, Bean>::type>;
  //          };
  //
  //  template <template <template <typename> typename, typename...> typename T,
  //            typename Interface, typename... Interfaces>
  //  concept service_container_resolve =
  //          basic_service_container_resolve<T, bean_t, Interface,
  //          Interfaces...>;
}  // namespace di

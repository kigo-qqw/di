export module di:bean;

import :lifetime;


export namespace di {
  template <typename Interface> struct bean_t {
      using type = Interface;
      using lifetime_type = transient_t;
  };

  template <typename T>
  concept bean = requires {
    typename T::type;
    typename T::lifetime_type;

    lifetime<typename T::lifetime_type>;
  };
}  // namespace di

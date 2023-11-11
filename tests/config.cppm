export module config;

import <iostream>;

import di;


struct foo_t {
    foo_t() {
      std::cout << "foo_t()" << std::endl;
    }
    foo_t(foo_t const &) {
      std::cout << "foo_t(const foo_t &)" << std::endl;
    }
    foo_t(foo_t &&) noexcept {
      std::cout << "foo_t(foo_t &&)" << std::endl;
    }
    ~foo_t() {
      std::cout << "~foo_t()" << std::endl;
    }
};

export struct foo_i {};

export template <> struct di::bean_t<foo_i> {
    using type = foo_t;
    using lifetime_type = di::transient_t;
};

template <class Foo = foo_i> struct bar_t {
    explicit bar_t(Foo foo) : foo_{std::move(foo)} {
      std::cout << "bar_t(Foo)" << std::endl;
    }
    bar_t(bar_t const &other) : foo_{other.foo_} {
      std::cout << "bar_t(const bar_t &)" << std::endl;
    }
    bar_t(bar_t &&other) noexcept : foo_{std::move(other.foo_)} {
      std::cout << "bar_t(bar_t &&)" << std::endl;
    }
    ~bar_t() {
      std::cout << "~bar_t()" << std::endl;
    }
    Foo foo_;
};

export struct bar_i {};

export template <> struct di::bean_t<bar_i> {
    using type = bar_t<>;
    using lifetime_type = di::transient_t;
};

export using container_t = di::service_container_t<foo_i, bar_i>;

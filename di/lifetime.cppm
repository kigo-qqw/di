export module di:lifetime;

import :utils;


export namespace di {
  struct transient_t {};
  struct scoped_t {};
  struct singleton_t {};
  struct thread_local_t {};

  template <typename T>
  concept lifetime =
          utils::one_of<T, transient_t, scoped_t, singleton_t, thread_local_t>;
}  // namespace di

TODO List
=========
- [x] Add usage of std::mutex to support multi-threaded environments.

- [x] Allow multiple Appenders for each Logger.

- [x] Add __dllexport() macro to support dynamic linking (\*.dll).

- [x] Make it possible to change settings during runtime.

- [ ] Allow configuration via config file.

- [ ] Add some performance tests.

- [x] Add general class to provide formatting.

- [ ] Add high performance clock tick time.

- [ ] Add utility prefix-tree impl to provide faster access on loggers by prefix-search
      (e.g. change log level for all loggers beginning with "core.gui").

- [ ] Add cmake.config/find.cmake script to make it easier using the library.

# Benchmarks

## Submit your benchmark

You can commit your own benchmark with a pull-request on GitHub for this file.

## Existing benchmarks

All benchmarks are created with the *mtperformance_example* binary
which is shipped as an example project with HumbleLogging source.

```
Usage:
  binary [thread-count] [events-per-thread] [appender] [formatted:bool(0,1)]
```

The result gets more accurate by increasing the number of log-events.
You should use a minimum of 20000000 log-events per thread to get a good
result. The benchmarks on this page always use the *null* appender.
The number of threads should equal the number of real-cores of your
machine (no Hyperthreading cores).
E.g:

```bash
mtperformance_example.exe 4 20000000 null 0
```

### Release 4.0.0

Environment | Events | Threads | Duration (ms) | Throughput (events/second)
------------|--------|---------|---------------|---------------------------
Windows 11 Pro 22H2 22621.963 / VS 2022 / AMD Ryzen 7 5800X @ 3.80 GHz | 80000000 | 4 | 10619 | 7533666

### Release 3.0.1

Environment | Events | Threads | Duration (ms) | Throughput (events/second)
------------|--------|---------|---------------|---------------------------
Windows 8.1 Update 2 32 bit / VC 2013 Community / Core i7 3770K @ 3.50 GHz | 80000000 | 4 | 10619 | 7533666

### Release 1.0

Environment | Events | Threads | Duration (ms) | Throughput (events/second)
------------|--------|---------|---------------|---------------------------
Windows 8.1 Update 1 32 bit / VC 2012 / Core i7 3770K @ 3.50 GHz | 80000000 | 4 | 12468 | 6416426
Windows 8.1 Update 2 32 bit / VC 2013 Community / Core i7 920 @ 2.67 GHz | 80000000 | 4 | 18645 | 4290695
Windows 8.1 Update 2 64 bit / VC 2013 Community / Core i7 920 @ 2.67 GHz | 80000000 | 4 | 15320 | 5221932

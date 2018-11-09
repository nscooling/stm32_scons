Arm GCC Scons build

```
$ scons
```
To Build with FeabhOS
```
$ scons --rtos-build
```

There are separate SConstruct files for RTOS and non-RTOS builds
```
$ scons -f SConstruct.no-rtos
$ scons -f SConstruct.rtos
```

To build with Docker:
```
docker run --rm -v $(pwd):/usr/project feabhas/gcc-arm-scons:1.0
```

To test with QEMU:
```
$ docker run --rm -v $(pwd):/usr/project feabhas/qemu:2.8.0 qemu-system-gnuarmeclipse --mcu STM32F407VG --nographic --image build/debug/C-501.elf --semihosting-config enable=on,target=native
```
or
```
$ docker run --rm -v $(pwd):/usr/project feabhas/qemu:2.8.0 qemu-system-gnuarmeclipse --verbose --board STM32F4-Discovery --mcu STM32F407VG -d unimp,guest_errors --nographic --image build/debug/C-501.elf --semihosting-config enable=on,target=native
```

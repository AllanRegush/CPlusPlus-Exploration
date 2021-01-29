# Hello, World Linux kernel module

Make sure you have your kernel configured. You might need to install kernel development packages or install another kernel.
Such as `zypper in kernel-default-devel`

#### To Compile
`make`

#### To run
`sudo insmod hello.ko`

#### Checking your work

To see if module loaded run `lsmod`
should see `hello` in list of modules
```
$ lsmod | grep hello
hello                  16384  
```

check `tail /var/log/syslog/` or `journalctl` or `dmesg`

Example
```
[1222447.706888] Hello, World
[1222482.666160] Goodbye :)
```

#### To Unload
`sudo rmmod hello`

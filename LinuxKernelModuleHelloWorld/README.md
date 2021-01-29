# Hello, World Linux kernel module

Make sure you have your kernel configured. You might need to install kernel development packages or install another kernel.
Such as `zypper in kernel-default-devel`

#### To Compile
`make`

#### To run
`sudo insmod hello.ko`

#### To check if it worked

check `tail /var/log/syslog/` or `journalctl`

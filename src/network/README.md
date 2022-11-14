# Linux Network

## 127.0.0.1

127 开头的都属于回环地址，是 IPV4 的特殊地址，人为规定的。

```c
/* Address to loopback in software to local host.  */
#define    INADDR_LOOPBACK     0x7f000001  /* 127.0.0.1   */
```

![.](https://mmbiz.qpic.cn/mmbiz_png/FmVWPHrDdnkr3eLdxxIK0eujAOibyGS3al814qA9PQccVHwXclglX7Vm2Ro1aN6rj2Mzom2WOPB9Nh5tOiaZeshg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

IPV4 的地址是 32 位的，大概只有 40 亿+，已经无法满足现在的需求。

### IPV6

IPv6 的地址是 128 位的，大概是 2 的 128 次方 ≈10 的 38 次方。

![.](https://mmbiz.qpic.cn/mmbiz_png/FmVWPHrDdnkr3eLdxxIK0eujAOibyGS3aDribNWH3v6rqs4qJgTpg835BwUW1Eg2NwJBjEbNMhQpjeSfdlN1gSjw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

IPV6 就以 16 位为一组，每组之间用 : 号隔开。如果全是 0，那么可以省略不写。

```sh
ping 127.0.0.1
ping6 ::1
```

执行 ping 0.0.0.0 ，是会失败的，因为它在 IPV4 中表示的是无效的目标地址。

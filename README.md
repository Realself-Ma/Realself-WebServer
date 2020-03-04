# [:earth_asia:Http WebServer](https://github.com/Realself-Ma/Realself-WebServer)
> 可以解析http GET POST请求

### 项目目的

在学习完《Linux多线程服务端编程-使用muduo C++网络库》后，想着仿照muduo做一个简单的服务器，之前做过TCP的后台服务器，这次就想做一个Web的后台服务器，不用管客户端的事情，只要有浏览器就可以当做客户端来访问服务器。

在项目中，涵盖以下知识点和概念

- HTTP1.1协议
- 非阻塞IO+IO复用+线程池
- RAII锁机制
- 智能指针的使用
- 多线程下临界资源的判别及处理
- 优雅关闭连接

### 测试页

- [http://121.36.20.9:2020/](http://121.36.20.9:2020/)

### 开发环境

- 服务器操作系统：Ubuntu 18.04
- 编译器：gcc 7.4.0

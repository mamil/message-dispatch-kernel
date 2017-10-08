# message-dispatch-kernel
仿MFC的消息分发内核 ，仅供新手学习

里面还有蛮多的问题，以后慢慢填坑。

现在基本的消息分发已经完成，可以自己写消息类，处理函数

## 基本原理
### Service
在Service里面保存一个map，是各个command的唯一标识（我这里用了command的类名，也可以用虚表），和对应的处理函数。

这样每次kernel里面把消息分发过来的时候，就可以根据command的标识来找到对应的处理函数，调用函数来处理这个command。

### Kernel
kernel里面基本原理类似。

里面存了map，是各个command对应的service，这样受到command的时候，就可以找到对应的service，把command给那个service处理。
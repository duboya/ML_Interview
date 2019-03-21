在前面两篇文章中，我们用一个框架梳理了各大优化算法，并且指出了以Adam为代表的自适应学习率优化算法可能存在的问题。那么，在实践中我们应该如何选择呢？



本文介绍Adam+SGD的组合策略，以及一些比较有用的tricks.



回顾前文：

[Adam那么棒，为什么还对SGD念念不忘 (1)](https://zhuanlan.zhihu.com/p/32230623)

[Adam那么棒，为什么还对SGD念念不忘 (2)](https://zhuanlan.zhihu.com/p/32262540)



## 不同优化算法的核心差异：下降方向



从第一篇的框架中我们看到，不同优化算法最核心的区别，就是第三步所执行的下降方向：

![\eta_t = (\alpha/ \sqrt{V_t} ) \cdot m_t ](https://www.zhihu.com/equation?tex=%5Ceta_t+%3D+%28%5Calpha%2F+%5Csqrt%7BV_t%7D+%29+%5Ccdot+m_t+)

这个式子中，前半部分是实际的学习率（也即下降步长），后半部分是实际的下降方向。SGD算法的下降方向就是该位置的梯度方向的反方向，带一阶动量的SGD的下降方向则是该位置的一阶动量方向。自适应学习率类优化算法为每个参数设定了不同的学习率，在不同维度上设定不同步长，因此其下降方向是缩放过（scaled）的一阶动量方向。





**由于下降方向的不同，可能导致不同算法到达完全不同的局部最优点。**[An empirical analysis of the optimization of deep network loss surfaces](http://link.zhihu.com/?target=https%3A//arxiv.org/abs/1612.04010) 这篇论文中做了一个有趣的实验，他们把目标函数值和相应的参数形成的超平面映射到一个三维空间，这样我们可以直观地看到各个算法是如何寻找超平面上的最低点的。

![img](https://pic1.zhimg.com/80/v2-39c5df1673d9831e9bc10c9e9c4f12a8_hd.jpg)

上图是论文的实验结果，横纵坐标表示降维后的特征空间，区域颜色则表示目标函数值的变化，红色是高原，蓝色是洼地。他们做的是配对儿实验，让两个算法从同一个初始化位置开始出发，然后对比优化的结果。可以看到，几乎任何两个算法都走到了不同的洼地，他们中间往往隔了一个很高的高原。这就说明，**不同算法在高原的时候，选择了不同的下降方向。**





## Adam+SGD 组合策略



正是在每一个十字路口的选择，决定了你的归宿。如果上天能够给我一个再来一次的机会，我会对那个女孩子说：SGD！



不同优化算法的优劣依然是未有定论的争议话题。据我在paper和各类社区看到的反馈，主流的观点认为：Adam等自适应学习率算法对于稀疏数据具有优势，且收敛速度很快；但精调参数的SGD（+Momentum）往往能够取得更好的最终结果。



那么我们就会想到，可不可以把这两者结合起来，**先用Adam快速下降，再用SGD调优**，一举两得？思路简单，但里面有两个技术问题：



1. **什么时候切换优化算法？**——如果切换太晚，Adam可能已经跑到自己的盆地里去了，SGD再怎么好也跑不出来了。
2. **切换算法以后用什么样的学习率？**——Adam用的是自适应学习率，依赖的是二阶动量的累积，SGD接着训练的话，用什么样的学习率？



上一篇中提到的论文 [Improving Generalization Performance by Switching from Adam to SGD](http://link.zhihu.com/?target=http%3A//arxiv.org/abs/1712.07628) 提出了解决这两个问题的思路。



**首先来看第二个问题**，**切换之后用什么样的学习率**。Adam的下降方向是

![\eta_t^{Adam} = (\alpha/ \sqrt{V_t} ) \cdot m_t](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BAdam%7D+%3D+%28%5Calpha%2F+%5Csqrt%7BV_t%7D+%29+%5Ccdot+m_t)

而SGD的下降方向是

![\eta_t^{SGD} = \alpha^{SGD}\cdot g_t](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BSGD%7D+%3D+%5Calpha%5E%7BSGD%7D%5Ccdot+g_t).

![\eta_t^{SGD}](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BSGD%7D) 必定可以分解为 ![\eta_t^{Adam}](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BAdam%7D) 所在方向及其正交方向上的两个方向之和，那么其在 ![\eta_t^{Adam}](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BAdam%7D) 方向上的投影就意味着SGD在Adam算法决定的下降方向上前进的距离，而在 ![\eta_t^{Adam}](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BAdam%7D) 的正交方向上的投影是 SGD 在自己选择的修正方向上前进的距离。



![img](https://pic2.zhimg.com/80/v2-8d01c2572fa44781af05e91bdf6da729_hd.jpg)图片来自原文，这里p为Adam下降方向，g为梯度方向，r为SGD的学习率。

如果SGD要走完Adam未走完的路，那就首先要接过Adam的大旗——沿着 ![\eta_t^{Adam}](https://www.zhihu.com/equation?tex=%5Ceta_t%5E%7BAdam%7D) 方向走一步，而后在沿着其正交方向走相应的一步。



这样我们就知道该如何确定SGD的步长（学习率）了——**SGD在Adam下降方向上的正交投影，应该正好等于Adam的下降方向（含步长）**。也即：

![proj_{\eta_t^{SGD}} =\eta_t^{Adam}](https://www.zhihu.com/equation?tex=proj_%7B%5Ceta_t%5E%7BSGD%7D%7D+%3D%5Ceta_t%5E%7BAdam%7D)

解这个方程，我们就可以得到接续进行SGD的学习率：

![\alpha_t^{SGD}=( (\eta_t^{Adam})^T \eta_t^{Adam})/( (\eta_t^{Adam})^Tg_t)](https://www.zhihu.com/equation?tex=%5Calpha_t%5E%7BSGD%7D%3D%28+%28%5Ceta_t%5E%7BAdam%7D%29%5ET+%5Ceta_t%5E%7BAdam%7D%29%2F%28+%28%5Ceta_t%5E%7BAdam%7D%29%5ETg_t%29)

为了减少噪声影响，作者使用移动平均值来修正对学习率的估计：

![\lambda_t^{SGD}=\beta_2\cdot\lambda_{t-1}^{SGD} + (1-\beta_2) \cdot\alpha_t^{SGD}](https://www.zhihu.com/equation?tex=%5Clambda_t%5E%7BSGD%7D%3D%5Cbeta_2%5Ccdot%5Clambda_%7Bt-1%7D%5E%7BSGD%7D+%2B+%281-%5Cbeta_2%29+%5Ccdot%5Calpha_t%5E%7BSGD%7D)

![\tilde{\lambda}_t^{SGD}=\lambda_t^{SGD}/(1-\beta_2^t)](https://www.zhihu.com/equation?tex=%5Ctilde%7B%5Clambda%7D_t%5E%7BSGD%7D%3D%5Clambda_t%5E%7BSGD%7D%2F%281-%5Cbeta_2%5Et%29)

这里直接复用了Adam的 ![ \beta_2](https://www.zhihu.com/equation?tex=+%5Cbeta_2) 参数。



**然后来看第一个问题，何时进行算法的切换**。

作者的回答也很简单，那就是当 SGD的相应学习率的移动平均值基本不变的时候，即：

![|\tilde{\lambda}_t^{SGD} - \alpha_t^{SGD}|<\epsilon](https://www.zhihu.com/equation?tex=%7C%5Ctilde%7B%5Clambda%7D_t%5E%7BSGD%7D+-+%5Calpha_t%5E%7BSGD%7D%7C%3C%5Cepsilon) . 每次迭代玩都计算一下SGD接班人的相应学习率，如果发现基本稳定了，那就SGD以 ![\tilde{\lambda}_t^{SGD}](https://www.zhihu.com/equation?tex=%5Ctilde%7B%5Clambda%7D_t%5E%7BSGD%7D) 为学习率接班前进。



## 优化算法的常用tricks



最后，分享一些在优化算法的选择和使用方面的一些tricks。



1. **首先，各大算法孰优孰劣并无定论。**如果是刚入门，**优先考虑****SGD+Nesterov Momentum**或者**Adam.**（[Standford 231n](http://link.zhihu.com/?target=http%3A//cs231n.github.io/neural-networks-3/) : *The two recommended updates to use are either SGD+Nesterov Momentum or Adam*）
2. **选择你熟悉的算法**——这样你可以更加熟练地利用你的经验进行调参。
3. **充分了解你的数据**——如果模型是非常稀疏的，那么优先考虑自适应学习率的算法。
4. **根据你的需求来选择**——在模型设计实验过程中，要快速验证新模型的效果，可以先用Adam进行快速实验优化；在模型上线或者结果发布前，可以用精调的SGD进行模型的极致优化。
5. **先用小数据集进行实验。**有论文研究指出，随机梯度下降算法的收敛速度和数据集的大小的关系不大。（*The mathematics of stochastic gradient descent are amazingly independent of the training set size. In particular, the asymptotic SGD convergence rates are independent from the sample size. [2]*）因此可以先用一个具有代表性的小数据集进行实验，测试一下最好的优化算法，并通过参数搜索来寻找最优的训练参数。
6. **考虑不同算法的组合。**先用Adam进行快速下降，而后再换到SGD进行充分的调优。切换策略可以参考本文介绍的方法。
7. **数据集一定要充分的打散（shuffle）。**这样在使用自适应学习率算法的时候，可以避免某些特征集中出现，而导致的有时学习过度、有时学习不足，使得下降方向出现偏差的问题。
8. 训练过程中**持续监控训练数据和验证数据**上的目标函数值以及精度或者AUC等指标的变化情况。对训练数据的监控是要保证模型进行了充分的训练——下降方向正确，且学习率足够高；对验证数据的监控是为了避免出现过拟合。
9. **制定一个合适的学习率衰减策略。**可以使用定期衰减策略，比如每过多少个epoch就衰减一次；或者利用精度或者AUC等性能指标来监控，当测试集上的指标不变或者下跌时，就降低学习率。



这里只列举出一些在优化算法方面的trick，如有遗漏，欢迎各位知友在评论中补充，我将持续更新此文。提前致谢！



神经网络模型的设计和训练要复杂得多，initialization, activation, normalization 等等无不是四两拨千斤，这些方面的技巧我再慢慢写，欢迎关注我的知乎专栏和微信公众号（Julius-AI），一起交流学习。



参考文献：

[1] [CS231n Convolutional Neural Networks for Visual Recognition](http://link.zhihu.com/?target=http%3A//cs231n.github.io/neural-networks-3/)

[2] [Stochastic Gradient Descent Tricks.](http://link.zhihu.com/?target=https%3A//www.microsoft.com/en-us/research/wp-content/uploads/2012/01/tricks-2012.pdf)

[3] [Efficient BackProp](http://link.zhihu.com/?target=http%3A//yann.lecun.com/exdb/publis/pdf/lecun-98b.pdf)



本系列目录：

[Adam那么棒，为什么还对SGD念念不忘 (1) —— 一个框架看懂优化算法](https://zhuanlan.zhihu.com/p/32230623)

[Adam那么棒，为什么还对SGD念念不忘 (2)—— Adam的两宗罪](https://zhuanlan.zhihu.com/p/32262540)

[Adam那么棒，为什么还对SGD念念不忘 (3)—— 优化算法的选择与使用策略](https://zhuanlan.zhihu.com/p/32338983)



————————————————————

行有所思，学有所得，陋鄙之言，请多指教。

欢迎关注我的微信公众号 Julius-AI
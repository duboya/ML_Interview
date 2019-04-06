# 「Stacking」与「神经网络」

作者：微调

\* 本文偏理论，需要较多背景知识，请选择性阅读。

\* 文末提供了一些开放的研究方向，欢迎讨论与合作研(灌)究(水)。

------

**Stacking是Kaggle比赛中常见的集成学习框架**。一般来说，就是训练一个多层(一般是两层，本文中默认两层)的学习器结构，第一层(也叫学习层)用n个不同的分类器(或者参数不同的模型)将得到预测结果合并为新的特征集，并作为下一层分类器的输入。一个简单的示意图如下：

![img](https://pic1.zhimg.com/80/v2-3c432375cfc93bf378c2394972d0ef2c_hd.jpg)图片来源：https://www.quora.com/What-is-stacking-in-machine-learning

给出一个比较简单的例子：你想要预测明天是否会下雨，并有相关的气象数据。你训练了十个分类器比如逻辑回归，svm，knn等。你通过stacking的方法在第一层将这十个分类器的结果作为了第二层训练器的数据，通过第二层的输出训练器得到了最终预测结果。Stacking本身不是文章的讨论重点，因此建议读者可以阅读以下科普文章了解什么是stacking：

- [Kris Zhao：【干货】比赛后期大招之stacking技术分享](https://zhuanlan.zhihu.com/p/27493821)
- [峰峰：详解Stacking](https://zhuanlan.zhihu.com/p/29418981)
- [Stacked Regression的详细步骤和使用注意事项](https://link.zhihu.com/?target=http%3A//www.cnblogs.com/yucaodie/p/7044737.html)

**本文的核心观点是提供一种对于stacking的理解，即与神经网络对照来看。**当然，在[阿萨姆：为什么做stacking之后，准确率反而降低了？](https://www.zhihu.com/question/59769987/answer/269367049)中我已经说过stacking不是万能药，但往往很有效。通过与神经网络的对比，读者可以从另一个角度加深对stacking的理解。

**1. Stacking是一种表示学习(representation learning)**

表示学习指的是模型从原始数据中自动抽取有效特征的过程，比如深度学习就是一种表示学习的方法。关于表示学习的理解可以参考：[阿萨姆：人工智能（AI）是如何处理数据的？](https://www.zhihu.com/question/264417928/answer/283087276)

原始数据可能是杂乱无规律的。在stacking中，通过第一层的多个学习器后，有效的特征被学习出来了。从这个角度来看，stacking的第一层就是特征抽取的过程。在[1]的研究中，上排是未经stacking的数据，下排是经过stacking(多个无监督学习算法)处理后的数据，我们显著的发现红色和蓝色的数据在下排中分界更为明显。** 数据经过了压缩处理*。这个小例子说明了，**有效的stacking可以对原始数据中的特征有效的抽取**。

![img](https://pic1.zhimg.com/80/v2-92ff83c7c6acc0dea6bc53ffe815e8bc_hd.jpg)

**2. Stacking和神经网络从某种角度看有异曲同工之妙，神经网络也可以被看作是集成学习**

承接上一点，stacking的学习能力主要来自于对于特征的表示学习，这和神经网络的思路是一致的。这也是为什么我说“第一层”，“最后一层”。

而且神经网络也可以被看做是一种集成学习，主要取决于不同神经元、层对于不同特征的理解不同。从浅层到深层可以理解为一种从具体到抽象的过程。

Stacking中的第一层可以等价于神经网络中的前 n-1层，而stacking中的最终分类层可以类比于神经网络中最后的输出层。不同点在于，stacking中不同的分类器通过异质来体现对于不同特征的表示，神经网络是从同质到异质的过程且有分布式表示的特点(distributed representation)。Stacking中应该也有分布式的特点，主要表现在多个分类器的结果并非完全不同，而有很大程度的相同之处。

但同时这也提出了一个挑战，多个分类器应该尽量在保证效果好的同时尽量不同，stacking集成学习框架的对于基分类器的两个要求：

- 差异化(diversity)要大
- 准确性(accuracy)要高

**3. Stacking的输出层为什么用逻辑回归？**

如果你看懂了上面的两点，你应该可以理解stacking的有效性主要来自于特征抽取。**而表示学习中，如影随形的问题就是过拟合，试回想深度学习中的过拟合问题。**

在[3]中，周志华教授也重申了stacking在使用中的过拟合问题。因为第二层的特征来自于对于第一层数据的学习，那么第二层数据中的特征中不该包括原始特征，**以降低过拟合的风险**。举例：

- 第二层数据特征：仅包含学习到的特征
- 第二层数据特征：包含学习到的特征 + 原始特征

另一个例子是，stacking中一般都用交叉验证来避免过拟合，足可见这个问题的严重性。

为了降低过拟合的问题，第二层分类器应该是较为简单的分类器，广义线性如逻辑回归是一个不错的选择。**在特征提取的过程中，我们已经使用了复杂的非线性变换，因此在输出层不需要复杂的分类器**。这一点可以对比神经网络的激活函数或者输出层，都是很简单的函数，一点原因就是不需要复杂函数并能控制复杂度。

因此，stacking的输出层不需要过分复杂的函数，用逻辑回归还有额外的好处：

- 配合L1正则化还可以进一步防止过拟合
- 配合L1正则化还可以选择有效特征，从第一层的学习器中删除不必要的分类器，节省运算开销。
- 逻辑回归的输出结果还可被理解为概率

**4. Stacking是否需要多层？第一层的分类器是否越多越好？**

通过以上分析，stacking的表示学习不是来自于多层堆叠的效果，而是来自于不同学习器对于不同特征的学习能力，并有效的结合起来。一般来看，2层对于stacking足够了。多层的stacking会面临更加复杂的过拟合问题，且收益有限。

第一层分类器的数量对于特征学习应该有所帮助，经验角度看越多的基分类器越好。即使有所重复和高依赖性，我们依然可以通过特征选择来处理，问题不大。

这提出了另一个stacking与深度学习不同之处:

- stacking需要宽度，深度学习不需要
- 深度学习需要深度，而stacking不需要

但stacking和深度学习都共同需要面临：

- 黑箱与解释问题
- 严重的过拟合问题

如果stacking和深度学习都是一种表示学习，如何选择？我认为和样本量有关：

- 小样本上深度学习不具备可操作性，stacking或许可以
- 大样本上stacking的效率理当不如深度学习，这也是一种取舍

**5. 现阶段我正在研究的问题：**

- stacking中用逻辑回归，或者MLR一直是被证明比较好的方法 [4]。但跳出这个框架，新的对于过拟合较为鲁棒的boosting模型是否可以替代？
- stacking中的过拟合是因为在第一层使用监督学习，与第二层的监督学习目标相同。如果第一层使用无监督学习，那么是否可以有效的降低过拟合问题？同理，是否可以用stacking的框架做半监督学习？
- stacking往往面临很大的运算开销，在预测时需要运行多个模型，是否可以用更有效的特征选择来控制运算开销。比如仅选择分类器x，y，z构成的特征空间？
- stacking中第二层的特征空间由第一层分类器决定，如何有效的压缩这个特征空间？

Stacking相关的文献和研究都还有限，得到广泛关注的有[2, 4, 5, 6, 7, 8]。**本文提供了一个不同的角度，属于个人观点，请批判的看。欢迎评论、私信、以及合作研(灌)究(水)。**

------

[1] Micenkova, B., McWilliams, B. and Assent, I., 2014. Learning Representations for Outlier Detection on a Budget. arXiv preprint. *arXiv preprint arXiv:1507.08104*.

[2] Seewald, A.K., 2002, July. How to make stacking better and faster while also taking care of an unknown weakness. In *Proceedings of the nineteenth international conference on machine learning* (pp. 554-561). Morgan Kaufmann Publishers Inc.

[3] Zhou, Z.H., 2012. *Ensemble methods: foundations and algorithms*. CRC press.

[4] Džeroski, S. and Ženko, B., 2004. Is combining classifiers with stacking better than selecting the best one?. *Machine learning*, *54*(3), pp.255-273.

[5] Van der Laan, M.J., Polley, E.C. and Hubbard, A.E., 2007. Super learner. *Statistical applications in genetics and molecular biology*, *6*(1).

[6] Wolpert, D.H., 1992. Stacked generalization. *Neural networks*, *5*(2), pp.241-259.

[7] Breiman, L., 1996. Stacked regressions. *Machine learning*, *24*(1), pp.49-64.

[8] Ting, K.M. and Witten, I.H., 1999. Issues in stacked generalization. *J. Artif. Intell. Res.(JAIR)*, *10*, pp.271-289.
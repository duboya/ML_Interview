最近被面试问到如何评估 embedding 质量，之前没怎么思考过这个问题，现收集整理如下：

## 1. 前言

虽然目前word embedding的应用已经十分火热，但对其评价问题，即衡量该word embedding是好是坏，并没有非常完美的方案。实际上，评价其质量最好的方式就是以word embedding对于具体任务的实际收益（上线效果）为评价标准。但是若能找到一个合适的方案，可以在上线前对得到的word embedding进行评估，那将具有很大的意义。
本文并没有提出什么新的方案（以后若有会更新），只是总结了目前为止的一些评价方法，并附上自己的一些思考，读者有任何想法可与我交流，欢迎各位批评指正。
若读者对文中涉及的word embedding，word2vec，item2vec等概念不熟悉，建议先到网上查找相关资料。之后我会专门写一篇关于这些概念的文章，但本文对这些概念不做解释，也会附上一些链接，请读者自查。

## 2. 主要方法

此节分为word2vec和item2vec两个部分，前者有较多的比较成熟的度量方案，后者则基本上没有统一认可的方案。对此，试图借鉴word2vec的一些方法能够设计出对于item2vec向量的度量方法。

### 2.1 word2vec

**1. Relatedness**
Relatedness:task(相似度评价指标，看看空间距离近的词，跟人的直觉是否一致)目前大部分工作都是依赖wordsim353等(wordsim353相关内容参考网址：<http://alfonseca.org/eng/research/wordsim353.html> ) 词汇相似性数据集进行相关性度量，并以之作为评价word embedding质量的标准。这种评价方式对数据集的大小、领域等属性很敏感。
示例如图：![1.png](http://www.rongzijing.win/usr/uploads/2018/05/1825205024.png)

> Google官网：<https://code.google.com/archive/p/word2vec/> 中给出的方案也是这个意思：
> How to measure quality of the word vectors
> Several factors influence the quality of the word vectors: *amount and quality of the training data* size of the vectors * training algorithm
> The quality of the vectors is crucial for any application. However, exploration of different hyper-parameter settings for complex tasks might be too time demanding. Thus, we designed simple test sets that can be used to quickly evaluate the word vector quality.
> For the word relation test set described in [1], see ./demo-word-accuracy.sh, for the phrase relation test set described in [2], see ./demo-phrase-accuracy.sh. Note that the accuracy depends heavily on the amount of the training data; our best results for both test sets are above 70% accuracy with coverage close to 100%.
> 其中 [1] [3]分别是Word2Vec 作者Tomas Mikolov 的三篇代表作的前两篇（见参考文献），其中也提到了：Note that the accuracy depends heavily on the amount of the training data，即数据集的大小会对结果产生较大影响。

**2. Analogy**
Analogy:task也就是著名 A - B = C - D 词汇类比任务（所谓的 analogy task，如 king – queen = man – woman），示例如图：
![2.jpg](http://www.rongzijing.win/usr/uploads/2018/05/2118460399.jpg)

**3. Categorization**
Categorization分类 看词在每个分类中的概率：
![5.png](http://www.rongzijing.win/usr/uploads/2018/05/3611446030.png)

而对于文本也可采用 document classification task：

这是一种通过使用词向量来计算文本向量（可以被用来进行文本分类的工作）的方法，为了得到文本向量，task通常采用了一种很简单的方法:取文本中所有词的词向量的平均值来代表该文本的文本向量，进而通过文本分类的准确度来反向评价训练出的词向量的质量。

**4. 聚类算法（可视化）**
例如 kmeans 聚类，查看聚类分布效果 。若向量维度偏高，则对向量进行降维，并可视化。如使用pca，t-sne等降维可视化方法，包括google的tensorboard（<http://projector.tensorflow.org/>），python的matplotlib等工具，从而得到词向量分布。

### 2.2 Item2vec

关于 Item2Vec 请参考论文：Item2Vec: Neural Item Embedding for Collaborative Filtering (论文下载链接：<https://arxiv.org/vc/arxiv/papers/1603/1603.04259v2.pdf>)

Item2vec 应用到推荐场景中，把 item 视为 word，将用户的行为序列视为一个集合，item间的共现为正样本，并按照item的频率分布进行负样本采样。

目前绝大部分的资料都是针对 word2vec 的，很多方案（上述方法 1, 2, 3）并不能迁移到 item2vec。比如第 1 个方案，对于 word2vec，目前存在 wordsim353 作为评价 word embedding 质量的标准，但是 item2vec 并没有此类标准。而对于2, 3来说，用户行为序列并不太容易用来 Analogy 和 Categorization。

目前想到和收集到的解决方式如下：

1. 从item2vec得到的词向量中随机抽出一部分进行人工判别可靠性。即人工判断各维度item与标签item的相关程度，判断是否合理，序列是否相关。

2. 然后word2vec的方法4,5可以借鉴，对item2vec得到的词向量进行聚类或者可视化，查看其聚类效果如何。这样就从局部（抽样人工筛查）和整体（聚类效果）两方面进行了评估，虽然不够准确，但是也算是一种思路。

   > 事实上，个人认为这种方式相对更容易操作一些，例如，对于用户商品 ID 特征，是否训练之后对应的 embedding 可以聚类到一起（可通过 TensorBoard 的 t-sne 进行可视化展现），从可视化结果中应该可以得到一个较好的展现。

3. 还有一种方案，就是用大量数据训练出一个相对新的类似于 wordsim353 标准的 item 类型的标准，之后进行相似度度量。但是实现难度主要在训练数据的质量和时效性方面，对于商品类还好，但对于新闻类这种更新率极快的 item 类型，时效性是很大问题。

4. 当然，也可通过观察实际效果来定，也可采用替换 embedding 对应值为初试值来看预测效果是否有显著下降；

## 3. 总结与思考

如果脱离实际任务或者具体情形，很难去评价不同的 word embedding 哪个更好。还是那句话，评价其质量最好的方式就是以 word embedding 对于具体任务的实际收益（上线效果）为评价标准。至于对其直接的评估方法，若要找到一个合适的方案，除了要考虑具体的适用领域和场景，还有很长的路要走。

### 参考文献

[1] Tomas Mikolov, Kai Chen, Greg Corrado, and Jeffrey Dean. Efficient Estimation of Word Representations in Vector Space. In Proceedings of Workshop at ICLR, 2013.
[2] Tomas Mikolov, Ilya Sutskever, Kai Chen, Greg Corrado, and Jeffrey Dean. Distributed Representations of Words and Phrases and their Compositionality. In Proceedings of NIPS, 2013.
[3] Tomas Mikolov, Wen-tau Yih, and Geoffrey Zweig. Linguistic Regularities in Continuous Space Word Representations. In Proceedings of NAACL HLT, 2013.
[4] https://wenku.baidu.com/view/5f8055a709a1284ac850ad02de80d4d8d15a01e6.html

[5] http://www.rongzijing.win/index.php/archives/6/

[6] [word2vec算出的词向量怎么衡量好坏？](https://www.zhihu.com/question/37489735/answer/73314819)
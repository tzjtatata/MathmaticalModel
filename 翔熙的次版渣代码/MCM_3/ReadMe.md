数据结构说明
==========================

读入三个文件格式依照MCM_2中所述，输出两个文件dataOrganize.txt和referOrganize.txt。

前一个文件按照数据块来组织数据，每一个数据块包含BUF_LEN条数据项，每条数据项由两个int型数据recordOrder
和kMerPosition组成。

后一个文件按照次序记录了kMerOrder数据，每一个数据项的位置对应了dataOrganize数据块的位置。

进行查找时，先将kMer转换为对应的kMerOrder，然后在referOrganize中找到对应数据块的位置，以此在dataOrganize
中打开对应的数据块，输出其中的非-1数据，即为所求的数据。

下一个中间层需要解决二分查找的问题。现在referOrganize已经是高度有序的了，但是要想实现有效的二分查找，
还需要进一步的reduce。

目标的数据结构是一个长度为kMerNumber的数组，用排列的顺序标志着对应的kMerOrder值，每一个元素储存的内容
是其对应的kMerOrder在referOrganize出现的次数；另需一个同样长度的数组，用以记录在referOrganize中出现的
位置。当然，这原本可以通过一个二维数组来解决，但是考虑到二维数组在文件读写时的困难，用两个一维数组应当
会更为快速。

就酱。
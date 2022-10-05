1、git status/diff命令中怎样以彩色显示改动状态
git config --global color.ui false
git config --global color.ui true

从github上下载代码: git clone + 网址 （SSH ：git@github.com:yangchaofeng/gittest.git） --depth=1
git clone git@github.com:yangchaofeng/gittest.git --depth=1
将本地提交更新到github上
git push

----------- 2019.06.27  init  workspace

从github上更新: git pull
在github上查看gittest某个提交修改：a5fc8638556295ae9f575f222ee66c383cc4e735
https://github.com/yangchaofeng/gittest/commit/a5fc8638556295ae9f575f222ee66c383cc4e735
----------- 20210109 

2、new ubuntu set

sudo apt-get install git
git config --global user.name yangchaofeng
git config --global user.email 471552006@qq.com

生成SSH密钥过程：
1.查看是否已经有了ssh密钥：vim  /home/yangchaofeng/.ssh/id_ed25519.pub
如果没有密钥则使用下面命令生成
2.生存密钥：
ssh-keygen -t ed25519
按3个回车，密码为空。
3、vim  /home/yangchaofeng/.ssh/id_ed25519.pub
4).打开GitHubn账户，打开设置找到SSH Keys
----------- 20221005 

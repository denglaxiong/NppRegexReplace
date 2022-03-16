# NppRegexReplace notepad++插件
* 应用于notepad++的正则替换，使用一个或者多个正则替换对文本进行处理，  
* 计划设计一个可视化窗口进行正则表达式的编辑，  
* 插件所有的功能保存在一个配置文件中regexconfig.txt，程序启动时自动读取，编辑时对配置文件进行操作  
* 配置文件的使用自定义的格式，也可以用文本编辑工具进行编辑,如 名称>>;>>替换前;;<;;替换后<<;<<替换前;;<;;替换后<<;<<替换前;;<;;替换后<<;<<替换前;;<;;替换后
* 注：之前一直使用录制宏，但是正则表达式不支持编辑，比较麻烦，所以设计一个插件


# 计划设计这样的页面

## 页面-功能页 -'按编辑功能跳转到编辑页面-按下应用按钮进行内容匹配与替换

 描述  | 功能  
 ---- | ----- 
 转换为双引号包含  | 编辑 应用
 按照逗号换行  | 编辑 应用
 转换为sql建表语句  | 编辑 应用 
## 页面-编辑页

##### 名称   转换为双引号包含   
##### 正则列表-'根据列表中的正则依次替换-按调试自己定位到ctrl+h的页面并且把内容带上
 
 替换前的匹配  |  替换后的显示  | 操作
 ---- | ----- | -----
 (.+)\t(.+)\t(.+)  |  \2\3\1 | 调试
 ,  | \r\n | 调试
 
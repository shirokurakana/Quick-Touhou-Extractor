# Quick Touhou Extractor

能够方便快速地解包东方dat文件和anm文件并按照原有目录结构进行编排的工具。若需要其他功能（比如替换文件，打包等）请使用thtkgui。

目前绝赞开xia发xie中（咕咕咕）

为了缩写是QTE而取的这个名字。

## 自动模式

放在游戏根目录可以自动识别游戏dat文件并解包（限妖妖梦及以后的STG作），而红魔乡可以通过手动模式解包，红魔乡的自动解包还在做（咕咕咕）

## 手动模式

此模式通过手动指定dat文件绝对路径和游戏版本的方式，可以比自动模式支持更多的游戏，也支持在非游戏根目录解包。

若在当前目录没有找到符合`thxx.dat`形式的dat文件（比如汉化版、红魔乡或某些小数点作的dat文件），或者当前目录根本没有dat文件（比如你随便找了个地方运行），就会自动进入手动模式。

此时，直接将要解包的dat文件拖进来即可，会自动填入该dat文件的绝对路径。当然你要是闲得慌想自己手动输入我也管不了你（

然后，紧跟着输入`>`号可以手动指定游戏版本（否则自动识别游戏版本）。注意一定要是紧跟着输入，我没写额外的东西去处理其他输入。路径也不要带空格，我同样也没处理这个。

例子：

<code>C:\th10\th10c.dat>10</code>

上面这个例子中，指定游戏版本为10（即风神录），这样即可不改文件名就解压汉化版dat。自动识别的话考虑做，但不一定做出来（懒

需要注意的是，指定风神录以前的游戏版本时不需要加前导的`0`，比如要解包红魔乡请指定游戏版本为`6`而不是`06`。

QTE能够识别的游戏版本编号和支持信息可以查看下表。

QTE编号 | 游戏名 | 自动模式 | 手动模式 |备注
:-: | :-: | :-: | :-: | :-: 
| 1 | 东方灵异传 ～ Highly Responsive to Prayers. | 否 | 未知 | 没试过 |
| 2 | 东方封魔录 ～ the Story of Eastern Wonderland. | 否 | 未知 | 没试过 |
| 3 | 东方梦时空 ～ Phantasmagoria of Dim. Dream. |否 | 未知 | 没试过 |
| 4 | 东方幻想乡 ～ Lotus Land Story. | 否 | 未知 | 没试过 |
| 5 | 东方怪绮谈 ～ Mystic Square. | 否 | 未知 | 没试过 |
| 6 | 东方红魔乡 ～ the Embodiment of Scarlet Devil. |计划| 可 | 有六个dat文件 |
| 7 | 东方妖妖梦 ～ Perfect Cherry Blossom. | 可 | 可 | 不支持汉化版 |
| 8 | 东方永夜抄 ～ Imperishable Night. | 可 | 可 | 不支持汉化版 |
| 9 | 东方花映塚 ～ Phantasmagoria of Flower View. | 可 | 可 | 不支持汉化版 |
| 95 | 东方文花帖 ～ Shoot the Bullet. | 可 | 可 |  |
| 10 | 东方风神录 ～ Mountain of Faith. | 可 | 可 |  |
| 103 | 黄昏酒場～Uwabami Breakers～. | 计划 | 可 |  |
| 105 | 东方绯想天 ～ Scarlet Weather Rhapsody. | 计划 | 计划 |  |
| 11 | 东方地灵殿 ～ Subterranean Animism. | 可 | 可 |  |
| 12 | 东方星莲船 ～ Undefined Fantastic Object. | 可 | 可 |  |
| 123 | 东方非想天则 ～ 追寻特大型人偶之谜 | 计划 | 计划 |  |
| 125 | Double Spoiler ～ 东方文花帖 | 计划 | 可 |  |
| 128 | 妖精大战争 ～ 东方三月精 | 计划 | 可 |  |
| 13 | 东方神灵庙 ～ Ten Desires. | 可 | 可 |  |
| 14 | 东方辉针城 ～ Double Dealing Character. | 可 | 可 |  |
| 143 | 弹幕天邪鬼 ～ Impossible Spell Card. | 计划 | 可 |  |
| 15 | 东方绀珠传 ～ Legacy of Lunatic Kingdom. | 可 | 可 |  |
| 16 | 东方天空璋 ～ Hidden Star in Four Seasons. | 可 | 可 |  |
| 165 | 秘封噩梦日记　～ Violet Detector. | 计划 | 可 |  |
| 17 | 东方鬼形兽　～ Wily Beast and Weakest Creature. | 可 | 可 |  |
| 175(推测) | 东方刚欲异闻～被水淹没的沉愁地狱 | 否 | 否 |  |


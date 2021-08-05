============================================================

      Memory Dump Module for DEVHOOK 2006.7.21版
                                       ねこかぶ
============================================================



DEVHOOKでメモリをファイルに保存することが出来るようになる追加モジュールです。
このモジュールを導入する事で、DEVHOOKで動作するゲーム、XMBで
0x08800000～0x09FFFFFFまでのユーザーメモリを保存する事が出来ます

●導入方法
付属の「nkthread.prx」、「memdump.prx」ファイルをメモリースティックの
「ms0:/dh/kb」フォルダ内にコピーし、次のファイルを書き換えます。

	・ゲーム中にスクリーンショットを使う場合
	ms0:/dh/150/flash0/kd/pspbtcnf_game.txt
	ms0:/dh/200/flash0/kd/pspbtcnf_game.txt
	ms0:/dh/250/flash0/kd/pspbtcnf_game.txt
	ms0:/dh/260/flash0/kd/pspbtcnf_game.txt
	ms0:/dh/271/flash0/kd/pspbtcnf_game.txt
	ms0:/dh/150F/flash0/kd/pspbtcnf_game.txt

	・XMB中にスクリーンショットを使う場合
	ms0:/dh/150/flash0/kd/pspbtcnf.txt
	ms0:/dh/200/flash0/kd/pspbtcnf.txt
	ms0:/dh/250/flash0/kd/pspbtcnf.txt
	ms0:/dh/260/flash0/kd/pspbtcnf.txt
	ms0:/dh/271/flash0/kd/pspbtcnf.txt
	ms0:/dh/150F/flash0/kd/pspbtcnf.txt

それぞれのテキストファイル内の「ms0:/dh/kd/devhook.prx」の次の行に
「ms0:/dh/kd/nkthread.prx」、「ms0:/dh/kd/memdump.prx」を追加してください。
※必ずnkthread.prxを先に追加すること

例：
～
/kd/isofs.prx
ms0:/dh/kd/devhook.prx
ms0:/dh/kd/nkthread.prx  #この行を追加する
ms0:/dh/kd/memdump.prx   #この行を追加する
/kd/wlan.prx



●使い方
メモリを保存したいところでRボタン+Vol+を押してください。


　※メモリースティックに書き込み中は電源を切ったりしないでください


●不具合
モノによってはスクリーンショット保存中もゲームが進行してしまい、
うまく画像を保存できない事があります


●更新履歴
2006/7/6	・公開
2006/7/21	・nkthread.prxファイルを追加


●ソースコードについて
ソースコードの改変は自由です。
ただし改変したバイナリを配布する場合は
そのソースコードも配布すること作者は望みます。


●＝＝＝　免責事項　＝＝＝
　このソフトウェアによるいかなる損害にも作者は一切責任を負いません。
　各自の責任において使用してください。


ねこかぶ
HP     :http://nekokabu.s7.xrea.com/
mail   :nekokabu@gmail.com

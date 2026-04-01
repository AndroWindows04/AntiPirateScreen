Set Sound = CreateObject("WMPlayer.OCX.7")
Sound.URL = "pst8mp3.mp3"
Sound.settings.setMode "loop", True

Sound.Controls.play

do while Sound.currentmedia.duration = 0
    wscript.sleep 100
loop

do
    wscript.sleep 1000
loop

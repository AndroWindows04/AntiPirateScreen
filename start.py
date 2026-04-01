import cv2
import os
import subprocess

video_path = 'pst8mp4.mp4'
audio_script = 'pirmus.vbs'
window_name = 'Anti Piracy Screen'

if os.path.exists(audio_script):
    os.startfile(audio_script)

cap = cv2.VideoCapture(video_path)

if not cap.isOpened():
    exit()

cv2.namedWindow(window_name, cv2.WND_PROP_FULLSCREEN)
cv2.setWindowProperty(window_name, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

while True:
    ret, frame = cap.read()
    
    if not ret:
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
        continue

    rect = cv2.getWindowImageRect(window_name)
    if rect[2] > 0 and rect[3] > 0:
        frame = cv2.resize(frame, (rect[2], rect[3]))

    cv2.imshow(window_name, frame)

    if cv2.waitKey(25) & 0xFF == 27 or cv2.getWindowProperty(window_name, cv2.WND_PROP_VISIBLE) < 1:
        break

cap.release()
cv2.destroyAllWindows()
subprocess.run("taskkill /F /IM wscript.exe /T", shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

import math
import socket
import cv2
from ultralytics import YOLO
import torch
import time

# Check GPU availability
print("CUDA available:", torch.cuda.is_available())
print("Using device:", torch.cuda.get_device_name(0) if torch.cuda.is_available() else "CPU")


UDP_IP = "192.168.4.1"
UDP_PORT = 21

YAW_ANGLE = 30
PITCH_ANGLE = 50
MAX_MISSED_FRAMES_CLOSE = 20
MAX_MISSED_FRAMES_VOICELINE = 8

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

missed_frames = 0
is_open = False
lost_target_debouce = False

# Initialize YOLOv8 model (use your trained or pre-trained model)
model = YOLO('yolov8n.pt')  # lightweight for real-time
model.to('cuda')  # force GPU, optional

# ESP32-CAM MJPEG stream URL
stream_url = "http://192.168.4.10:81/stream"

cap = cv2.VideoCapture(stream_url)
if not cap.isOpened():
    print("Error: Cannot open ESP32-CAM stream.")
    exit()

prev_time = time.time()

last_target_position = (0, 0)

def lerp(a, b, t):
    return a + (b - a) * t

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        continue

    # YOLO inference
    results = model(frame, verbose=False)[0]

    # Filter for 'person' class (COCO class id 0 in YOLOv8)
    person_detections = results.boxes

    persons = []

    #filter to persons
    for result in person_detections:
        cls_id = int(result.cls[0].item())
        if cls_id == 0:
            persons.append(result)

    if len(persons) > 0:
        missed_frames = 0
        if not is_open:
            is_open = True
            sock.sendto(bytearray("Aopen".encode()), (UDP_IP, UDP_PORT))
            sock.sendto(bytearray("voiceline_found".encode()), (UDP_IP, UDP_PORT))
            sock.sendto(bytearray("ArevOn".encode()), (UDP_IP, UDP_PORT))
            sock.sendto(bytearray("AfireOn".encode()), (UDP_IP, UDP_PORT))
    else:
        missed_frames += 1

        if missed_frames >= MAX_MISSED_FRAMES_VOICELINE and not lost_target_debouce:
            sock.sendto(bytearray("voiceline_lost".encode()), (UDP_IP, UDP_PORT))

        if missed_frames > MAX_MISSED_FRAMES_CLOSE and is_open:
            is_open = False
            sock.sendto(bytearray("Aclose".encode()), (UDP_IP, UDP_PORT))
            sock.sendto(bytearray("ArevOff".encode()), (UDP_IP, UDP_PORT))
            sock.sendto(bytearray("voiceline_close".encode()), (UDP_IP, UDP_PORT))

    lowest_dist_indx = None
    lowest_dist = 123123132
    i = 0
    #see which one is closer to last position
    for box in person_detections:
        xyxy = box.xyxy[0].tolist()
        x1, y1, x2, y2 = map(int, xyxy)
        cx = (x1 + x2) // 2
        cy = (y1 + y2) // 2

        dist = math.sqrt((cx - last_target_position[0]) ** 2 + (cy - last_target_position[1]) ** 2)
        if dist < lowest_dist:
            lowest_dist_indx = i
            lowest_dist = dist
        i = i + 1

    i = 0
    for box in persons:
        cls_id = int(box.cls[0].item())
        if True:  # person class in COCO
            xyxy = box.xyxy[0].tolist()
            x1, y1, x2, y2 = map(int, xyxy)
            cx = (x1 + x2) // 2
            cy = (y1 + y2) // 2

            # Draw bounding box and center
            if i == lowest_dist_indx:
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 255), 2)
                last_target_position = (cx, cy)
                #print(f"Target person: ({cx}, {cy})")

                posX = lerp(last_target_position[0], cx, 0.3)
                posY = lerp(last_target_position[1], cy, 0.3)

                relPosX = posX / frame.shape[1]
                relPosY = posY / frame.shape[0]

                yaw = lerp(YAW_ANGLE, -YAW_ANGLE, relPosX)
                pitch = lerp(PITCH_ANGLE, -PITCH_ANGLE, relPosY) + 10

                msg = f"AP{pitch:.2f}Y{yaw:.2f}"
                sock.sendto(msg.encode(), (UDP_IP, UDP_PORT))


            else:
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

            cv2.circle(frame, (cx, cy), 5, (0, 0, 255), -1)
            cv2.putText(frame, f"({cx},{cy})", (cx + 10, cy),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
        i = i + 1

    # FPS calculation
    curr_time = time.time()
    fps = 1 / (curr_time - prev_time)
    prev_time = curr_time
    cv2.putText(frame, f"FPS: {fps:.2f}", (10, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 255), 2)

    # Display the frame
    cv2.imshow("YOLOv8 Person Tracking", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
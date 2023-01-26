# Line Follower-Robotics

### Description
The final project for the Introduction to Robotics course. The task was to build a robot using the received kit, that can follow a curved black line and finish a course in a relatively short time. This was a team project and I teamed up with my colleague, Andrei Dina, to form Team Andre. His repo: https://github.com/AndreiConstantinDina/LineFollower

### How it works
The first stage is the auto-calibration stage. The robot moves from left to right repeatedely so that the sensor can calibrate to follow the line. Then, the robot is centered on the line and starts to move along it. The error from the sensors is mapped to the [-75, 75] interval and the PID values are: kp = 20, ki = 0, kd = 5. The robot finished the course from the video in 28,253 seconds.

### Components used
- 1x Arduino Uno
- 1x LiPo battery
- 2x Wheels
- 1x QTR-8A reflectance sensor
- 2x DC motors
- 1x L293D motor driver
- 1x Medium Breadboard
- 1x Chassis

### Pictures of the setup
<p float = "left">
    <img src = "https://user-images.githubusercontent.com/34553466/213790870-2a804666-dff5-43f1-ad84-7afbe32d9219.jpeg" height = "450" width = 45%>
    <img src = "https://user-images.githubusercontent.com/34553466/213791251-e5cfe95e-2b80-4476-bd65-dcf9d1ceac72.jpeg" height = "450" width = 45%>
</p>

### Link for the showcase video
https://youtube.com/shorts/x_sb7Z2Y2aE?feature=share

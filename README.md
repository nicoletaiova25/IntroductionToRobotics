# IntroductionToRobotics

Laboratory assignments for the Robotics Introduction Course, completed during the third year of study at the Faculty of Mathematics and Computer Science, University of Bucharest. Each assignment has got included the instructions we had to follow, implementation guidelines, code samples, and also is accompanied by image files.

# What you can find here
1. Homework - RGB LED [✴️](#hmwk1) 
2. Homework - ELEVATOR [✴️](#hmwk2) 
3. Homework - 7-SEGMENT DISPLAY DRAWING [✴️](#hmwk3) 
4. Homework - STOPWATCH TIMER [✴️](#hmwk4)
5. Homework - MENU [✴️](#hmwk5)
6. Homework - 8x8 LED MATRIX GAME [✴️](#hmwk6)
7. Homework - GAME CHECKPOINT [✴️](#hmwk7)

<a name="hmwk1"></a>
## Homework-1 RGB

<details>
<p><b>Assignment details 🗞️</b></p> 
This assignment focuses on controlling each channel (Red, Green, and Blue) of  an  RGB  LED  using  individual  potentiometers.   By  the  end  of  this  task, we  will  gain  experience  in  interfacing  potentiometers  with  the  Arduino  and controlling RGB LEDs based on the analog readings. <br>
The main components we will use specifically for this task are an RGB led, 3 potentiometers, resistors and as many wires as needed. <br>

<b>Components:</b>
1. RGB LED 💡
2. 3 potentiometers 🟣
3. 3 220Ω resistors
4. wires as needed

<p><b>Electrical scheme</b></p>

<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/ce070ffa-b757-4207-b943-45da46103d37.png" width="400" height="500">

<br>
<p><b>Setup of the assignment 📷 </b></p>

<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/9b02530c-3707-450b-912f-c404d49e19cd.jpg" width="400" height="500">

<br>

 ### 🎞️ A video showcasting functionality of assignment: [Video](https://youtu.be/9celDTJKHCI)

 
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/Homework1-RGB.ino)
 
</details>

<a name="hmwk2"></a>
## Homework-2 Elevator
<details>
<p><b>Assignment details 🗞️</b></p> 
This assignment focuses on simulating a 3-floor elevator control system using LEDs, buttons, and a buzzer. <br>
Components 🧰:<br> 💡 4 LEDs, 3 for the floors and 1 for the operational state of the elevator <br>
               🔳 3 buttons, to call the elevator to the desired floor <br>
               🔉 1 buzzer, to let the individual know when the elevator has arrived, the doors are opening and closing <br>
               🪛 as many wires and resistors as needed <br>
<br>
 <b>Tehnical Task</b>
 <details>Design a control system that simulates a 3-floor elevator using the Arduino platform. Here are the specific requirements:<br>
     • LED Indicators: Each of the 3 LEDs should represent one of the 3 floors. The LED corresponding to the current floor should light up.
Additionally, another LED should represent the elevator’s operational state. It should blink when the elevator is moving and remain static when stationary. <br>
     • Buttons: Implement 3 buttons that represent the call buttons from the3 floors. When pressed, the elevator should simulate movement towardsthe floor after a short interval (2-3 seconds). <br>
     • Buzzer: The buzzer should sound briefly during the following scenarios: <br>
                    – Elevator arriving at the desired floor (something resembling a ”cling”). <br>
                    – Elevator doors closing and movement (pro tip: split them into 2 different sounds) <br>
     • State Change & Timers: If the elevator is already at the desired floor, pressing the button for that floor should have no effect. Otherwise, after a button press, the elevator should ”wait for the doors to close” and then ”move” to the corresponding floor. If the elevator is in movement, it should either do nothing or it should stack its decision (get to the first programmed floor, open the doors, wait, close them and then go to the next desired floor). <br>
    • Debounce: Remember to implement debounce for the buttons to avoid unintentional repeated button presses.</details>
<br>
<p><b>Setup of the assignment 📷 </b></p>

<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/0e9abe97-24fb-41d3-8fbf-baefbb4b64d0.jpg" width="400" height="500">

<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/eb3093d3-a9a3-4971-b545-1cdf62830541.jpg" width="400" height="500">

<br>

 ### 🎞️ A video showcasting functionality of assignment: [Video](https://youtube.com/shorts/g3ytp2m51iY?feature=share)

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/homework2_elevator.ino)
 
</details>

<a name="hmwk3"></a>
## Homework-3 7 Segemnt Display Drawing

<details>
<p><b>Assignment details 🗞️</b></p> 
 <br>
This assingment requires using the joystick to control the position ofthe segment and ”drawing” on the display. The movement between segments should be natural, meaning they should jump from the current position only to neighbors, but without passing through ”walls”.
<b>Requirements</b><br>
The initial position should be on the DP. The current position always blinks (irrespective of the fact that the segment is on or off). Use the joystick to move from one position to neighbors (see table for corresponding movement). Short pressing the button toggles the segment state from ON to OFF or from OFF to ON. Long pressing the button resets the entire display by turning all the segments OFF and moving the current position to the decimal point.

 ![image](https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/d6dbb440-0643-4a47-8250-c6fb169df43b)



<br>
<p><b>Setup of the assignment 📷 </b></p>

<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/3e532aed-b1af-44e3-9ed3-c1b9fa0574dc.jpg" width="400" height="500">


<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/a34ed096-ab1a-4e5f-ac67-ffc2bad21598.jpg" width="400" height="500">


<br>

 ### 🎞️ A video showcasting functionality of assignment: [Video](https://youtube.com/shorts/xklG7r3SEkc?feature=share)

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/homework3_7segmentDisplay.ino)
 
</details>

<a name="hmwk4"></a>
## Homework4 - Stopwatch Timer

<details>
<p><b>Assignment details 🗞️</b></p> 
<br>
Using the 4 digit 7 segment display and 3 buttons, this assigment requires implementing a stopwatch timer that counts in 10ths of a second and has a save lap functionality (similar to most basic stopwatch functions on most phones).<br>
Neccessary:  The starting value of the 4 digit 7 segment display shouldbe ”000.0”. The buttons should have the following functionalities:<br>
– Button 1: Start / pause.<br>
– Button 2: Reset (if in pause mode). Reset saved laps (if in lap viewing mode).<br>
– Button 3: Save lap (if in counting mode), cycle through last saved laps (up to 4 laps).<br><br>
<b>Rules of the workflow:</b><br>
1. Display shows ”000.0”. When pressing the Start button, the timer should start.<br>
2. During timer counter, each time you press the lap button, you should save that timer’s value in memory (not persistent, it is OK to be deleted upon reset), up to 4 laps (or more if you want); pressing the 5th time should override the 1st saved one. If you press the reset button while timer works, nothing happens. If you press the pause button, the timer stops. <br>
3. In Pause Mode, the lap flag button doesn’t work anymore. Pressing the reset button resets you to 000.0. <br>
4. After reset, you can now press the flag buttons to cycle through the lap times. Each time you press the flag button, it takes you to the next saved lap. Pressing it continuously should cycle you through it continuously. Pressing the reset button while in this state resets all your flags and takes the timer back to ”000.0”. <br><br>

<b>Components used</b> <br>
<li>
A 4-Digit 7-segment display 🖥️
3 buttons 🔲
Resistors and wires 🪛
A LED 💡
</li>
<br>
<br>
<p><b>Setup of the assignment 📷 </b></p>


<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/564de18a-074c-4d37-b686-74e0d2630dc4.jpg" width="400" height="500">

<br>

 ### 🎞️ A video showcasting functionality of assignment: [Video](https://youtu.be/IAuIUipVpyk?feature=shared)

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/Homework4_4Digit7SegmentDisplay.ino)
 
</details>


<a name="hmwk5"></a>
## Homework5 - Pseudo-Smart Environment Monitor and Logger

<details>
<p><b>Assignment details 🗞️</b></p> 
<br>
Develop a ”Smart Environment Monitor and Logger” using Arduino. This system will utilize various sensors to gather environmental data, log this data into EEPROM, and provide both visual feedback via an RGB LED and user interaction through a Serial Menu.<br>
Neccessary:  Menu Structure   <br><br>
1. Sensor Settings
   1.1 Sensors Sampling Interval.
   1.2 Ultrasonic Alert Threshold. 
   1.3 LDR Alert Threshold. 
   1.4 Back // Return to main menu
2. Reset Logger Data
   2.1 Yes.
   2.2 No.
3. System Status
   3.1 Current Sensor Readings
   3.2 Current Sensor Settings
   3.3 Display Logged Data
   3.2 Back
4. RGB LED Control
   4.1 Manual Color Control
   4.2 LED: Toggle Automatic ON/OFF
   4.3 Back
 
<b>Components used</b> <br>
Ultrasonic Sensor (HC-SR04) <br>
LDR (Light-Dependent Resistor) aka Photocell aka Photoresistor aka Light Sensor <br>
Resistors and wires 🪛<br>
RGB LED💡<br>
<br>
<br>
<p><b>Setup of the assignment 📷 </b></p>

<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/f1bbf503-8ffb-4514-8281-b3e641b7a740.jpg" width="400" height="500">

<br>

 ### 🎞️ A video showcasting functionality of assignment: 🌠
[The video to see the LED](https://youtube.com/shorts/BZy-QLIXm08?feature=share)
[The video to see the Menu](https://youtu.be/dfeNue5wNA4)
I couldn't make it work with pausing the video in between so 2 videos it is 🌠

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/Homework5_Menu.ino)
 
</details>

<a name="hmwk6"></a>
## Homework6 - Mini 8x8 LED Matrix Game

<details>
<p><b>Assignment details 🗞️</b></p> 
<br>
Develop a small game on the 8x8 matrix using Arduino. I chose to do a game Bomberman style, while following the requirements. Said requirements of the game must-have are: displaying three types of elements( a player that blinks slowly, a bomb that blinks faster than the player and walls that don't blink, but they are getting blown away. The walls are randomly generated on 50-75% of the matrix and the player is moving around with the help of the joystick and destroys the walls by planting bombs and detonating them.<br>
 
<b>Components used</b> <br>
Joystick 🕹️  <br>
8x8 LED Matrix  <br>
Resistors, capacitors and wires 🪛 <br>
LED💡 <br>
Buzzer 🔉

<br>
<b>Rules of the game: </b><br>
The matrix will firstly display a greeting image (HI!). To start the game user must press the joystick on time. The walls and the player will be displayed. Using the joystick, player can be moved around. To place the bomb, the joystick button needs to be pressed. To detonate the bomb the button is to be pressed again. Don't get startled by the sound, couldn't make it more bomb like, so it is what it is (also used a resistor of 10 ohms, the 110 one was suppressing the sound too much). 
After all the walls are destroyed user can see the score in the Serial Monitor, greetings image is again displayed and user can play again.
<br>
<p><b>Setup of the assignment 📷 </b></p>


<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/74fc714e-1d9c-413f-b2fc-f738a0b494ab.jpg" width="500" height="600">

<br>

 ### 🎞️ A video showcasting functionality of assignment: 🌠 [The video](https://youtu.be/A4NL7QThA4M) 🌠

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/Homework7MatrixGame.ino)
 
</details>

<a name="hmwk7"></a>
## Homework67 - Game Checkpoint

<details>
 <p>Mind it is still a work in progress, good things take time 🌠 </p>
<p><b>Assignment details 🗞️</b></p> 
<br>

 1. Intro Message - When powered, a greeting message is shown on the LCD
 2. Menu - user can scroll using joystick through the options displayed and choose what they want
    a. Start Game, the game is displayed on the matrix
    b. Settings, with 3 options itself, set intensity to LCD, set intensity to matrix, return to menu
    c. About - details, it displays the github of the creator (mine, obviously)
 3. End Message -  it displays 'GAME OVER' and the score, goes back to menu
 4. During Gameplay - it displays the lives of the player and the time since the game began

<br>
<p><b>Setup of the assignment 📷 </b></p>
<img src="https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/f20ebd7f-653d-462d-adec-c74624af9f11).jpg" width="500" height="600">
<br>

 ### 🎞️ A video showcasting functionality of assignment: 🌠 [The video](https://youtu.be/rWYjC3Rg-bc?feature=shared) 🌠

## 🤡 Sometimes it connects to the universe and receives messages: [Blooper](https://youtube.com/shorts/nsyfeJaSUA4?feature=shared)
 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/homeworkCheckpoint.ino)

</details>

# IntroductionToRobotics

Laboratory assignments for the Robotics Introduction Course, completed during the third year of study at the Faculty of Mathematics and Computer Science, University of Bucharest. Each assignment has got included the instructions we had to follow, implementation guidelines, code samples, and also is accompanied by image files.


# Homework-1 RGB

<details>
<p><b>Assignment details 🗞️</b></p> 
This assignment focuses on controlling each channel (Red, Green, and Blue) of  an  RGB  LED  using  individual  potentiometers.   By  the  end  of  this  task, we  will  gain  experience  in  interfacing  potentiometers  with  the  Arduino  and controlling RGB LEDs based on the analog readings. <br>
The main components we will use specifically for this task are an RGB led, 3 potentiometers, resistors and as many wires as needed. <br>


<br>
<p><b>Setup of the assignment 📷 </b></p>

![Imagine WhatsApp 2023-10-24 la 22 14 33_be484245](https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/92c4fabb-56cb-4d59-b390-5244c7a50cbb)

<br>

 ### 🎞️ A video showcasting functionality of assignment: [Video](https://youtu.be/oJoWSr1SlDc)

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/sketch_oct23b_copy_20231024232706.ino)
 
</details>

# Homework-2 Elevator
<details>
<p><b>Assignment details 🗞️</b></p> 
This assignment focuses on simulating a 3-floor elevator control system using LEDs, buttons, and a buzzer. <br>
Components 🧰: 💡 4 LEDs, 3 for the floors and 1 for the operational state of the elevator
               🔳 3 buttons, to call the elevator to the desired floor
               🔉 1 buzzer, to let the individual know when the elevator has arrived, the doors are opening and closing
               🪛 as many wires and resistors as needed
<br>
 <b>Tehnical Task</b>
 <details>Design a control system that simulates a 3-floor elevator using the Arduino platform. Here are the specific requirements:
     • LED Indicators: Each of the 3 LEDs should represent one of the 3 floors. The LED corresponding to the current floor should light up.
Additionally, another LED should represent the elevator’s operational state. It should blink when the elevator is moving and remain static when stationary.
     • Buttons: Implement 3 buttons that represent the call buttons from the3 floors. When pressed, the elevator should simulate movement towardsthe floor after a short interval (2-3 seconds).
     • Buzzer: The buzzer should sound briefly during the following scenarios:
                    – Elevator arriving at the desired floor (something resembling a ”cling”).
                    – Elevator doors closing and movement (pro tip: split them into 2 different sounds)
     • State Change & Timers: If the elevator is already at the desired floor, pressing the button for that floor should have no effect. Otherwise, after a button press, the elevator should ”wait for the doors to close” and then ”move” to the corresponding floor. If the elevator is in movement, it should either do nothing or it should stack its decision (get to the first
programmed floor, open the doors, wait, close them and then go to the next desired floor).
    • Debounce: Remember to implement debounce for the buttons to avoid unintentional repeated button presses.</details>
<br>
<p><b>Setup of the assignment 📷 </b></p>

![elv1](https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/0e9abe97-24fb-41d3-8fbf-baefbb4b64d0)

![elv2](https://github.com/nicoletaiova25/IntroductionToRobotics/assets/148574222/eb3093d3-a9a3-4971-b545-1cdf62830541)

<br>

 ### 🎞️ A video showcasting functionality of assignment: [Video](https://youtube.com/shorts/g3ytp2m51iY?feature=share)

 <br>
 
 ### 💻 The code: [You can find it here](https://github.com/nicoletaiova25/IntroductionToRobotics/blob/main/Homework/homework2_elevator.ino)
 
</details>



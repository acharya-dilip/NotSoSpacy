# NotSoSpacy
A Space themed Alarm Clock where you can see your live time
and set reminders to a future moment and when the time ticks
It warps space and when the time comes a transcending sound will play.
<br>
This Project was fully built on C, it used the GTK4 library for
the construction of the GUI. CSS to add some style to the GtkWidgets
and gstreamer to play the sounds in the given program.

# How to Use?
- Look at your local time and have it open while you're doing your work
- Click the "➕" on the titlebar to add an Alarm/Reminder.
- Click the "🔻🔺" buttons in the respective column of hours and
entries to increase or decrease them to your liking
- Once you've selected the time Set The Alarm for that given time
- The setted Alarm's will appear in the main window below the clock
- You can add as many Alarms as you like by repeating the steps
- If you mistakenly selected the wrong time that click the "❌" button
besides that Alarm to remove it
- Once the Alarm is triggered a sound will constantly play until you press the stop button
## Happy Clockin

# Demo Video
-

# Arch Linux Build Instructions
| Commands                                            | What They Do?                     |
|-----------------------------------------------------|-----------------------------------|
| git clone https://github.com/acharya/NotSoSpacy.git | Clones into the gh repo           |
| cd NotSoSpacy                                       | Navigates into the NotSoSpacy dir |
| chmod +x install.sh                                 | Makes the install.sh be runnable  |
| ./install.sh                                        | Runs the install Script           |
| cd build                                            | Navigates into the build dir      |
| ./NotSoSpacy                                        | Runs the Clock                    |

# What's inside the install.sh?
| Commands                  | What They Do?                |
|---------------------------|------------------------------|
| sudo pacman -S base-devel | Installs Base devel          |
| sudo pacman -S cmake      | Installs Cmake               |
| sudo pacman -S gtk        | Installs GTK                 |
| sudo pacman -S gstreamer  | Installs Gstreamer           |
| cd build                  | Navigates into the build dir |
| cmake ..                  | Checks for the Cmake file    |
|cmake --build .| Executes the build           |
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
- You can press the '🔇' button to turn on some chill space music
- You can press the '🎧️' button to stop the chill music
- Click the "➕" on the titlebar to add an Alarm/Reminder.
- Click the "🔻🔺" buttons in the respective column of hours and
entries to increase or decrease them to your liking
- Once you've selected the time Set The Alarm for that given time
- The setted Alarm's will appear in the main window below the clock
- You can add as many Alarms as you like by repeating the steps
- If you mistakenly selected the wrong time that click the "❌" button
besides that Alarm to remove it
- Once the Alarm is triggered a sound will constantly play until you press the stop button
- 
## Happy Clockin Sloppy Toppin

# Demo Video
- https://hc-cdn.hel1.your-objectstorage.com/s/v3/e23a95e461104701d418b80097a19b0dd369e73f_2025-11-17_20-08-27.mp4

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
| cmake --build .           | Executes the build           |

# Credit Goes To
- @HolyBasil => This Guy Spent like 7 and a half hours on a single day cuz 
he spent the rest of the week procasitnating and now he's doomed 
cause he hasn't gotten enough sleep and his schools starts in 2 hours
- contactme: acharyamission6@gmail.com
- I had fun building this but was dissapointed to see how it turned out alot sloppier than I thought

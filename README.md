# Air-Conditioner-Arduino

When your AC doesn't work.. make one with arduino!! Each room has it's own temperature sensors, 
ventilation shafts and fan controllers. It was the arduino's job to monitor the room temperature
and control the fans to achieve the desired temperature. Surprisingly it worked quite well. Considering
we simply used the window (thanks canadian winters!) as our cold air source.

I should mention the only reason this worked is the fact that we were living in a dorm. The furnace worked great!
So great that it would not turn off. Leaving our room at 30 degrees celsius while we slept. This is why the
project was able to achieve stable temperatures in both rooms. Heat from the furnace was battling with
the (controlled) cold air flow from our air conditioner connected to the window. Kind of sketchy I know,
we literally made ventilation shafts out of cardboard and hot glued them to the cieling. Hey it worked, who's laughing
now!

In the src/ folder you can view the simple code ran on the arduino to read temperature data, control fans between rooms, 
and display all information on an LCD screen. It was quite simple to code since arduino's language is just C with added functions. 
This was my first project with arduino. I used to be just a software guy but I have fallen in love with hardware. Recently I have
been designing circuits for custom lithium ion battery packs. Power is the most fundamental aspect to all electronics, which is 
why this is so interesting to me. It's just kind of funny that this air conditioner thing is what got me started with circuit design
and low level electronics.

*a project by Devon Crawford.*

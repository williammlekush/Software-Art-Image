# c1t13s

## Inspiration
A few years ago in the NYUAD Art Gallery Project Space, I approached a podium, its top slanted at about 30 degrees, displaying an artwork somewhere between hip and shoulder height. About 50cm x 50cm, the work consisted of many multi-colored lines stretching across the screen, some turning at 90 degree angles at different points on the screen. The illusion of depth drew me in, but I started to lose interest when I realized that there was little else. And then I saw one of the lines was moving, slowly drawing across the screen. Looking closer, I noticed that almost every visible line was drawing itself slowly, almost impercetibly across the screen. 

This work had been going on for months, slowly drawing more and more. That intention of using a computer-a tool we glorify for its speed-to create something slow resonated with me. It articulated those lives I'd witnessed which remain determinately slow in contexts trying to whisk them away into an instantaneous future. It reminded me of my own struggle to remain slow in the face institutions who demand me to move faster to make up for their lack of integrity. Today, I feel a little silly because something so much like the Windows Pipe screensaver nearly made me cry.

Of course, I don't remember the artist or the artwork, and I haven't been able to find it online. This was when I first was starting to feel pulled back into art after a six year hietus (thank you adolescent angst...), and I was relearning how to engage with art. I might have never even looked at the placard, or this could have been a dream or even an implanted memory, but I don't know if that really matters. It inspired my piece [_Futility_](https://williammlekush.com/futility/), which I've been gradually improving whenever I'm in a weird moment with no other projects to tackle, and it inspired this piece, _blu3pr1nts_.

## Description

_c1t13s_ started as an attempt to recreate that line piece, and the code here could be tweaked for such an installation with the addition of new lines being added at a set time interval. However, the still results that emerged at this stage satsified me. They are distinctly architectural and industrial, reminiscent of product designs and building layouts, or maybe the the everpresent speed that sits constantly at the edge of my peripheral senses whenever I'm in a bustling city. Each line might be a person, a building, or any other extension of the environment of a city which is drawn and drawn over as time goes on.

Under the hood, this sketch extends my Lines sketch to work for any number of individual lines, each with their own thicknesses, colors, speeds, and frequency of turning. It is not all purely random, however. I used the lerping technique from [my circles sketch](https://github.com/williammlekush/Software-Art-Image/main/01_threeCircles) to generate the colors, and the frequency of turns are related through noise to reduce the overall visual noise of the piece. The bounds of randomness also keep everything coherent, so the lines won't be too thin or too thick, the speeds too slow or too fast, etc. The stills chosen here selected for their visual coherence - the colors feel harmonious, the lines compelling, and the shapes layered upon each other.

![Example 1](https://github.com/williammlekush/Software-Art-Image/tree/main/03_assignment1/bin/data/screenshot23515.png)
![Example 2](https://github.com/williammlekush/Software-Art-Image/tree/main/03_assignment1/bin/data/screenshot62495.png)
![Example 3](https://github.com/williammlekush/Software-Art-Image/tree/main/03_assignment1/bin/data/screenshot56625.png)
![Example 4](https://github.com/williammlekush/Software-Art-Image/tree/main/03_assignment1/bin/data/screenshot38301.png)

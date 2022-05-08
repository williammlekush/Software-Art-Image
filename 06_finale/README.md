# c1rclez

## Concept

An extension of _lim f(x) = 0_, _C1rclez_ expands that reflection on endless decay to include growth and death. Rather than imply a zero point, the narrative implies an endless cycle from nothing, to bliss, through decay, and back to nothingness. This new loop leaves behind the illusory experience of fate, zooming out to view that experience in the context of the constant cycles in which it occurs. It moves toward a more comforting and empowering conception of time, one in which we are freed from the confines of linearity, which render meaning a constant. Within this cycle, meaning's apparent arbitrariness offers space to define for ourselves how to interpret and respond to our experiences, to redefine it how we wish.

## Program

_C1rclez_ corrects the technical issues with _lim f(x) = 0_. Each circle visualizes one band. The frequencies included in these bands expands and contracts depending on the overal distribution of frequencies, approximated through playbackspeed. With clarity on the relationship between the sound and the visuals, non-essential visuals were removed, improving the performance and allowing for the use of `ofPolyline` and `ofPath` to play with the shapes.

![screenshot_3](https://user-images.githubusercontent.com/56037586/167299600-b6fd6980-8373-4e28-8d09-d55bffba128f.png)

The program itself is essentially an instrument. A player can change the playback speed and volume of the audio. They can also add and remove visualized frequency bands. They can also create and modulate a 'glitch' in the instrument. The visual glitch works by spreading rearranging the x and y coordinates of the vertices in each circle's `ofPolyline`. Players can also create a subtle or obvious audio glitch, and they can modulate the noisiness of the obvious glitch. These glitches are achieved by moving the `ofSoundPlayer` position around the sound file with each frame. The subtle glitch moves it forward, skipping through the audio loop. Because the audio is so similar across the file, the glitch is noticeable but not obtrusive. The obvious glitch moves the position back and forth within a mutable range, creating more intense noise.

## Narrative

The narrative performance of the piece starts with an empty screen of some color. A circle appears. The audio fades in, and the circle responds to it. As the audio plays, the position of the circle and the color scheme change with the beats. New circles begin to appear. They are all growing faster than they decay. As they begin to grow past the edges of the screen, the audio speeds up and the circles shrink. They can no longer grow faster than they decay, and they are dancing around the screen. The audio glitches subtly and one of the circles glitches. As the audio continues, the circle movements lose sync with it, and it starts to glitch more frequently. The glitch eventually dominates the screen. All the circles are now glitching, and the audio is incredibly noisy. Caught in the glitch, the audio deepns and the grow. Everything goes black. Color fades in. A circle appears. The audio fades in, and the circle responds to it. . . 

[Watch a demo!](https://youtu.be/tWKgbNsKUlA)

This is just one of dozens of narratives that this instrument might be used to create.

## Reflection / Challenges

This time around, the development went much smoother. There was a big hurdle with figuring out how to manipulate the outline of the circles while retaining a filled shape. I ended up having to create `ofPolyline` outlines for each of the circles based on their `ofVec3f` parameters (z is used for radii) AND THEN copy all those vertices into an `ofPath` for each circle so the glitched shapes could be drawn filled. I'm sure there's a way to do this with only `ofPath`, but this solution works and took up enough of my time figuring out to justify finding a proper solution. The other glaring technical elephant is my reliance on parallel list structures. I'm sure there's a way to do this better using some sort of key-indexed data structure. But again, this worked for the execution of the idea and can always be refactored later. All the other challenges were minor, and I'm much happier with where this ended up, especially with the much more direct tie between the audio and the visuals.

![screenshot_1](https://user-images.githubusercontent.com/56037586/167299603-5eb843ee-0b20-43c4-acd5-52e38c5fc0ac.png)

Aside from these technical problems, I also faced some difficulty finding the right balance with the glitching. Too much of one type of disharmony (like ripping the circle outlines offscreen) and too many methods of disharmony (like glitching the colors too) made the piece far too overwhelming, distracting from the narrative. This was true both in the affordances of the code and in the performance. I had to ensure a the modulated parameters were adequately bounded and also be intentional about the way I accumulate and release tension with the performance.

![screenshot_2](https://user-images.githubusercontent.com/56037586/167299609-4ea5b51a-f7b9-4aa1-bacd-c121eec5673c.png)

What remains is to refactor and extend it. Adding some texture to the colors so they are not so flat would probably be the first next step. If the colors felt a little less algorithmic, the glitching might be less anticipated. Different methods of glitching would be fun to play with. I could experiment with different shapes, different methods of color generation, different narrative directions, and different sound loops as well. (I did throw a speech by Baldwin in there at one point and... it doesn't really work 😅.

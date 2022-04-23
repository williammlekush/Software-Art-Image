# lim f(x) = 0

## Concept

During Intro to Interactive Media in 2019, I built [a full-body instrument](https://github.com/williammlekush/Intro-to-IM/tree/master/finale_surveillance) that allowed people to modify a continuous loop of piano chords using their body. This piece remixes that (not-very-successful) effort to spark conversations about surveillance into a new conceptual context of endless loss. An oxymoronic sense that we are approaching a zero point, void, or end that will never arrive, this experience seems to arise in moments of extended crises, or when we mislabel symptomatic catastropes as acute crises. _lim f(x) = 0_ invites viewers to reflect on circles struggling to resist their own disappearance.

## Description

This project extends my three circles project in three ways. First, the code is now extendable to any number of circles, the circles sync with an audio experience, and viewers can modify the audiovisual expereince to create mini performances. Alogirthmically, the circles are visualizing the frequency bands and playback speed of the sound. Each circle watches a certain bandwidth, and increases its radius when the audio crosses that bandwidth (in proportion to its maximum radius). Otherwise, radii decrease slowly. Higher playback speeds result in smaller circles while slower playback speeds result in larger circles. The concentric circles effect occurs due to the way these bandwidths must be watched, and an improvement would be to achieve a one-to-one mapping of bandwidth-watched to circles-generated.

## Reflection / Challanges

The initial inspiration for this piece came from a video showed in class of an analog animation of different geometric visuals synced to classical music (I could not find the piece on the syllabus 😿). I initially wanted to achieve something similar, syncing the radii changes to the beats of the piano notes, but I could not figure out how to determine the exact frequencies these notes occur at, nor can I tell if or how the `bands` and `fft` represent the sound. Further research and experimentation would lead to something like this, but as I played around with the code, I started to enjoy the slower audiovisuals. It reminds me of looking out the back of a car or watching waves come in and out of the shore. Three circles was not enough though. It just felt...too empty. So I changed form arrays to vectors and made a bunch more circles. That gave me something worth sharing.

I'm satisfied with this sketch for what it is, but I still want the one-to-one sync. Maybe I'll keep playing and figure it out, but for now, I think I'll move on until the memory of my frustration passes. 😸

## Docs

[Video](https://youtu.be/JVMUuG2Ovd4)

![Experience Screenshot 1](https://github.com/williammlekush/Software-Art-Image/blob/main/05_assignment_2/bin/data/screenshot48063.png)
![Experience Screenshot 2](https://github.com/williammlekush/Software-Art-Image/blob/main/05_assignment_2/bin/data/screenshot49366.png)
![Experience Screenshot 3](https://github.com/williammlekush/Software-Art-Image/blob/main/05_assignment_2/bin/data/screenshot51286.png)
![Experience Screenshot 4](https://github.com/williammlekush/Software-Art-Image/blob/main/05_assignment_2/bin/data/screenshot68587.png)
![Experience Screenshot 5](https://github.com/williammlekush/Software-Art-Image/blob/main/05_assignment_2/bin/data/screenshot71046.png)


//Introduction

This is the first file in the prototype_engine project. This file is meant to outline what this project is about and the scope of what's to be accomplished. 
The engine isn't meant to be a multi-purpose engine, but an engine that meets the needs of a game revolving around the story of "Stairs to Hell". 
This story is a self-written one that revolves around a war between angels allied with humans against the gods. 
I want this game to be a role-playing, open world, combat-intensive type of game.

//3D

Now, first things first, this game must be in 3D. 
This will be the main challenge in writing this game, but once this behemoth of a requirement is out of the way, it'll mostly be smooth sailing. (Aside from debugging, that'll be hell). 
This 3D world must also accommodate for the fighting mechanics, which will be revolving around swords/melee weapons.

//Save states

The engine must also have a save state function too. 
This is imperative for a story-telling game, because no-one wants to play all the way back to where they last were, over and over again.
If this were to be broken in some way, it would completely break the players experience. 
So make sure that the file saving mechanic is memory safe and possibly power-outage resistant.

//Good graphic implementation

Next, the way that the graphics are implemented is IMPERATIVE. 
One of the main goals is to be able to have this game run on essentially all systems. 
Obviously, no game can run on every system, aside from doom, but having this being able to run on very low-budget systems will be a joy. 
Frankly, I am dissapointed with the state that gaming is in at the time of writing. 
Game developers prioritize resolution and graphics over performance, and this is at cost to gameplay and fun. 
To add on, it's also at cost to the consumer to buy a better graphics card to run the game. (Even with high end graphics cards, some AAA games can barely reach 60 FPS with DLSS!) I'd like for this not to even be a problem. 
Invisible to the consumer. 
You just click the start up button, and it works.

//Good UI

Further, the UI must be invisible too. 
The start up menu should just be intuitive and simple. 
Of course, I'd love to make it very bouncy. 
What I mean by bouncy is that the screen pops and maybe on start up, there is an animation. 
Similar to what Super Mario Galaxy has. 
I'd also like the settings in both the start up menu and gameplay settings to be detailed. 
If I can, I'd like the user to have complete control over the graphics and performance in their system. 
Along with that, some premade settings for managing that by the system itself would be default unless changed.

//Revolutionary controls

To address the controls, it must be something revolutionary, yet simple to the user. 
What I mean is something parallel to what Rainbow Six Siege did with their leaning mechanic. 
Almost no other FPS (First Person Shooter) has this very special mechanic in the way its been implemented that is as fun to use compared to others. 
And in a way, its another example of being invisible. Once the user plays for very little time, they begin to conform to the new controls very fast. 
Using them to gain an advantage over the enemy. 
How does this relate to the game engine? 
Throughout this outline, I will be outlining a lot of things that may seem unrelated, but will be integral when actually designing the engine. 
So, having a mechanic that differs far from many other games will definitely need to be outlined in order to use it in the engine. 
However, I have not thought of anything that could transform the user's experience beyond the keyboard and mouse. 
One idea I've had is instead of just tapping the left mouse button for attacking, and since this game's weapons are going to be swords, the user could instead slide their mouse to attack. 
This however begs a defeating question. How do you translate 2D movement (because the mouse moves along a 2D plane) to a 3D environment while also maintaining that the input feels like it's actually "inputting"? 
Or what if the user doesn't have a mouse? 
The main scope of the project was to make sure this was accessible to as many people as possible. 
Those are problems that must be tackled in the making of this prototype.

//Developer tools

Another aspect that is more for the ease of use by the user of this engine is that the developer must be able to easily see what's going on when the project begin to heavely abstract. 
When there's thousands of lines of code doing miscellaneous operations and manipulation, a simple yet effective log is to be made when unfortunate bugs arise. Further, it could maybe be made so well that even the user has access to such tools. 
Just like with someone's house getting broken into, the person's machine that has been infested by a bug is the first responder to it. 
It should be within their grasp to handle a problem that they see fit while residing in the bounds of software security. 
This is definitely more of an idea than an actual implementation to be made, but this could also be revolutionary compared to other games. 
It would also give detailed logs for problem solving. 
Say a game breaking bug happened on the user's end, they could then go to the internet and quickly figure it out with a simple error code and instruction from given source. 
Just by entering some commands or doing a sequence of instructions, they could fix their problem without the studio's intervention. 
In this case however, it would still be the upmost duty to get that bug report to do a more "federal" level fix.

//Audio

For me, audio is one of the most important things when making a game. 
If a game I play has very bad music, or the sound is just jarring, I immedietaly stop playing the game. 
Hopefully, while maintaining a small storage capacity, the audio can transcend user expectations. 
This engine must be able to access audio files instantaneously while making sure that it isn't taking too much computing power. 
Even if audio is a miniscule optimization to be made, it must also be compressed (not file wise) to a point that it balances usability and quality. 
Just like with the UI section, a setting for something like this could be made so the user can decide what is necessary.

//Storage

Just like with graphics, the effect that storage has had on most consumers is detremental to their experience. 
A term floating around a lot is called "bloat-ware", which is essentially an application that is terribly optimized to the point of taking up too much space. 
A good examplem of this is Call of Duty. 
When I used to own a PS5, I would have about 5 games downloaded (and that was liberal depending on what was downloaded). 
The one big game I would have is Call of Duty, which sits at about 200 GB including warzone and all of its other garbage, and then maybe some other small games. 
I'm personally not sure whether this is because their bloated game engine, which is most likely not the MAIN case, but a component, or their assets. 
Either of which, I plan to make this engine efficient on both ends. 
While file storage seems to be out of scope for what this project is about, it is absolutely tied to the efficiency. 
Would you rather have a seasoned artist copy over art from canvas to canvas, or a guy off the street who knows how to draw. 
This analogy obviously isn't the best, but whom ever is reading this should get the point. 
So, if this game could be kept, at most, under 10 GB, then I would be happy. 
This amount of storage is fast enough to download on most people's systems within a reasonable amount of time, while being a good barometer for what becomes bloat-ware.

//A note on DLSS

Should this game engine be even somewhat reliant on DLSS? 
God no! Back when Super Mario 64 was the best 3D game out, along with others, it had to work with 8 MB (yes, 8 megabytes!) of RAM! 
How could a game that was a 3D platformer, work with what seems like such a low amount of RAM? 
Well, it was thanks to the amazing minds at Nintendo that optimized the game to high hell. 
Everything from the textures, 3D computation, and memory management was amazingly implemented. 
Games like Cyberpunk that basically crutch on DLSS are, in my opinion, pitiful. 
That isn't to say that DLSS isn't a technology to be used at all, but as the saying goes, "With great power, comes great responsibility".

//Screen resolution (size)

I would prefer if the game engine relied on the user being in fullscreen. 
I wanted to add this note because I feel like no one on god's earth likes playing games while being able to see their background. 
Perhaps I'm wrong, but I would like to specifically design this engine with the user being in fullscreen in mind. 
This isn't really a big thing to mention, but being thorough will keep out indescrepencies. 
Of course, there probably should be an option to play in windowed view, but it just won't be designed with that in mind.

//Cutscenes

Since this engine is going to be designed around a role-playing game, it must support cutscenes. 
The question does arise however, will the cutscenes be rendered at run time? 
Or will they be prerecorded? 
The problem with it having prerecorded is that it one, takes up a lot of storage, and two, it's not dynamic. 
What I mean in terms of dynamic is that if the player is wearing custom armor, it won't show up in the cutscene, which is truly not immersive. 
There are two solutions (that I can think of) to this problem. 
You can just not have a custom appearance for the character, or you can make all cutscenes at render time. 
Which one will I choose? 
The one with the best promise and fitting the needs of this game engine is most likely run-time cutscenes. 
I chose this because I would prefer going through pain-staking debugging and development at the prize of immersiveness. 
Beware though, this does cause the chance of certain bugs arising.

//Open source

Okay, let's look into the far future of this project and say that this engine comes to a usable manner, to where I finally make my dream game. 
Should it be open source? 
In my opinion, yes, it should be open source. 
I can understand though why certain game studios may want to privatize their work, but I have no interest in captilaizing off of the engine itself. 
Sure, I would want this engine to just be better than other game engines, making it a better reason to play my game, but I simply don't care. 
And, that's to say that this engine actually comes to fruition (haha). 
Plus, this engine is essentially made for a specific game, so this being used for other games may not even be applicable in certain scenerios where the developer isn't seasoned in it's languages.

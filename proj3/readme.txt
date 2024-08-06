Hash Function One: Almost exactly the one from the slides from class. Take the hash of the last letter (initially zero),
multiply by 11 (prime), and add the ascii value of the letter. Then modulus by the mapSize and repeat for each letter
of the word.

Hash Function Two: Go through the word backwards (but it doesn't matter which direction) adding up all the ascii values
then modulus by the mapSize at the end.

Collision Function One: Linear Probing - add i (incrementing) to the hash everytime until there is an open spot.

Collision Function Two: Quadratic Probing - add i^2 to the hash everytime until there is an open spot.



Seussout1.txt
Collisions per key using hash 1: 3.34299, and collision handling 1: 2.09102

Congratulations! Today is out!' 'now! now! have no harm. I could not, on a wonderful view! He has a box? Would you like
green eggs and so slick,

Decided he'd taken enough. And some are some, down at all, May have six feet in the song of them out!' 'now! now!

"Your Majesty, please?" "SILENCE!" the hat. 'these Things are fat. The instant I'd be here in a box. Not in the Turtle!



Quotes from Seussout2.txt
Collisions using hash 2: 4.62929, and collision handling 1: 2184.25

Congratulations! Today is what, or a small for a game that day? should not in Whoville they came.
They run down the Lorax.

But HOW?" Then he came with a mile! "All mine!" Yertle the whole Christmas tree? WHY?"

Yertle the Plain-Belly Sneetches. Off again! On the Lorax, "-please pardon my roads. I would feast on the Turtle King,
lifted and 3/4 percent guaranteed.) KID, YOU'LL GO!



Quotes from Seussout3.txt
Collisions using hash 1: 3.34919, and collision handling 2: 2.29789

Congratulations! Today is not eat them with a small pile of them with sally. we saw ALL the game? Not in the Lorax said
with a house? Would you, in a sour, Grinchy trick!"

And I think such a mule! I'm figgering On Again! In that the things Are everywhere. Here they had something new.
Some are thin. And then! Oh, marvelous me! For he chuckled, and i can still wet and ham.

Then he said, Things are low. And I'm the shade in Whoville, Did NOT! The Grinch hated Christmas!



Quotes from Seussout4.txt
Collisions using hash 2: 4.77782, and collision handling 2: 2182.48

Congratulations! Today is not like these Things really got frightfully mad. I would not, in Whoville will buy." "I will
eat them in the side of town. All the house.

But I quickly Sylvester McMonkey McBean. And he slid down in on another one's back and with a king!

That plain little toy ship, sank it back and puzzling: "How could not know if Santa could see enough.
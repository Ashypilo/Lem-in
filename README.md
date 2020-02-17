<b>Goal:</b>

• The project is to find the quickest way to get n ants across the farm.

• Quickest way means the solution with the least number of lines, respecting the
output format requested below.

• Obviously, there are some basic constraints. To be the first to arrive, ants will need
to take the shortest path (and that isn’t necessarily the simplest). They will also
need to avoid traffic jams as well as walking all over their fellow ants.

• At the beginning of the game, all the ants are in the room ##start. The goal is
to bring them to the room ##end with as few turns as possible. Each room can
only contain one ant at a time. (except at ##start and ##end which can contain
as many ants as necessary.)

• We consider that all the ants are in the room ##start at the beginning of the game.

• At each turn you will only display the ants that moved.

• At each turn you can move each ant only once and through a tube (the room at
the receiving end must be empty).

• You must to display your results on the standard output in the following format:

number_of_ants

the_rooms

the_links

Lx-y Lz-w Lr-o ...

x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
w, o represents the rooms’ names.

<b>The ant farm is defined by the following links:</b>

number_of_ants

##start

1 23 3

2 16 7

#comment

3 16 3

4 16 5

5 9 3

6 1 5

7 4 8

##end

0 9 5

0-4

0-6

1-3

4-3

5-2

3-5

#another comment

4-2

2-1

7-6

7-2

7-4

6-5

#another comment

<b>Run:</b>

make

./lem-in text_ferm.txt

<b>Example:</b>
[0]-[2]-[3]-[1]

3

##start

0 1 0

##end

1 5 0

2 9 0

3 13 0

0-2

2-3

3-1

L1-2

L1-3 L2-2

L1-1 L2-3 L3-2

L2-1 L3-3

L3-1

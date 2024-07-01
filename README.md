# Convert regular expressions into FAs (Finite Automatata)
Automata Program NFA construction


Rule 1: There is an FA that accepts any symbol of Σ  and there is an FA that accepts ε.
If x is in Σ then give an FA that accepts x
Give an FA that accepts ε.

Rule 2: Given FA1 that accepts regular expression r1 and FA2 that accepts regular expression r2 then make FA3 that accepts r1 | r2. 
Add a new start state s and make a ε-transition from this state to the start states of FA1 and FA2. 
Add a new final state f and make a ε-transition to this state from each of the final states of FA1 and FA2.

Rule 3: Given FA1 that accepts regular expression r1 and FA2 that accepts regular expression r2 then make FA3 that accepts r1·r2. 
 * Add a ε-transition from the final state of r1 to the start state of r2. 
 * The start state of FA3 is the start state of FA1 and the final state of FA3 is the final state of FA2.
 
 
Rule 4: Given FA1 that accepts regular expression r then make an FA2 that accepts r*. 
* Add a new start state s and make a ε-transition from this state to the start state of FA1. 
* Make a ε-transition from the final state of F1 to the new start state s. 
* The final states of FA1 are no longer final and s is the final state of FA2. 


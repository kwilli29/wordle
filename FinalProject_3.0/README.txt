Here are the changes I made to make the program work:

1. When constructing a "Word," you have to pass a map that has every single possible five letter word, along with its commonality score. That way, when a Word is made, it can read the map and find its commonality score in O(1) time. The common-words.txt file will only need to be read once

2. I gave each letter two scores: one for information and one for commonality. If there was only one score, then I think you would have to sort and read files a lot more than if there were two. To increase efficiency, I decided to give each word two scores.

3. The letter_map gets cleared and re-initialized every iteration of the while loop. The reason why I did this was to help with the case of duplicate letters in a word. It is easier to tell if there is a duplicate letter if you are only analyzing the word you just entered. The reason this works and doesn't cause any words to come up that shouldn't is because of the structure of the find_words() function. Find_words() deletes and words that can't be used and they aren't re-initialized at every iteration of the while loop. So even though letter_map gets cleared every new guess, bad words are not picked up.

4. I added an option that if a user enters 'q' they can quit the game. They also can enter 'h' to see the help menu again.

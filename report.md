## TDT4230 Final Project: Bioluminescent jellyfish using bloom and HDR
#### *Kasper Midttun Søreide*
<br>

<!--
Final Report
The final report should document the process that went into implementing your project. It should
give an idea of what you did to get to your final product, and what the greatest challenges were on
the way. In at most 5 pages it should describe the following:
Briefly describe your project topic.
How does your implementation achieve its goal?
What are some notable problems you encountered on the way? How did you solve them?
What did you find out about the method in terms of its advantages, its limitations, and how
to use it effectively?
Briefly mention what resources did you used to learn about the technique. No need to include
every link to everything you read, but I should get a general idea of how you figured it out,
even if the answer ends up being pure experimentation!
If working as a team: disclose who did what

-->

### Project Overview


In this project I wanted to implement cool-looking glowing jellyfish, something like in this video: [1]. I wanted to acheive a cool glow effect that have a blurred halo. I googled arond a bit and found a great article describing bloom, a method that make bright regions glow. I ended up doing a simplified version of this, because I got improved visual results by blooming everything and not just the brightest colors. The jellyfish model is code generated and rendered using points. 

### The jellyfish model
Initially when I started this project, I was recommended to use 

### References

[1]: The secret superpowers of jellyfish, Quartz (https://www.youtube.com/watch?v=-irjnOIjNcs) <br>
[2]: Bloom, LearnOpenGL (https://learnopengl.com/Advanced-Lighting/Bloom)
